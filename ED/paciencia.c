#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//estrutura tipo carta
typedef struct{
  char simbolo;
  char naipe;
  int indice;
  bool ordem;
}Carta;

//estrutura tipo pilha;
struct NoPilha{
  struct NoPilha* proximo;
  Carta carta;
};

typedef struct{
  struct NoPilha* topo;
  int tamanho;
}PilhaCartas;

//estrutura tipo lista
struct NoLista{
  struct NoLista* proximo;
  Carta carta;
};

typedef struct{
  struct NoLista* inicio;
  int tamanho;
}ListaCartas;

void iniciaPilha(PilhaCartas *p);
bool estaVaziaPilha(PilhaCartas *p);
void imprimePilhaIntermediaria(PilhaCartas *p, int i);
void imprimePilhaDefinitiva(PilhaCartas *p, int i);
void imprimePilhaAuxiliar(PilhaCartas *p, int i);
void imprimePilhavirtual(PilhaCartas *p);
void empilha(PilhaCartas *pilha, Carta carta);
Carta desempilha(PilhaCartas *p);
void iniciaListaCartas(ListaCartas* lista);
bool estaVaziaLista(ListaCartas *lista);
void imprimeLista(ListaCartas *lista);
bool percorreLista(ListaCartas *lista, int valor);
void entraListaCartas(ListaCartas *lista, Carta carta);
Carta removeDaLista(ListaCartas *lista, int sorteio);
void carteado(ListaCartas* baralho, PilhaCartas pilha[8]);
void criaBaralho(ListaCartas *lista);
bool verificaPilhaDefinitiva(PilhaCartas* cartaTopo, PilhaCartas *pilhaDefinitiva, int numeroLista);
bool verificaPilhaIntermediariaEmpilha(PilhaCartas *pilha, Carta carta);
int permitido(PilhaCartas pilha[4]);

void iniciaPilha(PilhaCartas *p){
  p->topo = NULL;
  p->tamanho = 0;
}

bool estaVaziaPilha(PilhaCartas *p){
  return (p->tamanho == 0);
}

void imprimePilhaIntermediaria(PilhaCartas *p, int i){
  printf("P.Inter.[%d]: (", i);
  for(struct NoPilha* aux = p->topo; aux != NULL; aux = aux->proximo){
  printf("  %c[%c]",  aux->carta.simbolo, aux->carta.naipe);
  if(aux->carta.ordem)
  printf("T");
  else printf("F");
 }
  printf(")\n");
}
void imprimePilhaDefinitiva(PilhaCartas *p, int i){
  printf("P.Def.[%d]: (", i);
  for(struct NoPilha* aux = p->topo; aux != NULL; aux = aux->proximo)
  printf("   %c[%c]  ",  aux->carta.simbolo, aux->carta.naipe);
  printf(")\n");
}
void imprimePilhaAuxiliar(PilhaCartas *p, int i){
  printf("P.Auxiliar.[%d]: (", i);
  for(struct NoPilha* aux = p->topo; aux != NULL; aux = aux->proximo)
  printf("   %c[%c]  ",  aux->carta.simbolo, aux->carta.naipe);
  printf(")\n");
}
void imprimePilhavirtual(PilhaCartas *p){
  printf("P.Virual: (");
  for(struct NoPilha* aux = p->topo; aux != NULL; aux = aux->proximo)
  printf("   %c[%c]  ",  aux->carta.simbolo, aux->carta.naipe);
  printf(")\n");
}

void empilha(PilhaCartas *pilha, Carta carta){
  struct NoPilha* Aux = (struct NoPilha*) malloc(sizeof(struct NoPilha));
//  Aux->carta.indice = carta.indice;
//  Aux->carta.simbolo = carta.simbolo;
//  Aux->carta.naipe = carta.naipe;
Aux->carta = carta;
  carta.ordem = true;
  if(!estaVaziaPilha(pilha)){
  if(verificaPilhaIntermediariaEmpilha(pilha, carta)){

    pilha->topo->carta.ordem = true;
  }else{
    pilha->topo->carta.ordem = false;
    }
  }

  Aux->carta.ordem = carta.ordem;
  Aux->proximo = pilha->topo;
  pilha->topo = Aux;
  pilha->tamanho++;
}

Carta desempilha(PilhaCartas *p){
  Carta retorna;
  if(!estaVaziaPilha(p)){
    struct NoPilha* Aux;
    Aux = p->topo;
    retorna.naipe = Aux->carta.naipe;
    retorna.simbolo = Aux->carta.simbolo;
    retorna.indice = Aux->carta.indice;
    retorna.ordem = Aux->carta.ordem;

    p->topo = p->topo->proximo;
    p->tamanho--;
    free(Aux);
    return retorna;
  }else printf("\n A pilha esta vazia!");
}

void iniciaListaCartas(ListaCartas* lista){
  lista->inicio = NULL;
  lista->tamanho = 0;
}

bool estaVaziaLista(ListaCartas *lista){
  return (lista->tamanho == 0);
}

void imprimeLista(ListaCartas *lista) {
  printf("Baralho: (");
  for(struct NoLista* aux = lista->inicio; aux != NULL; aux = aux->proximo){
    printf("   %c[%c]   ",  aux->carta.simbolo, aux->carta.naipe);
   }
  printf(")\n\n");
}

bool percorreLista(ListaCartas *lista, int valor){
    if(estaVaziaLista(lista)){
      return false;
    }else{
      struct NoLista *aux = lista->inicio;
      while(aux != NULL && aux->carta.indice <= valor){
          if(aux->carta.indice == valor) return true;
          aux = aux->proximo;
      }
      return false;
    }
}

void entraListaCartas(ListaCartas *lista, Carta carta){
    struct NoLista* aux = lista->inicio;
    struct NoLista* temp = (struct NoLista*) malloc(sizeof(struct NoLista));
    temp->carta.simbolo = carta.simbolo;
    temp->carta.naipe = carta.naipe;
    temp->carta.indice = carta.indice;
    temp->carta.ordem = carta.ordem;

    if(estaVaziaLista(lista) || carta.indice < lista->inicio->carta.indice){
      temp->proximo = lista->inicio;
      lista->inicio = temp;
    }else{

    while(aux->proximo != NULL && aux->proximo->carta.indice < carta.indice ){
      aux = aux->proximo;
    }
    temp->proximo = aux->proximo;
    aux->proximo = temp;
  }
    lista->tamanho++;
}

Carta removeDaLista(ListaCartas *lista, int sorteio){

  if(!estaVaziaLista(lista) && percorreLista(lista, sorteio)){
    if(sorteio == lista->inicio->carta.indice){
      struct NoLista *temp = lista->inicio;
      Carta retorna;

      retorna.indice = lista->inicio->carta.indice;
      retorna.simbolo = lista->inicio->carta.simbolo;
      retorna.naipe = lista->inicio->carta.naipe;
      retorna.ordem = lista->inicio->carta.ordem;

      lista->inicio = lista->inicio->proximo;
      lista->tamanho--;
      free(temp);
      return retorna;

    }else{

      struct NoLista *aux = lista->inicio;
      struct NoLista *destroi;
      Carta retorna;

      while(aux->proximo != NULL && sorteio > aux->proximo->carta.indice){
        aux = aux->proximo;
      }

      retorna.simbolo = aux->proximo->carta.simbolo;
      retorna.naipe = aux->proximo->carta.naipe;
      retorna.indice = aux->proximo->carta.indice;
      retorna.ordem = aux->proximo->carta.ordem;
      destroi = aux->proximo;
      aux->proximo = aux->proximo->proximo;
      free(destroi);
      lista->tamanho--;
      return retorna;
    }
  }
}

void carteado(ListaCartas* baralho, PilhaCartas pilha[8]){
  int sorteio;
  Carta retorno;
  srand(time(NULL));

  //preenche 4 pilhas com 7 cartas aleatorias
  for(int i = 0; i<4 ; i++){
    for(int j = 0; j<7; j++){
      //sorteia numeros até encontrar um indice valido
      do{
      sorteio = rand() % 52;
    }while(!percorreLista(baralho, sorteio));

      retorno = removeDaLista(baralho, sorteio);
      empilha(&pilha[i], retorno);
    }
  }

  //preenche 4 pilhas com 6 cartas aleatorias
  for(int i = 4; i<8 ; i++){
    for(int j = 0; j<6; j++){
      //sorteia numeros até encontrar um indice valido
      do{
      sorteio = rand() % 52;
    }while(!percorreLista(baralho, sorteio));

      retorno = removeDaLista(baralho, sorteio);
      empilha(&pilha[i], retorno);
    }
  }
}

void criaBaralho(ListaCartas *lista){
  int indice = 0;
  Carta carta;
  char naipes[4] = { 'P', 'C', 'E', 'O'};//paus, copas, espadas, ouro
  char simbolo[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'D', 'J', 'Q', 'K'};

      for(int i = 0 ;i<4 ; i++){
        for(int j = 0; j <13 ; j++){
          carta.simbolo = simbolo[j];
          carta.naipe = naipes[i];
          carta.indice = indice;
          carta.ordem = false;
          entraListaCartas(lista, carta);
          indice++;
        }
    }
}

bool verificaPilhaDefinitiva(PilhaCartas* cartaTopo, PilhaCartas *pilhaDefinitiva, int numeroLista){
  int naipe = cartaTopo->topo->carta.indice / 13;
  int simbolo1 = cartaTopo->topo->carta.indice % 13;

  if(estaVaziaPilha(pilhaDefinitiva)){
      if( naipe == numeroLista && simbolo1 == 0)
        return true;
      else return false;
  }else{
    int simbolo2 = pilhaDefinitiva->topo->carta.indice % 13;
    if(naipe  == numeroLista && simbolo1 == (simbolo2 + 1))
      return true;
    else return false;
  }
}

bool verificaPilhaIntermediariaEmpilha(PilhaCartas *pilha, Carta carta){
  if(estaVaziaPilha(pilha)){
    return true;
  }else{
    int cor1 = (pilha->topo->carta.indice / 13) % 2;
    int cor2 = (carta.indice / 13) % 2;
    int simbolo1 = pilha->topo->carta.indice % 13;
    int simbolo2 = carta.indice % 13;

     if(cor1 != cor2 && simbolo1 == (simbolo2 + 1)) {
      return true;
    }else return false;
  }
}

int permitido(PilhaCartas pilha[4]){
  int cont = 5;
  for(int i = 0; i<4 ; i++){
  if(!estaVaziaPilha(&pilha[i]))
  cont--;
  }
  return cont;
}

int main(int agrc, char *argv[]){

  ListaCartas baralho;
  PilhaCartas pilhaIntemediaria[8];
  PilhaCartas pilhaDefinitiva[4];
  PilhaCartas pilhaAuxiliar[4];
  PilhaCartas pilhaVirtual;
  int escolha, indiceP1, indiceP2, quantidade;
  Carta aux;

  iniciaListaCartas(&baralho);
  criaBaralho(&baralho);
  imprimeLista(&baralho);

  for(int i = 0; i < 8; i++)
    iniciaPilha(&pilhaIntemediaria[i]);

  for(int i = 0; i < 4; i++)
    iniciaPilha(&pilhaDefinitiva[i]);

  for(int i = 0; i<4; i++){
    iniciaPilha(&pilhaAuxiliar[i]);
  }

  iniciaPilha(&pilhaVirtual);
  carteado(&baralho, pilhaIntemediaria);

  do{
  for(int i = 0; i < 8; i++){
  imprimePilhaIntermediaria(&pilhaIntemediaria[i], i);
  }
  printf("\n");
  for(int i = 0; i < 4; i++){
  imprimePilhaAuxiliar(&pilhaAuxiliar[i], i);
  }
  printf("\n");
  for(int i = 0; i < 4; i++){
  imprimePilhaDefinitiva(&pilhaDefinitiva[i], i);
  }
  printf("\n");

  printf("Menu: 1 para pegar uma carta da P.Intermediarias e colocar em outra p.Inter.\n");
  printf("      2 para pegar uma carta da P.Intermediaria e colocar na P.Auxiliar\n");
  printf("      3 para pegar uma carta da P.Auxiliar e colocar na P.Intermediaria\n");
  printf("      4 para pegar uma carta da P.Intermediaria e colocar na P.Definitiva\n");
  printf("      5 para pegar uma carta da P.Auxiliar e colocar na P.Definitiva\n");
  printf("     -1 para sair do programa\n");
  scanf("%d", &escolha);

  switch(escolha){
    case 1:
    do{
    printf("Digite o indice da pilha Intermediaria(0 a 7):\n");
    scanf("%d", &indiceP1 );
  }while(0 > indiceP1 || indiceP1 > 7 );
    do{
    printf("Digite quantas cartas:\n");
    scanf("%d", &quantidade );
    if(quantidade > permitido(pilhaAuxiliar))
    quantidade = 53;
  }while(0 >= quantidade || quantidade > pilhaIntemediaria[indiceP1].tamanho);
    escolha = 6;

    for(int i = 0; i < quantidade; i++){
        if(pilhaIntemediaria[indiceP1].topo->carta.ordem  && escolha == 6){
          aux = desempilha(&pilhaIntemediaria[indiceP1]);
          empilha(&pilhaVirtual, aux);
          }else{
          escolha = 1;
          while(pilhaVirtual.topo != NULL){
            aux = desempilha(&pilhaVirtual);
            empilha(&pilhaIntemediaria[indiceP1], aux);
           }
        }
      }

      if(escolha == 1){
        printf("Nao foi possivel\n");
      break;
      }
      case 6:
      if(!estaVaziaPilha(&pilhaIntemediaria[indiceP1])){
      aux = desempilha(&pilhaIntemediaria[indiceP1]);
      empilha(&pilhaIntemediaria[indiceP1], aux);
      }
      imprimePilhavirtual(&pilhaVirtual);

      do{
      printf("Digite em qual pilha Intermediaria voce quer empilhar\n");
      scanf("%d", &indiceP2 );
    }while(0 > indiceP2 || indiceP2 > 7);

      if(verificaPilhaIntermediariaEmpilha(&pilhaIntemediaria[indiceP2], pilhaVirtual.topo->carta)) {
        while(pilhaVirtual.topo != NULL){
          aux = desempilha(&pilhaVirtual);
          empilha(&pilhaIntemediaria[indiceP2], aux);
          }
        }else{
          printf("Nao foi possivel. \n\n");
          while(pilhaVirtual.topo != NULL){
            aux = desempilha(&pilhaVirtual);
            empilha(&pilhaIntemediaria[indiceP1], aux);
        }
      }

    break;
    case 2:
    do{
    printf("Digite o indice da pilha Intermediaria(0 a 7):\n");
    scanf("%d", &indiceP1 );
  }while(0 > indiceP1 || indiceP1 > 7 );

    if(estaVaziaPilha(&pilhaIntemediaria[indiceP1])){
      printf("pilha Vazia\n");
      break;
    }

    aux = desempilha(&pilhaIntemediaria[indiceP1]);
    printf("Carta selecionada :  %c[%c]  \n", aux.simbolo, aux.naipe);

    do{
    printf("Digite o indice da pilha Auxiliar:\n");
    scanf("%d", &indiceP2);
  }while(0 > indiceP2 || indiceP2 > 3);

    if(estaVaziaPilha(&pilhaAuxiliar[indiceP2])){
      empilha(&pilhaAuxiliar[indiceP2], aux);
      if(!estaVaziaPilha(&pilhaIntemediaria[indiceP1]))
      pilhaIntemediaria[indiceP1].topo->carta.ordem = true;
    }else{
      printf("Pilha pilha Auxiliar cheia\n\n");
      empilha(&pilhaIntemediaria[indiceP1], aux);
    }
    break;

    case 3:
    do{
    printf("Digite o indice da pilha Auxiliar:\n");
    scanf("%d", &indiceP2);
  }while(0 > indiceP2 || indiceP2 > 3);

    if(estaVaziaPilha(&pilhaAuxiliar[indiceP2])){
      printf("Pilha vazia. Nao foi possivel\n\n");
    }else{

      do{
      printf("Digite o indice da pilha Intermediaria: \n");
      scanf("%d", &indiceP1);
    }while(0 > indiceP1 || indiceP1 > 7);

      if(verificaPilhaIntermediariaEmpilha(&pilhaIntemediaria[indiceP1], pilhaAuxiliar[indiceP2].topo->carta)) {
        aux = desempilha(&pilhaAuxiliar[indiceP2]);
        empilha(&pilhaIntemediaria[indiceP1], aux);
      }else{
        printf("Nao foi possivel, carta nao pode ser empilhada\n\n");
      }
    }

    break;
    case 4:
    do{
    printf("Digite o indice da pilha Intermediaria(0 a 7):\n");
    scanf("%d", &indiceP1 );
  }while(0 > indiceP1 || indiceP1 > 7 );

    if(estaVaziaPilha(&pilhaIntemediaria[indiceP1])){
      printf("pilha Vazia\n");
      break;
    }

  printf("Carta selecionada:  %c[%c]\n", pilhaIntemediaria[indiceP1].topo->carta.simbolo,
  pilhaIntemediaria[indiceP1].topo->carta.naipe);

    do{
    printf("Digite o indice da pilha Definitiva:\n 0 = paus|  1 = copas|  2 = espadas| 3 = ouros\n");
    scanf("%d", &indiceP2);
  }while(0 > indiceP2 || indiceP2 > 3 );

    if(verificaPilhaDefinitiva(&pilhaIntemediaria[indiceP1], &pilhaDefinitiva[indiceP2], indiceP2)){
      aux = desempilha(&pilhaIntemediaria[indiceP1]);
      empilha(&pilhaDefinitiva[indiceP2], aux);
      if(!estaVaziaPilha(&pilhaIntemediaria[indiceP1]))
      pilhaIntemediaria[indiceP1].topo->carta.ordem = true;
    }else printf("Nao foi possivel\n");
    break;

    case 5:
    do{
    printf("Digite o indice da pilha Auxiliar(0 a 3):\n");
    scanf("%d", &indiceP1 );
  }while(0 > indiceP1 || indiceP1 > 3 );

    if(estaVaziaPilha(&pilhaAuxiliar[indiceP1]))
    break;

    printf("Carta selecionada:  %c[%c]\n", pilhaAuxiliar[indiceP1].topo->carta.simbolo,
    pilhaAuxiliar[indiceP1].topo->carta.naipe);

    do{
    printf("Digite o indice da pilha Definitiva:\n 0 = paus|  1 = copas|  2 = espadas| 3 = ouros\n");
    scanf("%d", &indiceP2);
    }while(0 > indiceP2 || indiceP2 > 3 );

    if(verificaPilhaDefinitiva(&pilhaAuxiliar[indiceP1], &pilhaDefinitiva[indiceP2], indiceP2)){
      aux = desempilha(&pilhaAuxiliar[indiceP1]);
      empilha(&pilhaDefinitiva[indiceP2], aux);
    }else printf("Nao foi possivel\n");
    break;

    case -1:
    break;

    default:
    printf("Voce digitou um numero invalido\n\n");

  }
}while(escolha != -1);
  printf("\n\n GAME OVER \n\n");

  for(int i = 0; i<8 ; i++){
    while(pilhaIntemediaria[i].topo != NULL )
    desempilha(&pilhaIntemediaria[i]);
  }

  for(int i = 0; i<4 ; i++){
    while(pilhaDefinitiva[i].topo != NULL )
    aux =desempilha(&pilhaDefinitiva[i]);
    while(pilhaAuxiliar[i].topo != NULL)
    aux = desempilha(&pilhaAuxiliar[i]);
  }

  while(pilhaVirtual.topo != NULL)
  aux = desempilha(&pilhaVirtual);

  return 0;
}
