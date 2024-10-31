#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

int main(){

  FILE *arquivo = fopen("nnn.txt", "r");
  FILE *saida = fopen("mmm.txt", "w");
  char string[200];
  int contador = 0, tm;
  bool controle = 1;


  while(fgets(string, 200 , arquivo) != NULL){
    tm = strlen(string);
    for(int i = 0; i < tm; i++){
      if(isalpha(string[i]) || ispunct(string[i]))
      exit(1);
      if(isdigit(string[i]))
      controle = 0;
    }
    if(controle == 0)
    contador++;
    controle = 1;
  }
  int *vetor = (int*) malloc(contador*sizeof(int));
  fseek(arquivo,0, SEEK_SET);
  int numero, i = 0;

  printf("numero de linhas %d\n",contador );

  while( fscanf(arquivo,"%d,", &numero) != EOF ){
    vetor[i] = numero;
    i++;
  }
  for(int j = 0; j<contador; j++){
    fprintf(saida, "%-4d   %d\n", j, vetor[j]);
  }
  fclose(arquivo);
  fclose(saida);
  return 0;
}
