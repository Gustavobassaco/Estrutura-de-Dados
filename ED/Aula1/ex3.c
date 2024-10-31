#include <stdio.h>
#include <stdlib.h>

/*
Exerc´ıcio 3. [Recurs˜ao] Escreva uma fun¸c˜ao recursiva para calcular o valor de um n´umero inteiro de base
x elevada a um expoente inteiro y
*/

int exponencial(int base, int expoente){
  if(expoente == 0){
    return 1;
  }else{
    expoente --;
    return base*exponencial(base, expoente );
}
}

int main(){
  int base, expoente, resultado;

  printf("Digite os valores para x e y, para calcular a exponencial de x^y\n");
  scanf("%d", &base);
  scanf("%d", &expoente);

  resultado = exponencial(base, expoente);
  printf("\n O resultado da exponencial %d ^ %d = %d\n",base, expoente, resultado );

  return 0;
}
