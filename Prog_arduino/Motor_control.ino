// Definições de Pinos da Ponte H L298N
// Lado Esquerdo (Motores 1 e 2 em paralelo)
#define ENA 5   // Controle de Velocidade PWM
#define IN1 6   // Sentido
#define IN2 7   // Sentido

// Lado Direito (Motores 3 e 4 em paralelo)
#define IN3 8   // Sentido
#define IN4 9   // Sentido
#define ENB 10  // Controle de Velocidade PWM

// Variáveis da câmera
int centro_camera = 160; // Centro geométrico em X (320/2)

// Constantes de Velocidade e Controle
int velocidade_base = 120; // Ajuste entre 0 e 255
float kp = 0.8;            // Constante Proporcional (Ajuste na pista)

void setup() {
  Serial.begin(115200); // MESMA VELOCIDADE DO PYTHON
  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  pararMotores();
}

void loop() {
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');
    comando.trim(); // Remove espaços em branco
    
    if (comando.startsWith("X:")) {
      // MODO SEGUIR LINHA
      int posicao_x = comando.substring(2).toInt();
      seguirLinha(posicao_x);
    } 
    else if (comando == "E") {
      // CURVA 90 ESQUERDA
      girarEsquerda(200); // Velocidade do giro
      delay(500);         // Tempo do giro (Ajuste conforme o peso do robô)
      pararMotores();
    }
    else if (comando == "D") {
      // CURVA 90 DIREITA
      girarDireita(200);
      delay(500);
      pararMotores();
    }
    else if (comando == "U") {
      // RETORNO 180 GRAUS (Beco)
      girarDireita(200);
      delay(1000); // Dobro do tempo do giro de 90
      pararMotores();
    }
  }
}

// ================= LÓGICA DE MOVIMENTAÇÃO =================

void seguirLinha(int x) {
  // Controle Proporcional simples
  int erro = x - centro_camera;
  int ajuste = erro * kp; 
  
  int vel_esq = velocidade_base + ajuste;
  int vel_dir = velocidade_base - ajuste;
  
  // Limita os valores de PWM entre 0 e 255
  vel_esq = constrain(vel_esq, 0, 255);
  vel_dir = constrain(vel_dir, 0, 255);
  
  moverFrente(vel_esq, vel_dir);
}

void moverFrente(int velEsq, int velDir) {
  // Motores da Esquerda giram pra frente
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velEsq);
  
  // Motores da Direita giram pra frente
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, velDir);
}

void girarEsquerda(int vel) {
  // Motores Esquerda pra trás, Direita pra frente
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, vel);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, vel);
}

void girarDireita(int vel) {
  // Motores Esquerda pra frente, Direita pra trás
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, vel);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, vel);
}

void pararMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}
