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
          pinoDisparador = 7, // sensor triggerPin
          pinoLed = 13, // led usada para os testes iniciais
          pinoVibracall = 5, // vibracall
          tempoAtualizacao = 10, // em microsegundos
          SENS_ALTA  = 250, // sensibilidade do vibracall
          SENS_MEDIA = 150,
          SENS_BAIXA = 90;
 

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
    Serial.println("Versao: 2.1 BETA");
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
     vibracall(SENS_ALTA, 1000, 1000);
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
    
    
    if(cm == ultimoCM ||
         cm == ultimoCM + 1 || cm == ultimoCM - 1 ||
         cm == ultimoCM + 2 || cm == ultimoCM - 2 ||
         cm == ultimoCM + 3 || cm == ultimoCM - 3 ||
         cm == ultimoCM + 4 || cm == ultimoCM - 4 ||
         cm == ultimoCM + 5 || cm == ultimoCM - 5){
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
    
    
    // distancia da aba do boné // 8 cm
    if(cm > 0 && cm < 8){
       vibracall(255, 1000, 1000); 
    }
   
    if(cm > 8 && cm <= 70) {
        vibracall(255, 1000, 1000);
    }
    
    if(cm > 70 && cm <= 120) {
         vibracall(SENS_MEDIA, 800, 800); 
    }
    
    if(cm > 120 && cm < 190) {
       vibracall(SENS_MEDIA, 800, 800); 
    }
    
    
   ultimoCM = cm;
}
