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

// debug mode
const boolean debug = true, ligado = true; // controle pelo botao1

// pinos de todos os componentes
const int pinoEco = 12, // sensor; echoPin
          pinoDisparador = 7, // sensor; triggerPin
          pinoLed = 13, // led usada para os testes iniciais
          pinoVibracall = 5, // vibracall
          tempoAtualizacao = 0; // em microsegundos

// inicia o ultrassonico
Ultrasonic ultrasonic(pinoDisparador, pinoEco);

int ultimoCM = 0;
unsigned long time;
   
void setup() {
  Serial.begin(9600); // inicia o serial
  
  // mensagem inicial
  if(debug){
    Serial.println("Projeto SensorEYE");
    Serial.println("Escrito por Eduardo Ramos @ 1 EMIA");
    Serial.println("Versao: 2.0 BETA");
    Serial.println("Compilado em " __DATE__ " as " __TIME__);
    Serial.println(); // nova linha
  }
  
  pinMode(pinoEco, INPUT);
  pinMode(pinoDisparador, OUTPUT);
  pinMode(pinoVibracall, OUTPUT);
  pinMode(pinoLed, OUTPUT);
  
  inicializar();
}
 
void loop() {
   int distancia = atualizarSensor();
   
   if(millis() - time > 500) { // intervalo de meio segundo para vibrar novamente, impede que fique vibrando demais
     linguagem(distancia);
   }
     
   delay(tempoAtualizacao);
}

void inicializar() {
  time = millis();
  
  // duas vibrações iniciais para teste junto ao led de status
  for (int i = 0; i < 2; i++){
     vibracall(200);
     digitalWrite(pinoLed, HIGH);
     delay(500);
     vibracall(0);
     digitalWrite(pinoLed, LOW);
     delay(400);
  } 
  
  digitalWrite(pinoLed, HIGH); // liga o led de status
}

float atualizarSensor() {
    long pingSegundos = ultrasonic.timing();
    int cm = ultrasonic.convert(pingSegundos, Ultrasonic::CM);
  
    if(debug) {
      Serial.print("Distancia: ");
      Serial.print(cm);
      Serial.print("cm, ");
      Serial.print(cm / 100);
      Serial.print("metros, Ping: ");
      Serial.print(pingSegundos);
      Serial.print(" ms");
      Serial.println();
    }
    
    return cm;
}

// !!vibracação tem que ser maior que 100 para sentir
void vibracall(int intensidade) {  
  if(intensidade > 255){
     intensidade = 255; // previne ser maior que 255 
  }
  
  if(debug) {
    Serial.print("Vibracall funcionando! Com intensidade de ");
    Serial.print(intensidade);
    Serial.println();
  }
  
  analogWrite(pinoVibracall, intensidade);
}

void linguagem(int distancia) {
    float cm = distancia;
    time = millis();
    
    if(cm > 450) {
       return; // HC-SR04 não suporta mais que essa distância 
    }
    
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
       cm == ultimoCM + 14 || cm == ultimoCM - 14 ||
       cm == ultimoCM + 15 || cm == ultimoCM - 15 ||
       cm == ultimoCM + 16 || cm == ultimoCM - 16 ||
       cm == ultimoCM + 17 || cm == ultimoCM - 17 ||
       cm == ultimoCM + 18 || cm == ultimoCM - 18 ||
       cm == ultimoCM + 19 || cm == ultimoCM - 19 ||
       cm == ultimoCM + 20 || cm == ultimoCM - 20){
        ultimoCM = cm; // continua apenas com uma diferença muito grande, ou se nao fica vibrando toda hora  
        return;
    }
    
    // SensorEYE modo casa, curtas distancias
    if(ligado == false) {
      ultimoCM = cm;
      return; 
    }
    
    /////////////////////////////////////////
    // vibrações de acordo com a distância //
    /////////////////////////////////////////
    if(cm > 400) {
          
    }
       
    if(cm > 350 && cm < 400) {
         vibracall(35);
         delay(200);
         vibracall(0);
         delay(100);
     }
       
    if(cm > 300 && cm < 350) {
        vibracall(60);
        delay(400);
        vibracall(0);
        delay(300);
    }
       
    if(cm > 250 && cm < 300) {
       vibracall(80);
       delay(500);
       vibracall(0);
       delay(300);
     }
     
     if(cm > 200 && cm < 250) {
       vibracall(95);
       delay(500);
       vibracall(0);
       delay(300);
     }
     
     if(cm > 150 && cm < 200) {
       vibracall(110);
       delay(500);
       vibracall(0);
       delay(300);
     }
     
     if(cm > 100 && cm < 150) {
       vibracall(125);
       delay(500);
       vibracall(0);
       delay(300);
     }
     
     if(cm > 90 && cm < 100) {
       vibracall(155);
       delay(500);
       vibracall(0);
       delay(300);
     }
     
     if(cm > 60 && cm < 90) {
       vibracall(205);
       delay(500);
       vibracall(0);
       delay(300);
     }
     
     if(cm > 30 && cm < 60) {
       vibracall(220);
       delay(600);
       vibracall(0);
       delay(300);
     }
     
     if(cm > 5 && cm < 30) {
       vibracall(255);
       delay(800);
       vibracall(0);
       delay(300);
    }
     
   ultimoCM = cm;
}
