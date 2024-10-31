#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <io.h>

struct NoLista{
  struct NoLista* proximo;
  int valor;
};

typedef struct{
  struct NoLista* inicio;
  int tamanho;
}ListaDinamica;

struct Objeto{
  char palavra[100];
  ListaDinamica lista;

};

struct NoArvore{
  struct NoArvore* esquerda;
  struct NoArvore* direita;
  struct Objeto objeto;
};

// -----------------------------------------------------------------
//  Lista Simplismente Encadeada
// -----------------------------------------------------------------

void iniciaLista(ListaDinamica* lista){
  lista->inicio = NULL;
  lista->tamanho = 0;
}

bool estaVazia(ListaDinamica *lista){
  return (lista->tamanho == 0);
}

bool percorre(ListaDinamica *lista, int valor){
  if(estaVazia(lista)){
    return false;
  }else{
    struct NoLista *aux = lista->inicio;
    while(aux != NULL && aux->valor <= valor){
      if(aux->valor == valor) return true;
      aux= aux->proximo;
    }
    return false;
  }
}

void entraListaDinamica(ListaDinamica *lista, int valor){
  if(!percorre(lista, valor)){
    struct NoLista* aux = lista->inicio;
    struct NoLista* temp = (struct NoLista*) malloc(sizeof(struct NoLista));
    temp->valor = valor;

    if(estaVazia(lista) || valor < lista->inicio->valor){
      temp->proximo = lista->inicio;
      lista->inicio= temp;
    }else{

      while(aux->proximo != NULL && aux->proximo->valor < valor ){
        aux = aux->proximo;
      }

      temp->proximo = aux->proximo;
      aux->proximo = temp;
    }
    lista->tamanho++;
  }
}

void imprimeLista(ListaDinamica *lista, FILE *saida) {
  if(estaVazia(lista))
  fprintf(saida, ": Nenhuma ocorrencia");
  for(struct NoLista* aux = lista->inicio; aux != NULL; aux = aux->proximo)
  fprintf(saida,",  %d", aux->valor);

}

//--------------------------------------------------------
//  Arvore Binaria
//--------------------------------------------------------


void iniciaArvoreBinaria(struct NoArvore **arvore){
  *arvore = NULL;
}

bool estaVaziaArvore(struct NoArvore **arvore) {
  return(*arvore == NULL);
}



void imprimeSaida(struct NoArvore **arvore, FILE *saida){
  if(*arvore == NULL)
  return;

  imprimeSaida(&(*arvore)->esquerda, saida);

  fprintf(saida, "%s", (*arvore)->objeto.palavra);
  imprimeLista(&(*arvore)->objeto.lista, saida);
  fprintf(saida, "\n");

  imprimeSaida(&(*arvore)->direita, saida);
}


bool pesquisaArvoreBinaria(struct NoArvore **arvore, char palavra[], int pagina){

  if(*arvore == NULL)
  return (false);

  if(strcasecmp((*arvore)->objeto.palavra, palavra) == 0){
    //printf("%s\n",(*arvore)->objeto.palavra );
    entraListaDinamica(&(*arvore)->objeto.lista, pagina);
    return true;
  }


  if(strcasecmp((*arvore)->objeto.palavra, palavra) > 0){
    return (pesquisaArvoreBinaria(&(*arvore)->esquerda, palavra, pagina));
  } else {
    return (pesquisaArvoreBinaria(&(*arvore)->direita, palavra, pagina));
  }
}

bool inserirArvoreBinaria(struct NoArvore **arvore, char palavra[100]){

  if(*arvore == NULL){
    (*arvore) = malloc(sizeof(struct NoArvore));
    (*arvore)->direita = NULL;
    (*arvore)->esquerda = NULL;
    strcpy((*arvore)->objeto.palavra, palavra);
    iniciaLista(&(*arvore)->objeto.lista);
    return true;
  }

  if(strcasecmp((*arvore)->objeto.palavra, palavra) == 0 ){
    return false;
  }

  if(strcasecmp((*arvore)->objeto.palavra, palavra) > 0 ){
    return (inserirArvoreBinaria(&(*arvore)->esquerda, palavra));
  }else {
    return (inserirArvoreBinaria(&(*arvore)->direita, palavra));
  }
}

void destroiArvore(struct NoArvore **noArvore){

  if((*noArvore) != NULL){
    destroiArvore(&(*noArvore)->esquerda);
    destroiArvore(&(*noArvore)->direita);
    free(*noArvore);
    (*noArvore)=NULL;
  }
}

int main(int argc, char* argv[]){

  struct NoArvore *raiz;
  iniciaArvoreBinaria(&raiz);

  long tamanho_arquivo;
  int tamanho, pagina;
  char *sub;
  char linha[200];
  char palavra[100];

  FILE *entrada, *saida;

  entrada = fopen(argv[1], "r");
  if(entrada == NULL){
    printf("Erro na abertura do arquivo de entrada\n");
    exit(1);
  }

  saida = fopen(argv[2], "w");
  if(saida == NULL){
    printf("Erro na abertura do arquivo de saida\n");
    fclose(entrada);
    exit(1);
  }

  // salva o tamanho do arquivo
  tamanho_arquivo = filelength( fileno( entrada ) );

  if ( tamanho_arquivo == 0L ){ // teste para saber se o tamanho do arquivo é zero
    printf("\nArquivo vazio \n");
    exit(1);
  }

  //verifica se o arquivo esta dentro do padrão
  fgets(linha, 9, entrada);
  if( strcasecmp(linha, "<termos:") != 0){
    printf("Arquivo fora do modelo\n");
    exit(1);
  }
  //pega as palavras para busca
  fscanf(entrada,"%s>", linha);
  sub = strtok(linha, ",>");

  //se não houver palavras, fecha
  if(strlen(sub) == 1){
    fprintf(saida, "Nenhuma consulta\n" );
    fclose(entrada);
    fclose(saida);
    exit(1);
  }


  //insere as palavras na arvore
  while(sub != NULL){
    inserirArvoreBinaria(&raiz, sub);
    sub= strtok(NULL, ",>");
  }

  //verifica se o arquivo esta correto
  fseek(entrada, -1, SEEK_CUR);

  fgets(linha, 200, entrada);
  tamanho = strlen(linha);


  if(linha[0] != '>'){
    printf("Arquivo fora do padrao %c\n", linha[0]);
    exit(1);
  }

  for(int i = 1; i < tamanho; i++){
    // se houver letra ou pontuação ou digitos: fecha
    if(ispunct(linha[i]) || isalpha(linha[i]) || isdigit(linha[i])){
      printf("Arquivo fora do padrao\n");
      exit(1);
    }//if
  }//for

  char pagina_char[10];
  int aux = 0;

  // while(fgets(linha, 300, entrada) != NULL){
  //   sub = strtok(linha," ,.() \n");
  //   while (sub != NULL) {
  //     if (sub[0] == '<' && sub[1] == 'p' && sub[2] == 'a' && sub[3] == 'g' && sub[4] == 'e') {
  //       while (sub[6+aux] != '>'){
  //         pagina_char[aux] = sub[6+aux];
  //         aux++;
  //       }
  //       pagina = atoi(pagina_char);
  //       aux=0;
  //     }
  //
  //     pesquisaArvoreBinaria(&raiz, sub, pagina);
  //     sub = strtok(NULL, " ,.() \n");
  //   }
  // }

  //pega cada palavra do arquivo
    while(fgets(linha, 200, entrada) != NULL){
      sub = strtok(linha, " .,:\n>");

      while(sub != NULL){
        //compara a palavra para saber se mudiu a pagina
        if(strcasecmp(sub, "<page") == 0){
          //caso sim, a pagin é atualizada
          sub= strtok(NULL, " .,:\n>");
          pagina = atoi(sub);
        }
        //verifica se a palavra esta na arvore
        pesquisaArvoreBinaria(&raiz, sub, pagina);
        sub= strtok(NULL, " .,:\n>");
      }
    }

  imprimeSaida(&raiz, saida);
  destroiArvore(&raiz);
  fclose(entrada);
  fclose(saida);

  return 0;
}
