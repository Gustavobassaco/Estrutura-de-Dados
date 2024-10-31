#include <stdio.h>
#include <stdlib.h>

/*Exerc´ıcio 5. [Structs, Ponteiros] Defina um tipo abstrato de dados que ir´a representar bandas de m´usica.
Essa estrutura deve ter o nome da banda, que tipo de m´usica ela toca, o n´umero de integrantes, e em que
posi¸c˜ao do ranking essa banda est´a dentre as suas 5 bandas favoritas.
a) Crie uma fun¸c˜ao para preencher as 5 estruturas de bandas criadas no exemplo passado;
b) Ap´os criar e preencher, exiba todas as informa¸c˜oes das bandas/estruturas. N˜ao se esque¸ca de usar o
operador → para preencher os membros das structs;
c) Crie uma fun¸c˜ao que pe¸ca ao usu´ario um n´umero de 1 at´e 5. Em seguida, seu programa deve exibir
informa¸c˜oes da banda cuja posi¸c˜ao no seu ranking ´e a que foi solicitada pelo usu´ario.
*/

typedef struct{
 char nome[50];
 char estilo[50];
 int integrantes;
 int posicao;
}bandas;

void preenche(bandas* banda, int n){
  for (int i = 0; i<n; i++){
    printf("digite o nome da  banda[%d]\n", i);
    scanf("%49[^\n]s", banda[i].nome );
    while(getchar() != '\n');
    printf("digite o estilo da  banda[%d]\n", i);
    scanf("%49[^\n]s", banda[i].estilo );
    while(getchar() != '\n');
    printf("digite o numero de integrantes da banda[%d]\n", i );
    scanf("%d", &banda[i].integrantes );
    while(getchar() != '\n');
    printf("digite o numero da posição da banda[%d] no seu ranking\n", i );
    scanf("%d", &banda[i].posicao );
    while(getchar()!= '\n');
  }
}

void pede(bandas* banda, int m){
int n;

printf("digite a posicao de uma banda e veja as informações desta banda\n");
scanf("%d",&n );
while(getchar() != \n);

printf("o nome da banda[%d] = %s:\n", n, banda[n].nome);
printf("o estilo da banda[%d] = %s\n", n, banda[n].estilo );
printf("o numero de integrantes da banda[%d] = %d\n",n, banda[n].integrantes );
printf("a posicao da banda[%d] no ranking = %d\n",n , banda[n].posicao);

}


int main(){

  bandas banda[5];
  preenche(&banda[0],5);

for(int i = 0; i<5; i++){
printf("\n===============================================\n" );
printf("o nome da banda[%d] = %s:\n", i, banda[i].nome);
printf("o estilo da banda[%d] = %s\n", i , banda[i].estilo );
printf("o numero de integrantes da banda[%d] = %d\n",i, banda[i].integrantes );
printf("a posicao da banda[%d] no ranking = %d\n",i , banda[i].posicao);

}

   pede(&banda[0], 5);

  return 0;
}
