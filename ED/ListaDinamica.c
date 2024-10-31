#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct NoLista{
  struct NoLista *proximo;
  int valor;
};

typedef struct{
  struct NoLista *inicio;
  int tamanho;
}ListaDinamica;

void iniciaListaDinamica(ListaDinamica *lista){
  lista->inicio = NULL;
  lista->tamanho = 0;
}

bool estaVaziaLista(ListaDinamica *lista){
  return (lista->tamanho == 0);
}

void imprimeLista(ListaDinamica *lista){
  printf("\nLista = {");
  for(struct NoLista* aux = lista->inicio; aux != NULL; aux = aux->proximo )
    printf("  %d  ", aux->valor);
  printf("}\n");
}

void entraListaDinamica(ListaDinamica *lista, int valor){
  struct NoLista * aux = (struct NoLista*) malloc(sizeof(struct NoLista*));
  aux->valor = valor;

  if(estaVaziaLista(lista) || valor < lista->inicio->valor){
    aux->proximo = lista->inicio;
    lista->inicio = aux;

  }else {
    struct NoLista* temp = lista->inicio;

    while ((temp->proximo != NULL) && (valor > temp->proximo->valor)) {
      temp = temp->proximo;
    }
    aux->proximo = temp->proximo;
    temp->proximo = aux;

  }
  lista->tamanho++;
}

bool pesquisaListaDinamica(ListaDinamica *lista, int consulta) {

  if(estaVaziaLista(lista))
    return false;

struct NoLista* percorre = lista->inicio;
  while(percorre != NULL && consulta > percorre->valor) {
    percorre = percorre->proximo;
  }
  if(percorre == NULL || percorre->valor > consulta) {
    return false;
  }
  // 3
  return true;
}


int removeDaLista(ListaDinamica *lista, int valor){

  if(!estaVaziaLista(lista) && pesquisaListaDinamica(lista, valor)){
    if(valor == lista->inicio->valor){
      struct NoLista *temp = lista->inicio;
      int retorna;

      retorna = lista->inicio->valor;
      lista->inicio = lista->inicio->proximo;
      lista->tamanho--;
      free(temp);
      return retorna;

    }else{

      struct NoLista *aux = lista->inicio;
      struct NoLista *temp;
      int retorna;

      while(aux->proximo != NULL && valor > aux->valor){
        temp->proximo = aux;
        aux = aux->proximo;
      }

      retorna = aux->valor;
      temp->proximo = aux->proximo;
      free(aux);
      lista->tamanho--;
      return retorna;
    }
  }
}


/*

int main(int agrc, char *argv[]){
  ListaDinamica lista;
  iniciaListaDinamica(&lista);

  for(int i = 1 ; i <11; i++){
  entraListaDinamica(&lista, i);
  imprimeLista(&lista);
  }


if(pesquisaListaDinamica(&lista, 1))
  printf("\nElemento na lista\n");
  else printf("\nElemento fora da lista\n");

  int saiu;
  for(int i = 0; i <12; i++){
    saiu = removeDaLista(&lista, i);
  printf("\n saiu %d", saiu);
  printf("\n tamanho %d", lista.tamanho);
}
  imprimeLista(&lista);

  return 0;
}
*/

ListaDinamica *constroi(int n, int v[]){
    //cria uma lista
    ListaDinamica *lista;
    //inicia a lista
    iniciaListaDinamica(lista);
    if(n == 0){
      return lista;
    }else{
      for (int i = 0; i < n; i++) {
        //insere o valor da posição i de v na lista
        entraListaDinamica(lista, v[i]);
      }
      return lista;
  }
}

int main(){

  ListaDinamica* l;
  int num;
  int *vetor;

 srand(time(NULL));

  iniciaListaDinamica(l);

  printf(" Digite o tamanho desejado para o vetor v: ");
  scanf("%d", &num);

  vetor = (int*) malloc(num*sizeof(int));

  for (int i = 0; i < num; i++) {
    vetor[i] = rand() % 100;
    //v[i]= i;
    //printf(" v[%d]:%d \n", i+1, vetor[i] );
  }


  l = constroi(num, vetor);
  imprimeLista(l);


free(vetor);
  return 0;
}
