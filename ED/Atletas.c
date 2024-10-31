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

int main(int argc, char *argv[]){

  Atleta atletas[8];

  for(int i = 0; i<8 ; i++){
    printf("digite o nome do atleta %d: \n", i);
    scanf("%s", &atletas[i].nome);
    fflush(stdin);

    printf("digite o pais do atleta %d: \n", i);
    scanf("%s", &atletas[i].pais);
    fflush(stdin);

    printf("digite a idade do atleta %d:  \n",i );
    scanf("%d", &atletas[i].idade);

    printf("digite a altura do atleta %d: \n",i );
    scanf("%f", &atletas[i].altura);

    printf("digite o tempo do atleta %d:  \n",i );
    scanf("%f", &atletas[i].tempo);
  }

  FILE* arquivo = fopen("atletas.txt", "w");

  for(int i = 0; i<8 ; i++){
    fprintf(arquivo, "%s\n%s\n%d\n%f\n%f\n", atletas[i].nome,atletas[i].pais, atletas[i].idade,
  atletas[i].altura, atletas[i].tempo );
  }

  return 0;
}
