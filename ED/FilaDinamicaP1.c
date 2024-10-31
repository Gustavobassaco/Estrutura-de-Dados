#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Nofila{
  int valor;
  struct Nofila *proximo;
};

typedef struct{
  struct Nofila* final;
  struct Nofila* inicio;
  int tamanho;
}FilaDinamica;

void iniciaFila(FilaDinamica *fila){
  fila->final = NULL;
  fila->inicio = NULL;
  fila->tamanho = 0;
}

bool estaVazia(FilaDinamica *fila){
  return (fila->tamanho == 0);
}


void imprimeFila(FilaDinamica *fila){
   printf("\n Fila = (");
   for(struct Nofila* temp = fila->inicio; temp != NULL; temp = temp->proximo)
     printf("  %d,", temp->valor );
   printf(")\n");
}

void entraFila(FilaDinamica *fila, int valor){
  struct Nofila* aux = (struct Nofila*) malloc(sizeof(struct Nofila));
  aux->valor = valor;
  aux->proximo = NULL;

  if(estaVazia(fila)){
    fila->final = aux;
    fila->inicio = aux;

  }else{
    fila->final->proximo = aux;
    fila->final = fila->final->proximo;
  }
  fila->tamanho++;
}

int tamanhoFila(FilaDinamica *fila){
  return fila->tamanho;
}

int saiFila(FilaDinamica *fila){
  int retorno;

  if(estaVazia(fila)){
    printf("Erro: Esta Vazia.\n");
    return -999;
  } else {
    struct Nofila *aux = fila->inicio;
    retorno = aux->valor;

    fila->inicio = fila->inicio->proximo;
    fila->tamanho--;
    free(aux);
    return retorno;
  }
}

void inverteFilas(FilaDinamica *fila1, FilaDinamica *fila2){
  //guarda os valores dos tamanhos de cada fila
  //cria uma variavel com o tamanho da fila1
  int tamanho1 = fila1->tamanho;
  //cria uma variavel com o tamanho da fila2
  int tamanho2 = fila2->tamanho;

  //laço de repetição que passa por cada elemento da fila 2
  for(tamanho2; tamanho2>0 ; tamanho2--){
    //cada elemento da fila2 ira sair da fila2 e realocado na fila1
    entraFila(fila1, saiFila(fila2));
  }
  for(tamanho1; tamanho1>0; tamanho1--){
    //todos os elemento originais da fila1 agora serão realocados na fila2
    entraFila(fila2, saiFila(fila1));
  }
}

int main(int argc, char *argv[]){
  FilaDinamica fila1, fila2;
  iniciaFila(&fila1);
  iniciaFila(&fila2);

  for (int i = 0; i<10; i++){
    entraFila(&fila1, i);
  }
  imprimeFila(&fila1);

  for (int i = 10; i>2; i--){
    entraFila(&fila2, i);
  }
  imprimeFila(&fila2);

  inverteFilas(&fila1, &fila2);
  printf("\n\n");
  imprimeFila(&fila1);
  imprimeFila(&fila2);

  return 0;
}
