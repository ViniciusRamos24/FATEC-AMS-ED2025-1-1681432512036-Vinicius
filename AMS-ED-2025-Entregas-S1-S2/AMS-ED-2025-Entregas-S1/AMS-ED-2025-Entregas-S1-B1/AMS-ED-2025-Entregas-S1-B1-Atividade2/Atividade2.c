/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-2                                 */
/*             Objetivo: <<  Manipulacao de Array com ponteiro  >>                  */
/*                                                                                  */
/*                                  Autor: Vinícius da Silva Ramos                  */
/*                                                                   Data:06/03/2024*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50

typedef struct Candidato {
    char nome[50];
    float PE[4], AC[5], PP[10], EB[3];
    float NF;
    struct Candidato *proximo;
} Candidato;

float mediaCentral(float *notas, int tamanho) {
    float soma = 0.0, maior = notas[0], menor = notas[0];

    for (int i = 1; i < tamanho; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
    }

    for (int i = 0; i < tamanho; i++) {
        soma += notas[i];
    }

    return (soma - maior - menor) / (tamanho - 2);
}

void entradaNotas(float *notas, int tamanho, const char *descricao) {
    printf("Digite as %d notas para %s:\n", tamanho, descricao);
    for (int i = 0; i < tamanho; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &notas[i]);
    }
}

void incluirCandidato(Candidato **lista, int *quantidade) {
    if (*quantidade >= MAX_CANDIDATOS) {
        printf("Número máximo de candidatos atingido!\n");
        return;
    }

    Candidato *novo = (Candidato *)malloc(sizeof(Candidato));
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    getchar();
    printf("\nDigite o nome do candidato: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    entradaNotas(novo->PE, 4, "Prova Escrita (PE)");
    entradaNotas(novo->AC, 5, "Analise Curricular (AC)");
    entradaNotas(novo->PP, 10, "Prova Pratica (PP)");
    entradaNotas(novo->EB, 3, "Entrevista em Banca (EB)");

    float pe = mediaCentral(novo->PE, 4);
    float ac = mediaCentral(novo->AC, 5);
    float pp = mediaCentral(novo->PP, 10);
    float eb = mediaCentral(novo->EB, 3);

    novo->NF = (pe * 0.3) + (ac * 0.1) + (pp * 0.4) + (eb * 0.2);
    novo->proximo = *lista;
    *lista = novo;
    (*quantidade)++;
}

void ordenarCandidatos(Candidato **lista) {
    if (!*lista) return;

    int trocado;
    Candidato **ptr1, *temp, *anterior = NULL;

    do {
        trocado = 0;
        ptr1 = lista;

        while ((*ptr1) && (*ptr1)->proximo) {
            if ((*ptr1)->NF < (*ptr1)->proximo->NF) {
                temp = (*ptr1)->proximo;
                (*ptr1)->proximo = temp->proximo;
                temp->proximo = *ptr1;
                *ptr1 = temp;
                trocado = 1;
            }
            ptr1 = &((*ptr1)->proximo);
        }
    } while (trocado);
}

void imprimirClassificacao(Candidato *lista) {
    printf("\nClassificacao Final:\n");
    int posicao = 1;
    Candidato *atual = lista;

    while (atual != NULL && posicao <= 5) {
        printf("%d Lugar: %s - Nota Final: %.2f\n", posicao, atual->nome, atual->NF);
        atual = atual->proximo;
        posicao++;
    }
}

void liberarMemoria(Candidato *lista) {
    Candidato *atual = lista;
    while (atual != NULL) {
        Candidato *temp = atual;
        atual = atual->proximo;
        free(temp);
    }
}

int main() {
    Candidato *listaCandidatos = NULL;
    int quantidade = 0;
    char continuar;

    do {
        incluirCandidato(&listaCandidatos, &quantidade);

        if (quantidade >= MAX_CANDIDATOS) {
            printf("\nLimite de %d candidatos atingido. Encerrando entrada.\n", MAX_CANDIDATOS);
            break;
        }

        printf("\nDeseja adicionar outro candidato? (s/n): ");
        scanf(" %c", &continuar); 
    } while ((continuar == 's' || continuar == 'S') && quantidade < MAX_CANDIDATOS);

    ordenarCandidatos(&listaCandidatos);
    imprimirClassificacao(listaCandidatos);
    liberarMemoria(listaCandidatos);

    return 0;
}
