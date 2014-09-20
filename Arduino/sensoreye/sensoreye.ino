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

// Pinos do sensor ultrasonico
const int pinoEco = 1; // sensor echo Pin
const int pinoDisparador = 2; // sensor trigger Pin
const int pinoLed = 4; // led usada para os testes iniciais
const int pinoVibracall = 5; // vibracall

// const float velocidadeSom = 346.3 // velocidade do som em (m/s) a +25 °C
byte comandoSerial;

Ultrasonic ultrasonic(pinoDisparador, pinoEco);

void setup() {
  Serial.begin(9600); // inicia o serial
  
  // mensagem inicial
  Serial.println("Projeto SensorEYE");
  Serial.println("Escrito por Eduardo Ramos, Filipe Gianotto e Felipe Pereira @ 1 EMIA");
  Serial.println("Versao: 0.0 ALPHA");
  Serial.println("Compilado em " __DATE__ " as " __TIME__);
  Serial.println("Pressione h para /help");
  Serial.println(); // nova linha
  
  pinMode(pinoEco, INPUT);
  pinMode(pinoDisparador, OUTPUT);
  pinMode(pinoLed, OUTPUT);
  
  inicializar();
}
 
void loop() {
   // verifica se há comandos no Serial
   if(Serial.available() > 0){
      comandoSerial = Serial.read(); 
   }
   
   // comandos do Serial
   switch(comandoSerial){
       
   }
   comandoSerial = 0;
   
   float distancia = calcular();
   
   delay(100);
}

// funções internas
void help() { 
  Serial.println("");
}

void inicializar() {
  // dois beeps/vibrações iniciais para teste
  for (int i = 0; i < 2; i++){
     vibracall(200);
     delay(1000);
     desligaVibracall();
     delay(1000); 
  }   
}

// funcao do ultrasonico
float calcular() {
    long microsec = ultrasonic.timing();
    float distanciaCM = ultrasonic.convert(microsec, Ultrasonic::CM);

    if(debug) {
      Serial.print("Microsegundos: ");
      Serial.print(microsec);
      Serial.print(", CM: ");
      Serial.print(distanciaCM);
      Serial.println();
    }
    
    return distanciaCM;
}

void vibracall(int intensidade) {
  analogWrite(pinoVibracall, intensidade); // 1-255
}

void desligaVibracall() {
   vibracall(0);
}

void fonebeep(int intensidade) { }

void linguagem(int distancia) {
    /*
     distancia em CM
     1 M = 100 CM
     */
    float centimetros = distancia;
    float metros = centimetros * 100;
    
    // objetos pertos (em cm)
    if(distancia < 100){
    
    
    
    // objetos distantes (em metros)  
    } else {      
      
    }
}
