// Pinos do Encoder
#define ENCODER_A_ESQUERDA 2  // Pino de interrupção
#define ENCODER_B_ESQUERDA 4  // Pino comum

#define ENCODER_A_DIREITA 3  // Pino de interrupção
#define ENCODER_B_DIREITA 22  // Pino comum

// Pinos do Motor (usando Ponte H)
#define PWM_MOTOR_DIREITA 5
#define PWM_MOTOR_ESQUERDA 8

//// ENABLE MOTORES ////
#define ENABLE_MOTOR_DIREITA A0
#define ENABLE_MOTOR_ESQUERDA A1

//// PINOS DIREÇÕES MOTOR DIREITA //// 
#define DIRECAO_HORARIO_DIREITA 6
#define DIRECAO_ANTIHORARIO_DIREITA 7

//// PINOS DEIREÇÕES MOTOR ESQUERDA ////
#define DIRECAO_HORAIO_ESQUERDA 12
#define DIRECAO_ANTIHORARIO_ESQUERDA 11

volatile long encoderPulses_Esquerda = 0;  // Contagem dos pulsos do encoder
volatile long encoderPulses_Direita = 0;
int targetPulses = 1100;          // Quantidade de pulsos alvo (exemplo)

// Interrupção para contar os pulsos
void encoderISR_ESQUERDA() {
    if (digitalRead(ENCODER_A_ESQUERDA) == digitalRead(ENCODER_B_ESQUERDA)) {
        encoderPulses_Esquerda++;  // Incrementa se girando em um sentido
    } else {
        encoderPulses_Direita--;  // Decrementa se girando no outro sentido
    }
}

void encoderISR_DIREITA() {
    if (digitalRead(ENCODER_A_DIREITA) == digitalRead(ENCODER_B_DIREITA)) {
        encoderPulses_Direita++;  // Incrementa se girando em um sentido
    } else {
        encoderPulses_Direita--;  // Decrementa se girando no outro sentido
    }
}
/*
// Função para mover o motor até um número específico de pulsos
void moveToPosition(int target) {
    encoderPulses = 0;  // Zera a contagem
    
    if (target > 0) {
        digitalWrite(MOTOR_IN1, HIGH);
        digitalWrite(MOTOR_IN2, LOW);
    } else {
        digitalWrite(MOTOR_IN1, LOW);
        digitalWrite(MOTOR_IN2, HIGH);
        target = -target;  // Garante que a comparação seja correta
    }

    while (abs(encoderPulses) < target) {
        // Aguarda atingir o alvo
    }

    // Para o motor ao atingir a posição desejada
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
}
*/

void setup() {
  pinMode(ENCODER_A_ESQUERDA, INPUT_PULLUP);
  pinMode(ENCODER_B_ESQUERDA, INPUT_PULLUP);

  pinMode(ENCODER_A_DIREITA, INPUT_PULLUP);
  pinMode(ENCODER_B_DIREITA, INPUT_PULLUP);

  pinMode(PWM_MOTOR_DIREITA, OUTPUT);
  pinMode(PWM_MOTOR_ESQUERDA, OUTPUT);

  pinMode(ENABLE_MOTOR_DIREITA, OUTPUT);
  pinMode(ENABLE_MOTOR_ESQUERDA, OUTPUT);

  pinMode(DIRECAO_HORARIO_DIREITA, OUTPUT);
  pinMode(DIRECAO_ANTIHORARIO_DIREITA, OUTPUT);

  pinMode(DIRECAO_HORAIO_ESQUERDA, OUTPUT);
  pinMode(DIRECAO_ANTIHORARIO_ESQUERDA, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(ENCODER_A_ESQUERDA), encoderISR_ESQUERDA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A_DIREITA), encoderISR_DIREITA, CHANGE);

  Serial.begin(9600);
}

void loop() {
  
  
  digitalWrite(ENABLE_MOTOR_ESQUERDA, HIGH);
  digitalWrite(ENABLE_MOTOR_DIREITA, HIGH);

  digitalWrite(DIRECAO_HORAIO_ESQUERDA, HIGH);
  digitalWrite(DIRECAO_ANTIHORARIO_ESQUERDA, LOW);
  analogWrite(PWM_MOTOR_ESQUERDA, 255);


  digitalWrite(DIRECAO_HORARIO_DIREITA, HIGH);
  digitalWrite(DIRECAO_ANTIHORARIO_DIREITA, LOW);
  analogWrite(PWM_MOTOR_DIREITA, 255);

  Serial.print("ENCODER ESQUERDA:  ");
  Serial.println(encoderPulses_Esquerda); 
  Serial.print("ENCODER DIREITA:  ") ;
  Serial.println(encoderPulses_Direita);  
 

}