#include "lm35.h"

int Le_temperatura()
{
  int i, temperatura;
  float vet_temperatura[TAM], aux;

  aux = 0;
  for (i = 0; i < TAM; i++)
  {
    vet_temperatura[i] = (float(analogRead(LM35)) * 5 / (1023)) / 0.01;
    aux += vet_temperatura[i];
  }
  aux = (aux / TAM);
  temperatura = (int)aux;

  return temperatura;
}