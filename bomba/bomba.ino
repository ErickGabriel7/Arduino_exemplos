#include "bomba.h"

void setup()
{Serial.begin(9600);
confES();
}

void loop()
{
  procEstado(leituraSens());
}

