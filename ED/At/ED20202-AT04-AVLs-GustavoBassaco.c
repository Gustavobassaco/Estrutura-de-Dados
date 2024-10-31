#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <io.h>

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
      rotacaoSimplesDireita(&(*arvore));
    }else{
      rotacaoDuplaDireita(&(*arvore));
    }
  }else{
    temp = (*arvore)->direita;
    he = alturaAVL(&temp->esquerda);
    hd = alturaAVL(&temp->direita);
    h = hd - he;

    if(h>0){
      rotacaoSimplesEsquerda(&(*arvore));
    }else{
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

}
void imprimePreOrdem(struct NoAVL **arvore){
  if(*arvore == NULL)
  return;

  int he =  alturaAVL(&(*arvore)->esquerda);
  int hd = alturaAVL(&(*arvore)->direita);
  int h = hd - he;
  imprimePreOrdem(&(*arvore)->esquerda);
  imprimePreOrdem(&(*arvore)->direita);

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

int menorValorDireita(struct NoAVL** arvore){
  if((*arvore)->esquerda == NULL )
  return (*arvore)->chave;

  if((*arvore)->esquerda != NULL)
  menorValorDireita(&(*arvore)->esquerda);
}

bool removeDaArvore(struct NoAVL **arvore, int chave, char escolha){
  int aux;
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
      if(escolha == 'e' || escolha == 'E'){
        aux = maiorValorEsquerda(&(*arvore)->esquerda);
      }else{
        aux = menorValorDireita(&(*arvore)->direita);
      }
      removeDaArvore(&(*arvore), aux, escolha);
      (*arvore)->chave =  aux;
    }
    return true;
  }

  if(chave < (*arvore)->chave )
  boleano = removeDaArvore(&(*arvore)->esquerda, chave, escolha);
  else
  boleano = removeDaArvore(&(*arvore)->direita, chave, escolha);

  if(boleano == false)
  return false;

  int he =  alturaAVL(&(*arvore)->esquerda);
  int hd =  alturaAVL(&(*arvore)->direita);
  int h = hd - he;

  if(h > 1 || h < -1){
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
    balanceiaAVL(&(*arvore));
  }
  (*arvore)->altura = atualizaAltura((*arvore)->esquerda, (*arvore)->direita);
  return(true);
}

void printEmNivel(struct NoAVL* arvore, int level, FILE* saida)

{
  if (arvore == NULL)
  return;
  if (level == 1){
    int he =  alturaAVL(&(arvore)->esquerda);
    int hd = alturaAVL(&(arvore)->direita);
    int h = hd - he;
    fprintf(saida, "%d(%d)  ", arvore->chave, h);
  }else if (level > 1)
  {
    printEmNivel(arvore->esquerda, level-1, saida);
    printEmNivel(arvore->direita, level-1, saida);
  }
}

void imprimeEmNivel(struct NoAVL* arvore, FILE* saida)
{
  int h = alturaAVL(&arvore);

  for (int i=1; i<=h; i++){
    printEmNivel(arvore, i, saida);
    fprintf(saida,"\n");
  }
}

void destroiAVL(struct NoAVL **arvore) {
  if((*arvore) != NULL ) {
    destroiAVL( &(*arvore)->esquerda);
    destroiAVL( &(*arvore)->direita);
    free(*arvore);
    *arvore = NULL;
  }
}

void destroi(struct NoAVL **arvore, FILE* entrada,FILE* saida){
  destroiAVL(arvore);
  fclose(entrada);
  fclose(saida);
}

int main(int argc, char *argv[]){

  if(argc != 3){
    printf("Warning: O programa deve receber 3 arquivos de entrada\n");
    exit(1);
  }

  struct NoAVL *raiz;
  iniciaArvoreAVL(&raiz);
  FILE *entrada, *saida;

  entrada = fopen(argv[1], "r");
  if(entrada == NULL){
    printf("Erro na abertura do arquivo de entrada\n");
    exit(1);
  }

  saida = fopen(argv[2], "w");
  if(saida == NULL){
    printf("Erro na abertura do arquivo de saida\n");
    fclose(entrada);
  }

  // salva o tamanho do arquivo
  long tamanho_arquivo = filelength( fileno( entrada ) );

  if ( tamanho_arquivo == 0L ){ // teste para saber se o tamanho do arquivo é zero
    printf("\nArquivo vazio \n");
    destroi(&raiz, entrada, saida);
    exit(1);
  }

  char string[200], *sub;
  int chave;

  fgets(string, 199, entrada);
  int tam = strlen(string);



  for(int i = 0; i < tam; i++){
    // se houver letra ou pontuação ou digitos: fecha
    if(isalpha(string[i])){
      printf("Arquivo fora do padrao\n");
      destroi(&raiz, entrada, saida);
      exit(1);
    }//if
  }//for

  sub = strtok(string, " ,");

  while(sub != NULL){
    chave = atoi(sub);
    insereAVL(&raiz, chave);
    sub = strtok(NULL, " ,");
  }

  fprintf(saida, "[*]antes\n");
  imprimeEmNivel(raiz, saida);
  fprintf(saida, "\n");

  fgets(string, 199, entrada);
  char escolha = getc(entrada);

  //verifica a terceira linha
  if(escolha != 'e' && escolha != 'd' && escolha != 'E' && escolha != 'D' ){
    printf("letra invlida\n");
    destroi(&raiz, entrada, saida);
  }

  //volta pra segunda linha
  fseek(entrada, tam+1, SEEK_SET);
  fgets(string, 199, entrada);

   tam = strlen(string);

  for(int i = 0; i < tam; i++){
    // se houver letra ou pontuação ou digitos: fecha
    if(isalpha(string[i])){
      printf("Arquivo fora do padrao\n");
      destroi(&raiz, entrada, saida);
      exit(1);
    }//if
  }//for


  sub = strtok(string, " ,");

  while(sub != NULL){
    chave = atoi(sub);
    removeDaArvore(&raiz, chave, escolha);
    sub = strtok(NULL, " ,");
  }

  fprintf(saida, "[*]depois\n");
  imprimeEmNivel(raiz, saida);

  destroi(&raiz, entrada, saida);

  return 0;
}
