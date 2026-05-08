```cpp
// Definições de Pinos da Ponte H L298N
// Lado Esquerdo (Motores 1 e 2 em paralelo)
#define ENA 5   // Controle de Velocidade PWM Esquerda
#define IN1 6   // Sentido
#define IN2 7   // Sentido

// Lado Direito (Motores 3 e 4 em paralelo)
#define IN3 8   // Sentido
#define IN4 9   // Sentido
#define ENB 10  // Controle de Velocidade PWM Direita

// Variável para você testar a força (Escolha entre 0 e 255)
// Dica: Valores abaixo de 80 podem não ter força para quebrar a inércia do motor
int velocidade_teste = 150; 

void setup() {
  // Inicia a comunicação Serial para os logs
  Serial.begin(115200);
  Serial.println("=== INICIANDO TESTE DE BANCADA ===");
  
  // Configura os pinos como saída
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  Serial.println("Pinos configurados. Aguardando 3 segundos...");
  pararMotores();
  delay(3000); // Dá um tempo de 3 segundos para você colocar o robô no chão
}

void loop() {
  // ==========================================================
  // SEQUÊNCIA DE TESTES
  // Observe as rodas do robô e veja se o movimento corresponde
  // ==========================================================

  // 1. Testa ir para FRENTE
  Serial.println("Acao: FRENTE");
  moverFrente(velocidade_teste, velocidade_teste);
  delay(2000); // Anda por 2 segundos
  Serial.println("Acao: PARAR");
  pararMotores();
  delay(1000); // Pausa 1 segundo

  // 2. Testa ir para TRÁS
  Serial.println("Acao: TRAS");
  moverTras(velocidade_teste, velocidade_teste);
  delay(2000); // Anda por 2 segundos
  Serial.println("Acao: PARAR");
  pararMotores();
  delay(1000); // Pausa 1 segundo

  // 3. Testa girar no próprio eixo para a ESQUERDA
  Serial.println("Acao: GIRAR ESQUERDA");
  girarEsquerda(velocidade_teste);
  delay(2000); // Gira por 2 segundos
  Serial.println("Acao: PARAR");
  pararMotores();
  delay(1000); // Pausa 1 segundo

  // 4. Testa girar no próprio eixo para a DIREITA
  Serial.println("Acao: GIRAR DIREITA");
  girarDireita(velocidade_teste);
  delay(2000); // Gira por 2 segundos
  Serial.println("Acao: PARAR");
  pararMotores();
  
  // Espera 5 segundos antes de repetir a rotina toda
  Serial.println("Aguardando 5 segundos para reiniciar o ciclo...");
  Serial.println("-----------------------------------");
  delay(5000); 
}

// ================= FUNÇÕES DE MOVIMENTAÇÃO =================

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

void moverTras(int velEsq, int velDir) {
  // Motores da Esquerda giram pra trás
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velEsq);
  
  // Motores da Direita giram pra trás
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
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
  // Corta o sinal de direção e a velocidade
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

