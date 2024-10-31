#include <stdlib.h>
#include <stdbool.h>

typedef struct{
// char nome[50];
 int idade;
}CLIENTE;

typedef struct {
    CLIENTE info;
    struct no * prox;
}LISTA;

//LISTA = struct no



LISTA* inicializarListalista(){
return NULL;

}

    void inseririnicio(LISTA** lista, CLIENTE  cl){
      LISTA* novo = (LISTA*) malloc(sizeof(LISTA));
      novo->info.idade = cl;
      novo->prox = *lista;
      *lista = novo;
    }



void inserirfinal(LISTA** lista, CLIENTE cl){
   LISTA* aux = *lista;
   LISTA* anterior = NULL;
   LISTA*novo = (LISTA*) malloc(1*sizeof(LISTA));
   novo->info = cl;
   novo->prox = NULL;

    if(*lista == NULL){
      *lista = novo;
    }
    else{
      while(aux != NULL){
        anterior = aux;
        aux = aux->prox;
      }
      anterior->prox = novo;
    }
}

 void inserirmeio(LISTA** lista, CLIENTE cl, int pos){
  LISTA* novo = (LISTA*)malloc(1*sizeof(LISTA));
  LISTA* anterior = NULL;
  LISTA* aux = *lista;

  lista->novo = cl;
  //lista->novo = *lista;

  int i = 0;

   while((aux != NULL) && (i != pos)){

     anterior = aux;
     aux = aux->prox;
     i++;
   }
   if(anterior ==  NULL){
     novo->prox = *lista;
     *lista = novo;
   }
  else {
  anterior->prox = novo;
  novo->prox = aux;
 }
 }

/*
    void exibeLista(LISTA** lista){

      printf("Lista: \n");
      while(){
        printf("{%d}  ", lista->vetor[i].idade);
      }
      printf("\n");
    }


void retiraelemento(LISTA* lista, CLIENTE cl);

LISTA* inicializarLista(){
//  return NULL;
}



    int encontrar(LISTA *lista, CLIENTE cl){
      int i;
      for(i = 0; i < lista->Nelem; i++){
        if(cl.idade == lista->vetor[i].idade){
          printf("numero encontrado na pos %d \n", i);
          return i;
          }
      }if(i == lista->Nelem)
      return -1;
    }

    void retiraelemento(LISTA*lista, CLIENTE ch){
      int pos;
      pos = encontrar(lista, ch);
      if(pos == -1){
        printf("elemento não encontrado: \n");
        return;
      }
    for(int i = pos; i < lista->Nelem ; i++){
        lista->vetor[i] = lista->vetor[i + 1];
      }
      lista->Nelem--;
    }

    void retiraelementofinal(LISTA *lista){
      int pos;
      pos = lista->Nelem - 1;
    for(int i = pos; i < lista->Nelem ; i++){
        lista->vetor[i] = lista->vetor[i + 1];
      }
      lista->Nelem--;
    }

    void retiraelementoinicio(LISTA *lista){
      int pos;
      pos = 0 ;
    for(int i = pos; i < lista->Nelem ; i++){
        lista->vetor[i] = lista->vetor[i + 1];
      }
      lista->Nelem--;
    }

    void exibevalor(LISTA* lista, int pos){
    if (pos >= lista->Nelem)
    printf("o valor do elemento da posicao %d : %d\n", lista->Nelem - 1, lista->vetor[lista->Nelem - 1].idade);

    else printf("o valor do elemento da posicao %d : %d \n", pos, lista->vetor[pos].idade);
    }
*/
int main(){

  int solicitado, posicao;
  int numero;
  CLIENTE ch;
  LISTA* lista;

 lista = inicializarLista();

do{
  printf("digite 1 para inserir elementos no final da lista:\n");
  printf("digite 2 para inserir elementos no meio da lista:\n");
  printf("digite 3 para inserir elementos no inicio da lista:\n");
/*  printf("digite 3 para saber o tamanho da lista\n");
  printf("digite 4 para exibir a lista:\n");
  printf("digite 5 para remover certo elemento a lista:\n");
  printf("digite 6 para remover elemento do final:\n");
  printf("digite 7 para remover elemento do inicio:\n");
  printf("digite 8 para acessar o conteudo de uma posicao:\n");
  */printf("digite 9 para sair do programa:\n");
  scanf("%d", &solicitado );
  while(getchar() != '\n');

  switch(solicitado){
    case 1:
    if(lista.Nelem >= MAX){
      printf("pilha cheia.\n");
      break;
    }
    printf("digite a idade a ser adicionado:\n");
    scanf("%d", &ch.idade );
    while(getchar() != '\n');

    inserirfinal(&lista, ch);
    //exibeLista(&lista);
   break;

   case 2:
   if(lista.Nelem >= MAX){
     printf("pilha cheia.\n");
     break;
   }
   printf("digite a idade a ser adicionado:\n");
   scanf("%d", &ch.idade );
   while(getchar() != '\n');
   printf("digite a posicao a ser inserido:\n");
   scanf("%d", &posicao );
   while(getchar() != '\n');
   inserirmeio(&lista, ch, posicao);
   //exibeLista(&lista);
   break;

   case 3:
   if(lista.Nelem >= MAX){
     printf("pilha cheia.\n");
     break;
   }
   printf("digite a idade a ser adicionado:\n");
   scanf("%d", &ch.idade );
   while(getchar() != '\n');
   inseririnicio(&lista, ch);
   //exibeLista(&lista);
   break;
/*
   case 4:
   exibeLista(&lista);
   break;

   case 5:
   printf("digite o numero do elemento a ser retidado \n");
   scanf("%d", &ch.idade );
   retiraelemento(&lista, ch);
   exibeLista(&lista);
   break;

   case 6:
   retiraelementofinal(&lista);
   exibeLista(&lista);
   break;

   case 7:
   retiraelementoinicio(&lista);
   exibeLista(&lista);
   break;

   case 8:
   printf("digite p numero da posicao do elemento: \n");
   scanf("%d",  &posicao);
   exibevalor(&lista, posicao);
   break;
*/
}
}while(solicitado != 9);

  return 0;
}
