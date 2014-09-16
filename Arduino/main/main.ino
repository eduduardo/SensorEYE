/*
 *  Sensoreye Program
 * 
 *  Equipamento para deficientes visuais criado com um chapéu/boné usando um sensor ultrassônico 
 *  preso junto há também um fone ou pulseira que irá emitir sons ou vibrações de acordo com a 
 *  distância de objetos/obstáculos
 *
 *  Autores:
 *  Eduardo Augusto Ramos
 *  Filipe Dias Gianotto
 *  Felipe Pereira Jorge
 *  
 *  ETEC Pedro Ferreira Alves @ 1 EMIA 2014
 */

#include <Ultrasonic.h>

// Pinos do sensor ultrasonico
const int pinoEco 1 // sensor echo Pin
const int pinoDisparador 2 // sensor trigger Pin
const int pinoLed 4 // led usada para os testes iniciais
const int pinoVibracall 5 // vibracall

// const float velocidadeSom = 346.3 // velocidade do som em (m/s) a +25 °C


void setup() {
  Serial.begin(9600); // inicia o serial
  pinMode(pinoEco, INPUT);
  pinMode(pinoDisparador, OUTPUT);
  pinMode(pinoLed, OUTPUT);
  
  // dois beeps/vibris iniciais para teste
  for (int i = 0; i < 2; i++){
     vibracall(200);
     delay(2); 
  }
  
  // mensagem inicial do serial
  Serial.println("========================");
  Serial.println("====== SensorEYE =======");
  Serial.println("========================");
  
  Serial.println("Voce pode usar os seguintes comandos: ");
  Serial.println("1 - ");
  Serial.println("2 - ");
 
}
 
void loop() {
   
}

// linguagem para os deficientes visuais
void vibracall(int intensidade) {
  analogWrite(pinoVibracall, intensidade); // 1-255
}

void fonebeep(int intensidade) {
  analogWrite(pinFone, intensidade); // 1-255
}

