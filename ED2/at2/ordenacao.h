/**** 
 * @file ordenacao.h
 * @author Gustavo Rodrigues Bassaco
 * @date 19 Jul 2021
 * @brief Implementacao dos métodos de ordenacao
 * Implementa os metodos de ordenacao vistos na disciplina
 * pesquisa e classificacao de dados.
 */

#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <io.h>


/**
 * \brief Ordena o vetor usando BubbleSort
 *
 * \param vetor[]: vetor a ser ordenado
 * \param tamanho: tamanho do vetor
 * \param troca: numero de trocas ocorridas
 * \param comparacao: numero de comparacoes ocorridas
 *
 * Ordena o vetor usando o método Bubble Sort
 * Esse algorimo tem um comportamento assintótico O (N²)
 */
void bubbleSort(int vetor[], int tamanho,long int *troca,long int *comparacao);

/**
 * \brief Ordena o vetor usando SelectionSort
 *
 * \param vetor[]: vetor a ser ordenado
 * \param tamanho: tamanho do vetor
 * \param troca: numero de trocas ocorridas
 * \param comparacao: numero de comparacoes ocorridas
 *
 * Ordena o vetor usando o método SelectionSort
 * Esse algorimo tem um comportamento assintótico O (N²)
 */
void SelectionSort(int vetor[], int tamanho, long int* troca, long int *comparacao);

/**
 * \brief Ordena o vetor usando InsertionSort
 *
 * \param vetor[]: vetor a ser ordenado
 * \param tamanho: tamanho do vetor
 * \param troca: numero de trocas ocorridas
 * \param comparacao: numero de comparacoes ocorridas
 *
 * Ordena o vetor usando o método InsertionSort
 * Esse algorimo tem um comportamento assintótico O (N²)
 */
void InsertionSort(int vetor[], int tamanho, long int* troca, long int* comparacao);

/**
 * \brief Junta dois sub-vetores em um vetor maior e ordenado
 *
 * \param vetor[]: vetor a ser ordenado
 * \param inicio: indice do inicio do vetor
 * \param meio: indice central do vetor
 * \param final: indice do fim do vetor
 * \param troca: numero de trocas ocorridas
 * \param comparacao: numero de comparacoes ocorridas
 *
 */
void merge(int vetor[], int inicio, int meio, int final, long int* troca, long int* comparacao);

/**
 * \brief Ordena o vetor usando mergeSort
 *
 * \param vetor[]: vetor a ser ordenado
 * \param inicio: indice do inicio do vetor
 * \param fianl: indice do fim do vetor
 * \param troca: numero de trocas ocorridas
 * \param comparacao: numero de comparacoes ocorridas
 *
 * Ordena o vetor usando o método mergeSort
 * Esse algorimo tem um comportamento assintótico O (n log n)
 */
void mergeSort(int vetor[], int inicio, int final, long int* troca, long int* comparacao);

/**
 * \brief posiciona o pivo na sua posição correta e retorna seu indice
 *
 * \param vetor[]: vetor a ser ordenado
 * \param inicio: indice do inicio do vetor
 * \param fim: indice do fim do vetor
 * \param troca: numero de trocas ocorridas
 * \param comparacao: numero de comparacoes ocorridas
 *
 */
int particao(int vetor[], int inicio, int fim, long int* troca, long int* comparacao);

/**
 * \brief Ordena o vetor usando quickSort
 *
 * \param vetor[]: vetor a ser ordenado
 * \param inicio: indice do inicio do vetor
 * \param fim: indice do fim do vetor
 * \param troca: numero de trocas ocorridas
 * \param comparacao: numero de comparacoes ocorridas
 *
 * Ordena o vetor usando o método quickSort
 * Esse algorimo tem um comportamento assintótico O (n log n)
 */
void quickSort(int vetor[], int inicio, int fim, long int* troca, long int* comparacao);

/**
 * \brief Transforma um vetor em uma Heap
 *
 * \param vetor[]: vetor a ser ordenado
 * \param i: indice do inicio do vetor
 * \param f: indice do fim do vetor
 * \param troca: numero de trocas ocorridas
 * \param comparacao: numero de comparacoes ocorridas
 *
 * reposiciona os elementos para ser uma heap
 */
void criarHeap(int vetor[], int i, int f, long int* troca, long int* comparacao);

/**
 * \brief Ordena o vetor usando HeapSort
 *
 * \param vetor[]: vetor a ser ordenado
 * \param tamanho: tamanho do vetor
 * \param troca: numero de trocas ocorridas
 * \param comparacao: numero de comparacoes ocorridas
 *
 * Ordena o vetor usando o método HeapSort
 * Esse algorimo tem um comportamento assintótico O (n log n)
 */
void HeapSort(int vetor[], int tamanho, long int* troca, long int*comparacao);

#endif
