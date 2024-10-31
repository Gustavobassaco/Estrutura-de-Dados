#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void bubbleSort(int vetor[], int tamanho){
  int continuar = 0;
  int aux;
  int controle=0;


  do{
    for(int i = 0; i<tamanho-1 ; i++){
      if(vetor[i] > vetor[i+1]){
        aux = vetor[i];
        vetor[i]= vetor[i+1];
        vetor[i+1] = aux;
        controle = 0;

      }
    }
    tamanho--;
    if(controle == 1)
    break;
    controle = 1;

    continuar++;
  }while(continuar != tamanho -1);

return;
}

int main(){
  int vetor[21], sorteado;
  srand(time(NULL));

  for(int i = 0; i<21 ; i++){
    sorteado = rand() % 100;
    vetor[i] = sorteado;
  }

  printf("vetor antes: ");
  for(int i = 0; i<21; i++){
    printf("%d ",vetor[i] );
  }

  bubbleSort(vetor, 21);

  printf("\n\nvetor depois: ");
  for(int i = 0; i<21; i++){
    printf("%d ",vetor[i] );
  }
  printf("\n\n ");
  return 0;
}
