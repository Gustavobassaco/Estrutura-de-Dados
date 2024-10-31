#include <stdio.h>
#include <stdlib.h>

/*
Exerc´ıcio 4. [Aloca¸c˜ao Dinˆamica] Fa¸ca um programa que leia um valor N e crie dinamicamente um
vetor com essa quantidade de elementos. Em seguida, passe esse vetor para uma fun¸c˜ao que vai ler os
elementos desse vetor. Depois, no programa principal, imprima os valores do vetor preenchido. Al´em disso,
antes de finalizar o programa, lembre-se de liberar a ´area de mem´oria alocada para armazenar os valores do
vetor.
*/

  void preenche(int* v, int tam){
    for(int i=0; i<tam; i++){
      v[i]=i;
    }
  }


int main(){
  int* vetor;
  int tamanho;

  printf("digite o tamanho desejado para o vetor: \n");
  scanf("%d", &tamanho );

  vetor = (int*) malloc(tamanho * sizeof(int));

  if(vetor == NULL){
  printf("Erro: Memória Insuficiente!\n");
  exit(1);
  }
  preenche(vetor, tamanho);

  for(int i = 0; i<tamanho; i++)
  printf("%d, ", vetor[i]);

  free(vetor);
  return 0;
}
