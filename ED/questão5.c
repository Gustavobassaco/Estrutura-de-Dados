/*Exercício 5. (Listas - 2,00 Pontos)
Implemente uma função que receba um vetor de valores inteiros
com n elementos e construa uma lista encadeada
armazenando os elementos do vetor v nos nós da lista.
Se o vetor tiver zero elementos, a função deve ter como valor
de retorno uma lista vazia. O protótipo da função é dado por:
Lista* constroi(int n, int* v);*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoLista* PtrNoLista;

typedef struct NoLista{
  int chave;
  PtrNoLista proximo;
} NoLista;

typedef struct {
  PtrNoLista inicio;
  int tamanho;
} ListaDinamica;

void iniciaListaDinamica(ListaDinamica *lista) {
  lista->inicio = NULL;
  lista->tamanho = 0;
}//iniciaListaDinamica

bool estaVaziaListaDinamica(ListaDinamica *lista) {
  return (lista->tamanho == 0);
}//estaVaziaListaDinamica

int tamanhoListaDinamica(ListaDinamica *lista) {
  return(lista->tamanho);
}//tamanhoListaDinamica

void imprimirListaDinamica(ListaDinamica *lista) {
  printf("Lista = {");

  PtrNoLista percorre;
  for(percorre = lista->inicio; percorre != NULL; percorre = percorre->proximo) {
    printf(" %d ", percorre->chave);
  }//for
  printf("}\n");
}//imprimirListaDinamica

void inserirListaDinamica(ListaDinamica *lista, int elemento) {
  // printf("Inserindo: %d \n", elemento);
  PtrNoLista novo;   // 1. Criar o ponteiro (Novo)
  novo =(PtrNoLista)malloc(sizeof(NoLista));  // 2. Aloca memoria para Novo
  novo->chave = elemento;  // 3. copia o valor do elemento p chave do Novo no

  if(estaVaziaListaDinamica(lista) || elemento < lista->inicio->chave) {
    novo->proximo = lista->inicio; // 4. proximo do novo aponta para nulo (inicio)
    lista->inicio = novo;// 5. Inicio aponta para o novo no
  }//if
  else {
    PtrNoLista aux; // aux = percorre a lista p gente (encontrar o ponto de insercao - posicao)
    aux = lista->inicio; // 4. percorrer e encontrar o ponto de insercao (aux)
    while((aux->proximo!= NULL) && (elemento > aux->proximo->chave)) {
      aux = aux->proximo;
    }//while
    novo->proximo = aux->proximo; // 5. proximo Novo aponta proximo Aux
    aux->proximo = novo; // 6. proximo do Aux aponta para Novo
  }//else
  lista->tamanho++; // 7. incrementa o contador
}//inserirListaDinamica

ListaDinamica* constroi (int n, int *v){
  ListaDinamica *listinha;
  iniciaListaDinamica(listinha);
  if(n > 0){
    for (int i = 1; i <= n; i++) {
      inserirListaDinamica(listinha, v[i]);
    }//for
    imprimirListaDinamica(listinha);
  }//if
  else{
    listinha->inicio = NULL;
  }//else
  return listinha;
}//ListaDinamica constroi

int main() {
  ListaDinamica listinha, *auxiliar;
  int n, *v;
  iniciaListaDinamica(&listinha);
  n=13; //valor de n

  v=(int*) malloc(n*sizeof(int)); //alocando dinamicamente


  //inserindo numeros
  // printf("vetor v= { " );
  for (int i = 1; i <= n; i++) {
    v[i] = 2*i;
  } //for

//  printf(" \n" );



  auxiliar = constroi(n,v);
  listinha = *auxiliar;

  if(estaVaziaListaDinamica(&listinha)){
    printf("Lista vazia\n");
  }//if
  else {
    printf("Lista contem elementos\n");
  }//else

  printf("Tamanho = %d\n", tamanhoListaDinamica(&listinha));
  imprimirListaDinamica(&listinha);

  free(v);

  return 0;
}//main
