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
const boolean debug = true;
const boolean ligado = true; // controle pelo botao1
boolean modoCasa = true; // padrao casa; modo rua = false

// pinos de todos os componentes
const int pinoEco = 12; // sensor; echoPin
const int pinoDisparador = 7; // sensor; triggerPin
const int pinoLed = 13; // led usada para os testes iniciais
const int pinoVibracall = 5; // vibracall
const int pinoBotao1 = 6; // botao para alguma função
const int pinoBotao2 = 8; // botao para outra função
const int tempoAtualizacao = 100; // em microsegundos

Ultrasonic ultrasonic(pinoDisparador, pinoEco);
int ultimoCM = 0;
unsigned long time;
   
void setup() {
  Serial.begin(9600); // inicia o serial
  
  // mensagem inicial
  if(debug){
    Serial.println("Projeto SensorEYE");
    Serial.println("Escrito por Eduardo Ramos @ 1 EMIA");
    Serial.println("Versao: 1.3 ALPHA");
    Serial.println("Compilado em " __DATE__ " as " __TIME__);
    Serial.println(); // nova linha
  }
  
  pinMode(pinoEco, INPUT);
  pinMode(pinoDisparador, OUTPUT);
  pinMode(pinoLed, OUTPUT);
  pinMode(pinoBotao1, INPUT);
  pinMode(pinoBotao2, INPUT);
  
  inicializar();
  time = millis();
}
 
void loop() {
   int distancia = atualizarSensor();
   
   //if(millis() - time > 1000) { // vibra apenas após 1 segundo
     linguagem(distancia);
   //}
   
   
    
   delay(tempoAtualizacao);
}

void inicializar() {
  // duas vibrações iniciais para teste junto ao led de status
  for (int i = 0; i < 2; i++){
     vibracall(200);
     digitalWrite(pinoLed, HIGH);
     delay(500);
     vibracall(0);
     digitalWrite(pinoLed, LOW);
     delay(400);
  }  
}

float atualizarSensor() {
    long pingSec = ultrasonic.timing();
    int distanciaCM = ultrasonic.convert(pingSec, Ultrasonic::CM);
  
    if(debug) {
      Serial.print("Distancia: ");
      Serial.print(distanciaCM);
      Serial.print("cm, ");
      Serial.print(distanciaCM / 100);
      Serial.print("m, Ping: ");
      Serial.print(pingSec);
      Serial.print(" ms");
      Serial.println();
    }
    
    return distanciaCM;
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
       cm == ultimoCM + 20 || cm == ultimoCM - 20 ||
       cm == ultimoCM + 21 || cm == ultimoCM - 21 ||
       cm == ultimoCM + 22 || cm == ultimoCM - 22 ||
       cm == ultimoCM + 23 || cm == ultimoCM - 23 ||
       cm == ultimoCM + 24 || cm == ultimoCM - 24 ||
       cm == ultimoCM + 25 || cm == ultimoCM - 25 ||
       cm == ultimoCM + 26 || cm == ultimoCM - 26 ||
       cm == ultimoCM + 27 || cm == ultimoCM - 27 ||
       cm == ultimoCM + 28 || cm == ultimoCM - 28 ||
       cm == ultimoCM + 29 || cm == ultimoCM - 29 ||
       cm == ultimoCM + 30 || cm == ultimoCM - 30){
        ultimoCM = cm; // continua apenas com uma diferença muito grande, ou se nao fica vibrando toda hora  
        return;
    }
    
    // SensorEYE modo casa, curtas distancias
    if(ligado == false) {
      ultimoCM = cm;
      return; 
    }
    
    if(modoCasa) {
       if(cm > 400) {
          
       }
       
       if(cm > 350 && cm < 400) {
         vibracall(35);
         delay(500);
         vibracall(0);
         delay(300);
       }
       
       if(cm > 300 && cm < 350) {
         vibracall(60);
         delay(500);
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
         vibracall(255);
         delay(500);
         vibracall(0);
         delay(300);
       }
       
    } else {
      
    }

   ultimoCM = cm;
}
