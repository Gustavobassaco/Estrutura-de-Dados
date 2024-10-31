#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void shellSort(int vetor[], int tamanho){
  int aux, i, j, h = tamanho/2;

  while(h > 0){
    i = h;
    while(i < tamanho){

      aux = vetor[i];
      j = i;
      while(j>= h && aux < vetor[ j - h ]){
        vetor[j]= vetor[j - h];
        j = j - h;
      }
      vetor[j] = aux;
      i++;
    }
    h = h/2;
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

  shellSort(vetor, 20);

  printf("\n\nvetor depois: ");
  for(int i = 0; i<20; i++){
    printf("%d ",vetor[i] );
  }
  printf("\n\n ");





  return 0;
}
