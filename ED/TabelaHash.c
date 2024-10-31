#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define M 11

typedef struct{
  int indice;
  char string[200];
}Objeto;

typedef struct{
  Objeto *vetor[M];
  int contador;
}TabelaHash;

void iniciaTabelaHash( TabelaHash* tabela){
  for(int i = 0; i<M; i++){
    tabela->vetor[i] = NULL;
  }
  tabela->contador = 0;
}

int hash(int indice){
  return indice % M;
}

int colisao(TabelaHash *tabela, Objeto *obj){
  int pos = hash(obj->indice);


  while(tabela->vetor[pos] != NULL){
    if(pos == (M-1))
    pos = 0;
    else
    pos ++;
  }
  tabela->vetor[pos] = obj;
  tabela->contador ++;
}

bool estaCheia(TabelaHash *tabela){
  return (tabela->contador == M);
}

bool percorreTabelaHash(TabelaHash *tabela, Objeto* obj){
  int pos = hash(obj->indice);
  int cont = 0;

  while(cont != M){
    if(tabela->vetor[pos] == obj)
    return true;

    if(pos == (M-1))
    pos = 0;
    else
    pos ++;
    cont++;
  }
  return false;

}

void inserirTabelaHash(TabelaHash *tabela, Objeto* obj){
  if(estaCheia(tabela)){
    printf("Nao foi possivel inserir: Tabela Cheia\n");
    return;
  }
  int pos = hash(obj->indice);
  if(tabela->vetor[pos] != NULL){
    printf("Colisao\n");
    colisao(tabela, obj);
  }
  else{
    tabela->vetor[pos] = obj;
    //printf("%s\n",obj.string );
    tabela->contador++;
  }
}

void removerTabelaHash(TabelaHash *tabela, Objeto *obj){
  int pos = hash(obj->indice);
  int cont = 0;

  while(cont != M){
    if(tabela->vetor[pos] == obj){
      tabela->vetor[pos] = NULL;
      tabela->contador--;
      return;
    }
    if(pos == (M-1))
    pos = 0;
    else
    pos ++;
    cont++;
  }
}

void imprimeTabelaHash(TabelaHash *tabela){
  printf("------------------------------------\n");
  printf("            Tabela Hash             \n");
  printf("------------------------------------\n");

  for(int i = 0; i < M; i++){
    printf("[%d]  ", i);
    if(tabela->vetor[i] != NULL)
    printf("  %s",tabela->vetor[i]->string);
    else
    printf("  ");

    printf("\n");
  }
  printf("------------------------------------\n");
}



int main(int agrc, char* argv[]){
  TabelaHash tabela;

  iniciaTabelaHash(&tabela);
  imprimeTabelaHash(&tabela);

  Objeto obj1 = {3, "murieelllll"};
  Objeto obj2 = {5, "bassaco"};
  Objeto obj3 = {6, "paola"};
  Objeto obj4 = {5, "alex"};
  Objeto obj5 = {9, "neymar"};



  inserirTabelaHash(&tabela, &obj1);
  inserirTabelaHash(&tabela, &obj2);
  inserirTabelaHash(&tabela, &obj3);
  inserirTabelaHash(&tabela, &obj4);

  imprimeTabelaHash(&tabela);

  if(percorreTabelaHash(&tabela, &obj5))
  printf("Elemento dentro da tabela\n");
  else printf("Nao esta na tabela\n" );

  removerTabelaHash(&tabela, &obj4);
  removerTabelaHash(&tabela, &obj5);

  imprimeTabelaHash(&tabela);


  return  0;
}
