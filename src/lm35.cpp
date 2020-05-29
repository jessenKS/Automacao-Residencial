#include "lm35.h"

float temperatura;

void Le_temperatura()
{
  int i;
  float vet_temperatura[TAM], aux;

  aux = 0;
  for (i = 0; i < TAM; i++)
  {
    vet_temperatura[i] = (float(analogRead(LM35)) * 5 / (1023)) / 0.01;
    aux += vet_temperatura[i];
  }
  aux = (aux / TAM);
  temperatura = aux;
}