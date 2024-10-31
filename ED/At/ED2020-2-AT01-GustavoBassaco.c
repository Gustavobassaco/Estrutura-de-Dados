#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <io.h>
//tamanho maximo da pilha Estatica
#define N 100

//definicao da estrtura pilha Estatica
typedef struct{
  int numero;
}objeto;

typedef struct{
  objeto vetor[N];
  int topo;
}pilhaEstatica;

//inicia pilha estatica
void iniciaPilhaEstatica(pilhaEstatica *pilha){
  pilha->topo = 0;
}

//verifica se a pilha estatica esta vazia
bool estaVaziaEstatica(pilhaEstatica *pilha){
  return (pilha->topo == 0);
}

//verifica se a pilha estatica esta cheia
bool estaCheiaEstatica(pilhaEstatica *pilha){
  return (pilha->topo == N);
}

// empilha um elemento na pilha Estatica
void empilhaEstatica(pilhaEstatica *pilha, int valor){
  if(!estaCheiaEstatica(pilha)){
    pilha->vetor[pilha->topo].numero = valor;
    pilha->topo++;
  }else {
    printf("\n Alerta: A pilha esta cheia\n");
  }
}

// desempilha um elemento da pilha Estatica
int desempilhaEstatica(pilhaEstatica *pilha){
  int valor = 0;
  if(!estaVaziaEstatica(pilha)){
    valor = pilha->vetor[pilha->topo- 1].numero;
    pilha->topo--;
    return valor;
  }else printf("\n pilha vazia");
}

// verifica o tamanho da pilha Estatica
  int tamanhoPilhaEstatica(pilhaEstatica *pilha){
    int contador=0;
    for(int i = 0; i<pilha->topo; i++)
    contador++;
    return contador;
  }

// definicao da estrutura pilha dinamica
struct No{
  int valor;
  struct No *proximo;
};

typedef struct{
  struct No *topo;
  int tamanho;;
}PilhaDinamica;

// inicia pilha dinamica
void iniciaPilhaDinamica(PilhaDinamica *p){
  p->topo = NULL;
  p->tamanho = 0;
}

// verifica se a pilha dinamica esta vazia
bool estaVaziaDinamica(PilhaDinamica *p){
  return (p->tamanho == 0);
}

//empilha um elemento na pilha
void empilhaDinamica(PilhaDinamica *p, int valor){
  // aloca memoria para um No da pilha
  struct No* Aux = (struct No*) malloc(sizeof(struct No));
  Aux->valor = valor;
  Aux->proximo = p->topo;
  p->topo = Aux;
  p->tamanho++;
}

int desempilhaDinamica(PilhaDinamica *p){
  int retorna= -1;
  if(!estaVaziaDinamica(p)){
    struct No* Aux;
    Aux = p->topo;
    retorna = Aux->valor;
    p->topo = p->topo->proximo;
    p->tamanho--;
    free(Aux);
    return retorna;
  }else printf("\n A pilha esta vazia!");
}
// fecha os arquivos
  void fechaArquivo(FILE* entrada, FILE* saida){
    fclose(entrada);
    fclose(saida);
  }

int main(int argc, char *argv[]){

  FILE *entrada, *saida;
  int numero, tamanho;
  int retorno, resto;
  char string[200];

  //abre o arquivo de entrada com o nome do segundo argumento do prompt de comanda
  entrada = fopen(argv[1], "r");

  //verifica se o arquivo de entrada foi aberto corretamente
  if(entrada == NULL){
    printf("\nFalha ao abrir o arquivo.\n ");
    exit(1);
  }

  // abre o arquivo de saida com o nome do terceiro argumento do prompt de comando
  saida = fopen(argv[2], "w");

  //verifica se o arquivo de saida foi aberto corretamente
  if(saida == NULL){
    printf("\nFalha ao abrir o arquivo\n");
    fclose(entrada);
    exit(1);
  }

    // verifica se o arquivo esta vazio
    long tamanho_arquivo;
    // salva o tamanho do arquivo
    tamanho_arquivo = filelength( fileno( entrada ) );

     if ( tamanho_arquivo == 0L ){ // teste para saber se o tamanho do arquivo é zero
       printf("\nArquivo vazio \n");
       fechaArquivo(entrada,saida);
       exit(1);
     }

    //verifica se o primeiro caractere do arquivo é a letra 'd'
    char primeira = fgetc(entrada);

    // le todas as linhas do arquivo
    while(fgets(string, 200, entrada) != NULL){
      tamanho = strlen(string);
      //verifica se existem letras ou pontos no arquivo, caso existam, fecha o programa
      for(int i = 0; i < tamanho; i++){
        if(ispunct(string[i]) || isalpha(string[i])){
          printf("\nERRO: O Arquivo so pode conter numeros decimais positivos\n");
          fechaArquivo(entrada, saida);
          exit(1);
        }//if
      }//for
    }//while

    //coloca o ponteiro do arquivo na segunda posicao do arquivo
   fseek(entrada,1, SEEK_SET);

   // se for d, entao o prorama transforma em binario utilizando pilhas dinamicas
  if(primeira == 'd' || primeira == 'D'){
    //declaracao de variaveis
    PilhaDinamica pilha1, pilha2;
    //inicia as duas pilhas
    iniciaPilhaDinamica(&pilha1);
    iniciaPilhaDinamica(&pilha2);

    //percorre o arquivo salvando os valores na pilha1
  while(!feof(entrada)){
      //salva os valores de cada linha na variavel numero
      fscanf(entrada,"%d", &numero);
      //empilha o valor de numero
      empilhaDinamica(&pilha1, numero);
  }//while

    // desempilha o ultimo valor da pilha pois ele se repete
    desempilhaDinamica(&pilha1);

    //percorre toda a pilha1
    while(pilha1.topo != NULL){
      //salva o valor do topo da pilha1 na variavel retorno
      retorno = desempilhaDinamica(&pilha1);

      //se retorno igual a 0, imprime 0
      if(retorno == 0){
        fprintf(saida, "%d\n", 0);
      }else{
      // se retorno diferente de o
      while(retorno != 0){
        // salva o resto da divisao por dois
        resto = retorno%2;
        // empilha o valor resto da pilha2
        empilhaDinamica(&pilha2, resto);
        //retorno = retorno dividido por 2
        retorno /= 2;

      }//while

      //percorre a pilha2
      while(!estaVaziaDinamica(&pilha2)){
        //salva o valor do topo na variavel retorno
        retorno = desempilhaDinamica(&pilha2);
        // salva o retorno no arquivo de saida
        fprintf(saida, "%d", retorno);
      }//while
      //quebra a linha
      fprintf(saida, "\n");
    }//else
  }//while principal
  }

  else if(primeira == 'e' || primeira == 'E' ){
    pilhaEstatica pilha1, pilha2;
    //inicia as duas pilhas
    iniciaPilhaEstatica(&pilha1);
    iniciaPilhaEstatica(&pilha2);

  //percorre o arquivo salvando os valores na pilha1
  while(!feof(entrada)){
      //salva os valores de cada linha na variavel numero
      fscanf(entrada,"%d", &numero);
      //empilha o valor de numero
      empilhaEstatica(&pilha1, numero);
  }//while

    // desempilha o ultimo valor da pilha pois ele se repete
    desempilhaEstatica(&pilha1);

    //percorre toda a pilha1
    while(!estaVaziaEstatica(&pilha1)){
      //salva o valor do topo da pilha1 na variavel retorno
      retorno = desempilhaEstatica(&pilha1);

      //se retorno igual a 0, imprime 0
      if(retorno == 0){
        fprintf(saida, "%d\n", 0);
      }else{
      // se retorno diferente de o
      while(retorno != 0){
        // salva o resto da divisao por dois
        resto = retorno%2;
        // empilha o valor resto da pilha2
        empilhaEstatica(&pilha2, resto);
        //retorno = retorno dividido por 2
        retorno /= 2;

      }//while

      //percorre a pilha2
      while(!estaVaziaEstatica(&pilha2)){
        //salva o valor do topo na variavel retorno
        retorno = desempilhaEstatica(&pilha2);
        // salva o retorno no arquivo de saida
        fprintf(saida, "%d", retorno);
      }//while
      //quebra a linha
      fprintf(saida, "\n");
    }//else
  }//while principal
  }else printf("\n Letra inicial nao valida: ");

  //fecha os arquivos
  fechaArquivo(entrada, saida);

  return 0;
}//main
