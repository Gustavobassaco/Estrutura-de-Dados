#include  "ordenacao.c"

int main(int argc, char *argv[]){

  double tempo1, tempo2;
  clock_t ticks[4];// para saber o tempo de execução total e o de ordenação
  long int comparacao = 0;
  long int troca = 0;

  ticks[0] = clock();//Pega o tempo1 antes

  if(argc != 3){
    printf("numero de argumentos invalido\n");
    exit(1);
  }
  char escolha= argv[1][0];

  FILE *arquivo = fopen(argv[2], "r");
  if(arquivo == NULL){
    printf("Erro na abertura do aquivo \n");
    exit(1);
  }

  int tamanho = 0, tam;
  char string[200];
  int numero, i = 0;

  //encontra o numero de valores para saber quanta memoria alocar
  while(fgets(string, 200, arquivo) != NULL ){
    tamanho++;
    tam = strlen(string);
    for(int j = 0; j < tam; j++){
      // se houver letra ou pontuação: fecha
      if( ispunct(string[j]) || isalpha(string[j])){
        printf("Arquivo fora do padrao\n");
        exit(1);
      }//if
    }//for
  }

  int *vetor = (int*) malloc(tamanho*sizeof(int));

  fseek(arquivo,0, SEEK_SET);
  while(fgets(string, 200, arquivo) != NULL ){
    // pega cada numero de cada linha como string e o transforma em decimal
    // apos isso coloca o numero dentro de um vetor
    numero = atoi(string);
    vetor[i] = numero;
    i++;
  }
  tam = strlen(argv[2]);
  char extensao[60];
  char nome[60];

  // pega o nome do arquivo com numeros
  // mas desconsidera sua extensão
  for(int j = 0 ; j<tam - 4; j++){
    nome[j] = argv[2][j];
  }

   ticks[2] = clock();//Pega o tempo1 antes
  switch(escolha){
    case 'b':
    case 'B':
    bubbleSort(vetor, tamanho, &troca, &comparacao);
    strcpy(extensao, "_bubblesort.txt");
    strcat(nome, extensao);

    break;
    case 'i':
    case 'I':
    InsertionSort(vetor, tamanho, &troca, &comparacao);
    strcpy(extensao, "_insertionsort.txt");
    strcat(nome, extensao);

    break;
    case 's':
    case 'S':
    SelectionSort(vetor, tamanho, &troca, &comparacao);
    strcpy(extensao, "_selectionsort.txt");
    strcat(nome, extensao);

    break;
    case 'm':
    case 'M':
    mergeSort(vetor, 0,  tamanho-1, &troca, &comparacao);
    strcpy(extensao, "_mergesort.txt");
    strcat(nome, extensao);

    break;
    case 'q':
    case 'Q':
    quickSort(vetor, 0,  tamanho-1, &troca, &comparacao);
    strcpy(extensao, "_quicksort.txt");
    strcat(nome, extensao);

    break;
    case 'h':
    case 'H':
    HeapSort(vetor, tamanho, &troca, &comparacao);
    strcpy(extensao, "_heapsort.txt");
    strcat(nome, extensao);

    break;
    default:
    printf("\nopção invalida\n");
    exit(1);
  }
  ticks[3] = clock();// Pega o tempo2 depois

  FILE *saida = fopen(nome, "w");
  if(saida == NULL){
    printf("Erro na abertura do aquivo \n");
    exit(1);
  }
  for(int j = 0; j < tamanho; j++)
    fprintf(saida, "%d\n",vetor[j] );

  ticks[1] = clock();// pega o tempo1 depois
  printf("Numeros ordenados: %d \n",tamanho );
  printf("Quantidade de comparacoes: %d \n",comparacao );
  printf("Quantidade de trocas: %d \n", troca);
  tempo1 = (double)(ticks[1] - ticks[0])*1000 / (CLOCKS_PER_SEC);
  tempo2 = (double)(ticks[3] - ticks[2])*1000 / (CLOCKS_PER_SEC);
  printf("Tempo ordenacao: %.3f ms.\n", tempo2);
  printf("Tempo total: %.3f ms.\n", tempo1);

  // desaloca memoria
  for(int j = 0; j<tamanho; j++)
  free(vetor);

  return 0;
}
