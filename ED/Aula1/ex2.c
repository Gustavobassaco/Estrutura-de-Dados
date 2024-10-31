#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Exerc´ıcio 2. [Arquivos] Fa¸ca um programa que receba do usu´ario um arquivo texto. Crie outro arquivo
texto de sa´ıda contendo o texto do arquivo de entrada original, por´em substituindo todas as vogais pelo
caractere ‘*’. Al´em disso, mostre na tela quantas linhas esse arquivo possui. Dentro do programa fa¸ca
o controle de erros, isto ´e, insira comandos que mostre se os arquivos foram abertos com sucesso, e caso
contr´ario, imprima uma mensagem de erro encerrando o programa.
*/


int main(){

  char string[200];
  char nomearquivo[200];
  int contador=0, tamanho;

  printf("digite o nome do arquivo\n" );
  scanf("%199[^\n]s", &nomearquivo );
  while(getchar() != '\n');

  FILE* arquivo;
  arquivo = fopen (nomearquivo, "r");

  if(arquivo == NULL){
  printf("Erro ao abrir o arquivo\n" );
  exit(1);
  }

  FILE* saida;
  saida = fopen ("saida.txt", "w");

  if(arquivo == NULL){
  printf("Erro ao abrir o arquivo\n" );
  exit(1);
  }

  while (fgets(string, 200, arquivo) != NULL){
  tamanho = strlen(string);

  for(int i = 0; i<tamanho; i++){
  if(string[i] == 'a' || string[i] == 'A' || string[i] == 'e' || string[i] == 'E' || string[i] == 'i' ||
   string[i] == 'I' || string[i] == 'o' || string[i] == 'O' || string[i] == 'u' || string[i] == 'U')
    fputc('*', saida);
  else fputc(string[i], saida);

  }
  contador++;
 }
  printf("Quantidade de linhas igual a : %d\n", contador );
  fclose(arquivo);
  fclose(saida);

  return 0;
}
