// Controlled bridge rectifier with Arduino
// EPA 08/12/2022
//************************************************************************************

//Definir portas Arduino
#define scr1_gate   8 //disparo tiristor 1 no pino digital 8
#define scr2_gate   10 //disparo tiristor 2 no pino digital 10
#define pot        A0 //potenciometro pino analogico A0
#define comp        2 //comparador no pino digital 2

//************************************************************************************
//definição de variáveis
int ZC=0;
float ADCValue;
float alpha;
float VirtualDelay;
int RealDelay;


//************************************************************************************
//rotina SETUP
void setup(void) {
  pinMode(scr1_gate, OUTPUT); //define pino tiristor 1 como saida
  digitalWrite(scr1_gate, LOW); //coloca pino tiristor 1 a nivel baixo
  pinMode(scr2_gate, OUTPUT); //define pino tiristor 2 como saida
  digitalWrite(scr2_gate, LOW); //coloca pino tiristor 2 a nivel baixo
  attachInterrupt(digitalPinToInterrupt(comp), ZC_detect, CHANGE);       // activa interrupt externo para a função de deteccao de cruzamento por zero
    
  pinMode(13, OUTPUT); //led da placa, se for necessário utilizar
  digitalWrite(13, LOW);

  Serial.begin(9600);
}
//************************************************************************************
//função de detecção cruzamento por zero 
void ZC_detect() {
  digitalWrite(scr2_gate,LOW);
  digitalWrite(scr1_gate,LOW);
  if(digitalRead(2))
    ZC = 1;
  else
    ZC = 2;
}

//************************************************************************************
//rotina loop
void loop() {
  if(ZC == 1){
    ADCValue = analogRead(pot);
    alpha = ADCValue * 180;
    alpha = alpha/1023;
    VirtualDelay = (alpha * 9500) / 180;
    RealDelay = VirtualDelay;
    
    delayMicroseconds(RealDelay);
    digitalWrite(scr1_gate,HIGH);
    ZC = 0;
  }

  if(ZC == 2){
    
    ADCValue = analogRead(pot);
    alpha = ADCValue * 180;
    alpha = alpha/1023;
    VirtualDelay = (alpha * 9500) / 180;
    RealDelay = VirtualDelay;
    
    delayMicroseconds(RealDelay);
    delayMicroseconds(alpha);
    digitalWrite(scr2_gate,HIGH);

    ZC = 0;
  }
  
  
}


/************************************************************************************
 * INFO
 * delayMicroseconds(alpha) - FAZ UM ATRASO DE alpha MICROSEGUNDOS
 * delay(alpha) - FAZ UM ATRASO DE alpha MILISEGUNDOS
 * analogRead(A0) - Le da porta analógica 10bits entao lê de 0 a 1024
 * digitalWrite(D1, Estado) - escreve na porta digital D1 o estado lógico: HIGH ou LOW
 * digitalRead(D1) - Lê o pino digital e retorna HIGH ou LOW
 * byte variavel = 0; variável tipo byte
 * uint16_t variavel = 0; variavel tipo int
 */