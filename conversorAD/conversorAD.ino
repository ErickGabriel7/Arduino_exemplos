/*Eletronica digital
 * Exercicio de entrega L7
 * Alunos: Erick Gabriel e Luigi Luz
 * Professor: Roberto Kenji Hiramatsu
 * 
 *TopLevel do projeto*/
#include "conversorAD.h"

void setup(){
  Serial.begin(9600);
  cfgT1();
  cfgADC();
}
  
void loop()
{
 trADC();
}
