/*
 * UACSA-UFRPE
 * Eletronica Digital
 * Exercicio de entrega E3 - questao 2
 * Alunos: Erick Gabriel e Luigi Luz
 * TopLevel da biblioteca elevador
 */

#include "elevador.h"

void setup()
{Serial.begin(9600);
}

void loop()
{
  int buttonPress = 7;
  procEstado(buttonPress);
  delay(1000);
}
