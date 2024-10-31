#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// define a estrutura que representa o aviao
typedef struct{
  int tempo_restante;
  int tempo_inicial;
  int id;
}Aviao;

// define a estrutura no de lista
struct Nofila{
  Aviao aviao;
  struct Nofila *proximo;
};

// define a estrutura de fila de prioridade
typedef struct{
  struct Nofila* final;
  struct Nofila* inicio;
  int tamanho;
}FilaPrioridade;

void iniciaFila(FilaPrioridade *fila){
  fila->final = NULL;
  fila->inicio = NULL;
  fila->tamanho = 0;
}

bool estaVazia(FilaPrioridade *fila){
  return (fila->tamanho == 0);
}

// função que exibe as filas de Aterrizagem
void imprimeFilaAterrizagem(FilaPrioridade *fila, int numero){
  printf(" Fila Aterrizagem[%d] = (", numero);
  for(struct Nofila* aux = fila->inicio; aux != NULL; aux = aux->proximo)
  printf("[%d]%d,   ", aux->aviao.tempo_restante,aux->aviao.id );
  printf(")\n");
}

// função que exibe as filas de decolagem
void imprimeFilaDecolagem(FilaPrioridade *fila, int numero){
  printf(" Fila Decolagem[%d] = (", numero);
  for(struct Nofila* aux = fila->inicio; aux != NULL; aux = aux->proximo)
  printf("  [%d] ", aux->aviao.id);
  printf(")\n");
}

// função que exibe as pistas
void imprimeFilaPista(FilaPrioridade *fila, int numero){
  printf(" Pista [%d] = (", numero);
  for(struct Nofila* aux = fila->inicio; aux != NULL; aux = aux->proximo)
  printf("  [%d] ", aux->aviao.id);
  printf(")\n");
}

// função de inserção na fila de prioridade que é identica à inserção em uma lista
void entraFila(FilaPrioridade *fila, Aviao aviao){
  struct Nofila* aux = (struct Nofila*) malloc(sizeof(struct Nofila));
  aux->aviao = aviao;

  if(estaVazia(fila)){
    aux->proximo = fila->inicio;
    fila->inicio = aux;
    fila->final = aux;

  }else if(aviao.tempo_restante < fila->inicio->aviao.tempo_restante){
    aux->proximo = fila->inicio;
    fila->inicio = aux;
  }else{
    struct Nofila* temp = fila->inicio;

    while ((temp->proximo != NULL) && (aviao.tempo_restante > temp->proximo->aviao.tempo_restante)) {
      temp = temp->proximo;
    }
    aux->proximo = temp->proximo;
    temp->proximo = aux;

    if(aux->proximo == NULL)
    fila->final = aux;

  }
  fila->tamanho++;
}


// função de remoção da fila
Aviao saiFila(FilaPrioridade *fila){
  Aviao retorno;
  retorno.id = -99;
  retorno.tempo_restante = -99;

  if(estaVazia(fila)){
    return retorno;
  } else {
    struct Nofila *aux = fila->inicio;
    retorno = aux->aviao;

    fila->inicio = fila->inicio->proximo;
    fila->tamanho--;
    free(aux);
    return retorno;
  }
}

// função que simula o desgaste de combustível do avião
void combustivel(FilaPrioridade *fila){
  // diminui o tempo restante de voo de cada avião da fila em uma unidade
  for(struct Nofila* aux = fila->inicio; aux != NULL; aux = aux->proximo)
  aux->aviao.tempo_restante--;
}

// função que retorna o índice da menor fila de aterrissagem para manter o equilibrio de tamanho
int menor_aterrissagem(FilaPrioridade filas[4]){
  int menor=0, x = filas[0].tamanho;

  for(int i = 0; i<4; i++){
    if(x >= filas[i].tamanho){
      x = filas[i].tamanho;
      menor = i;
    }
  }

  return menor;
}

//função que retorna o indice (0 ou 1) da maior fila para pousar na pista 0
int maiorAterrissagemPista0(FilaPrioridade filas[4]){
  int maior=0, x = filas[0].tamanho;

  for(int i = 0; i<2; i++){
    if(x <= filas[i].tamanho){
      x = filas[i].tamanho;
      maior = i;
    }
  }
  return maior;
}

//função que retorna o indice (2 ou 3) da maior fila para pousar na pista 1
int maiorAterrissagemPista1(FilaPrioridade filas[4]){
  int maior=2, x = filas[2].tamanho;

  for(int i = 2; i<4; i++){
    if(x <= filas[i].tamanho){
      x = filas[i].tamanho;
      maior = i;
    }
  }
  return maior;
}

//função que retorna o índice da menor fila de decolagem
int menorFilaDecolagem(FilaPrioridade filas[3]){
  int menor=0, x = filas[0].tamanho;

  for(int i = 0; i<3; i++){
    if(x >= filas[i].tamanho){
      x = filas[i].tamanho;
      menor = i;
    }
  }
  return menor;
}

//função que retorna o numero de pistas vazias
int pistasVazias(FilaPrioridade pista[3]){
  int numero = 3;

  for(int i =0; i<2; i++){
    if(!estaVazia(&pista[i]))
    numero--;
  }
  return numero;
}

int main(int argc, char *argv[]){
  //cria e inicia 4 filas para pouso, 3 filas para decolagem e 3 filas que representam as 3 pistas

  FilaPrioridade fila_aterrissagem[4];
  FilaPrioridade fila_decolagem[3];
  FilaPrioridade pista[3];

  for(int i = 0; i<4; i++){
    iniciaFila(&fila_aterrissagem[i]);
  }
  for(int i = 0; i<3; i++){
    iniciaFila(&fila_decolagem[i]);
    iniciaFila(&pista[i]);
  }

  float media_decolagem, media_aterrissagem;
  float cont_aterrizou = 0, tempo_decolagem =0, cont_decolou =0, tempo_aterrissagem =0;

  int escolha =0 , quantidade, menor_fila, maior_fila, pistas_vazias, cont_cairam =0;
  int id_par = 2, id_impar = 1, cont_sem_combustivel = 0;

  Aviao aviao;

  // função usadapara obter números pseudo-aleatórios
  srand(time(NULL));

  printf("---------------------------------\n");
  printf("Cada aviao tem [tempo_restante]id \n");
  printf("---------------------------------\n");

  do {

    // a cada repetição diminui uma unidade o combuntível de cada acião de cada fila
    for(int i = 0; i<4 ; i++)
    combustivel(&fila_aterrissagem[i]);

    for(int i = 0; i<3 ; i++)
    combustivel(&fila_decolagem[i]);

    // quantidade de avioes que podem chegar para aterrizar, entre 0 e 3
    quantidade = rand() % 3;
    printf("Numero de avioes que chegaram na fila para aterrizar: %d\n", quantidade );

    for(quantidade; quantidade > 0 ; quantidade--){
      // cada avião entra na menor fila de aterrissagem
      menor_fila = menor_aterrissagem(fila_aterrissagem);
      // o seu combustivel é 10 + (aleatorio de 0 a 24)
      aviao.tempo_restante = (rand() % 20) + 1;
      aviao.tempo_inicial = aviao.tempo_restante;
      aviao.id = id_par;
      // entra na fila de aterrissagem
      entraFila(&fila_aterrissagem[menor_fila], aviao);
      id_par += 2;
      if(id_par >= 98)
      id_par = 2;
    }
    // quantidade de avioes que podem chegar para decolar, entre 0 e 3
    quantidade = rand() % 4;
    printf("Numero de avioes que chegaram na fila para decolar: %d\n", quantidade );

    for(quantidade; quantidade > 0 ; quantidade--){
      // cada avião entra na menor fila de decolagem
      menor_fila = menorFilaDecolagem(fila_decolagem);
      //valor arbitrario
      aviao.tempo_restante = 200;
      aviao.tempo_inicial = aviao.tempo_restante;
      aviao.id = id_impar;
      // entra na fila de decolagem
      entraFila(&fila_decolagem[menor_fila], aviao);
      id_impar += 2;
      if(id_impar >= 99)
      id_impar = 1;
    }

    // imprime as filas de aterrissagem e de decolagem
    for(int i = 0; i<4; i++)
    imprimeFilaAterrizagem(&fila_aterrissagem[i], i);
    printf("\n");

    for(int i = 0; i<3; i++)
    imprimeFilaDecolagem(&fila_decolagem[i], i);

    for(int i = 0; i<4; i++){
      if(!estaVazia(&fila_aterrissagem[i])){

        // enquanto houver aviões sem combuntível na fila de aterrissagem:
        while(fila_aterrissagem[i].inicio->aviao.tempo_restante <= 0){
          cont_sem_combustivel++;
          // se estiver com combustível no fim, pouso de emergencia da pista 2
          // caso contrario, pouso na pista 1
          // caso contrario, pouso na pista 0
          // se ainda restar aviões sem combustível, aviao cai
          if(estaVazia(&pista[2])){
            aviao = saiFila(&fila_aterrissagem[i]);
            entraFila(&pista[2], aviao);
            printf("Pouso de emergencia do aviao %d na pista 2\n", aviao.id );

          }else if(estaVazia(&pista[1])){
            aviao = saiFila(&fila_aterrissagem[i]);
            entraFila(&pista[1], aviao);
            printf("Pouso de emergencia do aviao %d na pista 1\n", aviao.id );

          }else if(estaVazia(&pista[0])){
            aviao = saiFila(&fila_aterrissagem[i]);
            entraFila(&pista[0], aviao);
            printf("Pouso de emergencia do aviao %d na pista 0\n", aviao.id );

          }
          else{
            aviao = saiFila(&fila_aterrissagem[i]);
            cont_cairam++;
            printf("--------------------------------------------\n");
            printf("O aviao %d caiu por falta de combustivel.  ", aviao.id );
            printf("--------------------------------------------\n");
            break;
          }
          // se não tiver mais aviões na fila, sai do while
          if(estaVazia(&fila_aterrissagem[i]))
          break;
        }//while
      }//if
    }//for

    // pega a quantidade de pistas vazias e apos isso cria um numero aleatorio de 0 à quantidade
    pistas_vazias = pistasVazias(pista);
    quantidade = rand() % pistas_vazias;

    for(quantidade; quantidade > 0 ; quantidade--){

      if(estaVazia(&pista[0])){
        // pega o índice da maior fila de aterrissagem entre a 0 e 1
        maior_fila = maiorAterrissagemPista0(fila_aterrissagem);
        // se ela não está vazia, sai da fila e entra na pista
        if(!estaVazia(&fila_aterrissagem[maior_fila])){
          aviao = saiFila(&fila_aterrissagem[maior_fila]);
          entraFila(&pista[0], aviao);
          printf("Aviao com id: %d pronto para pousar na pista %d\n", aviao.id,  0);
        }
      }else if(estaVazia(&pista[1])){
        // pega o índice da maior fila de aterrissagem entre a 2 e 3
        maior_fila = maiorAterrissagemPista1(fila_aterrissagem);
        // se ela não esta vazia entra sai da fila e entra na pista
        if(!estaVazia(&fila_aterrissagem[maior_fila])){
          aviao = saiFila(&fila_aterrissagem[maior_fila]);
          entraFila(&pista[1], aviao);
          printf("Aviao com id: %d pronto para pousar na pista %d\n", aviao.id,  1);
        }
      }
    }

    // percorre cada pista verificando se está vazia, caso esteja:
    // tenta colocar um aviao da fila de decolagem na pista, caso a fila esteja vazia:
    // coloca um avião da maior fila de aterrissagem correspodente à pista
    for(int i = 0; i<3; i++){
      if(estaVazia(&pista[i])){
        // se a fila de decolagem não esta vazia:
        if(!estaVazia(&fila_decolagem[i])){
          // aviao sai da fila de decolagem e entra na pista
          aviao = saiFila(&fila_decolagem[i]);
          entraFila(&pista[i], aviao);
          printf("Aviao com id: %d pronto para decolar na pista %d\n", aviao.id,  i);
        }
        else{
          if(i == 0){
            // pega o índice da maior fila de aterrissagem entre a 0 e 1
            maior_fila = maiorAterrissagemPista0(fila_aterrissagem);
            // se ela não está vazia, sai da fila e entra na pista
            if(!estaVazia(&fila_aterrissagem[maior_fila])){
              aviao = saiFila(&fila_aterrissagem[maior_fila]);
              entraFila(&pista[0], aviao);
              printf("Aviao com id: %d pronto para pousar na pista %d\n", aviao.id,  0);
            }
          }
          else if ( i == 1){
            // pega o índice da maior fila de aterrissagem entre a 2 e 3
            maior_fila = maiorAterrissagemPista1(fila_aterrissagem);
            // se ela não esta vazia entra sai da fila e entra na pista
            if(!estaVazia(&fila_aterrissagem[maior_fila])){
              aviao = saiFila(&fila_aterrissagem[maior_fila]);
              entraFila(&pista[1], aviao);
              printf("Aviao com id: %d pronto para pousar na pista %d\n", aviao.id,  1);
            }
          }
        }
      }
    }
    printf("\n");

    // imprime as pistas
    for(int i = 0; i<3; i++)
    imprimeFilaPista(&pista[i], i);
    printf("\n");

    // percorre cada uma das pistas
    for(int i = 0; i<3; i++){
      //se ela não está vazia
      if(!estaVazia(&pista[i])){
        // avião sai da pista
        aviao = saiFila(&pista[i]);
        // se o id por par, foi um pouso, caso contrario uma aterrissagem
        if((aviao.id % 2) != 0 ){
          printf("Aviao com id: %d decolou com sucesso na pista %d\n", aviao.id,  i);
          cont_decolou++;
          tempo_decolagem += aviao.tempo_inicial - aviao.tempo_restante;
          media_decolagem = tempo_decolagem / cont_decolou;
        }else {
          printf("Aviao com id: %d pousou com sucesso na pista %d\n", aviao.id,  i);
          cont_aterrizou++;
          tempo_aterrissagem += aviao.tempo_inicial - aviao.tempo_restante;
          media_aterrissagem = tempo_aterrissagem / cont_aterrizou;
        }
      }
    }
    printf("\nMedia de tempo para decolagem: %.3f tempos\n", media_decolagem);
    printf("Media de tempo para Aterrizagem: %.3f tempos\n", media_aterrissagem);
    printf("Numero de avioes que aterrizaram sem combustivel %d\n", cont_sem_combustivel);
    printf("Avioes que cairam: %d\n", cont_cairam);

    printf("\n-------------------------------------------\n");
    printf("Digite -1 para sair ou outro numero para continuar:\n");
    //scanf("%d", &escolha);
    escolha++;
  }while(escolha != 5000);

  // desaloca memoria
  for(int i = 0; i < 4; i++){
    while(!estaVazia(&fila_aterrissagem[i]))
    saiFila(&fila_aterrissagem[i]);
  }
  for(int i = 0; i < 3; i++){
    while(!estaVazia(&fila_decolagem[i]))
    saiFila(&fila_aterrissagem[i]);
  }

  return 0;
}
