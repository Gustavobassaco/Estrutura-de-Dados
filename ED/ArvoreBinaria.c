#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct NoArvore{
  struct NoArvore *filho_esquerda;
  struct NoArvore *filho_direita;
  int chave;
};

void iniciaArvoreBinaria(struct NoArvore **arvore){
  *arvore = NULL;
}

bool estaVaziaArvore(struct NoArvore **arvore) {
  return(*arvore == NULL);
}


void imprimePreOrdem(struct NoArvore **arvore){
  if(*arvore == NULL)
  return;

  printf("%d  ", (*arvore)->chave);
  imprimePreOrdem(&(*arvore)->filho_esquerda);
  imprimePreOrdem(&(*arvore)->filho_direita);
}

void imprimePosOrdem(struct NoArvore **arvore){
  if(*arvore == NULL)
  return;

  imprimePosOrdem(&(*arvore)->filho_esquerda);
  imprimePosOrdem(&(*arvore)->filho_direita);
  printf("%d  ", (*arvore)->chave);

}

void imprimeEmOrdem(struct NoArvore **arvore){
  if(*arvore == NULL)
  return;

  imprimeEmOrdem(&(*arvore)->filho_esquerda);
  printf("%d  ", (*arvore)->chave);
  imprimeEmOrdem(&(*arvore)->filho_direita);

}

bool inserirArvoreBinaria(struct NoArvore **arvore, int chave){

  if(*arvore == NULL){
    (*arvore) = malloc(sizeof(struct NoArvore));
    (*arvore)->filho_direita = NULL;
    (*arvore)->filho_esquerda = NULL;
    (*arvore)->chave = chave;
    return true;
  }

  if((*arvore)->chave == chave){
    return false;
  }

  if(chave < (*arvore)->chave){
    return (inserirArvoreBinaria(&(*arvore)->filho_esquerda, chave));
  }else {
    return (inserirArvoreBinaria(&(*arvore)->filho_direita, chave));
  }
}


bool pesquisaArvoreBinaria(struct NoArvore **arvore, int chave){

  if(*arvore == NULL)
  return (false);

  if((*arvore)->chave == chave)
  return true;


  if(chave < (*arvore)->chave){
    return (pesquisaArvoreBinaria(&(*arvore)->filho_esquerda, chave));
  } else {
    return (pesquisaArvoreBinaria(&(*arvore)->filho_direita, chave));
  }
}

int maiorValorEsquerda(struct NoArvore** arvore){
  if((*arvore)->filho_direita == NULL )
  return (*arvore)->chave;

  if((*arvore)->filho_direita != NULL)
  maiorValorEsquerda(&(*arvore)->filho_direita);
};

bool removeDaArvore(struct NoArvore **arvore, int chave){
  int retorna;
  if(*arvore == NULL){
    printf("Elemento nao encontrado\n");
    return false;
  }
  if((*arvore)->chave == chave){
    if((*arvore)->filho_direita == NULL && (*arvore)->filho_esquerda == NULL){
      *arvore = (*arvore)->filho_direita;

    }else if((*arvore)->filho_direita == NULL){
      *arvore = (*arvore)->filho_esquerda;

    }else if((*arvore)->filho_esquerda == NULL){
      *arvore = (*arvore)->filho_direita;

    }else {
      int aux = maiorValorEsquerda(&(*arvore)->filho_esquerda);
      printf("\n%d\n", aux);
      removeDaArvore(&(*arvore), aux);
      (*arvore)->chave =  aux;
    }
    return true;
  }

  if(chave < (*arvore)->chave )
  return removeDaArvore(&(*arvore)->filho_esquerda, chave);
  else return removeDaArvore(&(*arvore)->filho_direita, chave);

}

int alturaArvore(struct NoArvore **arvore){
  int e, d;
  if( *arvore ==NULL){
    return -1;
  }
  e = alturaArvore(&(*arvore)->filho_esquerda);
  d = alturaArvore(&(*arvore)->filho_direita);

  if(e>d){
    return e+1;
  }else{
    return d+1;
  }

}

int main(int agrc, char* argv[]) {

  struct NoArvore* raiz;

  iniciaArvoreBinaria(&raiz);

  inserirArvoreBinaria(&raiz, 5);
  inserirArvoreBinaria(&raiz, 1);
  inserirArvoreBinaria(&raiz, 2);
  inserirArvoreBinaria(&raiz, -3);
  inserirArvoreBinaria(&raiz, 4);
  inserirArvoreBinaria(&raiz, 9);
  inserirArvoreBinaria(&raiz, 6);
  inserirArvoreBinaria(&raiz, 7);
  inserirArvoreBinaria(&raiz, 10);


  if(pesquisaArvoreBinaria(&raiz, 2)){
    printf("esta na arvore\n");
  }else printf("Nao esta na arvore\n");


  printf("\nArvore pre ordem: ");
  imprimePreOrdem(&raiz);

  printf("\nArvore pos ordem: ");
  imprimePosOrdem(&raiz);

  printf("\nArvore em ordem: ");
  imprimeEmOrdem(&raiz);

  int altura = alturaArvore(&raiz);
  printf("\nAltura da arvore: %d \n",altura );

  if(removeDaArvore(&raiz, 5)){
    printf("\nRemovido\n");
  }else printf("\n Falha ao remover\n");

  if(removeDaArvore(&raiz, -3)){
    printf("\nRemovido\n");
  }else printf("\n Falha ao remover\n");

  if(removeDaArvore(&raiz, 1)){
    printf("\nRemovido\n");
  }else printf("\n Falha ao remover\n");

  if(removeDaArvore(&raiz, 2)){
    printf("\nRemovido\n");
  }else printf("\n Falha ao remover\n");
  if(removeDaArvore(&raiz, 4)){
    printf("\nRemovido\n");
  }else printf("\n Falha ao remover\n");
  if(removeDaArvore(&raiz, 6)){
    printf("\nRemovido\n");
  }else printf("\n Falha ao remover\n");
  if(removeDaArvore(&raiz,7)){
    printf("\nRemovido\n");
  }else printf("\n Falha ao remover\n");
  if(removeDaArvore(&raiz, 9)){
    printf("\nRemovido\n");
  }else printf("\n Falha ao remover\n");
  if(removeDaArvore(&raiz, 10)){
    printf("\nRemovido\n");
  }else printf("\n Falha ao remover\n");

  printf("\nArvore em ordem: ");
  imprimeEmOrdem(&raiz);
  printf("\nArvore pre ordem: ");
  imprimePreOrdem(&raiz);

  inserirArvoreBinaria(&raiz, 3);
  inserirArvoreBinaria(&raiz, -2);
  inserirArvoreBinaria(&raiz, 27);
  inserirArvoreBinaria(&raiz, 18);

  printf("\nArvore em ordem: ");
  imprimeEmOrdem(&raiz);
  printf("\nArvore pre ordem: ");
  imprimePreOrdem(&raiz);

  return 0;
}
