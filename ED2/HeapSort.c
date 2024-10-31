#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void criarHeap(int vetor[], int i, int f){
  int aux = vetor[i];
  int j = i * 2 + 1;

  while(j <= f){
    if(j < f){
      if(vetor[j] < vetor[j + 1]){
        j = j + 1;
      }
    }
    if(aux < vetor[j]){
      vetor[i] = vetor[j];
      i = j;
      j = 2*i + 1;
    }else{
      j = f +1;
    }
  }
  vetor[i] = aux;
}

void HeapSort(int vetor[], int tamanho){
  int i, aux;
  for(i = (tamanho - 1)/2 ; i>=0; i--){
    criarHeap(vetor, i, tamanho - 1);
  }

  for(i = tamanho - 1; i >= 1; i--){
    aux = vetor[0];
    vetor[0] = vetor[i];
    vetor[i] = aux;
    criarHeap(vetor, 0, i-1);
  }
}

int main(){

  int vetor[20], sorteado;
  srand(time(NULL));

  for(int i = 0; i<20 ; i++){
    sorteado = rand() % 100;
    vetor[i] = sorteado;
  }

  printf("vetor antes: ");
  for(int i = 0; i<20; i++){
    printf("%d ",vetor[i] );
  }

  HeapSort(vetor, 20);

  printf("\n\nvetor depois: ");
  for(int i = 0; i<20; i++){
    printf("%d ",vetor[i] );
  }
  printf("\n\n ");




  return 0;
}
