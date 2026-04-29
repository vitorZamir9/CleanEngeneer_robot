import time
import cv2
import os
import numpy as np
import logging
from picamera2 import Picamera2

# ============ CONFIGURAÇÃO BÁSICA ============
os.environ['DISPLAY'] = ':0'
cv2.setNumThreads(0)
os.environ["LIBCAMERA_LOG_LEVELS"] = "1"
Picamera2.set_logging(logging.ERROR)

# ============ SISTEMA DE GRAVAÇÃO (DVR) ============
DEBUG_DIR = "debug_videos"
os.makedirs(DEBUG_DIR, exist_ok=True)
gravador_atual = None  

# ============ CONSTANTES DA LINHA ============
W, H = 320, 240
CENTRO_X = W // 2
BASE_Y = H

# Calibre essas cores conforme a iluminação da sala da OBR
GREEN_MIN = np.array([35, 40, 40])
GREEN_MAX = np.array([90, 255, 255])
BLACK_MAX = np.array([180, 255, 60]) 

# ============ VARIÁVEIS DE CONTROLE ============
picam2 = None  

def iniciar_imx500():
    global picam2, gravador_atual
    if picam2 is None:
        print("\n[*] LIGANDO CÂMERA (Modo Teste de Visão)...")
        picam2 = Picamera2()
        config = picam2.create_video_configuration(main={"format": "BGR888", "size": (W, H)})
        picam2.configure(config)
        picam2.start()
        
        nome_video = time.strftime("%Y%m%d_%H%M%S")
        caminho = f"{DEBUG_DIR}/teste_linha_{nome_video}.avi"
        fourcc = cv2.VideoWriter_fourcc(*'XVID')
        gravador_atual = cv2.VideoWriter(caminho, fourcc, 20.0, (W, H))
        time.sleep(1)

def parar_imx500():
    global picam2, gravador_atual
    if picam2 is not None:
        print("\n[*] DESLIGANDO CÂMERA e salvando vídeo...")
        picam2.stop()
        picam2.close()
        picam2 = None
        if gravador_atual:
            gravador_atual.release()
            gravador_atual = None

# ============ LÓGICA VETORIAL DE LINHA ============
def processar_linha_vetorial(frame):
    hud = frame.copy()
    
    frame_suave = cv2.GaussianBlur(frame, (5, 5), 0)
    hsv = cv2.cvtColor(frame_suave, cv2.COLOR_BGR2HSV)
    
    mask_black = cv2.inRange(hsv, np.array([0, 0, 0]), BLACK_MAX)
    mask_green = cv2.inRange(hsv, GREEN_MIN, GREEN_MAX)

    kernel_clean = np.ones((5, 5), np.uint8)
    mask_black = cv2.morphologyEx(mask_black, cv2.MORPH_OPEN, kernel_clean)

    kernel_dilate = np.ones((15, 15), np.uint8)
    mask_black_dilated = cv2.dilate(mask_black, kernel_dilate, iterations=1)

    alvo_x, alvo_y = CENTRO_X, BASE_Y // 2

    # Encontra a linha preta
    contours_blk, _ = cv2.findContours(mask_black, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    if contours_blk:
        maior_linha = max(contours_blk, key=cv2.contourArea)
        if cv2.contourArea(maior_linha) > 1500: 
            cv2.drawContours(hud, [maior_linha], -1, (255, 0, 0), 2)
            M = cv2.moments(maior_linha)
            if M["m00"] > 0:
                alvo_x = int(M["m10"] / M["m00"])
                alvo_y = int(M["m01"] / M["m00"])

    # Encontra os quadrados verdes
    contours_grn, _ = cv2.findContours(mask_green, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    greens_brutos = []
    
    for cnt in contours_grn:
        if cv2.contourArea(cnt) > 200:  
            x, y, w, h = cv2.boundingRect(cnt)
            if 0.5 <= float(w)/h <= 2.0:
                mask_this_green = np.zeros_like(mask_green)
                cv2.drawContours(mask_this_green, [cnt], -1, 255, -1)
                # Verifica se o verde está tocando na linha preta
                if cv2.countNonZero(cv2.bitwise_and(mask_black_dilated, mask_this_green)) > 0:
                    greens_brutos.append((x, y, w, h))
                    cv2.rectangle(hud, (x, y), (x+w, y+h), (0, 255, 0), 2)

    greens_validos = []
    if greens_brutos:
        greens_brutos = sorted(greens_brutos, key=lambda g: g[1], reverse=True)
        y_mais_proximo = greens_brutos[0][1]
        for g in greens_brutos:
            if abs(g[1] - y_mais_proximo) < 40:
                greens_validos.append(g)
        greens_validos = sorted(greens_validos, key=lambda g: g[0])

    # ==========================================================
    # ÁRVORE DE DECISÃO GEOMÉTRICA (VERDE VS LINHA)
    # ==========================================================
    if len(greens_validos) >= 1:
        cy_verde_media = sum([g[1] + (g[3] // 2) for g in greens_validos]) / len(greens_validos)
        verde_depois = cy_verde_media < (alvo_y - 10)
        
        if verde_depois:
            comando = "VERDE DEPOIS DA LINHA (Ignorar)"
        else:
            if len(greens_validos) >= 2:
                comando = "VERDE DUPLO (Retorno/Beco)"
            else:
                gx, gy, gw, gh = greens_validos[0]
                cx_verde = gx + (gw // 2)
                
                if cx_verde < alvo_x: 
                    comando = "VERDE ESQUERDA (Curva 90º)"
                else: 
                    comando = "VERDE DIREITA (Curva 90º)"
    else:
        # Se não tem verde, apenas mostra a posição X da linha preta
        comando = f"LINHA NO CENTRO X: {alvo_x}" 
    # ==========================================================

    cv2.line(hud, (CENTRO_X, BASE_Y), (alvo_x, alvo_y), (0, 0, 255), 2)
    cv2.putText(hud, f"VISAO: {comando}", (10, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

    return comando, hud

# ============ LOOP PRINCIPAL ============
print("\n[+] SCRIPT DE TESTE DE VISÃO INICIADO [+]")
print("[+] Pressione Ctrl+C para sair.\n")
iniciar_imx500()

try:
    while True:
        start_time = time.time()
        
        # 1. Captura a Imagem
        frame = picam2.capture_array("main")
        
        # Inverte a imagem se a câmera estiver de ponta-cabeça no robô (Mude para 0 ou 1 se precisar)
        frame = cv2.flip(frame, -1) 
        
        # 2. Processa a Visão
        comando, hud_frame = processar_linha_vetorial(frame)
        
        # 3. Salva o Vídeo (DVR)
        if gravador_atual:
            gravador_atual.write(hud_frame)
        
        # 4. PRINT NA TELA DO QUE A CÂMERA ESTÁ VENDO
        fps = 1.0 / (time.time() - start_time)
        print(f"[CÂMERA] Decisão: {comando:<35} | FPS: {fps:.1f}")

except KeyboardInterrupt:
    print("\n[*] Encerrando sistema...")
finally:
    parar_imx500()
