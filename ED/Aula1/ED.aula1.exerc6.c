#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

/*Exerc´ıcio 6. [Structs, Ponteiros] Como vimos na aula passada, um baralho normal frequentemente
usado em v´arios jogos para entretenimento pode ser codificado definindo dois tipos abstrato de dados:
• Carta: que representa uma carta f´ısica do baralho. Possui trˆes atributos: s´ımbolo/valor, o naipe, e
uma vari´avel booleana indicando se a carta j´a foi jogada ou n˜ao;
• Baralho: uma estrutura que representa um conjunto de Cartas.
O c´odigo-fonte abaixo mostra poss´ıveis defini¸c˜oes para estas estruturas em linguagem C:
typedef struct {
char valor;
char naipe;
bool foiJogada;
} Carta;
typedef struct {
Carta array[54];
} Baralho;
Entretanto, apenas a defini¸c˜ao dos tipos n˜ao garante a modelagem completa do objeto Baralho. Para que
um baralho seja manipulado adequadamente ele precisa de fun¸c˜oes/m´etodos que mudem seu estado/configura¸c˜ao.
Por exemplo, temos que: criar o baralho, adicionando as cartas; consultar a carta do topo ou
fundo; embaralhar novamente as cartas; retirar cartas e entregar para os jogadores, etc. A tabela abaixo
mostra algumas fun¸c˜oes que podem manipular esse tipo de objeto:
Fun¸c˜ao Descri¸c˜ao
void criaBaralho(baralho *baralho); inicia um novo baralho criando todas as cartas nele contido.
int cartasNaoJogadas(Baralho *baralho); Consulta o n´umero de cartas dispon´ıveis para jogo.
Carta topo(Baralho *baralho); Consulta a carta do topo de um baralho.
Carta fundo(Baralho *baralho); Consulta a carta do fundo de um baralho.
Carta* carteado(Baralho *baralho); Retorna um array com 3 cartas aleat´orias para um jogador;
Tabela 1: Opera¸c˜oes b´asicas com uma baralho
Assim sendo, escreva fun¸c˜oes em C para simular os comportamentos listados na Tabela 1. Adicione comandos
na fun¸c˜ao principal que testem e validem todas as fun¸c˜oes implementadas*/

typedef struct {
  char simbolo;
  char naipe;
  bool foiJogada;
}Carta;

typedef struct {
  Carta array[52];
}Baralho;


void criaBaralho(Baralho *baralho){
  int indice;
  char naipes[4] = { 'P', 'E', 'C', 'O'};//paus, espadas, copas, ouro
  char simbolo[13] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'D', 'Q', 'J', 'K'};

      for(int i = 0 ;i<4 ; i++){
        for(int j = 0; j <13 ; j++){
          indice = (13*i) + j;
          printf("indice %d \n",indice );
          baralho->array[indice].simbolo = simbolo[j];
          baralho->array[indice].naipe = naipes[i];
          baralho->array[indice].foiJogada = false;
        }
    }
}

void imprimeBaralho(Baralho *baralho){
  int resto;
  printf("\n Cartas Disponiveis \n\n");

  for(int i = 0 ;i<52 ; i++){
    if(baralho->array[i].foiJogada == false){
    printf("Cart:");
    printf(" %c[%c]  ", baralho->array[i].simbolo, baralho->array[i].naipe );
    resto = (i+1) % 6;
    if (resto == 0)
    printf("\n");
    }
  }

    printf("\n\n Cartas Indisponiveis \n\n");
    for(int i =0; i<52; i++){
      if(baralho->array[i].foiJogada == true){
      printf("Carta %c[%c]  ", baralho->array[i].simbolo, baralho->array[i].naipe );

      resto = (i+1) % 6;
      if (resto == 0)
      printf("\n");
      }
    }
    printf("\n\n");
}

int cartasNaoJogadas(Baralho *baralho){
  int contador=0;
  for(int i =0; i<52; i++){
    if(baralho->array[i].foiJogada == false)
    contador++;
  }
  return contador;
}

void carteado(Baralho *baralho, Carta* sorteado){
  int sorteio;
  srand(time(NULL));

  for(int i = 0; i < 3; i++){
    do{
  sorteio = rand() % 52;

}while(baralho->array[sorteio].foiJogada == true);

  sorteado[i].naipe = baralho->array[sorteio].naipe;
  sorteado[i].simbolo = baralho->array[sorteio].simbolo;
  baralho->array[sorteio].foiJogada = true;
  }
}

Carta topo(Baralho *baralho){
  Carta t;

  for(int i =0; i<52; i++){
    if(baralho->array[i].foiJogada == false){
     t.naipe = baralho->array[i].naipe;
     t.simbolo = baralho->array[i].simbolo;
     break;
    }
  }  return t;
}

Carta fundo(Baralho *baralho){
  Carta t;

  for(int i =0; i<52; i++){
    if(baralho->array[i].foiJogada == false){
     t.naipe = baralho->array[i].naipe;
     t.simbolo = baralho->array[i].simbolo;
    }
  }  return t;
}

int main(){
  Baralho baralho;
  Carta sorteado[3], cartaTopo, cartaFundo;
  int repeticao = 0;
  criaBaralho(&baralho);

  do{
    imprimeBaralho(&baralho);
    carteado(&baralho, &sorteado[0]);
    cartaTopo = topo(&baralho);
    cartaFundo = fundo(&baralho);

    printf("\n\n Carta do Topo  %c[%c],  Carta do fundo %c[%c] \n\n",cartaTopo.simbolo,
    cartaTopo.naipe, cartaFundo.simbolo, cartaFundo.naipe );

    printf("\n As 3 cartas sortadas sao: \n\n");
    for(int i = 0; i<3; i++){
      printf("\n Carta: %c [%c] ", sorteado[i].simbolo, sorteado[i].naipe);
    }

    if (cartasNaoJogadas(&baralho) == 1)
    repeticao = -1;

    printf("\n\n Cartas restantes : %d", cartasNaoJogadas(&baralho));
    printf("\n Digite -1 para sair ou continue digitando qualquer caractere.  \n");
    scanf("%d", &repeticao);
  }while(repeticao != -1);

  return 0;
}
