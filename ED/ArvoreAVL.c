#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct NoAVL{
  struct NoAVL* direita;
  struct NoAVL* esquerda;
  int altura;
  int chave;
};

void iniciaArvoreAVL(struct NoAVL **arvore){
  *arvore = NULL;
}


int alturaAVL(struct NoAVL **arvore) {
  if (*arvore == NULL)
  return 0; // altura da árvore vazia
  else return (*arvore)->altura;
}

int atualizaAltura(struct NoAVL *esquerda, struct NoAVL *direita){

  int he = alturaAVL(&esquerda);
  int hd = alturaAVL(&direita);
  if (he > hd)
  return he + 1;
  else
  return hd + 1;
}

void rotacaoSimplesEsquerda(struct NoAVL **arvore){
  struct NoAVL *u = (*arvore)->direita;

  (*arvore)->direita = u->esquerda;
  u->esquerda = (*arvore);

  (*arvore)->altura = atualizaAltura((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);
  (*arvore)=u;
}

void rotacaoSimplesDireita(struct NoAVL **arvore){
  struct NoAVL *u = (*arvore)->esquerda;

  (*arvore)->esquerda = u->direita;
  u->direita = (*arvore);

  (*arvore)->altura = atualizaAltura((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);
  (*arvore)=u;
}

void rotacaoDuplaEsquerda(struct NoAVL **arvore){
  struct NoAVL *u = (*arvore)->direita;
  struct NoAVL *v = u->esquerda;

  (*arvore)->direita = v->esquerda;
  u->esquerda = v->direita;
  v->direita = u;
  v->esquerda = (*arvore);

  (*arvore)->altura = atualizaAltura((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);
  v->altura = atualizaAltura(v->esquerda, v->direita);

  (*arvore)= v;
}

void rotacaoDuplaDireita(struct NoAVL **arvore){
  struct NoAVL *u = (*arvore)->esquerda;
  struct NoAVL *v = u->direita;

  u->direita = v->esquerda;
  v->esquerda = u;
  (*arvore)->esquerda = v->direita;
  v->direita = (*arvore);

  (*arvore)->altura = atualizaAltura((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);
  v->altura = atualizaAltura(v->esquerda, v->direita);

  (*arvore)= v;
}

void balanceiaAVL(struct NoAVL **arvore){

  int he =  alturaAVL(&(*arvore)->esquerda);
  int hd = alturaAVL(&(*arvore)->direita);
  int h = hd - he;
  struct NoAVL *temp;

  if(h < 0 ){
    temp = (*arvore)->esquerda;
    he = alturaAVL(&temp->esquerda);
    hd = alturaAVL(&temp->direita);
    h = hd - he;

    if(h < 0){
      printf("Rotacao simpes direita: %d\n", (*arvore)->chave);
      rotacaoSimplesDireita(&(*arvore));
    }else{
      printf("Rotacao dupla direita: %d\n", (*arvore)->chave);
      rotacaoDuplaDireita(&(*arvore));
    }
  }else{
    temp = (*arvore)->direita;
    he = alturaAVL(&temp->esquerda);
    hd = alturaAVL(&temp->direita);
    h = hd - he;

    if(h>0){
      printf("Rotacao simpes esquerda: %d\n", (*arvore)->chave);
      rotacaoSimplesEsquerda(&(*arvore));
    }else{
      printf("Rotacao dupla esquerda: %d\n", (*arvore)->chave);
      rotacaoDuplaEsquerda(&(*arvore));
    }
  }
}


void imprimePosOrdem(struct NoAVL **arvore){
  if(*arvore == NULL)
  return;
  int he =  alturaAVL(&(*arvore)->esquerda);
  int hd = alturaAVL(&(*arvore)->direita);
  int h = hd - he;

  imprimePosOrdem(&(*arvore)->esquerda);
  imprimePosOrdem(&(*arvore)->direita);
  printf("%d(%d)  ", (*arvore)->chave, h);

}
void imprimePreOrdem(struct NoAVL **arvore){
  if(*arvore == NULL)
  return;

  int he =  alturaAVL(&(*arvore)->esquerda);
  int hd = alturaAVL(&(*arvore)->direita);
  int h = hd - he;
  printf("%d(%d)  ", (*arvore)->chave, h);
  imprimePreOrdem(&(*arvore)->esquerda);
  imprimePreOrdem(&(*arvore)->direita);

}
void imprimeEmOrdem(struct NoAVL **arvore){
  if(*arvore == NULL)
  return;

  int he =  alturaAVL(&(*arvore)->esquerda);
  int hd = alturaAVL(&(*arvore)->direita);
  int h = hd - he;
  imprimeEmOrdem(&(*arvore)->esquerda);
  printf("%d(%d)  ", (*arvore)->chave, h);
  imprimeEmOrdem(&(*arvore)->direita);

}



bool pesquisaAVL(struct NoAVL **arvore, int chave){

  if(*arvore == NULL)
  return (false);

  if((*arvore)->chave == chave)
  return true;


  if(chave < (*arvore)->chave)
  return (pesquisaAVL(&(*arvore)->esquerda, chave));
  else
  return (pesquisaAVL(&(*arvore)->direita, chave));
}

int maiorValorEsquerda(struct NoAVL** arvore){
  if((*arvore)->direita == NULL )
  return (*arvore)->chave;

  if((*arvore)->direita != NULL)
  maiorValorEsquerda(&(*arvore)->direita);
}

bool removeDaArvore(struct NoAVL **arvore, int chave){

  bool boleano;

  if(*arvore == NULL){
    return false;
  }
  if((*arvore)->chave == chave){

    if((*arvore)->direita == NULL && (*arvore)->esquerda == NULL){
      *arvore = (*arvore)->direita;

    }else if((*arvore)->direita == NULL){
      *arvore = (*arvore)->esquerda;

    }else if((*arvore)->esquerda == NULL){
      *arvore = (*arvore)->direita;

    }else {
      int aux = maiorValorEsquerda(&(*arvore)->esquerda);
      removeDaArvore(&(*arvore), aux);
      (*arvore)->chave =  aux;
    }
    return true;
  }

  if(chave < (*arvore)->chave )
  boleano =  removeDaArvore(&(*arvore)->esquerda, chave);
  else
  boleano = removeDaArvore(&(*arvore)->direita, chave);

  if(boleano == false)
  return false;

  int he =  alturaAVL(&(*arvore)->esquerda);
  int hd =  alturaAVL(&(*arvore)->direita);
  int h = hd - he;

  if(h > 1 || h < -1){
    printf("Balanceia\n");
    balanceiaAVL(&(*arvore));
  }

  (*arvore)->altura = atualizaAltura((*arvore)->esquerda, (*arvore)->direita);

  he =  alturaAVL(&(*arvore)->esquerda);
  hd =  alturaAVL(&(*arvore)->direita);
  h = hd - he;

  return(true);
}


bool insereAVL(struct NoAVL **arvore, int chave){

  bool boleano;
  if(*arvore == NULL){
    (*arvore) = malloc(sizeof(struct NoAVL));
    (*arvore)->direita = NULL;
    (*arvore)->esquerda = NULL;
    (*arvore)->chave = chave;
    (*arvore)->altura = 1;
    return true;
  }

  if((*arvore)->chave == chave){
    return false;
  }

  if(chave < (*arvore)->chave){
    boleano = (insereAVL(&(*arvore)->esquerda, chave));
  }else {
    boleano = (insereAVL(&(*arvore)->direita, chave));
  }

  if(!boleano)
  return (false);

  int he =  alturaAVL(&(*arvore)->esquerda);
  int hd =  alturaAVL(&(*arvore)->direita);
  int h = hd - he;

  if(h > 1 || h < -1){
    printf("Balanceia\n");
    balanceiaAVL(&(*arvore));

  }
  (*arvore)->altura = atualizaAltura((*arvore)->esquerda, (*arvore)->direita);
  return(true);
}

void printEmNivel(struct NoAVL* arvore, int level)

{
  if (arvore == NULL)
  return;
  if (level == 1){
    int he =  alturaAVL(&(arvore)->esquerda);
    int hd = alturaAVL(&(arvore)->direita);
    int h = hd - he;
    printf("%d(%d)  ", arvore->chave, h);
  }else if (level > 1)
  {
    printEmNivel(arvore->esquerda, level-1);
    printEmNivel(arvore->direita, level-1);
  }
}

void imprimeEmNivel(struct NoAVL* arvore)
{
  int h = alturaAVL(&arvore);

  for (int i=1; i<=h; i++){
    printEmNivel(arvore, i);
    printf("\n");
  }
}

int main(int argc, char *argv[]){

  struct NoAVL *raiz;

  iniciaArvoreAVL(&raiz);
  imprimePreOrdem(&raiz);

  printf("inserindo 20\n");
  insereAVL(&raiz, 20);
  printf("\nPos ordem: (");
  imprimePosOrdem(&raiz);
  printf(")\n");

  printf("inserindo 15\n");
  insereAVL(&raiz, 15);
  printf("\nPos ordem: (");
  imprimePosOrdem(&raiz);
  printf(")\n");

  printf("inserindo 25\n");
  insereAVL(&raiz, 25);
  printf("\nPos ordem: (");
  imprimePosOrdem(&raiz);
  printf(")\n");

  printf("inserindo 10\n");
  insereAVL(&raiz, 10);
  printf("\nPos ordem: (");
  imprimePosOrdem(&raiz);
  printf(")\n");

  printf("inserindo 30\n");
  insereAVL(&raiz, 30);
  printf("\nPos ordem: (");
  imprimePosOrdem(&raiz);
  printf(")\n");

  printf("inserindo 24\n");
  insereAVL(&raiz,24);
  printf("\nPos ordem: (");
  imprimePosOrdem(&raiz);
  printf(")\n");

  printf("inserindo 17\n");
  insereAVL(&raiz, 17);
  printf("\nPos ordem: (");
  imprimePosOrdem(&raiz);
  printf(")\n");

  printf("inserindo 12\n");
  insereAVL(&raiz,12);
  printf("\nPos ordem: (");
  imprimePosOrdem(&raiz);
  printf(")\n");


  printf("inserindo 5\n");
  insereAVL(&raiz,5);
  printf("\nPos ordem: (");
  imprimePosOrdem(&raiz);
  printf(")\n");


  printf("inserindo 3\n");
  insereAVL(&raiz, 3);
  printf("Pos ordem: (");
  imprimePosOrdem(&raiz); 
  printf("\nEm ordem: (");
  imprimeEmOrdem(&raiz);
  printf(")\n----------------------------------------------------------- \n");

  imprimeEmNivel(raiz);
  printf("\n");
  /*
  if(removeDaArvore(&raiz, 60)){
  printf("\nRemovido 60\n");
}else printf("\n Falha ao remover 60\n");
printf("Pos ordem: (");
imprimePosOrdem(&raiz);
printf(")\n");
printf("Pre ordem: (");
imprimePreOrdem(&raiz);
printf(")\n");

if(removeDaArvore(&raiz, 50)){
printf("\nRemovido 50\n");
}else printf("\n Falha ao remover 50\n");
printf("Pos ordem: (");
imprimePosOrdem(&raiz);
printf(")\n");
printf("Pre ordem: (");
imprimePreOrdem(&raiz);
printf(")\n");

if(removeDaArvore(&raiz, 40)){
printf("\nRemovido 40\n");
}else printf("\n Falha ao remover 40\n");
printf("Pos ordem: (");
imprimePosOrdem(&raiz);
printf(")\n");
printf("Pre ordem: (");
imprimePreOrdem(&raiz);
printf(")\n");

if(removeDaArvore(&raiz,30)){
printf("\nRemovido 30\n");
}else printf("\n Falha ao remover 30\n");
printf("Pos ordem: (");
imprimePosOrdem(&raiz);
printf(")\n");
printf("Pre ordem: (");
imprimePreOrdem(&raiz);
printf(")\n");

if(removeDaArvore(&raiz, 10)){
printf("\nRemovido 10\n");
}else printf("\n Falha ao remover 10\n");
printf("Pos ordem: (");
imprimePosOrdem(&raiz);
printf(")\n");
printf("Pre ordem: (");
imprimePreOrdem(&raiz);
printf(")\n -------------------------- \n");



imprimeEmNivel(raiz);
printf("\n");
*/
int a;
a = maiorValorEsquerda(&raiz);

printf("maior %d \n", a);

//a = menorValorDireita(&raiz);
printf("menor %d \n", a);

return 0;
}
