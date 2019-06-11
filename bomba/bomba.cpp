// Eletrônica Digital
// Data: 04/04/2019

//.cpp é a implementacao da biblioteca
//.h é o cabeçalho

#include "bomba.h"

// funcao para definir os pinos 3 e 4 como entrada
// e definimos o pino 5 como saída
void confES(){
  //defino os pinos 3 e 4 como entrada, ou seja, com valor binario 0
  //resetamos as posições usando o compound and
  DDRD &= ~((1<<DDD4)|(1<<DDD3)); //Sensores nos pinos 3 e 4
  // defino o pino 5 como saida, ou sejam, com valor binario 1
  //setamos a posicao usando o compound or
  DDRD |= (1<<DDD5); //Bomba no pino 5
  PORTD &= ~(1<<DDD5); /// Mantem saida 5 em zero/desligado
}

// leitura dos pinos 3 e 4
byte leituraSens(){
  // apenas desloco para facilitar a identificacao de que porta esta sendo lida
  // agora a leitura dos pinos 3 e 4 estarao nas posicoes 0 e 1
  // em que pino 3 -> posicao 0 e pino 4 -> posicao 1
   return (PIND & 0x18)>>3; // 0x18 = 00011000
  // PIND é equivalente ao digitalRead, mas lendo varios pinos simultaneamente
  // mapeamento dos sensores
  // sensor A (sensor superior) está na posicao 1
  // sensor B (sensor inferior) esta na posicao 0
  // se A=0, significa que o sensor superior esta desativado
  // se A=1, significa que o sensor superior esta ativado
  // se B=0, significa que o sensor inferior esta desativado
  // se B=1, significa que o sensor inferior esta ativado
}

//Liga a bomba 
void liga(){
  // vamos enviar nivel logico 1 na saida 5
  PORTD |= (1<<DDD5); /// liga 5
}
 //Desliga a bomba
void desliga(){
  // vamos enviar nivel logico 0 na saida 5
  PORTD &= ~(1<<DDD5); /// desliga 5
}

// definição dos estados desligado e ligado
#define DESLIGADO 0
#define LIGADO    1

byte estado = DESLIGADO;      

void procEstado(byte sensores) //essa entrada sera o leituraSens()
{
  switch(estado){
    case DESLIGADO:
      desliga();
        if(sensores == 0){ // os dois sensores estao desativados (lembrar do deslocamento)
              estado = LIGADO;}
    break;
    case LIGADO:
      liga();
        if(sensores == 3){ // os dois sensores estao ativados (lembrar do deslocamento)
              estado = DESLIGADO;}
    break;
  }
  
} 
