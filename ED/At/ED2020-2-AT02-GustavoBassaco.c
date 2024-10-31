#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <io.h>

typedef struct{
  int codigo;
  char nome[201];
  char sexo;
  float peso;
  float altura;
}Cadastro;

struct NoListaD{
  struct NoListaD *proximo;
  struct NoListaD *anterior;
  Cadastro paciente;
};

typedef struct{
  struct NoListaD *inicio;
  int tamanho;
}ListaD;

void iniciaListaD(ListaD *lista){
  lista->inicio = NULL;
  lista->tamanho = 0;
}

bool estaVaziaListaD(ListaD *lista){
  return (lista->tamanho == 0);
}


void imprimeListaC(ListaD *lista){
  printf("\nLista Crescente = (");
  for(struct NoListaD* aux = lista->inicio; aux != NULL; aux = aux->proximo )
    printf("   %d", aux->paciente.codigo);
  printf("}\n");
}

void imprimeCadastroC(ListaD *lista, FILE *saida){

  for(struct NoListaD* aux = lista->inicio; aux != NULL; aux = aux->proximo )
    fprintf(saida, "{%d,%s,%c,%1.f,%1.f}\n", aux->paciente.codigo, aux->paciente.nome,
      aux->paciente.sexo, aux->paciente.peso, aux->paciente.altura);
}

void imprimeCadastroD(ListaD *lista, FILE *saida){

  struct NoListaD* aux = lista->inicio;
  for( aux = lista->inicio; aux->proximo != NULL; aux = aux->proximo );
  for( aux ; aux != NULL; aux = aux->anterior)
    fprintf(saida, "{%d,%s,%c,%1.f,%1.f}\n", aux->paciente.codigo, aux->paciente.nome,
      aux->paciente.sexo, aux->paciente.peso, aux->paciente.altura);
}

void imprimeListaD(ListaD *lista){
  struct NoListaD* aux = lista->inicio;
  for( aux = lista->inicio; aux->proximo != NULL; aux = aux->proximo );

  printf("Lista Decrescente: (");
  for( aux ; aux != NULL; aux = aux->anterior)
  printf("   %d", aux->paciente.codigo);
  printf(")\n");

}


void entraListaD(ListaD *lista, Cadastro paciente){
  struct NoListaD * aux = (struct NoListaD*) malloc(sizeof(struct NoListaD));
  aux->paciente = paciente;

  if(estaVaziaListaD(lista) || paciente.codigo < lista->inicio->paciente.codigo){
    aux->proximo = lista->inicio;
    aux->anterior = NULL;

    if(!estaVaziaListaD(lista))
    lista->inicio->anterior = aux;

    lista->inicio = aux;

  }else {
    struct NoListaD* temp = lista->inicio;

    while ((temp->proximo != NULL) && (paciente.codigo > temp->proximo->paciente.codigo)) {
      temp = temp->proximo;
    }
    aux->proximo = temp->proximo;
    aux->anterior = temp;

    if(aux->proximo != NULL)
    aux->proximo->anterior = aux;

    temp->proximo = aux;
  }
  lista->tamanho++;
}

// -------------------------------------------------------------
// pesquisa se exite alguma pessoa cadastrada com determinado
// id e retorna as informações dela em um arquivo
// caso a lista esteja vazia, exibe essa informação no arquivo
// caso nao encontra, informa no arquivo
// -------------------------------------------------------------


void pesquisaCadastro(ListaD *lista, FILE *saida, int consulta) {

  if(estaVaziaListaD(lista)){
    fprintf(saida,"Arquivo vazio\n");
    }
struct NoListaD* aux = lista->inicio;
  while(aux != NULL && consulta > aux->paciente.codigo) {
    aux = aux->proximo;
  }
  if(aux == NULL || aux->paciente.codigo > consulta) {
    fprintf(saida,"O paciente nao foi encontrado\n");
  } else{
    fprintf(saida, "{%d,%s,%c,%1.f,%1.f}\n", aux->paciente.codigo, aux->paciente.nome,
      aux->paciente.sexo, aux->paciente.peso, aux->paciente.altura);

  }
}

// -------------------------------------------------------------
// percorre a lista verificando se ha uma pessoa com dado codigo
// -------------------------------------------------------------


bool pesquisaListaD(ListaD *lista, int consulta) {

  if(estaVaziaListaD(lista))
    return false;

struct NoListaD* percorre = lista->inicio;
  while(percorre != NULL && consulta > percorre->paciente.codigo) {
    percorre = percorre->proximo;
  }
  if(percorre == NULL || percorre->paciente.codigo > consulta) {
    return false;
  }
    return true;
}

// -------------------------------------------------------------
// função não usada nesse programa.
// ela removeria uma pessao do Cadastro
// -------------------------------------------------------------


Cadastro removeDaLista(ListaD *lista, int valor){

  if(!estaVaziaListaD(lista) && pesquisaListaD(lista, valor)){
    Cadastro retorna;

    if(valor == lista->inicio->paciente.codigo){
      struct NoListaD *temp = lista->inicio;

      retorna = lista->inicio->paciente;

      lista->inicio = lista->inicio->proximo;

      if(lista->inicio != NULL)
      lista->inicio->anterior = NULL;

      lista->tamanho--;
      free(temp);
      return retorna;

    }else{

      struct NoListaD *aux = lista->inicio;
      struct NoListaD *temp;

      while(aux->proximo != NULL && valor > aux->paciente.codigo){
        temp = aux;
        aux = aux->proximo;
      }

      retorna = aux->paciente;

      if(aux->proximo != NULL)
      aux->proximo->anterior = temp;

      if(aux->proximo != NULL){
      temp->proximo = aux->proximo;
      }else temp->proximo = NULL;

      free(aux);
      lista->tamanho--;
      return retorna;
    }
  }
}

// -------------------------------------------------------------
// destroi a lista
// -------------------------------------------------------------

void destroiRegistro(ListaD *registro){
  while(registro->inicio != NULL){
    struct NoListaD *aux;
    aux = registro->inicio;
    registro->inicio = registro->inicio->proximo;
    registro->tamanho--;
    free(aux);
  }
}

// -------------------------------------------------------------
// fecha a lista e os arquivos usados
// -------------------------------------------------------------

void fechaPrograma(FILE *entrada, FILE *saida, ListaD *registro){
  destroiRegistro(registro);
  fclose(entrada);
  fclose(saida);
  exit(1);
}

int main(int argc, char *argv[]){

  ListaD registro;
  FILE *entrada, *saida;
  int tamanho, escolha;
  Cadastro paciente;
  char resto[201];

  iniciaListaD(&registro);

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
 
  // verifica se o arquivo esta vazio
  long tamanho_arquivo;
  // salva o tamanho do arquivo
  tamanho_arquivo = filelength( fileno( entrada ) );

   if ( tamanho_arquivo == 0L ){ // teste para saber se o tamanho do arquivo é zero
     printf("\nArquivo vazio \n");
     fechaPrograma(entrada, saida, &registro);
   }

   char primeira = fgetc(entrada);
   if(primeira != '{'){
      printf("Arquivo fora do padrao\n");
      fechaPrograma(entrada, saida, &registro);
   }

   while(primeira == '{'){

     fscanf(entrada,"%d,", &paciente.codigo);
     fscanf(entrada,"%200[^,]s", &paciente.nome);
     fscanf(entrada,",%c", &paciente.sexo);
     fscanf(entrada,",%f", &paciente.peso);
     fscanf(entrada,",%f", &paciente.altura);

      fgets(resto, 200, entrada);
      tamanho = strlen(resto);

      if(pesquisaListaD(&registro, paciente.codigo)){
        printf("Erro: dois pacientes com o mesmo codigo\n");
        fechaPrograma(entrada, saida, &registro);
      }

      if(resto[0] != '}'){
        printf("Arquivo fora do padrao\n");
        fechaPrograma(entrada, saida, &registro);
      }
      for(int i = 1; i < tamanho; i++){
        // se houver letra ou pontuação ou digitos: fecha
        if(ispunct(resto[i]) || isalpha(resto[i]) || isdigit(resto[i])){
          printf("Arquivo fora do padrao\n");
          fechaPrograma(entrada, saida, &registro);
        }//if
      }//for

     primeira = fgetc(entrada);
     entraListaD(&registro, paciente);
 }//while

    // volta para a primeira posição da linha
     fseek(entrada, -1, SEEK_CUR);

     fgets(resto, 200, entrada);
     tamanho = strlen(resto);
     //se não for restritamente numero: fecha
     for(int i = 0; i < tamanho; i++){
       if(ispunct(resto[i]) || isalpha(resto[i])) {
         printf("Arquivo fora do padrao\n");
         fechaPrograma(entrada, saida, &registro);
       }//if
     }//for

     //volta para a linha de cima
     fseek(entrada, -(tamanho+1), SEEK_CUR);

     fscanf(entrada, "%d", &escolha);

     //desce para a linha seguinte do arquivo
     fgets(resto, 200, entrada);

     switch(escolha){
       case 1:
        imprimeCadastroC(&registro, saida);
       break;

       case 2:
        imprimeCadastroD(&registro, saida);
       break;

       case 3:

       // verifica se apenas há numeros
       fgets(resto, 200, entrada);
       tamanho = strlen(resto);

       for(int i = 0; i < tamanho; i++){
         if(ispunct(resto[i]) || isalpha(resto[i])) {
           printf("Arquivo fora do padrao\n");
           fechaPrograma(entrada, saida, &registro);
         }//if
       }//for

       //volta para linha anterior
       fseek(entrada, -(tamanho+1), SEEK_CUR);

       fscanf(entrada, "%d", &escolha);
       printf("%d\n",escolha );
       pesquisaCadastro(&registro, saida, escolha);
       break;

       default:
       printf("Escolha invalida\n");
       break;
     }

     fechaPrograma(entrada, saida, &registro);

  return 0;
}
