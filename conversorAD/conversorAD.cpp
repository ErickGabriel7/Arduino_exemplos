/*Eletronica digital
 * Exercicio de entrega L7
 * Alunos: Erick Gabriel e Luigi Luz
 * Professor: Roberto Kenji Hiramatsu
 * 
 *Criando amostrador @2500 amostras por segundo usando controle via timer 1*/

#include "conversorAD.h"

//configuracao do timer 1
void cfgT1(){
  cli();
  // Configuracao do timer0 CTC para 1Hz 
  TCCR1A=0;   
  TCCR1B = (1<<WGM12); //Colocando em CTC WGM1 3:0= 0100
//  TCCR1B = (1<<CS11); //Prescaler 8x cs1 2:0= 010
 // TCCR1B |= (1<<CS12)|(1<<CS10); //Prescaler 1024x cs1 2:0= 101 (teste)
 TCCR1B |= (1<<CS10); //Prescaler 1x cs1 2:0= 001 
  //OCR1A = 16MHz/2500Hz*1 = 6400
  OCR1A = 6400;         //para gerar o sinal na taxa de 2500Hz
  TCNT1=0;
  TIMSK1= (1<<OCIE1A); 
  sei();
}

//rotina de interrupcao
ISR(TIMER1_COMPA_vect){
 ADMUX  &= ~(1<<MUX0); //reseta ADMUX, fazendo com que a porta lida seja a A0
 ADCSRA |= (1<<ADSC);  //adsc e o bit que inicializa a conversao AD
}

//configuracao do ADC
void cfgADC(){
  cli();
  ADMUX = (1<<REFS0); //Referencia de voltagem  5V REFS 1:0= 01
  // A configuracao acima ja faz a entrada A1 estar selecionada, fazendo REFS 1:0 = 00, a entrada sera A0
  //REFS funciona como um multiplex das entradas
  ADCSRA = (1<<ADPS2)|(1<<ADPS1); //Configurar prescaler
           //em 64x 
           //estava em 128x e operava em 125kHz, dividindo o prescaler por 2, aumentamos para 250kHZ
           //ADPS 2:0 = 110
 ADCSRB = 0; //Captura livre
 ADCSRA |= (1<<ADEN)| (1<<ADIE); //Habilita ADC ADEN e interrupcao
sei();
}

//mostrando o que tem nos registradores, funcao usada como debugger (nao e essencial)
volatile uint8_t *rA[] = {&ADMUX,&ADCSRA,&ADCSRB,&DIDR0};
String srA[]={"ADMUX","ADCSRA","ADCSRB","DIDR0"};
void printRA(){
  for(byte i=0;i<4;i++){
    Serial.print(srA[i]+": ");
    Serial.println(*rA[i],16);
  }
}

//volatile unsigned long t0,t1=0;
volatile byte disp0 = 0, disp1 = 0; //variaveis que dirao se o adc ja esta pronto para ser transmitido para o serial
volatile int valor0, valor1; //variaveis que armazenarao o valor medido no adc

ISR(ADC_vect){ //Ocorre na conclusao da conversao
cli();
  //logica para multiplexar as entradas A0 e A1
  if((ADMUX &(1<<MUX0)) == 0)  //ve se o bit do multiplex esta em 0, se sim:
  {
    valor0 = ADC;       //le o valor que esta no ADC e salva em valor0
    ADMUX |= (1<<MUX0); //seta o lsb de ADMUX em 1 para posteriormente ler o valor da porta A1
    ADCSRA |= (1<<ADSC);  //adsc e o bit que inicializa a conversao AD | gera dnv a interrupcao
    disp0 = 1;           //avisa  que terminou (sera importante no void loop()
   }
   else      //caso contrario, se o lsb de ADMUX estiver em 1, ou seja, a porta selecionada e a A1
   {
    valor1 = ADC;   //le o valor
    disp1 = 1;      //avisa que terminou
    }
 /*  
  //metodo de calcular o tempo necesario para medicao
  t0=t1;
  t1=millis();
  valor=ADC;
 */
 sei();
}

byte conta0 = 0, conta1 = 0,conta =0;
void trADC()
  {
  if(disp0 && disp1){
    Serial.write(valor0);
    //Serial.print("\t");
    Serial.write(valor1);
    disp0 = 0;
    disp1 = 0;
    conta++;
    if (conta==100){
    Serial.write(0xff);
    //Serial.print("\t");
    Serial.write(0xff);
    conta = 0;}
  }
  }
