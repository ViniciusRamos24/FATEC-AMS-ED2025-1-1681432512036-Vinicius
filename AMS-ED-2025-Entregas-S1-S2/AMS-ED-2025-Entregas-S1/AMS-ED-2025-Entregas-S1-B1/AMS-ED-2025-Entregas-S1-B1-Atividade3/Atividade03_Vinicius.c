/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-3                                 */
/*             Objetivo: << Maipulação de Lista Ligada >>                           */
/*                                                                                  */
/*                                  Autor: Vinicius da Silva Ramos                  */
/*                                                                  Data:22/03/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Memoria {
    void* endereco;
    struct Memoria* proximo;
} Memoria;

Memoria* listaMemoria = NULL;

void* alocarMemoria(size_t tamanho) {
    void* ptr = malloc(tamanho);
    if (!ptr) {
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }
    Memoria* novo = (Memoria*)malloc(sizeof(Memoria));
    novo->endereco = ptr;
    novo->proximo = listaMemoria;
    listaMemoria = novo;
    return ptr;
}

void liberarTodaMemoria() {
    Memoria* atual = listaMemoria;
    while (atual) {
        Memoria* temp = atual;
        free(atual->endereco);
        atual = atual->proximo;
        free(temp);
    }
    printf("Toda a memoria alocada foi liberada!\n");
}

typedef struct Pedido {
    int numero;
    char cliente[50];
    char descricao[100];
    int quantidade;
    char status[20];
    struct Pedido* proximo;
} Pedido;

Pedido* criarLista() {
    return NULL;
}

Pedido* inserirPedido(Pedido* lista) {
    Pedido* novoPedido = (Pedido*)alocarMemoria(sizeof(Pedido));
    printf("Digite o numero do pedido: ");
    scanf("%d", &novoPedido->numero);
    getchar();
    
    printf("Digite o nome do cliente: ");
    fgets(novoPedido->cliente, 50, stdin);
    strtok(novoPedido->cliente, "\n");
    
    printf("Digite o nome do prato: ");
    fgets(novoPedido->descricao, 100, stdin);
    strtok(novoPedido->descricao, "\n");

    printf("Digite a quantidade: ");
    scanf("%d", &novoPedido->quantidade);
    getchar();

    selecionarStatus(novoPedido->status);

    novoPedido->proximo = lista;
    return novoPedido;
}

void selecionarStatus(char* status) {
    int escolha;
    do {
        printf("Selecione o status do pedido:\n");
        printf("1 - Pendente\n");
        printf("2 - Em Preparo\n");
        printf("3 - Pronto\n");
        printf("4 - Entregue\n");
        printf("Opcao: ");
        scanf("%d", &escolha);
        getchar();

        switch (escolha) {
            case 1: strcpy(status, "Pendente"); break;
            case 2: strcpy(status, "Em Preparo"); break;
            case 3: strcpy(status, "Pronto"); break;
            case 4: strcpy(status, "Entregue"); break;
            default: printf("Opcao invalida! Escolha um numero entre 1 e 4.\n");
        }
    } while (escolha < 1 || escolha > 4);
}

void obterPedido(Pedido* lista) {
    int numero;
    printf("Digite o numero do pedido a buscar: ");
    scanf("%d", &numero);
    
    Pedido* atual = lista;
    while (atual) {
        if (atual->numero == numero) {
            printf("Pedido encontrado:\n");
            printf("Numero: %d, Cliente: %s, Prato: %s, Quantidade: %d, Status: %s\n",
                   atual->numero, atual->cliente, atual->descricao, atual->quantidade, atual->status);
            return;
        }
        atual = atual->proximo;
    }
    printf("Pedido nao encontrado!\n");
}

void atualizarStatus(Pedido* lista) {
    int numero;
    printf("Digite o numero do pedido para atualizar o status: ");
    scanf("%d", &numero);
    getchar();

    Pedido* atual = lista;
    while (atual) {
        if (atual->numero == numero) {
            selecionarStatus(atual->status);
            printf("Status do pedido %d atualizado para: %s\n", numero, atual->status);
            return;
        }
        atual = atual->proximo;
    }
    printf("Pedido nao encontrado!\n");
}

Pedido* deletarPedido(Pedido* lista) {
    int numero;
    printf("Digite o numero do pedido a ser deletado: ");
    scanf("%d", &numero);

    Pedido *atual = lista, *anterior = NULL;
    while (atual) {
        if (atual->numero == numero) {
            if (anterior) {
                anterior->proximo = atual->proximo;
            } else {
                lista = atual->proximo;
            }
            free(atual); 
            printf("Pedido %d removido com sucesso!\n", numero);
            return lista;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Pedido nao encontrado!\n");
    return lista;
}


void exibirPedidos(Pedido* lista) {
    Pedido* atual = lista;
    printf("\n*** Pedidos Atuais ***\n");
    while (atual) {
        printf("Numero: %d, Cliente: %s, Prato: %s, Quantidade: %d, Status: %s\n",
               atual->numero, atual->cliente, atual->descricao, atual->quantidade, atual->status);
        atual = atual->proximo;
    }
}

void exibirPedidosPorStatus(Pedido* lista) {
    char statusFiltro[20];
    selecionarStatus(statusFiltro);

    Pedido* atual = lista;
    int encontrado = 0;
    printf("\n*** Pedidos com status %s ***\n", statusFiltro);
    while (atual) {
        if (strcmp(atual->status, statusFiltro) == 0) {
            printf("Numero: %d, Cliente: %s, Prato: %s, Quantidade: %d, Status: %s\n",
                   atual->numero, atual->cliente, atual->descricao, atual->quantidade, atual->status);
            encontrado = 1;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf("Nenhum pedido encontrado com status %s!\n", statusFiltro);
    }
}

int main() {
    printf("\nBem-vindo ao Restaurante Ramos! Aqui, cada pedido compila perfeitamente com seu apetite!\n");

    Pedido* lista = criarLista();
    int opcao;
    do {
        do {
            printf("\nMenu:\n");
            printf("1 - Adicionar Pedido\n");
            printf("2 - Buscar Pedido\n");
            printf("3 - Atualizar Status\n");
            printf("4 - Deletar Pedido - Entregue ou Incorreto\n");
            printf("5 - Exibir Todos os Pedidos\n");
            printf("6 - Exibir Pedidos por Status\n");
            printf("7 - Sair e Liberar Memoria\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            getchar();

            if (opcao < 1 || opcao > 7) {
                printf("Opcao invalida! Escolha um numero entre 1 e 7.\n");
            }
        } while (opcao < 1 || opcao > 7);

        switch (opcao) {
            case 1: lista = inserirPedido(lista); break;
            case 2: obterPedido(lista); break;
            case 3: atualizarStatus(lista); break;
            case 4: lista = deletarPedido(lista); break;
            case 5: exibirPedidos(lista); break;
            case 6: exibirPedidosPorStatus(lista); break;
            case 7: liberarTodaMemoria(); printf("Saindo...\n"); break;
        }
    } while (opcao != 7);
    return 0;
}
