# Guia de Utilização - Raspberry Pi 5 do Robô

Tutorial de como preparar o ambiente, estabelecer a conexão de rede (via Wi-Fi Direto ou Tailscale), executar a visão computacional do seguidor de linha e realizar a integração da Raspberry Pi 5 com o Arduino.

### Preparação do Ambiente e Arquivos

Para começar, você deve organizar os arquivos de trabalho no seu computador extraindo do repositório as seguintes pastas:
* **`Prog_rasp`**: Contém os scripts e arquivos da Raspberry Pi 5 (incluindo o servidor Flask e o código de visão).
* **`Prog_arduino`**: Contém os arquivos responsáveis pelo controle dos motores.

**Ponto Importante:** O arquivo `envia.bat` é o responsável por enviar as atualizações de código do seu PC para a placa.

### Alimentação de Energia

Caso você vá utilizar a Raspberry apenas para **testar a programação** e o robô não for realizar movimentos gigantescos ou rotinas pesadas de motor, recomenda-se:
* Utilizar a alimentação através de um **carregador USB-C** direto na tomada.
* Isso permite que você deixe a Raspberry ligada por horas de desenvolvimento contínuo sem precisar se preocupar em drenar ou trocar as baterias do robô.

---

### Métodos de Conexão de Rede

A Raspberry Pi 5 foi configurada para atuar como um roteador de rede local, mas também possui suporte para acesso remoto utilizando o Tailscale.

#### MÉTODO 1: Via Wi-Fi Direto da Raspberry (Rede Local)
Se você estiver perto do robô, pode se conectar diretamente à rede sem fio gerada pela própria placa.
1. No seu computador, abra a lista de redes Wi-Fi disponíveis.
2. Conecte-se na rede do robô:
   * **Nome da Rede (SSID):** `new`
   * **Senha padrão:** `senha123`
3. **Descobrindo o IP:** Após conectar, acesse o painel de controle/configurações de rede do seu PC, vá nos detalhes da conexão e pegue o IP listado como "Gateway Padrão" ou "Roteador". Este será o IP da sua Raspberry.

#### MÉTODO 2: Via Tailscale (Para acessar de qualquer distância/rede)
Este método permite que você acesse o robô de qualquer lugar do mundo, mesmo em redes diferentes.
1. Baixe o aplicativo do Tailscale na Raspberry e no PC que for usar.
2. Faça o login em ambas as máquinas para colocá-las na mesma malha de rede.
3. O Tailscale irá gerar um **IP Novo** exclusivo para a Raspberry. Você usará este IP para se conectar remotamente sem precisar estar conectado no Wi-Fi `new`.

---

### Acesso Remoto via SSH

Independentemente do método de rede escolhido, o acesso ao terminal é feito da mesma forma:

1. Aperte as teclas `Win + R`, digite `cmd` e dê Enter para abrir o terminal do seu computador.
2. Digite o seguinte comando para iniciar a conexão (Substitua `[IP_DA_RASP]` pelo IP que você pegou na rede Wi-Fi ou no Tailscale):

        ssh new@[IP_DA_RASP]

3. Quando solicitado, digite a senha padrão da Raspberry: `senha123`

---

### Executando a Visão Computacional (LINHA.py) e Dashboard

Para iniciar os sistemas de visão do robô, acesse o diretório correto e rode o script.

1. Entre na pasta onde estão as programações digitando:

        cd Prog_rasp/

2. Execute o código principal de visão do robô manualmente:

        python3 LINHA.py

**Sobre o Sistema de Visão (`LINHA.py`):**
* O código possui a identificação das cores verdes (interseções) e o mapeamento dos contornos da linha preta.
* **Contorno Fatiado:** A identificação dos contornos da linha utiliza uma estratégia de "fatiamento por pontos". Isso significa que o programa analisa trechos da linha mais perto e mais longe da câmera separadamente, permitindo que o robô faça maiores correções ou menores correções com precisão e suavidade nas curvas.

**Acessando as Câmeras (Servidor Flask / Dashboard):**
O servidor Flask nativo da Rasp 5 foi refeito com um layout muito melhor. Assim que o script `LINHA.py` estiver rodando, abra o navegador do seu computador e digite:

👉 **`http://[IP_DA_RASP]:5000`**

Você terá acesso à visualização do seguidor de linha diretamente pelo navegador do PC.

---

### Integração Rasp + Arduino

O processamento pesado fica na Raspberry Pi, mas o controle de hardware é feito pelo Arduino. No repositório, existe a pasta **`Prog_arduino`**, contendo duas programações:
* Uma para **testar os motores** isoladamente.
* Outra (Principal) para a **comunicação Rasp -> Arduino**, responsável por receber os cálculos de direção e acionar as velocidades dos motores.

**Como enviar código pro Arduino:**
A comunicação física é feita pelo próprio cabo USB conectado do Arduino na Raspberry Pi. Você não precisa conectar o Arduino no seu PC; **a programação do Arduino é compilada e enviada diretamente de dentro do terminal SSH da Raspberry Pi**.

---

### Como Atualizar a Programação da Rasp

Para não precisar programar diretamente no terminal do robô, você edita no seu PC e envia os arquivos via script.

1. **Pare a execução atual no robô:** No terminal SSH onde o script está rodando, pressione `Ctrl + C`.
2. **Edite e Salve o Código:** Faça as modificações na sua pasta local `Prog_rasp` pelo editor (como o VS Code) e salve SEMPRE com `Ctrl + S`.
3. **Execute o arquivo de envio:** Dentro da pasta raiz do seu PC, dê dois cliques no arquivo `envia.bat`.
4. **Autenticação:** Quando o terminal pedir a senha da Raspberry Pi, digite `senha123` e pressione Enter.
5. **Rode novamente:** Volte ao seu terminal SSH do robô e execute o comando para iniciar a nova versão:

        python3 LINHA.py
