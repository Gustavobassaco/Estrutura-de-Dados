#include <stdio.h>
#include <stdlib.h>


void InsertionSort(int vetor[], int tamanho){
  int i , j , eleito;

  for(i = 1; i<tamanho;  i++){
    eleito = vetor[i];
    j = i-1;

    while(j >-1 && eleito < vetor[j]){
      vetor[j+1] = vetor[j];
      j--;
    }
    j++;
    vetor[j] = eleito;
  }
}

int main(){
  int tamanho = 10;
  int vetor[] =  {11, 43, 55, 7, 87, 90, 21, 7, 68, 8};

  printf("vetor antes: ");
  for(int i = 0; i<10; i++){
    printf("%d ",vetor[i] );
  }

  InsertionSort(vetor, tamanho);

  printf("\n\nvetor depois: ");
  for(int i = 0; i<10; i++){
    printf("%d ",vetor[i] );
  }
  printf("\n\n ");
  return 0;
}
