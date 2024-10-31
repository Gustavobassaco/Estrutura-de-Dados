#include <stdio.h>
#include <stdlib.h>

/* Exerc´ıcio 1. [Ponteiros] Um ponteiro pode ser usado para dizer a uma fun¸c˜ao onde ela deve depositar
o resultado de seus c´alculos. Escreva uma fun¸c˜ao que converta uma quantidade de minutos na nota¸c˜ao
horas/minutos. A fun¸c˜ao recebe como parˆametro:
• um n´umero inteiro (totalMinutos); e
• os endere¸cos de duas vari´aveis inteiras, horas e minutos.
A fun¸c˜ao deve ent˜ao atribuir valores `as vari´aveis passadas por referˆencia, de modo que os valores atribu´ıdos
respeitem as seguintes condi¸c˜oes:
minutos < 60
60 ∗ horas + minutos = totalMinutos
Escreva tamb´em a fun¸c˜ao principal (main) que use a fun¸c˜ao desenvolvida.
*/

typedef struct{
  int hora;
  int minuto;
}horario;

void converte(horario *h){
  h->hora = h->minuto / 60;
  h->minuto= h->minuto % 60;
}

int main(){
  horario h;

  do{
  printf("\nDigite uma quantidade de minutos: \n");
  scanf("%d", &h.minuto);

  if(h.minuto < 0)
  printf("voce digitou um valor invalido \n");

}while(h.minuto < 0);

  converte(&h);

  printf("\n %d / %d \n", h.hora, h.minuto );
  return 0;
}
