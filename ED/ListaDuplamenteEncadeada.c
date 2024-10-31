#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
  int codigo;
}Objeto;

struct NoListaD{
  struct NoListaD *proximo;
  struct NoListaD *anterior;
  Objeto objeto;
};

typedef struct{
  struct NoListaD *inicio;
  int tamanho;
}ListaD;

void iniciaListaD(ListaD *lista){
  lista->inicio = NULL;
  lista->tamanho = 0;
}

bool estaVaziaListaD(ListaD *lista){
  return (lista->tamanho == 0);
}


void imprimeListaC(ListaD *lista){
  printf("\nLista Crescente = (");
  for(struct NoListaD* aux = lista->inicio; aux != NULL; aux = aux->proximo )
    printf("   %d", aux->objeto.codigo);

  printf("}\n");
}

void imprimeListaD(ListaD *lista){
  printf("Lista Decrescente: (");
  if(lista->inicio != NULL){
  struct NoListaD* aux = lista->inicio;
  for( aux ; aux->proximo != NULL; aux = aux->proximo );
  for( aux ; aux != NULL; aux = aux->anterior)
  printf("   %d", aux->objeto.codigo);
  }
  printf(")\n");

}

bool pesquisaListaD(ListaD *lista, int consulta) {

  if(estaVaziaListaD(lista))
    return false;

struct NoListaD* percorre = lista->inicio;
  while(percorre != NULL && consulta > percorre->objeto.codigo) {
    percorre = percorre->proximo;
  }
  if(percorre == NULL || percorre->objeto.codigo > consulta) {
    return false;
  }
    return true;
}

void entraListaD(ListaD *lista, Objeto chave){
  struct NoListaD * aux = (struct NoListaD*) malloc(sizeof(struct NoListaD));
  aux->objeto = chave;

  if(estaVaziaListaD(lista) || chave.codigo < lista->inicio->objeto.codigo){
    aux->proximo = lista->inicio;
    aux->anterior = NULL;

    if(!estaVaziaListaD(lista))
    lista->inicio->anterior = aux;

    lista->inicio = aux;

  }else {
    struct NoListaD* temp = lista->inicio;

    while ((temp->proximo != NULL) && (chave.codigo > temp->proximo->objeto.codigo)) {
      temp = temp->proximo;
    }
    aux->proximo = temp->proximo;
    aux->anterior = temp;

    if(aux->proximo != NULL)
    aux->proximo->anterior = aux;

    temp->proximo = aux;
  }
  lista->tamanho++;
}

int removeDaLista(ListaD *lista, int valor){

  if(!estaVaziaListaD(lista) && pesquisaListaD(lista, valor)){
    int retorna;

    if(valor == lista->inicio->objeto.codigo){
      struct NoListaD *temp = lista->inicio;

      retorna = lista->inicio->objeto.codigo;

      lista->inicio = lista->inicio->proximo;

      if(lista->inicio != NULL)
      lista->inicio->anterior = NULL;


      lista->tamanho--;
      free(temp);
      return retorna;

    }else{

      struct NoListaD *aux = lista->inicio;
      struct NoListaD *temp;

      while(aux->proximo != NULL && valor > aux->objeto.codigo){
        temp = aux;
        aux = aux->proximo;
      }

      retorna = aux->objeto.codigo;


      if(aux->proximo != NULL)
      aux->proximo->anterior = temp;

      if(aux->proximo != NULL){
      temp->proximo = aux->proximo;
      }else temp->proximo = NULL;

      free(aux);
      lista->tamanho--;
      return retorna;
    }
  }
}


int main(){

  ListaD lista;
  iniciaListaD(&lista);
  Objeto objeto;
  int saiu;

    for(int i = 2; i<257; i*=-2){
    objeto.codigo = i;
    entraListaD(&lista, objeto);
    imprimeListaC(&lista);
    imprimeListaD(&lista);
    }
    printf("\n");
    saiu = removeDaLista(&lista, 32);
    printf("saiu: %d \n",saiu );
    saiu = removeDaLista(&lista, 2);
    printf("saiu: %d \n",saiu );
    saiu = removeDaLista(&lista, 128);
    printf("saiu: %d \n",saiu );
    saiu = removeDaLista(&lista, -256);
    printf("saiu: %d \n",saiu );
    saiu = removeDaLista(&lista, 128);
    printf("saiu: %d \n",saiu );

    imprimeListaC(&lista);
    imprimeListaD(&lista);

    saiu = removeDaLista(&lista, -64);
    printf("saiu: %d \n",saiu );
    saiu = removeDaLista(&lista, -16);
    printf("saiu: %d \n",saiu );
    saiu = removeDaLista(&lista, -4);
    printf("saiu: %d \n",saiu );

    imprimeListaC(&lista);
   imprimeListaD(&lista);


    saiu = removeDaLista(&lista, 8);
    printf("saiuaaaaaa: %d \n",saiu );

    imprimeListaC(&lista);
    imprimeListaD(&lista);

  for(int i = 1; i<6; i++){
    objeto.codigo = i;
    entraListaD(&lista, objeto);
    imprimeListaC(&lista);
    imprimeListaD(&lista);
    }
    saiu = removeDaLista(&lista, -1);
    printf("saiu: %d \n",saiu );
    saiu = removeDaLista(&lista, 1);
    printf("saiu: %d \n",saiu );
    saiu = removeDaLista(&lista, 2);
    printf("saiu: %d \n",saiu );

    imprimeListaC(&lista);
    imprimeListaD(&lista);

    saiu = removeDaLista(&lista, 3);
    printf("saiu: %d \n",saiu );
    saiu = removeDaLista(&lista, 4);
    printf("saiu: %d \n",saiu );
    saiu = removeDaLista(&lista, 5);
    printf("saiu: %d \n",saiu );

imprimeListaC(&lista);
imprimeListaD(&lista);

for(int i = 1; i<6; i++){
  objeto.codigo = i;
  entraListaD(&lista, objeto);
  imprimeListaC(&lista);
  imprimeListaD(&lista);
  }


    return 0;
}
