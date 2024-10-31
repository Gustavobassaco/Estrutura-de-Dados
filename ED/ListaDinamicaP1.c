#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Nolista{
  struct Nolista* proximo; 
  int valor;
};

typedef struct{
  struct Nolista* inicio;
  int tamanho;
}ListaDinamica;

void iniciaListaDinamica(ListaDinamica* lista){
  lista->inicio = NULL;
  lista->tamanho = 0;
}

bool estaVazia(ListaDinamica *lista){
  return (lista->tamanho == 0);
}

void imprimeLista(ListaDinamica *lista) {
  printf("Lista: (");
  for(struct Nolista* aux = lista->inicio; aux != NULL; aux = aux->proximo)
    printf("  %d", aux->valor);
  printf(")\n");
}

bool percorre(ListaDinamica *lista, int valor){
    if(estaVazia(lista)){
      return false;
    }else{
      struct Nolista *aux = lista->inicio;
      while(aux != NULL && aux->valor <= valor){
          if(aux->valor == valor) return true;
          aux= aux->proximo;
      }
      return false;
    }
}

void entraListaDinamica(ListaDinamica *lista, int valor){
    struct Nolista* aux = lista->inicio;
    struct Nolista* temp = (struct Nolista*) malloc(sizeof(struct Nolista));
    temp->valor = valor;

    if(estaVazia(lista) || valor < lista->inicio->valor){
      temp->proximo = lista->inicio;
      lista->inicio= temp;
    }else{

    while(aux->proximo != NULL && aux->proximo->valor < valor ){
      aux = aux->proximo;
    }
    temp->proximo = aux->proximo;
    aux->proximo = temp;
  }
    lista->tamanho++;
}

int removeDaLista(ListaDinamica *lista, int valor){

  if(!estaVazia(lista) && percorre(lista, valor)){
    if(valor == lista->inicio->valor){
      struct Nolista *temp = lista->inicio;
      int retorna;

      retorna = lista->inicio->valor;
      lista->inicio = lista->inicio->proximo;
      lista->tamanho--;
      free(temp);
      return retorna;

    }else{

      struct Nolista *aux = lista->inicio;
      struct Nolista *destroi;
      int retorna;

      while(aux->proximo != NULL && valor > aux->proximo->valor){
        destroi = aux;
        aux = aux->proximo;
      }

      retorna = aux->proximo->valor;
      destroi = aux->proximo;
      aux->proximo = aux->proximo->proximo;
      free(destroi);
      lista->tamanho--;
      return retorna;
    }
  }
}
/*
ListaDinamica* constroi(int n, int* v){
  ListaDinamica  lista;
//  iniciaListaDinamica(lista);

  if(n == 0){
    lista.tamanho--;
    lista.inicio = NULL;
    return lista;
  }else{

  for(int i = 0; i<n; i++){
    entraListaDinamica(&lista, v[i]);
    imprimeLista(&lista);
  }
  return lista;
  }
}
*/
int main(){
  ListaDinamica lista;
  iniciaListaDinamica(&lista);
  imprimeLista(&lista);
  //iniciaListaDinamica(&lista);
  int saiu;

 for(int i = 0; i<10; i++){
 entraListaDinamica(&lista, i);
 imprimeLista(&lista);
 }
 for(int i = 12; i>=0; i--){
   saiu = removeDaLista(&lista, i);
   imprimeLista(&lista);
   printf("saiu %d\n", saiu );
 }
  return 0;
}
