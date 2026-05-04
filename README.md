<div align="center">
  <img src="https://github.com/user-attachments/assets/a547579f-f725-4e2e-8bf1-caec1e7137d9" style="width:60%;" alt="Logo CleanEngeneer"/>
</div>

<br/>
<br/>

<div align="center">
  <a href="[LINK_GITHUB_EMANUEL]">
    <img src="https://img.shields.io/badge/Mecanica-Emanuel-blue" alt="Emanuel">
  </a>
  
  <a href="[LINK_GITHUB_VYCTOR]">
    <img src="https://img.shields.io/badge/Eletronica-Victor-blue" alt="Vyctor">
  </a>

  <a href="[LINK_GITHUB_BERNARDO]">
    <img src="https://img.shields.io/badge/Dev-Bernardo-blue" alt="Bernardo">
  </a>

  <a href="[LINK_GITHUB_VITOR]">
    <img src="https://img.shields.io/badge/Mentor-Vitor_Zamir-purple" alt="Vitor Zamir">
  </a>
  
  <a href="[LINK_YOUTUBE_OU_INSTAGRAM]">
    <img src="https://img.shields.io/badge/YouTube-NewAtom-red?logo=youtube" alt="CleanEngeneer YouTube Channel">
  </a>
</div>

<br/>
<br/>

<p align="center">
  Este é o repositório oficial da equipe brasileira <b>CleanEngeneer</b>. Aqui documentamos o desenvolvimento do nosso robô, projetado para competir na modalidade de Resgate (Rescue Line / OBR).
</p>

## Sobre a Competição
<p align="center"><i>
  "A área de desastre é muito perigosa para os humanos alcançarem as vítimas. A sua equipe recebeu uma tarefa desafiadora. O robô deve ser capaz de realizar uma missão de resgate de forma totalmente autônoma, sem assistência humana. O robô deve ser durável e inteligente o suficiente para navegar por terrenos traiçoeiros com colinas, desníveis e destroços sem ficar preso. Ao alcançar as vítimas, ele deve transportá-las cuidadosamente para a área de evacuação..."
</i></p>

<div align="justify">
  <img src="https://private-user-images.githubusercontent.com/100859276/363510327-a0c5800d-fcd0-47f1-990c-3d6951691d1c.png?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3Nzc0OTE1NDksIm5iZiI6MTc3NzQ5MTI0OSwicGF0aCI6Ii8xMDA4NTkyNzYvMzYzNTEwMzI3LWEwYzU4MDBkLWZjZDAtNDdmMS05OTBjLTNkNjk1MTY5MWQxYy5wbmc_WC1BbXotQWxnb3JpdGhtPUFXUzQtSE1BQy1TSEEyNTYmWC1BbXotQ3JlZGVudGlhbD1BS0lBVkNPRFlMU0E1M1BRSzRaQSUyRjIwMjYwNDI5JTJGdXMtZWFzdC0xJTJGczMlMkZhd3M0X3JlcXVlc3QmWC1BbXotRGF0ZT0yMDI2MDQyOVQxOTM0MDlaJlgtQW16LUV4cGlyZXM9MzAwJlgtQW16LVNpZ25hdHVyZT1jOGQ2NzUxMDgwMzZkZjMxMDc1MzgxNTU2YTBkNGQzOWNhNzU2ZGZiMjYzMzg5ZWI5MGE3NjE4NTE3ZGJmNDViJlgtQW16LVNpZ25lZEhlYWRlcnM9aG9zdCZyZXNwb25zZS1jb250ZW50LXR5cGU9aW1hZ2UlMkZwbmcifQ.UwHvrhlFCXPWQa_A-zszZy_3U309LtPTPypqP8U07OA" style="width:70%;"/>
</div>

<p align="justify">
  O objetivo da competição é desenvolver um robô autônomo capaz de superar obstáculos como redutores de velocidade, rampas, encruzilhadas (com marcadores verdes) e falhas na linha preta. Ao final do trajeto, o robô precisa identificar a entrada da zona de resgate (linha prata), varrer a área, identificar vítimas vivas e mortas e posicioná-las com segurança na área de evacuação, finalizando a missão de forma autônoma.
</p>

## Sobre o Projeto

<img src="https://github.com/user-attachments/assets/b2ecc076-d6d6-4bd7-9651-6faeb64b11ed" aling="left" height="190"/>
<br/>

<p align="justify">
  Para cumprir todas as tarefas com precisão na <b>OBR</b> e na <b>RoboCup Junior Rescue Line</b>, desenvolvemos a nossa plataforma utilizando uma 
  arquitetura híbrida de hardware: combinamos a robustez e o tempo de resposta em baixo nível de um Arduino com o
  alto poder de processamento de IA e Visão Computacional de uma Raspberry Pi.
</p>

<p align="justify">
  Neste repositório, detalhamos o nosso sistema de seguimento de linha com PID, a integração serial e a nossa árvore de decisão baseada em processamento de imagem puro e redes neurais.
</p>

<br clear="both"/>
<img src="https://github.com/user-attachments/assets/86ce0a5e-0f3c-4e83-a090-5be3ccd89181" aling="right" height="190" />
<br/>

### Componentes Principais

<p align="justify">
  Além do chassi personalizado e rodas adaptadas para alta aderência, utilizamos os seguintes componentes eletrônicos para garantir a máxima performance:
</p>

- 1x Arduino (Controle de Motores, Sensores e Malha PID)
- 1x Raspberry Pi (Processamento de Visão e IA)
- 1x Módulo Giroscópio MPU6050 (Via I2C)
- 1x Câmera PiCamera2 / USB (Leitura de Linha e Verdes)
- Motores DC com caixa de redução
- Ponte H / Driver de Motor
- Step-Up Conversor de Tensão
- Sensores de Distância (Ultrassônicos ou ToF)
- [COLOQUE AQUI: Bateria LiPo ou de Íon de Lítio utilizada]

## Software e Lógica

### Controle de Baixo Nível (Arduino)
<p align="justify">
  O cérebro de movimentação e acionamento físico roda no Arduino utilizando C/C++. Desenvolvemos um algoritmo de <b>PID Dinâmico</b>. O robô avalia a variável de erro recebida da Raspberry: em retas, ele aplica a velocidade máxima. Ao detectar um erro alto (curvas), ele reduz proporcionalmente a base de velocidade, realizando curvas precisas sem que a inércia jogue o robô para fora da pista. O Arduino escuta continuamente via porta Serial as coordenadas e comandos enviados pela Raspberry.
</p>

### Visão Computacional (OpenCV na Raspberry)
<p align="justify">
  A câmera é responsável por guiar o robô em encruzilhadas e gaps. Usamos filtros HSV com <i>Gaussian Blur</i> e operações morfológicas para isolar a linha preta e os marcadores verdes. Uma árvore de decisão geométrica avalia a posição relativa entre a área verde e o centro de massa da linha para enviar comandos (ex: <i>"X: 160"</i> ou <i>"Curva 90 Esquerda"</i>) para o Arduino executar as manobras necessárias.
</p>

### Inteligência Artificial (YOLO)
<p align="justify">
  Ao detectar a fita prata de entrada do resgate, a Raspberry altera o modo de operação para buscar vítimas. Utilizando modelos de visão e redes neurais (como YOLO), o sistema detecta vítimas vivas e mortas, calcula a área em pixels e a posição relativa no frame, enviando as coordenadas exatas para o Arduino realizar a aproximação final e acionar a garra de resgate.
</p>

## Sobre a Equipe CleanEngeneer

<p align="justify">
  A equipe <b>CleanEngeneer</b> é formada por estudantes apaixonados por robótica, focados em desenvolver soluções eficientes e competitivas. Dividimos as nossas funções para otimizar o desenvolvimento de um robô de alto nível:
</p>

- **Emanuel** - <i>Mecânica e Design:</i> Responsável pela modelagem 3D, encaixes, estrutura física e tração do robô.
- **Victor** - <i>Eletrônica e Hardware:</i> Especialista na integração dos circuitos, gerenciamento de energia, cabeamento e comunicação entre placas.
- **Bernardo** - <i>Programação e Visão:</i> Desenvolvedor das lógicas de controle, processamento de imagem em Python, integração do OpenCV e algoritmos de navegação.
- **Vitor Zamir** - <i>Mentor:</i> Estudante de Ciência da Computação na UniFBV, Embaixador FIRST e competidor da modalidade de Robótica Móvel. Auxilia a equipe com arquitetura de software de alta performance e estratégia de prova.

### Conquistas
- [Ex: 1 Lugar Regional OBR 202X]
- [Ex: Prêmio de Melhor Design de Robô - Estadual OBR 202X]
- [Adicione mais conquistas aqui]

## Links Úteis

- [COLOQUE AQUI: Link para o vídeo do robô na pista]
- [COLOQUE AQUI: Link para fotos e diagramas do projeto]

## Licença
Este projeto está licenciado sob a licença [COLOQUE A LICENÇA AQUI, ex: MIT ou GNU GPLv3] - veja o arquivo LICENSE para detalhes.

---
*A equipe CleanEngeneer incentiva o compartilhamento de conhecimento. Sinta-se à vontade para explorar o nosso código e entender como implementamos a nossa arquitetura de visão e controle híbrido!*
