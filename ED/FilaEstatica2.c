#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 10

typedef struct{
  int dados;
}Objeto;

typedef struct{
	Objeto *valor ;
	int inicio;
	int final;
	int tamanho;
}FilaEstatica;

bool estaVazia(FilaEstatica *fila){
  return (fila->tamanho == 0);
}

bool estaCheia(FilaEstatica *fila){
  return (fila->tamanho == N);
}

void iniciaFila(FilaEstatica *fila){
  fila->valor = (Objeto*) malloc(N*sizeof(Objeto));
  fila->inicio = 0;
  fila->final = -1;
  fila->tamanho = 0;
}

void imprimeFila(FilaEstatica *fila){
  printf("\n Fila Estatica: {");

  int indice = fila->inicio;
  for(int i = 0; i < fila->tamanho;i++){
    printf("  %d  ", fila->valor[indice].dados);
    indice = (indice + 1)% N;
  }
  printf("}\n");
}

void entraFila(FilaEstatica *fila, int valor){
  if(!estaCheia(fila)){
    fila->final++;
    fila->final = fila->final % N;
    fila->valor[fila->final].dados = valor;
    fila->tamanho++;
}else printf("\nEsta cheia\n");
}


int saiFila(FilaEstatica *fila){
  int valor;
  if (!estaVazia(fila)){
    valor = fila->valor[fila->inicio].dados;
    fila->inicio++;
    fila->inicio %= N;
    fila->tamanho--;
    return valor;
  }else printf("\n Warning: Fila vazia \n");
}

int main(){
  FilaEstatica fila;

  iniciaFila(&fila);

  imprimeFila(&fila);

  for (int i = 1; i<12; i++){
    entraFila(&fila, i);
    imprimeFila(&fila);
  }

  printf("\nTamanho fila: %d ", fila.tamanho);
  imprimeFila(&fila);

  int retorno;
  for(int i =0; i<4; i++){
    retorno = saiFila(&fila);
    printf("\nSaiu da Fila: %d \n", retorno );
  }

  for (int i = 1; i<6; i++){
    entraFila(&fila, i);
    imprimeFila(&fila);
  }

  printf("\nTamanho fila: %d ", fila.tamanho);
  imprimeFila(&fila);

    for(int i =0; i<8; i++){
      retorno = saiFila(&fila);
      printf("\nSaiu da Fila: %d \n", retorno );
    }




}
