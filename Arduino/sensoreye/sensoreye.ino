/*
 *  SensorEYE
 * 
 *  Equipamento para deficientes visuais consituido de um boné, um sensor ultrassônico (HC-SR04) 
 *  uma pulseira e um vibracall que irá emitir vibrações de acordo com a distância 
 *  de objeto ou obstáculos.
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
const boolean debug = false;

// pinos de todos os componentes
const int pinoEco = 12, // sensor; echoPin
          pinoDisparador = 7, // sensor triggerPin
          pinoVibracall = 5, // vibracall
          tempoLoop = 0; // em microsegundos
 
// inicia o ultrassonico
Ultrasonic ultrasonic(pinoDisparador, pinoEco);

int ultimoCM = 0;
unsigned long time;
   
void setup() {
  if(debug){
    Serial.begin(9600); // inicia o serial
    
    // mensagem inicial
    Serial.println("Projeto SensorEYE");
    Serial.println("Escrito por Eduardo Ramos @ 1 EMIA");
    Serial.println("Versao: 3.0 LAMBDA");
    Serial.println("Compilado em " __DATE__ " as " __TIME__);
    Serial.println(); // nova linha
  }
  
  pinMode(pinoEco, INPUT);
  pinMode(pinoDisparador, OUTPUT);
  pinMode(pinoVibracall, OUTPUT);
  
  // tempo inicial interno
  time = millis();
  
  // duas vibrações iniciais para teste junto ao led de status
  for (int i = 0; i < 2; i++){
     vibracall(255, 1000, 1000);
  }
  
  // desliga o led da placa Arduino para economizar bateria
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}
 
void loop() {
   int distancia = atualizarSensor();
   
   if(millis() - time > 1000) { // intervalo de um segundo para vibrar novamente, impede que fique vibrando demais
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

// !!vibracação tem que ser maior que 100 para sentir
void vibracall(int intensidade, int primeiroDelay, int segundoDelay) {  
  if(intensidade > 255){
     intensidade = 255; // previne ser maior que 255 
  }
  
  if(debug) {
    Serial.print("Vibracall funcionando! Com intensidade de ");
    Serial.print(intensidade);
    Serial.println();
  }
  
  analogWrite(pinoVibracall, intensidade);
  delay(primeiroDelay);
  analogWrite(pinoVibracall, 0);
  delay(segundoDelay);
}

void linguagem(int distancia) {
    float cm = distancia;
    float metros = distancia / 100;
    time = millis();
    
    if(cm > 450) {
       return; // HC-SR04 não suporta mais que essa distância 
    }
    
    if(cm <= 80) {
    
      if(cm == ultimoCM ||
         cm == ultimoCM + 1 || cm == ultimoCM - 1 ||
         cm == ultimoCM + 2 || cm == ultimoCM - 2 ||
         cm == ultimoCM + 3 || cm == ultimoCM - 3 ||
         cm == ultimoCM + 4 || cm == ultimoCM - 4 ||
         cm == ultimoCM + 5 || cm == ultimoCM - 5){
          ultimoCM = cm; // continua apenas com uma diferença muito grande, ou se nao fica vibrando toda hora  
          return;
      }
      
    } else {
      
      
      if(cm == ultimoCM ||
         cm == ultimoCM + 1 || cm == ultimoCM - 1 ||
         cm == ultimoCM + 2 || cm == ultimoCM - 2 ||
         cm == ultimoCM + 3 || cm == ultimoCM - 3 ||
         cm == ultimoCM + 4 || cm == ultimoCM - 4 ||
         cm == ultimoCM + 5 || cm == ultimoCM - 5 ||
         cm == ultimoCM + 6 || cm == ultimoCM - 6 ||
         cm == ultimoCM + 7 || cm == ultimoCM - 7 ||
         cm == ultimoCM + 8 || cm == ultimoCM - 8 ||
         cm == ultimoCM + 9 || cm == ultimoCM - 9 ||
         cm == ultimoCM + 10 || cm == ultimoCM - 10 ||
         cm == ultimoCM + 11 || cm == ultimoCM - 11 ||
         cm == ultimoCM + 12 || cm == ultimoCM - 12 ||
         cm == ultimoCM + 13 || cm == ultimoCM - 13 ||
         cm == ultimoCM + 13 || cm == ultimoCM - 14 ||
         cm == ultimoCM + 15 || cm == ultimoCM - 15){
          ultimoCM = cm;  
          return;
      }  
    }
    
    /////////////////////////////////////////
    // vibrações de acordo com a distância //
    ///////////////////////////////////////// 
    
    // distancia da aba do boné // 8 cm
    if(cm > 0 && cm < 30){
       vibracall(255, 1200, 1200); 
    }
   
    if(cm > 30 && cm <= 80) {
        vibracall(200, 1000, 1000);
    }
    
    if(cm > 80 && cm <= 120) {
      vibracall(160, 800, 800); 
    }
    
    if(cm > 120 && cm <= 190) {
      vibracall(120, 700, 700); 
    }
    
    if(cm > 190 && cm < 240) {
      vibracall(100, 500, 500); 
    }
   ultimoCM = cm;
}
