#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
  int i;
  char palavra[100];

}objeto;

typedef struct{
  objeto obj;

}sla;

int main(){
  int sla;
  char palavra[] = "1";
  char vetor[] = {'a', 'b', 'e', 'i', '3', '0', '1', '2', '3', '4', '5', '6'};

sla = atoi(palavra);
printf("numero %d\n", sla);

    // for(int i = 0; i<12; i++){
    //   sla = atoi(vetor[i]);
    //   printf("%c  ---- %d \n",vetor[i], sla );
    // }


  return 0;
}
