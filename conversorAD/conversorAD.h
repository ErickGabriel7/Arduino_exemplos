/*Eletronica digital
 * Exercicio de entrega L7
 * Alunos: Erick Gabriel e Luigi Luz
 * Professor: Roberto Kenji Hiramatsu
 * 
 *Cabecalho da biblioteca conversor2500*/

#ifndef _CONVERSORAD_H
#define _CONVERSORAD_H
#include <Arduino.h>

void cfgT1();
ISR(ADC_vect);
ISR(TIMER1_COMPA_vect);
void cfgADC();
void trADC();
#endif;
