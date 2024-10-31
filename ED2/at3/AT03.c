/**
* @file AT03.c
* @author Gustavo Rodrigues Bassaco
* @author Rodrigo Oliveira Badega
* @date 04 Agosto 2021
* @brief Implementacao atividade 3
* Realiza as tarefas pedidas pelo Sr Astolfo
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <io.h>

//Funções para Numeros

struct NoAVL_N{
  struct NoAVL_N* direita;
  struct NoAVL_N* esquerda;
  int altura;
  int id;
  int rrn;
};//NoAVL_N

void iniciaArvoreAVL_N(struct NoAVL_N **arvore){
  *arvore = NULL;
}//iniciaArvoreAVL_N


int alturaAVL_N(struct NoAVL_N **arvore){
  if (*arvore == NULL)
  return 0; // altura da árvore vazia
  else return (*arvore)->altura;
}//alturaAVL_N

void imprimeEmOrdem_N(struct NoAVL_N **arvore, FILE* arquivo){
  if(*arvore == NULL)//criterio de parada da recursao=> se nó for nulo, retorna
  return;

  imprimeEmOrdem_N(&(*arvore)->esquerda, arquivo);//recursao pra subarvore esquerda
  fprintf(arquivo,"%4d   %d\n", (*arvore)->id, (*arvore)->rrn);//printa valor no arquivo
  imprimeEmOrdem_N(&(*arvore)->direita, arquivo);//recursao pra subarvore direita

}//imprimeEmOrdem_N

int atualizaAltura_AVL_N(struct NoAVL_N *esquerda, struct NoAVL_N *direita){

  int he = alturaAVL_N(&esquerda);//guarda altura subarvore esquerda
  int hd = alturaAVL_N(&direita);//guarda altura subarvore direita
  if (he > hd)//se sub esquerda > sub direita
  return he + 1;//aumenta altura sub esquerda em 1
  else
  return hd + 1;//aumenta altura sub direita em 1
}//atualizaAltura_AVL_N

void rotacaoSimplesEsquerda_N(struct NoAVL_N **arvore){
  struct NoAVL_N *u = (*arvore)->direita;//u recebe subarvore direita do no

  (*arvore)->direita = u->esquerda;//subarvore direita do no recebe subarvore esquerda do u
  u->esquerda = (*arvore);//subarvore esquerda do u recebe no

  //atualiza alturas
  (*arvore)->altura = atualizaAltura_AVL_N((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_N(u->esquerda, u->direita);
  //no recebe u
  (*arvore)=u;
}//rotacaoSimplesEsquerda_N

void rotacaoSimplesDireita_N(struct NoAVL_N **arvore){
  struct NoAVL_N *u = (*arvore)->esquerda;//u recebe subarvore esquerda do no

  (*arvore)->esquerda = u->direita;//subarvore esquerda do no recebe subarvore direita do u
  u->direita = (*arvore);//subarvore direita de u recebe no

  //atualiza alturas
  (*arvore)->altura = atualizaAltura_AVL_N((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_N(u->esquerda, u->direita);
  //no recebe u
  (*arvore)=u;
}//rotacaoSimplesDireita_N

void rotacaoDuplaEsquerda_N(struct NoAVL_N **arvore){
  struct NoAVL_N *u = (*arvore)->direita;//u recebe subarvore direita de no
  struct NoAVL_N *v = u->esquerda;//v recebe subarvore esquerda de u

  (*arvore)->direita = v->esquerda;//subarvore direita de no recebe subarvore esquerda de v
  u->esquerda = v->direita;//subarvore esquerda de u recebe subarvore direita de v
  v->direita = u;//subarvore direita de v recebe u
  v->esquerda = (*arvore);//subarvore esquerda de v recebe no

  //atualiza alturas
  (*arvore)->altura = atualizaAltura_AVL_N((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_N(u->esquerda, u->direita);
  v->altura = atualizaAltura_AVL_N(v->esquerda, v->direita);
  //no recebe v
  (*arvore)= v;
}//rotacaoDuplaEsquerda_N

void rotacaoDuplaDireita_N(struct NoAVL_N **arvore){
  struct NoAVL_N *u = (*arvore)->esquerda;//u recebe subarvore esquerda do no
  struct NoAVL_N *v = u->direita;//v recebe subarvore direita de u

  u->direita = v->esquerda;//subarvore direita de u recebe subarvore esquerda de v
  v->esquerda = u;//subarvore esquerda de v recebe u
  (*arvore)->esquerda = v->direita;//subarvore esquerda de no recebe subarvore direita de v
  v->direita = (*arvore);//subarvore direita de v recebe no

  //atualiza alturas
  (*arvore)->altura = atualizaAltura_AVL_N((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_N(u->esquerda, u->direita);
  v->altura = atualizaAltura_AVL_N(v->esquerda, v->direita);
  //no recebe v
  (*arvore)= v;
}//rotacaoDuplaDireita_N

void balanceiaAVL_N(struct NoAVL_N **arvore){

  int he =  alturaAVL_N(&(*arvore)->esquerda);//calcula altura da subarvore esquerda
  int hd = alturaAVL_N(&(*arvore)->direita);//calcula altura da subarvore direita
  int h = hd - he;//calcula diferenca de alturas
  struct NoAVL_N *temp;

  if(h < 0 ){//se diferenca menor que 0
    temp = (*arvore)->esquerda;//temp recebe subarvore esquerda do no
    he = alturaAVL_N(&temp->esquerda);//calcula altura da subarvore esquerda de temp
    hd = alturaAVL_N(&temp->direita);//calcula altura da subarvore direita de temp
    h = hd - he;//calcula nova diferenca

    if(h < 0){//se nova diferenca for maior que 0
      rotacaoSimplesDireita_N(&(*arvore));
    }else{//se nova diferenca for menor que 0
      rotacaoDuplaDireita_N(&(*arvore));
    }
  }else{//se diferenca maior que 0
    temp = (*arvore)->direita;//temp recebe subarvore direita do no
    he = alturaAVL_N(&temp->esquerda);//calcula altura da subarvore esquerda de temp
    hd = alturaAVL_N(&temp->direita);//calcula altura da subarvore direita de temp
    h = hd - he;//calcula nova diferenca

    if(h>0){//se nova diferenca maior que 0
      rotacaoSimplesEsquerda_N(&(*arvore));
    }else{//se nova diferenca menor que 0
      rotacaoDuplaEsquerda_N(&(*arvore));
    }
  }
}//balanceiaAVL_N

int maiorValorEsquerda_N(struct NoAVL_N** arvore){
  if((*arvore)->direita == NULL )//se subarvore direita do no for nula
  return (*arvore)->id;//retorna id do no

  if((*arvore)->direita != NULL)//se nao for
  maiorValorEsquerda_N(&(*arvore)->direita);//recursao
}//maiorValorEsquerda_N

bool insereAVL_N(struct NoAVL_N **arvore, int id, int rrn){

  bool boleano;
  if(*arvore == NULL){//se no for nulo
    (*arvore) = malloc(sizeof(struct NoAVL_N));//aloca memoria
    (*arvore)->direita = NULL;//subarvore direita e nula
    (*arvore)->esquerda = NULL;//subarvore esquerda e nula
    (*arvore)->id = id;
    (*arvore)->rrn = rrn;
    (*arvore)->altura = 1;
    return true;
  }

  if((*arvore)->id == id){//se ja ha um id desse tipo, nao insere
    return false;
  }

  if(id < (*arvore)->id){//se id for maior q o id do no
    boleano = (insereAVL_N(&(*arvore)->esquerda, id, rrn));//recursao para esquerda
  }else {//caso contrario
    boleano = (insereAVL_N(&(*arvore)->direita, id, rrn));//recursao para direita
  }

  if(!boleano)//se n houve troca, retorna falso
  return (false);
  //Se houve troca
  //calcula alturas
  int he =  alturaAVL_N(&(*arvore)->esquerda);
  int hd =  alturaAVL_N(&(*arvore)->direita);
  int h = hd - he;

  if(h > 1 || h < -1){//se arvore desbalanceou
    balanceiaAVL_N(&(*arvore));//balanceia a arvore

  }
  //atualiza altura do no
  (*arvore)->altura = atualizaAltura_AVL_N((*arvore)->esquerda, (*arvore)->direita);
  return(true);
}//insereAVL_N

void destroiAVL_N(struct NoAVL_N **arvore) {
  if((*arvore) != NULL ) {//se arvore tem nos
    destroiAVL_N( &(*arvore)->esquerda);//recursao para esquerda
    destroiAVL_N( &(*arvore)->direita);//recursao para direita
    free(*arvore);//libera memoria
    *arvore = NULL;//limpa no
  }//destroiAVL_N
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Funções para Caractere

//Todas as funcoes nao comentadas
//Funcionam da mesma forma que as funcoes acima
struct NoAVL_C{
  struct NoAVL_C* direita;
  struct NoAVL_C* esquerda;
  int altura;
  char nome[30];
  int rrn;
};

void iniciaArvoreAVL_C(struct NoAVL_C **arvore){
  *arvore = NULL;
}//iniciaArvoreAVL_C

int alturaAVL_C(struct NoAVL_C **arvore) {
  if (*arvore == NULL)
  return 0; // altura da árvore vazia
  else return (*arvore)->altura;
}//alturaAVL_C

int atualizaAltura_AVL_C(struct NoAVL_C *esquerda, struct NoAVL_C *direita){

  int he = alturaAVL_C(&esquerda);
  int hd = alturaAVL_C(&direita);
  if (he > hd)
  return he + 1;
  else
  return hd + 1;
}//atualizaAltura_AVL_C

void rotacaoSimplesEsquerda_C(struct NoAVL_C **arvore){
  struct NoAVL_C *u = (*arvore)->direita;

  (*arvore)->direita = u->esquerda;
  u->esquerda = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_C((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_C(u->esquerda, u->direita);
  (*arvore)=u;
}//rotacaoSimplesEsquerda_C

void rotacaoSimplesDireita_C(struct NoAVL_C **arvore){
  struct NoAVL_C *u = (*arvore)->esquerda;

  (*arvore)->esquerda = u->direita;
  u->direita = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_C((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_C(u->esquerda, u->direita);
  (*arvore)=u;
}//rotacaoSimplesDireita_C

void rotacaoDuplaEsquerda_C(struct NoAVL_C **arvore){
  struct NoAVL_C *u = (*arvore)->direita;
  struct NoAVL_C *v = u->esquerda;

  (*arvore)->direita = v->esquerda;
  u->esquerda = v->direita;
  v->direita = u;
  v->esquerda = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_C((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_C(u->esquerda, u->direita);
  v->altura = atualizaAltura_AVL_C(v->esquerda, v->direita);

  (*arvore)= v;
}//rotacaoDuplaEsquerda_C

void rotacaoDuplaDireita_C(struct NoAVL_C **arvore){
  struct NoAVL_C *u = (*arvore)->esquerda;
  struct NoAVL_C *v = u->direita;

  u->direita = v->esquerda;
  v->esquerda = u;
  (*arvore)->esquerda = v->direita;
  v->direita = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_C((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_C(u->esquerda, u->direita);
  v->altura = atualizaAltura_AVL_C(v->esquerda, v->direita);

  (*arvore)= v;
}//rotacaoDuplaDireita_C

void balanceiaAVL_C(struct NoAVL_C **arvore){

  int he =  alturaAVL_C(&(*arvore)->esquerda);
  int hd = alturaAVL_C(&(*arvore)->direita);
  int h = hd - he;
  struct NoAVL_C *temp;

  if(h < 0 ){
    temp = (*arvore)->esquerda;
    he = alturaAVL_C(&temp->esquerda);
    hd = alturaAVL_C(&temp->direita);
    h = hd - he;

    if(h < 0){
      rotacaoSimplesDireita_C(&(*arvore));
    }else{
      rotacaoDuplaDireita_C(&(*arvore));
    }
  }else{
    temp = (*arvore)->direita;
    he = alturaAVL_C(&temp->esquerda);
    hd = alturaAVL_C(&temp->direita);
    h = hd - he;

    if(h>0){
      rotacaoSimplesEsquerda_C(&(*arvore));
    }else{
      rotacaoDuplaEsquerda_C(&(*arvore));
    }
  }
}//balanceiaAVL_C



void imprimeEmOrdem_C(struct NoAVL_C **arvore, FILE* arquivo){
  if(*arvore == NULL)
  return;

  imprimeEmOrdem_C(&(*arvore)->esquerda, arquivo);
  fprintf(arquivo,"%s%d\n", (*arvore)->nome, (*arvore)->rrn);
  imprimeEmOrdem_C(&(*arvore)->direita, arquivo);

}//imprimeEmOrdem_C

bool pesquisaAVL_N(struct NoAVL_N **arvore,FILE *arquivo, int id){

  if(*arvore == NULL)//se no for nulo, retorna
  return (false);

  if((*arvore)->id == id){//se achou o no
    char string [100];
    fseek(arquivo,(*arvore)->rrn * 65, SEEK_SET);//vai ate o rrn no arquivo de dados
    fgets(string, 100, arquivo);//pega a string
    printf("Encontrado:%s\n",string );//printa a string na tela

    return true;
  }

  if(id < (*arvore)->id)//se id for menor que o do no
  return (pesquisaAVL_N(&(*arvore)->esquerda,arquivo, id));//recursao para esquerda
  else
  return (pesquisaAVL_N(&(*arvore)->direita, arquivo, id));//recursao para direita
}//pesquisaAVL_N

bool imprime_atletas(struct NoAVL_C **raiz_primaria, FILE* arquivo){

  if(*raiz_primaria == NULL){//se no vazio, retorna falso
    return (false);
  }

  imprime_atletas(&(*raiz_primaria)->esquerda, arquivo);//recursao para esquerda
  char string [100];
  fseek(arquivo,(*raiz_primaria)->rrn * 65, SEEK_SET);//acha rrn no arquivo
  fgets(string, 100, arquivo);//guarda na string
  printf("%s",string );//printa string
  imprime_atletas(&(*raiz_primaria)->direita, arquivo);//recursao para direita
}//imprime_atletas

bool verifica(char arvore[30], char nome[30] ){
  int i,tam =30;

  for(int i = 29; i >=0; i--){
    if(nome[i] != ' '){
      i= -1;
    }
    else tam --;
  }

  char *hhh = (char*) malloc(tam*sizeof(char));

  for(i = 0; i<tam; i++ ){
    hhh[i] = nome[i];
  }
  // printf("|%s|%s|\n",hhh, nome );
  // int cont;
  // for(i = 0; i<31-tam; i++){
  //   cont = 0;
  //   for(j = i, k = 0; k<tam; j++, k++){
  //     if(hhh[k] == arvore[j])
  //     cont++;
  //     else
  //     cont = 0;
  //     if(cont == tam){
  //       printf("askjdaksg\n");
  //     return true;
  //   }
  //   }
  // }
  // return false;
  char *ptr = strstr(arvore, hhh);
  if (ptr != NULL)
  return true;
  else return false;
}

int comparacao(char arvore[30], char nome[30] ){
  int i, tam =30;

  for(i = 29; i >=0; i--){
    if(nome[i] != ' '){
      i= -1;
    }
    else tam --;
  }

  char *aaa = (char*) malloc(tam*sizeof(char));
  char *nnn = (char*) malloc(tam*sizeof(char));

  for(i = 0; i<tam; i++ ){
    aaa[i] = arvore[i];
  }
  for(i = 0; i<tam; i++ ){
    nnn[i] = nome[i];
  }
  i = strcasecmp(nnn, aaa);
  return i;
}

bool pesquisaAVL_Nome(struct NoAVL_C **arvore, FILE* arquivo, char nome[30]){
  //funciona da mesma maneira que a versao para id
  if(*arvore == NULL){
    return (false);
  }

  int resultado_comparacao = comparacao((*arvore)->nome, nome);

  //  if(strcasecmp((*arvore)->nome, nome) == 0){//compara nome, se igual
  if(resultado_comparacao == 0 || verifica((*arvore)->nome, nome)){
    char string [100];
    fseek(arquivo,(*arvore)->rrn * 65, SEEK_SET);//acha rrn no arquivo
    fgets(string, 100, arquivo);//guarda na string a linha do arquivo
    printf("Encontrado:%s\n",string );//printa
  }

  //recursao
  /*
  // Essa recursão é indicada para encontra o nome da pessoa e não o sobrenome
  if(resultado_comparacao < 0){
    return (pesquisaAVL_Nome(&(*arvore)->esquerda, arquivo, nome));
  }else if (resultado_comparacao == 0){
    pesquisaAVL_Nome(&(*arvore)->esquerda, arquivo, nome);
    return pesquisaAVL_Nome(&(*arvore)->direita, arquivo, nome);
  } else{
    return (pesquisaAVL_Nome(&(*arvore)->direita, arquivo, nome));
  }
  */
  // para ver a ocorrencia de todo sobrenome, essa é a função mais indicada
   pesquisaAVL_Nome(&(*arvore)->esquerda, arquivo, nome);
   pesquisaAVL_Nome(&(*arvore)->direita, arquivo, nome);
}//pesquisaAVL_Nome

//modalidade
bool pesquisaAVL_Modalidade(struct NoAVL_C **raiz_secundaria_fraca, struct NoAVL_N **raiz_primaria, FILE* arquivo, char nome[30]){

  if(*raiz_secundaria_fraca == NULL){
    return (false);
  }

  if(strcasecmp((*raiz_secundaria_fraca)->nome, nome) == 0){//compara modalidade
    pesquisaAVL_N(raiz_primaria, arquivo, (*raiz_secundaria_fraca)->rrn);//procura por rrn
  }
  //recursao
  if(strcasecmp(nome,(*raiz_secundaria_fraca)->nome) < 0){
    return (pesquisaAVL_Modalidade(&(*raiz_secundaria_fraca)->esquerda, raiz_primaria, arquivo, nome));
  }else if (strcasecmp(nome, (*raiz_secundaria_fraca)->nome) == 0){
    pesquisaAVL_Modalidade(&(*raiz_secundaria_fraca)->esquerda, raiz_primaria, arquivo, nome);
    return pesquisaAVL_Modalidade(&(*raiz_secundaria_fraca)->direita, raiz_primaria, arquivo, nome);
  } else{
    return (pesquisaAVL_Modalidade(&(*raiz_secundaria_fraca)->direita, raiz_primaria, arquivo, nome));
  }
}//pesquisaAVL_Modalidade

char *maiorValorEsquerda_C(struct NoAVL_C** arvore){
  if((*arvore)->direita == NULL )
  return (*arvore)->nome;

  if((*arvore)->direita != NULL)
  maiorValorEsquerda_C(&(*arvore)->direita);
}//maiorValorEsquerda_C

bool insereAVL_C(struct NoAVL_C **arvore, char nome[30], int rrn){

  bool boleano;
  if(*arvore == NULL){
    (*arvore) = malloc(sizeof(struct NoAVL_C));
    (*arvore)->direita = NULL;
    (*arvore)->esquerda = NULL;
    strcpy((*arvore)->nome, nome);
    (*arvore)->rrn = rrn;
    (*arvore)->altura = 1;
    return true;
  }

  if(strcasecmp(nome, (*arvore)->nome) == 0) {
    if(rrn == (*arvore)->rrn)
    return false;
    else{
      if(rrn < (*arvore)->rrn){
        boleano = (insereAVL_C(&(*arvore)->esquerda, nome, rrn));
      }else {
        boleano = (insereAVL_C(&(*arvore)->direita, nome, rrn));

      }
    }
  }

  if(strcasecmp(nome, (*arvore)->nome) < 0){
    boleano = (insereAVL_C(&(*arvore)->esquerda, nome, rrn));
  }else if(strcasecmp(nome, (*arvore)->nome) > 0){
    boleano = (insereAVL_C(&(*arvore)->direita, nome, rrn));
  }

  if(!boleano)
  return (false);

  int he =  alturaAVL_C(&(*arvore)->esquerda);
  int hd =  alturaAVL_C(&(*arvore)->direita);
  int h = hd - he;

  if(h > 1 || h < -1){
    balanceiaAVL_C(&(*arvore));

  }
  (*arvore)->altura = atualizaAltura_AVL_C((*arvore)->esquerda, (*arvore)->direita);
  return(true);
}//insereAVL_C

void Tarefa1(FILE* entrada, FILE* indice_primario, struct NoAVL_N **raiz_primaria){

  char string[200], numero[4];
  int  rrn = 0, i =0, id;
  fseek(entrada,0, SEEK_SET);//inicio arquivo de dados

  while(fgets(string, 200, entrada)){
    i=0;
    while(string[i] != ' '){
      numero[i] = string[i];//guarda os caracteres do id
      i++;
    }
    id = atoi(numero);//converte o id de char pra int
    insereAVL_N(raiz_primaria, id, rrn);//insere na arvore de ids
    rrn++;
  }
  imprimeEmOrdem_N(raiz_primaria, indice_primario);//imprime indice primario
}

void Tarefa2(FILE* atletas, FILE* indice_primario, FILE* indice_secundario_forte, FILE *indice_secundario_fraco,
  struct NoAVL_N **raiz_primaria, struct NoAVL_C **raiz_secundaria_forte, struct NoAVL_C **raiz_secundaria_fraca){

    char string[200];
    char *nome =  malloc(30*sizeof(char));//aloca tamanho do campo nome

    int rrn = 0, i, j;
    fseek(atletas,0, SEEK_SET);//comeco do arquivo

    while(fgets(string, 200, atletas)){
      for(i = 0, j = 4; i<30 ; i++, j++){//especificacoes de posicoes onde esta o nome
        nome[i] = string[j];//guarda nome caractere por caractere
      }

      insereAVL_C(raiz_secundaria_forte, nome, rrn);//insere nome e rrn na arvore
      rrn++;
    }

    imprimeEmOrdem_C(raiz_secundaria_forte, indice_secundario_forte);//imprime no arquivo

    int  id;
    char numero[4];
    fseek(atletas,0, SEEK_SET);//volta pro comeco do arquivo

    while(fgets(string, 200, atletas)){//guarda na string
      i=0;
      while(string[i] != ' '){
        numero[i] = string[i];//guarda o numero
        i++;
      }
      id = atoi(numero);//converte o numero de char para int
      //limpando o nome para não ficar lixo de outro nome
      for(i = 0; i<30; i++){
        nome[i]= ' ';
      }
      // salva 25 caracteres partindo do caracter 38 da linha => modalidade
      for(i = 0, j = 38; i<25 ; i++, j++){
        nome[i] = string[j];//guarda modalidade
      }

      insereAVL_C(raiz_secundaria_fraca, nome, id);//guarda a modalidade e o id na arvore
    }
    imprimeEmOrdem_C(raiz_secundaria_fraca, indice_secundario_fraco);//imprime indice
    free(nome);//libera memoria
  }


  void destroiAVL_C(struct NoAVL_C **arvore) {
    if((*arvore) != NULL ) {
      destroiAVL_C( &(*arvore)->esquerda);
      destroiAVL_C( &(*arvore)->direita);
      free(*arvore);
      *arvore = NULL;
    }
  }//destroiAVL_C


  int main(int argc, char *argv[]){
    system("color a");//so pelo estilo kkkkk
    //declaracao de variaveis
    bool estado = false;
    int tamanho;
    int escolha = 0;
    char a;
    char string[200];
    char *nome = malloc(30*sizeof(char));
    //inicializacao de estruturas
    struct NoAVL_N *raiz_primaria;
    struct NoAVL_C *raiz_secundaria_forte, *raiz_secundaria_fraca;
    iniciaArvoreAVL_N(&raiz_primaria);
    iniciaArvoreAVL_C(&raiz_secundaria_forte);
    iniciaArvoreAVL_C(&raiz_secundaria_fraca);
    //abertura de arquivos
    FILE *indice_secundario_forte = fopen("indice_secundario_forte.txt", "w+");
    FILE *indice_secundario_fraco = fopen("indice_secundario_fraco.txt", "w+");
    FILE *indice_primario  = fopen("indice_primario.txt", "w+");
    FILE *atletas = fopen(argv[1], "r");
    //teste de erro
    if(indice_primario == NULL|| atletas == NULL || indice_secundario_forte == NULL || indice_secundario_fraco == NULL){
      printf("Erro na abertura do arquivo\n");
      exit(1);
    }//fim teste de erro
    while(estado == false){//teste de erro indice primario
      a = fgetc(indice_primario);
      if(a == EOF){//se indice vazio
        printf("Arquivo de Indice primario vazio \n");
        Tarefa1(atletas, indice_primario, &raiz_primaria);//cria indice
      }
      else{
        printf("Arquivo de indice primario foi criado corretamente \n");
        estado = true;//caso ja foi criado
      }
    }//fim teste de erro indice primario

    while(estado == true){//teste de erro indice secundario forte
      //por questao de otimizacao no codigo
      //true e false estao invertidos nesse
      a = fgetc(indice_secundario_forte);
      if(a == EOF){
        printf("Arquivo de Indice Secundário foretemente ligado vazio\n");
        Tarefa2(atletas, indice_primario, indice_secundario_forte, indice_secundario_fraco,
          &raiz_primaria, &raiz_secundaria_forte, &raiz_secundaria_fraca);
        }
        else{
          printf("Arquivo de Indice Secundario fortemente ligado foi criado corretamente \n");
          estado = false;
        }
      }//fim teste de erro indice secundario forte

      while(estado == false){//teste de erro indice secundario fraco
        a = fgetc(indice_secundario_fraco);
        if(a == EOF){
          printf("Arquivo de Indice Secundário fracamente ligado vazio\n");
          Tarefa2(atletas, indice_primario, indice_secundario_forte, indice_secundario_fraco,
            &raiz_primaria, &raiz_secundaria_forte, &raiz_secundaria_fraca);
          }
          else{
            printf("Arquivo de Indice Secundario fracamente ligado foi crido corretamente \n");
            estado = true;
          }
        }//fim teste de erro indice secundario fraco

        rewind(indice_primario);//volta ao comeco do arquivo
        //por algum motivo o indice primario so imprimia no fechamento do Programa
        //com isso ele mostra o txt impresso com o programa aberto

        while(escolha != 4){//menu comeca aqui
          printf("\nDigite qualquer tecla para prosseguir.\n" );
          getchar();//coleta entrada do teclado
          system("cls");
          printf("=========== Amigos do Astolfo ===========\n");
          printf("1 - Listar todos os dados dos Atletas\n");
          printf("2 - Pesquisar por Nome\n");
          printf("3 - Pesquisar por Modalidade\n");
          printf("4 - Sair do Programa\n");
          printf("\nDigite sua Opcao: ");
          // garantindo caso aconteça um erro do usuário, não havera bugs.
          escolha = 5;//escolha setada para o caso default
          scanf("%d", &escolha);
          while(getchar() != '\n');//limpa barra \n

          switch (escolha) {
            case 1:
            printf("\n=========================================\n");
            printf("      Imprimeindo Lista de ateltas\n" );
            printf("=========================================\n\n");
            imprime_atletas(&raiz_secundaria_forte, atletas);//imprime todos os dados
            printf("\n=========================================\n");
            break;

            case 2:
            printf("\n=========================================\n");
            printf("Digite o nome do Atleta: ");
            scanf("%29[^\n]s", nome);//armazena nome digitado na variavel
            while(getchar() != '\n');
            printf("=========================================\n\n");

            //preenche o nome com espaços para realizar a pesquisa corretamente
            tamanho = strlen(nome);
            for (int i =tamanho; i<30; i++){
              nome[i] = ' ';
            }
            pesquisaAVL_Nome(&raiz_secundaria_forte, atletas, nome);//pesquisa nome
            printf("=========================================\n");
            break;

            case 3:
            printf("\n=========================================\n");
            printf("Digite o nome da Modalidade: ");
            scanf("%24[^\n]s", nome);
            while(getchar() != '\n');
            printf("=========================================\n\n");

            tamanho = strlen(nome);
            for (int i =tamanho; i<30; i++){
              nome[i] = ' ';
            }
            //pesquisa modalidade
            pesquisaAVL_Modalidade(&raiz_secundaria_fraca, &raiz_primaria, atletas, nome);
            printf("=========================================\n");

            break;
            case 4://finaliza programa
            break;

            default:
            printf("Opção Invalida. Digite novamente.\n");
            break;
          }

        }
        printf("--------------------------------\n");
        printf("    Obrigado, Volte sempre!\n");
        printf("--------------------------------\n");
        //destroi estruturas
        destroiAVL_N(&raiz_primaria);
        destroiAVL_C(&raiz_secundaria_fraca);
        destroiAVL_C(&raiz_secundaria_forte);
        //fecha arquivos
        fclose(atletas);
        fclose(indice_primario);
        fclose(indice_secundario_forte);
        fclose(indice_secundario_fraco);


        return 0;
      }//main
