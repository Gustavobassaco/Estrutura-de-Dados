#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void SelectionSort(int vetor[], int tamanho){
  int n = 0;
  int indiceMenor, menor;
  bool controle;

  do{
    indiceMenor = n;

      for(int i = 0 + n; i <tamanho; i++){
        if(vetor[indiceMenor] > vetor[i]){
          indiceMenor = i;
        }
      }
      if(indiceMenor !=  n){
        menor = vetor[indiceMenor];
        vetor[indiceMenor] = vetor[n];
        vetor[n] = menor;
      }
    n++;
  }while(n != tamanho-1);
}

int main(){
  int tamanho = 10;
  int vetor[] =  {1, 33, 5, 705, 2, 50, 89, 5, 76, 89};

  printf("vetor antes: ");
  for(int i = 0; i<10; i++){
    printf("%d ",vetor[i] );
  }

  SelectionSort(vetor, tamanho);

  printf("\n\nvetor depois: ");
  for(int i = 0; i<10; i++){
    printf("%d ",vetor[i] );
  }
  printf("\n\n" );
  return 0;
}
