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
#define echoPin 1 // Echo Pin
#define trigPin 2 // Trigger Pin

#define testLed 4 // Led usada para os testes iniciais

void setup() {
  Serial.begin(9600); // inicia o serial
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(testLed, OUTPUT);
}
 
void loop() {
   
}

// linguagem para os deficientes visuais
void vibracall() {
  
}

void fonebeep() {
  
}

