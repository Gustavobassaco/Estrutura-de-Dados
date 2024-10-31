#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nome[50];
  char pais[50];
  int idade;
  float altura;
  float tempo;

}Atleta;

int comparacao_tempo(const void *x, const void *y) {
    int a = ((Atleta *)x)->tempo;
    int b = ((Atleta *)y)->tempo;
    return (a - b);
}

int comparacao_nome(const void *x, const void *y) {
    return strcmp(((Atleta *)x)->nome, ((Atleta*)y)->nome);
}

int main(int argc, char *argv[]){

  Atleta atletas[8];
  FILE* arquivo = fopen("atletas.txt", "r");
  FILE* saida_tempo = fopen("qsort_tempo.txt", "w");
  FILE* saida_nome = fopen("qsort_nome.txt", "w");

  for(int i = 0; i<8 ; i++){
    fscanf(arquivo, "%s", &atletas[i].nome );
    fscanf(arquivo, "%s", &atletas[i].pais);
    fscanf(arquivo, "%d", &atletas[i].idade);
    fscanf(arquivo, "%f", &atletas[i].altura);
    fscanf(arquivo, "%f", &atletas[i].tempo);
  }

  qsort(atletas, 8, sizeof(Atleta), comparacao_tempo);

  for(int i = 0; i<8 ; i++){
    fprintf(saida_tempo, "%s\n%s\n%d\n%f\n%f\n", atletas[i].nome,atletas[i].pais, atletas[i].idade,
  atletas[i].altura, atletas[i].tempo );
  }

  qsort(atletas, 8, sizeof(Atleta), comparacao_nome);

  for(int i = 0; i<8 ; i++){
    fprintf(saida_nome, "%s\n%s\n%d\n%f\n%f\n", atletas[i].nome,atletas[i].pais, atletas[i].idade,
  atletas[i].altura, atletas[i].tempo );
  }
  return 0;
}
