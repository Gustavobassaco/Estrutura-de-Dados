#include "ordenacao.h"

void bubbleSort(int vetor[], int tamanho, long int *troca, long int *comparacao){
  int continuar = 0;
  int controle=0;
  int aux;
  do{
    for(int i = 0; i<tamanho-1 ; i++){
      if(vetor[i] > vetor[i+1]){
        aux = vetor[i];
        vetor[i]= vetor[i+1];
        vetor[i+1] = aux;
        controle = 0;
        *troca = *troca + 1;

      }
      *comparacao = *comparacao + 1;
    }
    tamanho--;
    if(controle == 1){
      break;
    }
    controle = 1;
    *comparacao = *comparacao + 1;
    continuar++;
  }while(continuar != tamanho -1);

  return;
}

void SelectionSort(int vetor[], int tamanho, long int* troca, long int *comparacao){
  int n = 0;
  int indiceMenor, menor;
  bool controle;

  do{
    indiceMenor = n;

    for(int i = 0 + n; i <tamanho; i++){
      if(vetor[indiceMenor] > vetor[i]){
        indiceMenor = i;
      }
      *comparacao = *comparacao + 1;
    }
    if(indiceMenor !=  n){
      menor = vetor[indiceMenor];
      vetor[indiceMenor] = vetor[n];
      vetor[n] = menor;
      *troca = *troca + 1;
    }
    *comparacao = *comparacao + 1;
    n++;
  }while(n != tamanho-1);
}

void InsertionSort(int vetor[], int tamanho, long int* troca, long int* comparacao){
  int i , j , eleito;

  for(i = 1; i<tamanho;  i++){
    eleito = vetor[i];
    j = i-1;
    *comparacao = *comparacao + 1;

    while(j >-1 && eleito < vetor[j]){
      vetor[j+1] = vetor[j];
      j--;
      *comparacao = *comparacao + 1;
      *troca = *troca + 1;
    }
    j++;
    vetor[j] = eleito;
    *troca = *troca + 1;
  }
}


void merge(int vetor[], int inicio, int meio, int final, long int* troca, long int* comparacao){
  int x, y, tamanho;
  x = inicio;
  y = meio+1;
  tamanho = final - inicio + 1;

  int *temp = (int*) malloc((tamanho)*sizeof(int));

  if(temp != NULL){
    *comparacao = *comparacao + 1;
    for(int i = 0; i <tamanho; i++){
      *comparacao = *comparacao + 1;
      if(x <= meio && y <= final){
        *comparacao = *comparacao + 1;
        if(vetor[x] < vetor[y]){
          *troca = *troca + 1;
          temp[i] = vetor[x];
          x++;
        }else{
          *troca = *troca + 1;
          temp[i] = vetor[y];
          y++;
        }

      }else{
        *comparacao = *comparacao + 1;
        if(x <= meio){
          *troca = *troca + 1;
          temp[i] = vetor[x];
          x++;
        }else{
          *troca = *troca + 1;
          temp[i] = vetor[y];
          y++;
        }
      }
    }
    int j, k;
    for(j = 0, k = inicio; j < tamanho; j++, k++ )
    vetor[k] = temp[j];
    *troca = *troca + 1;
  }
  for(int i = 0; i < 10; i++){
    free(temp);
  }
}


void mergeSort(int vetor[], int inicio, int final, long int* troca, long int* comparacao){
  int meio = (inicio + final)/2;
  if(inicio<final){
    *comparacao = *comparacao + 1;
    mergeSort(vetor, inicio, meio, troca, comparacao);
    mergeSort(vetor, meio+1, final, troca, comparacao);
    merge(vetor, inicio, meio, final, troca, comparacao);
  }
}


int particao(int vetor[], int inicio, int fim, long int* troca, long int* comparacao){
  int pivo = vetor[fim], aux;
  int i = inicio;
  for(int j = inicio; j<fim; j++){
    *comparacao = *comparacao + 1;
    if(vetor[j] <= pivo){
      aux = vetor[i];
      vetor[i] = vetor[j];
      vetor[j] = aux;
      i++;
      *troca = *troca + 1;
    }
  }
  aux = vetor[i];
  vetor[i] = vetor[fim];
  vetor[fim] = aux;
  *troca = *troca + 1;
  return i;
}

void quickSort(int vetor[], int inicio, int fim, long int* troca, long int* comparacao){

  if(inicio < fim){
    *comparacao = *comparacao + 1;
    int p = particao(vetor, inicio, fim, troca, comparacao);
    quickSort(vetor, inicio, p-1, troca, comparacao);
    quickSort(vetor, p+1, fim, troca, comparacao);
  }
}
void criarHeap(int vetor[], int i, int f, long int* troca, long int* comparacao){
  int aux = vetor[i];
  int j = i * 2 + 1;

  while(j <= f){
    *comparacao = *comparacao + 1;
    if(j < f){
      *comparacao = *comparacao + 1;
      if(vetor[j] < vetor[j + 1]){
        j = j + 1;
        *troca = *troca + 1;
      }
    }
    *comparacao = *comparacao + 1;
    if(aux < vetor[j]){
      *troca = *troca + 1;
      vetor[i] = vetor[j];
      i = j;
      j = 2*i + 1;
    }else{
      j = f +1;
    }
  }
  vetor[i] = aux;
  *troca = *troca + 1;
}

void HeapSort(int vetor[], int tamanho, long int* troca, long int*comparacao){
  int i, aux;
  for(i = (tamanho - 1)/2 ; i>=0; i--){
    *comparacao = *comparacao + 1;
    criarHeap(vetor, i, tamanho - 1, troca, comparacao);
  }

  for(i = tamanho - 1; i >= 1; i--){
    *comparacao = *comparacao + 1;
    *troca = *troca + 1;
    aux = vetor[0];
    vetor[0] = vetor[i];
    vetor[i] = aux;
    criarHeap(vetor, 0, i-1, troca, comparacao);
  }
}
