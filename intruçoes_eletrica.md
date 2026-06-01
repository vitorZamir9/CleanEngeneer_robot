# Guia de Montagem e Conexões Elétricas - Rasp 5 + Arduino

Este documento detalha as conexões físicas e elétricas necessárias para a integração entre a Raspberry Pi 5 (Cérebro/Visão) e o Arduino (Tração/Motores) no chassi do robô.

---

## 1. Módulo Raspberry Pi 5 (Visão e Processamento)

A Raspberry Pi deve estar com a elétrica independente e totalmente funcional antes de se conectar ao Arduino.

### Fixação no Chassi
* **Isolamento:** A placa deve ser fixada firmemente no chassi utilizando espaçadores (standoffs) de nylon ou plástico. **Nunca** parafuse a placa diretamente sobre partes metálicas do chassi para evitar curtos-circuitos que podem queimar a Raspberry.
* **Acessibilidade:** Posicione a placa de modo que as portas USB, a porta USB-C (energia) e o cabo da câmera fiquem livres para manutenção rápida durante as competições ou testes.

### Alimentação Elétrica (Raspberry)
* A Raspberry Pi 5 precisa de uma fonte de energia estável de **5V e pelo menos 3A** (idealmente 5A). 
* Utilize um Power Bank de alta capacidade via USB-C ou um regulador de tensão (UBEC step-down) ligado à bateria principal.
* **Aviso:** Nunca alimente a Raspberry na mesma linha direta dos motores sem um bom regulador, pois a queda de tensão quando os motores aceleram fará a Raspberry reiniciar sozinha.

### Posicionamento e Instalação da Câmera
A câmera é o principal sensor do robô e sua posição dita o sucesso da programação.
* **Onde colocar:** Fixe a câmera na parte frontal extrema do robô, centralizada, com uma inclinação média voltada para o chão (pista).
* **Por que essa inclinação exata?** O seu código (`LINHA.py`) utiliza a lógica de **contorno fatiado por pontos**. Ele precisa ver a linha em diferentes distâncias. A inclinação deve permitir que a parte inferior da imagem mostre o que está imediatamente colado no robô (para correções rápidas) e a parte superior da imagem mostre a linha mais longe (para prever curvas antecipadamente). 
* **Conexão:** Se for câmera USB, conecte em uma das portas azuis (USB 3.0) da Rasp. Se for câmera nativa (Cabo Flat CSI), certifique-se de que os contatos metálicos do flat estão virados para o lado correto no conector da placa e trave bem.

---

## 2. Módulo Arduino (Controle de Motores)

O Arduino é responsável exclusivamente por receber as ordens de velocidade da Rasp e repassar para a Ponte H (Driver de Motor).

### O que já deve estar funcionando:
* Os motores DC devem estar montados nas rodas e fixados no chassi.
* Os fios dos motores (Direito e Esquerdo) devem estar conectados nas saídas do Driver de Motor (ex: L298N, TB6612, etc).
* Os pinos de controle do Driver (IN1, IN2, IN3, IN4 e PWM) devem estar devidamente conectados nas portas digitais do Arduino (conforme configurado na sua pasta `Prog_arduino`).

### Alimentação do Sistema de Tração
* **Bateria dos Motores:** A bateria principal do robô (ex: LiPo 2S ou 3S) deve ser conectada **diretamente na entrada de potência (VIN/VCC) do Driver de Motor**. O Arduino não tem força para girar motores sozinho.
* **Regra de Ouro (GND Comum):** O pino GND (Terra) da bateria, o GND do Driver de Motor e o GND do Arduino **precisam estar conectados juntos**. Se o GND não for comum, os sinais do Arduino não farão os motores girarem.

---

## 3. Integração e Comunicação (Rasp 🡘 Arduino)

Com a Raspberry ligada vendo a linha e o Arduino ligado pronto para girar os motores, é hora de conectar os dois.

* **O Cabo de Comunicação:** Utilize o cabo USB original do Arduino. Conecte a ponta menor no Arduino e a ponta USB tipo A em qualquer porta da Raspberry Pi 5.
* **O que esse cabo faz?**
  1. **Energia Lógica:** A Raspberry vai fornecer 5V através do cabo USB para manter a placa do Arduino ligada (Nota: isso não alimenta os motores, apenas a lógica do Arduino).
  2. **Comunicação Serial:** O cabo cria a ponte de dados. A programação da Rasp lê a câmera, calcula para qual lado o robô deve ir e envia os números de velocidade instantaneamente via USB Serial para o Arduino executar.

---

## ✅ Checklist Final de Pista

Antes de botar o robô no chão, revise:
- [ ] A Raspberry está isolada do metal do chassi?
- [ ] A câmera está inclinada corretamente para pegar a linha de perto e de longe?
- [ ] O Arduino está conectado via USB na Raspberry?
- [ ] A bateria dos motores está com carga e ligada no Driver de Motor?
- [ ] O GND do Driver está ligado no GND do Arduino?

Tudo certo? Pode rodar a comunicação e testar o tracking da linha!
