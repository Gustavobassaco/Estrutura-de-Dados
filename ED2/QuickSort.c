#include <stdio.h>
#include <stdlib.h>

int particao(int vetor[], int inicio, int fim){
  int pivo = vetor[fim], aux;
  int i = inicio;
  //printf("\n aaa \n");
  for(int j = inicio; j<fim; j++){
  //  printf("%d  ", vetor[j]);
    if(vetor[j] <= pivo){
      aux = vetor[i];
      vetor[i] = vetor[j];
      vetor[j] = aux;
      i++;
    }
  }
  aux = vetor[i];
  vetor[i] = vetor[fim];
  vetor[fim] = aux;

  return i;
}

void quickSort(int vetor[], int inicio, int fim){

  if(inicio < fim){
    int p = particao(vetor, inicio, fim);
    quickSort(vetor, inicio, p-1);
    quickSort(vetor, p+1, fim);
  }
}


int main(int argc, char* argv[]){

  int tamanho = 10;
  int vetor[] =  {11, 43, 55, 7, 87, 90, 21, 7, 68, 8};

  printf("vetor antes: ");
  for(int i = 0; i<10; i++){
    printf("%d ",vetor[i] );
  }

  quickSort(vetor, 0,  tamanho-1);

  printf("\n\nvetor depois: ");
  for(int i = 0; i<10; i++){
    printf("%d ",vetor[i] );
  }
  printf("\n\n ");

  return 0;
}
