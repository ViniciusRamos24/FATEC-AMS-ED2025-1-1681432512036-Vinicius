#include <stdio.h>

void AplicarDesconto(float *preco, float desconto) {
    *preco = *preco - (*preco * desconto / 100);
}

int main() {
    float precoProduto, desconto;

    printf("Digite o preco do produto: R$ ");
    scanf("%f", &precoProduto);

    printf("Digite a porcentagem de desconto: ");
    scanf("%f", &desconto);

    printf("Preco original: R$ %.2f\n", precoProduto);

    AplicarDesconto(&precoProduto, desconto);

    printf("Desconto aplicado: %.f%%\n", desconto);
    printf("Preco final apos o desconto: R$ %.2f\n", precoProduto);

    return 0;
}
