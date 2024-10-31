#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <io.h>

struct NoAVL_N{
  struct NoAVL_N* direita;
  struct NoAVL_N* esquerda;
  int altura;
  int id;
  int rrn;
};

void iniciaArvoreAVL_N(struct NoAVL_N **arvore){
  *arvore = NULL;
}


int alturaAVL_N(struct NoAVL_N **arvore) {
  if (*arvore == NULL)
  return 0; // altura da árvore vazia
  else return (*arvore)->altura;
}

void imprimeEmOrdem_N(struct NoAVL_N **arvore, FILE* arquivo){
  if(*arvore == NULL)
  return;

  imprimeEmOrdem_N(&(*arvore)->esquerda, arquivo);
  fprintf(arquivo,"%4d   %d\n", (*arvore)->id, (*arvore)->rrn);
  imprimeEmOrdem_N(&(*arvore)->direita, arquivo);

}

int atualizaAltura_AVL_N(struct NoAVL_N *esquerda, struct NoAVL_N *direita){

  int he = alturaAVL_N(&esquerda);
  int hd = alturaAVL_N(&direita);
  if (he > hd)
  return he + 1;
  else
  return hd + 1;
}

void rotacaoSimplesEsquerda_N(struct NoAVL_N **arvore){
  struct NoAVL_N *u = (*arvore)->direita;

  (*arvore)->direita = u->esquerda;
  u->esquerda = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_N((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_N(u->esquerda, u->direita);
  (*arvore)=u;
}

void rotacaoSimplesDireita_N(struct NoAVL_N **arvore){
  struct NoAVL_N *u = (*arvore)->esquerda;

  (*arvore)->esquerda = u->direita;
  u->direita = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_N((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_N(u->esquerda, u->direita);
  (*arvore)=u;
}

void rotacaoDuplaEsquerda_N(struct NoAVL_N **arvore){
  struct NoAVL_N *u = (*arvore)->direita;
  struct NoAVL_N *v = u->esquerda;

  (*arvore)->direita = v->esquerda;
  u->esquerda = v->direita;
  v->direita = u;
  v->esquerda = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_N((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_N(u->esquerda, u->direita);
  v->altura = atualizaAltura_AVL_N(v->esquerda, v->direita);

  (*arvore)= v;
}

void rotacaoDuplaDireita_N(struct NoAVL_N **arvore){
  struct NoAVL_N *u = (*arvore)->esquerda;
  struct NoAVL_N *v = u->direita;

  u->direita = v->esquerda;
  v->esquerda = u;
  (*arvore)->esquerda = v->direita;
  v->direita = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_N((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_N(u->esquerda, u->direita);
  v->altura = atualizaAltura_AVL_N(v->esquerda, v->direita);

  (*arvore)= v;
}

void balanceiaAVL_N(struct NoAVL_N **arvore){

  int he =  alturaAVL_N(&(*arvore)->esquerda);
  int hd = alturaAVL_N(&(*arvore)->direita);
  int h = hd - he;
  struct NoAVL_N *temp;

  if(h < 0 ){
    temp = (*arvore)->esquerda;
    he = alturaAVL_N(&temp->esquerda);
    hd = alturaAVL_N(&temp->direita);
    h = hd - he;

    if(h < 0){
      rotacaoSimplesDireita_N(&(*arvore));
    }else{
      rotacaoDuplaDireita_N(&(*arvore));
    }
  }else{
    temp = (*arvore)->direita;
    he = alturaAVL_N(&temp->esquerda);
    hd = alturaAVL_N(&temp->direita);
    h = hd - he;

    if(h>0){
      rotacaoSimplesEsquerda_N(&(*arvore));
    }else{
      rotacaoDuplaEsquerda_N(&(*arvore));
    }
  }
}

int maiorValorEsquerda_N(struct NoAVL_N** arvore){
  if((*arvore)->direita == NULL )
  return (*arvore)->id;

  if((*arvore)->direita != NULL)
  maiorValorEsquerda_N(&(*arvore)->direita);
}

bool insereAVL_N(struct NoAVL_N **arvore, int id, int rrn){

  bool boleano;
  if(*arvore == NULL){
    (*arvore) = malloc(sizeof(struct NoAVL_N));
    (*arvore)->direita = NULL;
    (*arvore)->esquerda = NULL;
    (*arvore)->id = id;
    (*arvore)->rrn = rrn;
    (*arvore)->altura = 1;
    return true;
  }

  if((*arvore)->id == id){
    return false;
  }

  if(id < (*arvore)->id){
    boleano = (insereAVL_N(&(*arvore)->esquerda, id, rrn));
  }else {
    boleano = (insereAVL_N(&(*arvore)->direita, id, rrn));
  }

  if(!boleano)
  return (false);

  int he =  alturaAVL_N(&(*arvore)->esquerda);
  int hd =  alturaAVL_N(&(*arvore)->direita);
  int h = hd - he;

  if(h > 1 || h < -1){
    balanceiaAVL_N(&(*arvore));

  }
  (*arvore)->altura = atualizaAltura_AVL_N((*arvore)->esquerda, (*arvore)->direita);
  return(true);
}

void destroiAVL_N(struct NoAVL_N **arvore) {
  if((*arvore) != NULL ) {
    destroiAVL_N( &(*arvore)->esquerda);
    destroiAVL_N( &(*arvore)->direita);
    free(*arvore);
    *arvore = NULL;
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct NoAVL_C{
  struct NoAVL_C* direita;
  struct NoAVL_C* esquerda;
  int altura;
  char nome[30];
  int rrn;
};

void iniciaArvoreAVL_C(struct NoAVL_C **arvore){
  *arvore = NULL;
}

int alturaAVL_C(struct NoAVL_C **arvore) {
  if (*arvore == NULL)
  return 0; // altura da árvore vazia
  else return (*arvore)->altura;
}

int atualizaAltura_AVL_C(struct NoAVL_C *esquerda, struct NoAVL_C *direita){

  int he = alturaAVL_C(&esquerda);
  int hd = alturaAVL_C(&direita);
  if (he > hd)
  return he + 1;
  else
  return hd + 1;
}

void rotacaoSimplesEsquerda_C(struct NoAVL_C **arvore){
  struct NoAVL_C *u = (*arvore)->direita;

  (*arvore)->direita = u->esquerda;
  u->esquerda = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_C((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_C(u->esquerda, u->direita);
  (*arvore)=u;
}

void rotacaoSimplesDireita_C(struct NoAVL_C **arvore){
  struct NoAVL_C *u = (*arvore)->esquerda;

  (*arvore)->esquerda = u->direita;
  u->direita = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_C((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_C(u->esquerda, u->direita);
  (*arvore)=u;
}

void rotacaoDuplaEsquerda_C(struct NoAVL_C **arvore){
  struct NoAVL_C *u = (*arvore)->direita;
  struct NoAVL_C *v = u->esquerda;

  (*arvore)->direita = v->esquerda;
  u->esquerda = v->direita;
  v->direita = u;
  v->esquerda = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_C((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_C(u->esquerda, u->direita);
  v->altura = atualizaAltura_AVL_C(v->esquerda, v->direita);

  (*arvore)= v;
}

void rotacaoDuplaDireita_C(struct NoAVL_C **arvore){
  struct NoAVL_C *u = (*arvore)->esquerda;
  struct NoAVL_C *v = u->direita;

  u->direita = v->esquerda;
  v->esquerda = u;
  (*arvore)->esquerda = v->direita;
  v->direita = (*arvore);

  (*arvore)->altura = atualizaAltura_AVL_C((*arvore)->esquerda, (*arvore)->direita);
  u->altura = atualizaAltura_AVL_C(u->esquerda, u->direita);
  v->altura = atualizaAltura_AVL_C(v->esquerda, v->direita);

  (*arvore)= v;
}

void balanceiaAVL_C(struct NoAVL_C **arvore){

  int he =  alturaAVL_C(&(*arvore)->esquerda);
  int hd = alturaAVL_C(&(*arvore)->direita);
  int h = hd - he;
  struct NoAVL_C *temp;

  if(h < 0 ){
    temp = (*arvore)->esquerda;
    he = alturaAVL_C(&temp->esquerda);
    hd = alturaAVL_C(&temp->direita);
    h = hd - he;

    if(h < 0){
      rotacaoSimplesDireita_C(&(*arvore));
    }else{
      rotacaoDuplaDireita_C(&(*arvore));
    }
  }else{
    temp = (*arvore)->direita;
    he = alturaAVL_C(&temp->esquerda);
    hd = alturaAVL_C(&temp->direita);
    h = hd - he;

    if(h>0){
      rotacaoSimplesEsquerda_C(&(*arvore));
    }else{
      rotacaoDuplaEsquerda_C(&(*arvore));
    }
  }
}



void imprimeEmOrdem_C(struct NoAVL_C **arvore, FILE* arquivo){
  if(*arvore == NULL)
  return;

  imprimeEmOrdem_C(&(*arvore)->esquerda, arquivo);
  fprintf(arquivo,"%s%d\n", (*arvore)->nome, (*arvore)->rrn);
  imprimeEmOrdem_C(&(*arvore)->direita, arquivo);

}

bool pesquisaAVL_N(struct NoAVL_N **arvore,FILE *arquivo, int id){

  if(*arvore == NULL)
  return (false);

  if((*arvore)->id == id){
    char string [100];
    fseek(arquivo,(*arvore)->rrn * 65, SEEK_SET);
    fgets(string, 100, arquivo);
    printf("Encontrado:%s\n",string );

    return true;
  }

  if(id < (*arvore)->id)
  return (pesquisaAVL_N(&(*arvore)->esquerda,arquivo, id));
  else
  return (pesquisaAVL_N(&(*arvore)->direita, arquivo, id));
}

bool imprime_atletas(struct NoAVL_C **raiz_primaria, FILE* arquivo){

  if(*raiz_primaria == NULL){
    return (false);
  }

  imprime_atletas(&(*raiz_primaria)->esquerda, arquivo);
  char string [100];
  fseek(arquivo,(*raiz_primaria)->rrn * 65, SEEK_SET);
  fgets(string, 100, arquivo);
  printf("%s",string );
  imprime_atletas(&(*raiz_primaria)->direita, arquivo);
}


bool pesquisaAVL_Nome(struct NoAVL_C **arvore, FILE* arquivo, char nome[30]){

  if(*arvore == NULL){
    return (false);
  }

  if(strcasecmp((*arvore)->nome, nome) == 0){
    char string [100];
    fseek(arquivo,(*arvore)->rrn * 65, SEEK_SET);
    fgets(string, 100, arquivo);
    printf("Encontrado:%s\n",string );
  }

  if(strcasecmp(nome,(*arvore)->nome) < 0){
    return (pesquisaAVL_Nome(&(*arvore)->esquerda, arquivo, nome));
  }else if (strcasecmp(nome, (*arvore)->nome) == 0){
    pesquisaAVL_Nome(&(*arvore)->esquerda, arquivo, nome);
    return pesquisaAVL_Nome(&(*arvore)->direita, arquivo, nome);
  } else{
    return (pesquisaAVL_Nome(&(*arvore)->direita, arquivo, nome));
  }
}

//modalidade
bool pesquisaAVL_Modalidade(struct NoAVL_C **raiz_secundaria_fraca, struct NoAVL_N **raiz_primaria, FILE* arquivo, char nome[30]){

  if(*raiz_secundaria_fraca == NULL){
    return (false);
  }

  if(strcasecmp((*raiz_secundaria_fraca)->nome, nome) == 0){
    pesquisaAVL_N(raiz_primaria, arquivo, (*raiz_secundaria_fraca)->rrn);
  }

  if(strcasecmp(nome,(*raiz_secundaria_fraca)->nome) < 0){
    return (pesquisaAVL_Modalidade(&(*raiz_secundaria_fraca)->esquerda, raiz_primaria, arquivo, nome));
  }else if (strcasecmp(nome, (*raiz_secundaria_fraca)->nome) == 0){
    pesquisaAVL_Modalidade(&(*raiz_secundaria_fraca)->esquerda, raiz_primaria, arquivo, nome);
    return pesquisaAVL_Modalidade(&(*raiz_secundaria_fraca)->direita, raiz_primaria, arquivo, nome);
  } else{
    return (pesquisaAVL_Modalidade(&(*raiz_secundaria_fraca)->direita, raiz_primaria, arquivo, nome));
  }
}

char *maiorValorEsquerda_C(struct NoAVL_C** arvore){
  if((*arvore)->direita == NULL )
  return (*arvore)->nome;

  if((*arvore)->direita != NULL)
  maiorValorEsquerda_C(&(*arvore)->direita);
}

bool insereAVL_C(struct NoAVL_C **arvore, char nome[30], int rrn){

  bool boleano;
  if(*arvore == NULL){
    (*arvore) = malloc(sizeof(struct NoAVL_C));
    (*arvore)->direita = NULL;
    (*arvore)->esquerda = NULL;
    strcpy((*arvore)->nome, nome);
    (*arvore)->rrn = rrn;
    (*arvore)->altura = 1;
    return true;
  }

  if(strcasecmp(nome, (*arvore)->nome) == 0) {
    if(rrn == (*arvore)->rrn)
    return false;
    else{
      if(rrn < (*arvore)->rrn){
        boleano = (insereAVL_C(&(*arvore)->esquerda, nome, rrn));
      }else {
        boleano = (insereAVL_C(&(*arvore)->direita, nome, rrn));

      }
    }
  }

  if(strcasecmp(nome, (*arvore)->nome) < 0){
    boleano = (insereAVL_C(&(*arvore)->esquerda, nome, rrn));
  }else if(strcasecmp(nome, (*arvore)->nome) > 0){
    boleano = (insereAVL_C(&(*arvore)->direita, nome, rrn));
  }

  if(!boleano)
  return (false);

  int he =  alturaAVL_C(&(*arvore)->esquerda);
  int hd =  alturaAVL_C(&(*arvore)->direita);
  int h = hd - he;

  if(h > 1 || h < -1){
    balanceiaAVL_C(&(*arvore));

  }
  (*arvore)->altura = atualizaAltura_AVL_C((*arvore)->esquerda, (*arvore)->direita);
  return(true);
}

void Tarefa1(FILE* entrada, FILE* indice_primario, struct NoAVL_N **raiz_primaria){

  char string[200], numero[4];
  int  rrn = 0, i =0, id;
  fseek(entrada,0, SEEK_SET);

  while(fgets(string, 200, entrada)){
    i=0;
    while(string[i] != ' '){
      numero[i] = string[i];
      i++;
    }
    id = atoi(numero);
    insereAVL_N(raiz_primaria, id, rrn);
    rrn++;
  }
  imprimeEmOrdem_N(raiz_primaria, indice_primario);
}

void Tarefa2(FILE* atletas, FILE* indice_primario, FILE* indice_secundario_forte, FILE *indice_secundario_fraco,
  struct NoAVL_N **raiz_primaria, struct NoAVL_C **raiz_secundaria_forte, struct NoAVL_C **raiz_secundaria_fraca){

    char string[200];
    char *nome =  malloc(30*sizeof(char));

    int rrn = 0, i, j;
    fseek(atletas,0, SEEK_SET);

    while(fgets(string, 200, atletas)){
      for(i = 0, j = 4; i<30 ; i++, j++){
        nome[i] = string[j];
      }

      insereAVL_C(raiz_secundaria_forte, nome, rrn);
      rrn++;
    }

    imprimeEmOrdem_C(raiz_secundaria_forte, indice_secundario_forte);

    int  id;
    char numero[4];
    fseek(atletas,0, SEEK_SET);

    while(fgets(string, 200, atletas)){
      i=0;
      while(string[i] != ' '){
        numero[i] = string[i];
        i++;
      }
      id = atoi(numero);
      //limpando o nome para não ficar lixo de outro nome
      for(i = 0; i<30; i++){
        nome[i]= ' ';
      }
      // salva 25 caracteres partindo do caracter 38 da linha
      for(i = 0, j = 38; i<25 ; i++, j++){
        nome[i] = string[j];
      }

      insereAVL_C(raiz_secundaria_fraca, nome, id);
    }
    imprimeEmOrdem_C(raiz_secundaria_fraca, indice_secundario_fraco);
    free(nome);
  }


  void destroiAVL_C(struct NoAVL_C **arvore) {
    if((*arvore) != NULL ) {
      destroiAVL_C( &(*arvore)->esquerda);
      destroiAVL_C( &(*arvore)->direita);
      free(*arvore);
      *arvore = NULL;
    }
  }


  int main(int argc, char *agrv[]){
    system("color m");
    bool estado = false;
    int tamanho;
    int escolha = 0;
    char a;
    char string[200];
    char *nome = malloc(30*sizeof(char));

    struct NoAVL_N *raiz_primaria;
    struct NoAVL_C *raiz_secundaria_forte, *raiz_secundaria_fraca;
    iniciaArvoreAVL_N(&raiz_primaria);
    iniciaArvoreAVL_C(&raiz_secundaria_forte);
    iniciaArvoreAVL_C(&raiz_secundaria_fraca);

    FILE *indice_secundario_forte = fopen("indice_secundario_forte.txt", "w+");
    FILE *indice_secundario_fraco = fopen("indice_secundario_fraco.txt", "w+");
    FILE *indice_primario  = fopen("indice_primario.txt", "w+");
    FILE *atletas = fopen("atletas.txt", "r");

    if(indice_primario == NULL|| atletas == NULL || indice_secundario_forte == NULL || indice_secundario_fraco == NULL){
      printf("Erro na abertura do arquivo\n");
      exit(1);
    }
    while(estado == false){
      a = fgetc(indice_primario);
      if(a == EOF){
        printf("Arquivo de Indice primario vazio \n");
        Tarefa1(atletas, indice_primario, &raiz_primaria);
      }
      else{
        printf("Arquivo de indice primario foi criado corretamente \n");
        estado = true;
      }
    }

    while(estado == true){
      a = fgetc(indice_secundario_forte);
      if(a == EOF){
        printf("Arquivo de Indice Secundário foretemente ligado vazio\n");
        Tarefa2(atletas, indice_primario, indice_secundario_forte, indice_secundario_fraco,
          &raiz_primaria, &raiz_secundaria_forte, &raiz_secundaria_fraca);
        }
        else{
          printf("Arquivo de Indice Secundario fortemente ligado foi criado corretamente \n");
          estado = false;
        }
      }

      while(estado == false){
        a = fgetc(indice_secundario_fraco);
        if(a == EOF){
          printf("Arquivo de Indice Secundário fracamente ligado vazio\n");
          Tarefa2(atletas, indice_primario, indice_secundario_forte, indice_secundario_fraco,
            &raiz_primaria, &raiz_secundaria_forte, &raiz_secundaria_fraca);
          }
          else{
            printf("Arquivo de Indice Secundario fracamente ligado foi crido corretamente \n");
            estado = true;
          }
        }

        rewind(indice_primario);

        while(escolha != 4){
          printf("\nDigite qualquer tecla para prosseguir.\n" );
          getchar();
          system("cls");
          printf("=========== Amigos do Astolfo ===========\n");
          printf("1 - Listar todos os dados dos Atletas\n");
          printf("2 - Pesquisar por Nome\n");
          printf("3 - Pesquisar por Modalidade\n");
          printf("4 - Sair do Programa\n");
          printf("\nDigite sua Opcao: ");
          // garantindo caso aconteça um erro do usuário, não havera bugs.
          escolha = 5;
          scanf("%d", &escolha);
          while(getchar() != '\n');

          switch (escolha) {

            case 1:
            printf("\n=========================================\n");
            printf("      Imprimeindo Lista de ateltas\n" );
            printf("=========================================\n\n");
            imprime_atletas(&raiz_secundaria_forte, atletas);
            printf("\n=========================================\n");
            break;

            case 2:

            printf("\n=========================================\n");
            printf("Digite o nome do Atleta: ");
            scanf("%29[^\n]s", nome);
            while(getchar() != '\n');
            printf("=========================================\n\n");
            //preenche o nome com espaços para realizar a pesquisa corretamente
            tamanho = strlen(nome);
            for (int i =tamanho; i<30; i++){
              nome[i] = ' ';
            }
            pesquisaAVL_Nome(&raiz_secundaria_forte, atletas, nome);
            printf("=========================================\n");

            break;

            case 3:
            printf("\n=========================================\n");
            printf("Digite o nome da Modalidade: ");
            scanf("%24[^\n]s", nome);
            while(getchar() != '\n');
            printf("=========================================\n\n");
            tamanho = strlen(nome);
            for (int i =tamanho; i<30; i++){
              nome[i] = ' ';
            }
            pesquisaAVL_Modalidade(&raiz_secundaria_fraca, &raiz_primaria, atletas, nome);
            printf("=========================================\n");
            break;
            case 4:
            break;

            default:
            printf("Opção Invalida. Digite novamente.\n");
            break;
          }

        }
        printf("\n=========================================\n");
        printf("    Obrigado, Volte sempre!\n");
        printf("=========================================\n");

        destroiAVL_N(&raiz_primaria);
        destroiAVL_C(&raiz_secundaria_fraca);
        destroiAVL_C(&raiz_secundaria_forte);

        fclose(atletas);
        fclose(indice_primario);
        fclose(indice_secundario_forte);
        fclose(indice_secundario_fraco);


        return 0;
      }
