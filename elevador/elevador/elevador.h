/*
 * UACSA-UFRPE
 * Eletronica Digital
 * Exercicio de entrega E3 - questao 2
 * Alunos: Erick Gabriel e Luigi Luz
 * Cabecalho da biblioteca elevador
 */

#ifndef _ELEVADOR_H
#define _ELEVADOR_H
#include <Arduino.h>
//funcoes presentes na biblioteca
void motionUp();
void idle();
void motionDown();
void openDoor();
void procEstado(int buttonPress);
#endif
