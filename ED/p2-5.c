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

int menorValor(struct NoArvore** arvore){
  if((*arvore)->filho_esquerda == NULL )
  return (*arvore)->chave;

  if((*arvore)->filho_esquerda != NULL)
  menorValor(&(*arvore)->filho_esquerda);
}

int maiorValor(struct NoArvore** arvore){
  if((*arvore)->filho_direita == NULL )
  return (*arvore)->chave;

  if((*arvore)->filho_direita != NULL)
  maiorValor(&(*arvore)->filho_direita);
}

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
      int aux = maiorValor(&(*arvore)->filho_esquerda);
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

void ordenaVetorTree(int n, int* array){
  struct NoArvore* raiz;
  iniciaArvoreBinaria(&raiz);

  if(n == 0){
    printf("vetor vazio \n");
  }else{
    for(int i  = 0; i < n ; i++){
      inserirArvoreBinaria(&raiz, array[i]);
    }

    printf(" pre ordem :");
    imprimePreOrdem(&raiz);
    printf("\n\n pos ordem :");
    imprimePosOrdem(&raiz);
    printf("\n\n em ordem :");
    imprimeEmOrdem(&raiz);
    printf("\n");
    int altura = alturaArvore(&raiz);
    printf("Altura: %d\n",altura );
  }

int a =  maiorValor(&raiz);
printf("maior %d \n",a );
a = menorValor(&raiz);
printf("menor %d \n",a );
}


int main(int agrc, char* argv[]) {

  int vetor[10] = {3, 65, 77, 87, 34, 45, 25, 98, 3, 120};

  ordenaVetorTree(10, vetor);

  return 0;
}
