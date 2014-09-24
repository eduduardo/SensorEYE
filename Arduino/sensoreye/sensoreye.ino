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

Ultrasonic ultrasonic(pinoDisparador, pinoEco);
int ultimoCM = 0;
   
void setup() {
  Serial.begin(9600); // inicia o serial
  
  // mensagem inicial
  if(debug){
    Serial.println("Projeto SensorEYE");
    Serial.println("Escrito por Eduardo Ramos @ 1 EMIA");
    Serial.println("Versao: 1.1 ALPHA");
    Serial.println("Compilado em " __DATE__ " as " __TIME__);
    Serial.println(); // nova linha
  }
  
  pinMode(pinoEco, INPUT);
  pinMode(pinoDisparador, OUTPUT);
  pinMode(pinoLed, OUTPUT);
  pinMode(pinoBotao1, INPUT);
  pinMode(pinoBotao2, INPUT);
  
  inicializar();
}
 
void loop() {
   float distancia = atualizarSensor();
   linguagem(distancia);

   delay(100);
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

// funcao do ultrasonico
float atualizarSensor() {
    long ping = ultrasonic.timing();
    int distanciaCM = ultrasonic.convert(ping, Ultrasonic::CM);
  
    if(debug) {
      Serial.print("Distancia: ");
      Serial.print(distanciaCM);
      Serial.print("cm, ");
      Serial.print(distanciaCM / 100);
      Serial.print("m, Ping: ");
      Serial.print(microsec);
      Serial.print(" ms")
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
    Serial.print("Vibrando! Com intensidade de ");
    Serial.print(intensidade);
    Serial.println();
  }
  
  analogWrite(pinoVibracall, intensidade);
}

void linguagem(int distancia) {
    float centimetros = distancia;
    float metros = centimetros * 100;
    
    if(centimetros > 450) {
       return; // HC-SR04 não suporta mais que essa distância 
    }
    
    if(centimetros == ultimoCM || centimetros == ultimoCM + 1 || centimetros == ultimoCM - 1 ||
       centimetros == ultimoCM + 2 || centimetros == ultimoCM - 2){
        ultimoCM = centimetros; // continua apenas com uma diferença muito grande, ou se nao fica vibrando toda hora  
        return;
    }
    
    if(centimetros < 5) {
      vibracall(200);
      delay(2000);
      vibracall(0); 
     }
   
     if(centimetros > 5 && centimetros < 10){
       vibracall(150);
       delay(1000);
       vibracall(0); 
     }
   
     if(centimetros > 10 && centimetros < 20) {
        vibracall(100);
        delay(500);
        vibracall(0); 
     }
   
   ultimoCM = centimetros;
}
