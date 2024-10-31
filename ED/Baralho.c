#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
  char valor;
  char naipe;
  bool foiJogada;
}Carta;

typedef struct{
  Carta carta[52];
}Baralho;

void criaBaralho(Baralho *baralho){ //inicia um novo baralho criando todas as cartas nele contido.

  int i, l, c;
  char naipe[4] = {'P','C','E','O'};
  char valor[13] = {'A','2','3','4','5','6','7','8','9','X','J','Q','K'};

  for ( l = 0; l < 4; l++) {
    for ( c = 0; c < 13; c++) {
      i = (13*l)+c;
      baralho->carta[i].valor = valor[c];
      baralho->carta[i].naipe = naipe[l];
      baralho->carta[i].foiJogada = false;
    }//for
  }//for
}// criaBaralho

int cartasNaoJogadas(Baralho *baralho){ //Consulta o numero de cartas disponıveis para jogo.

int disponiveis = 0;

  for (int i = 0; i < 52; i++) {
        if(  baralho->carta[i].foiJogada == false){
          disponiveis++;
        }//if
    }//for
    //printf(" Cartas disponiveis: %d\n", disponiveis);
    return disponiveis;
}//cartasNaoJogadas

//Carta fundo(Baralho *baralho); //Consulta a carta do fundo de um baralho.

void carteado(Baralho *baralho){ //Retorna um array com 3 cartas aleatorias para um jogador;

  srand(time(NULL));

  Carta carta[3];
  int n ,i=0;

  while (i < 3) {
    n = rand() % 52;
    //printf("rand %d\n", n);
      if (baralho->carta[n].foiJogada == false) {
        carta[i].valor = baralho->carta[n].valor;
        carta[i].naipe = baralho->carta[n].naipe;
        baralho->carta[n].foiJogada = true;
        i++;
      }//if else
    }//while

  for (int j = 0; j < 3; j++) {
    printf("cartas: %c %c\n", carta[j].valor, carta[j].naipe);
  }
  return;
}

int main() {

  Baralho b;
  Carta cartas[3];
  //*cartas = carteado(&b);

  int i = 0,escolha=0;

  criaBaralho(&b);
  cartasNaoJogadas(&b);


  do{
    printf("\n 1- Jogar novas cartas");
    printf("\n 0- Sair\n\n");
      scanf("%d", &escolha);
    switch(escolha){
      case 1:
      if(cartasNaoJogadas(&b) >= 3)
       carteado(&b);
       else
       printf("F\n");
        break;
    }
  }while(escolha!=0);

  return 0;
}
