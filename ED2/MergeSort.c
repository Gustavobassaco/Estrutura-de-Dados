#include <stdio.h>
#include <stdlib.h>

void merge(int vetor[], int inicio, int meio, int final){
  int x, y, tamanho;
  x = inicio;
  y = meio+1;
  tamanho = final - inicio + 1;

  int *temp = (int*) malloc((tamanho)*sizeof(int));

  if(temp != NULL){
    for(int i = 0; i <tamanho; i++){

      if(x <= meio && y <= final){
        if(vetor[x] < vetor[y]){
          temp[i] = vetor[x];
          x++;
        }else{
          temp[i] = vetor[y];
          y++;
        }

      }else{
        if(x <= meio){
          temp[i] = vetor[x];
          x++;
        }else{
          temp[i] = vetor[y];
          y++;
        }
      }
    }
    int j, k;
    for(j = 0, k = inicio; j < tamanho; j++, k++ )
    vetor[k] = temp[j];
  }
  printf("\n\n");
  for(int i = 0; i < 10; i++)
  printf("%d ", vetor[i]);
  free(temp);
}


void mergeSort(int vetor[], int inicio, int final){
  int meio = (inicio + final)/2;
  if(inicio<final){
    mergeSort(vetor, inicio, meio);
    mergeSort(vetor, meio+1, final);
    merge(vetor, inicio, meio, final);
  }
}

int main(int agrc, char* argv[]){
  int tamanho = 10;
  int vetor[] =  {11, 43, 55, 7, 87, 90, 21, 7, 68, 8};

  printf("vetor antes: ");
  for(int i = 0; i<10; i++){
    printf("%d ",vetor[i] );
  }

  mergeSort(vetor, 0,  tamanho-1);

  printf("\n\nvetor depois: ");
  for(int i = 0; i<10; i++){
    printf("%d ",vetor[i] );
  }
  printf("\n\n ");

  return 0;
}
