/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B2-2                                 */
/*             Objetivo: <<  Bublle Sort >>                                         */
/*                                                                                  */
/*                                  Autor: Vinicius da Silva Ramos                  */
/*                                                                   Data:06/05/2025*/
/*----------------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 5

void bubbleSort(float *vetor, int tamanho) {
    float temp;
    for (int x = 0; x < tamanho - 1; x++) {
        for (int j = 0; j < tamanho - 1 - x; j++) {
            if (vetor[j] > vetor[j + 1]) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

void exibir(float *vetor, int tamanho) {
    printf("Array ordenado em ordem ascendente:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%.2f ", vetor[i]);
    }
    printf("\n");
}

int main() {
    float *vetor;
    int i = 0;
    float entrada;
    char buffer[100];
    char extra;
    char resposta[10];

    vetor = (float*) malloc(MAX * sizeof(float));  
    if (vetor == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }

    do {
        printf("Digite o número %d: ", i + 1);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro ao ler entrada.\n");
            continue;
        }

        if (sscanf(buffer, "%f %c", &entrada, &extra) != 1) {
            printf("Entrada inválida! Por favor, digite um número válido.\n");
            continue;
        }

        vetor[i] = entrada;
        i++;

        if (i >= MAX) {
            printf("Limite de %d números atingido.\n", MAX);
            break;
        }

        printf("Deseja digitar outro número? (s/n): ");
        if (fgets(resposta, sizeof(resposta), stdin) != NULL) {
            resposta[0] = tolower(resposta[0]);
        } else {
            resposta[0] = 'n';
        }

    } while (resposta[0] == 's');

    bubbleSort(vetor, i);
    exibir(vetor, i);

    free(vetor);
    return 0;
}
