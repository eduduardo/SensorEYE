/*
 *  SensorEYE - Estante protoboard
 * 
 *  Protoboard teste para mostrar o funcionamento do sensor HC-SR04
 *
 *  Equipe:
 *  Ana Lacreta
 *  Brenda Conttessotto
 *  Caio Eduardo
 *  Eduardo Augusto Ramos
 *  Felipe Pereira Jorge
 *  Filipe Dias Gianotto
 *  Gabriel Filipe Ferreira
 *  Gustavo Elias
 *  Gustavo Oliveira
 *  Vitória Tenório
 *  Márcio Cibelli Bombo  
 *  
 *  ETEC Pedro Ferreira Alves @ 1 EMIA 2014
 */

#include <Ultrasonic.h>

// debug mode
const boolean debug = true;

// pinos de todos os componentes
const int pinoEco = 12, // sensor; echoPin
          pinoDisparador = 7, // sensor triggerPin
          pinoLedVermelha = 11, // led vermelha
          pinoLedAmarela  = 12, // led amarela
          pinoLedVerde    = 6, // led verde
          tempoLoop = 0; // em microsegundos
 
// inicia o ultrassonico
Ultrasonic ultrasonic(pinoDisparador, pinoEco);

int ultimoCM = 0;
unsigned long time;
   
void setup() {
  if(debug){
    Serial.begin(9600); // inicia o serial
    
    // mensagem inicial
    Serial.println("Projeto SensorEYE - Protoboard");
    Serial.println("Escrito por Eduardo Ramos @ 1 EMIA");
    Serial.println("Versao: 3.0 LAMBDA");
    Serial.println("Compilado em " __DATE__ " as " __TIME__);
    Serial.println(); // nova linha
  }
  
  pinMode(pinoEco, INPUT);
  pinMode(pinoDisparador, OUTPUT);
  pinMode(pinoLedVermelha, OUTPUT);
  pinMode(pinoLedAmarela, OUTPUT);
  pinMode(pinoLedVerde, OUTPUT);
  
  // tempo inicial interno
  time = millis();
  
  // desliga o led da placa Arduino para economizar bateria
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}
 
void loop() {
   int distancia = atualizarSensor();
   
   if(millis() - time > 500) { // intervalo de meio segundo para vibrar novamente, impede que fique vibrando demais
     linguagem(distancia);
   }
     
   delay(tempoLoop);
}

float atualizarSensor() {
    long pingSegundos = ultrasonic.timing();
    int cm = ultrasonic.convert(pingSegundos, Ultrasonic::CM);
  
    if(debug) {
      Serial.print("Distancia: ");
      Serial.print(cm);
      Serial.print("cm, ");
      Serial.print(cm / 100);
      Serial.print(" metros, Ping: ");
      Serial.print(pingSegundos);
      Serial.print(" ms");
      
      if(cm > 3000) {
         Serial.print(" - Erro: Fora do alcance!!") ;
      }
      Serial.println();
    }
    
    return cm;
}

void ligaLed(int pino) {
   if(debug) {
      Serial.print("Led ");
      
      switch(pino) {
         case pinoLedVermelha:
           Serial.print("vermelha");
         break;
         
         case pinoLedAmarela:
           Serial.print("amarela");
         break;
         
         case pinoLedVerde:
           Serial.print("verde");
         break;
      }
      
      Serial.print(" ligada.");
      Serial.println();
   }
   
   // desliga tudo
   digitalWrite(pinoLedVermelho, LOW);
   digitalWrite(pinoLedAmarela, LOW);
   digitalWrite(pinoLedVerde, LOW);
   
   digitalWrite(pino, HIGH);
}


void linguagem(int distancia) {
    float cm = distancia;
    float metros = distancia / 100;
    time = millis();
    
    if(cm > 450) {
       return; // HC-SR04 não suporta mais que essa distância 
    }
    
    if(cm == ultimoCM ||
         cm == ultimoCM + 1 || cm == ultimoCM - 1 ||
         cm == ultimoCM + 2 || cm == ultimoCM - 2 ||
         cm == ultimoCM + 3 || cm == ultimoCM - 3 ||
         cm == ultimoCM + 4 || cm == ultimoCM - 4 ||
         cm == ultimoCM + 5 || cm == ultimoCM - 5){
          ultimoCM = cm; // continua apenas com uma diferença muito grande, ou se nao fica vibrando toda hora  
          return;
      }
    
    /////////////////////////////////////////
    // vibrações de acordo com a distância //
    ///////////////////////////////////////// 
    
    // distancia da aba do boné // 8 cm
    if(cm > 0 && cm < 8){
        ligaLed(pinoLedVermelha); 
    }
   
    if(cm > 8 && cm <= 70) {
        ligaLed(pinoLedVermelha);
    }
    
    if(cm > 70 && cm <= 120) {
        ligaLed(pinoLedAmarela); 
    }
    
    if(cm > 120 && cm <= 190) {
       ligaLed(pinoLedAmarela); 
    }
    
    if(cm > 190 && cm < 240) {
       ligaLed(pinoLedVerde); 
    }
    
    ultimoCM = cm;
}
