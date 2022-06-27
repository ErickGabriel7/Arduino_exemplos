/*
 * UACSA-UFRPE
 * Eletronica Digital
 * Exercicio de entrega E3 - questao 2
 * Alunos: Erick Gabriel e Luigi Luz
 * Implementacao do processamento da biblioteca elevador
 */

//sentenciando esta implementacao no cabecalho "elevador.h" 
#include "elevador.h"  

//definindo os estados da maquina de estados
#define IDLE 0
#define MOTIONUP 1
#define MOTIONDOWN 2
#define OPENDOOR 3

int currentFloor = 1;
int buttonPress = 7;
int tempo = 15;

//definindo as funcoes que dirao o que cada estado vai fazer:

void motionUp(){
currentFloor = currentFloor + 1;
Serial.println("O elevador esta subindo ");
}

void idle(){
Serial.println("O elevador esta parado");
}

void motionDown(){
currentFloor = currentFloor - 1;
Serial.println("O elevador esta descendo");
}

void openDoor(){
Serial.println("A porta esta aberta no andar:");
Serial.println(currentFloor);
}

//definindo a variavel de estado da maquina
byte estado = IDLE;

//funcao de processamento da maquina de estado
void procEstado(int buttonPress){
  switch(estado){
  case IDLE:
    idle();
      if (buttonPress > currentFloor){
          estado = MOTIONUP;}
        else if (buttonPress < currentFloor){
          estado = MOTIONDOWN;
            }
         else { // buttonPress > currentFloor
            estado = IDLE;
          }
  break;
  case MOTIONUP:
    motionUp();   
      if (currentFloor < buttonPress){
        estado = MOTIONUP;
        }
      else { // buttonPress = currentFloor
          estado = OPENDOOR;         
        }
  break;
  case MOTIONDOWN:
      if (currentFloor > buttonPress)
        { // buttonPress < currentFloor
            estado = MOTIONDOWN;
        }
      else{
        estado = OPENDOOR;
        } 
  break;
  case OPENDOOR:
      openDoor();
      tempo = tempo - 1 ;
        if (tempo != 0){
            estado = OPENDOOR;}
        else {
              tempo = 15;
            estado = IDLE;}
  break;
  }
}
