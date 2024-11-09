#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../sistema.h"

void FormaPP(char *pagamento) {
    int formaPagamento;
    printf("Forma de Pagamento:\n");
    printf("1. Dinheiro\n");
    printf("2. Cartão de Crédito\n");
    printf("3. Cartão de Débito\n");
    printf("4. Pix\n");
    printf("Selecione uma opção: ");
    if (scanf("%d", &formaPagamento) != 1) {
        while (getchar() != '\n');
        printf("Entrada inválida!\n");
        strcpy(pagamento, "Inválido");
        return;
    }
    getchar();
    switch (formaPagamento) {
        case 1:
            strcpy(pagamento, "Dinheiro");
            break;
        case 2:
            strcpy(pagamento, "Cartão de Crédito");
            break;
        case 3:
            strcpy(pagamento, "Cartão de Débito");
            break;
        case 4:
            strcpy(pagamento, "Pix");
            break;
        default:
            printf("Opção inválida!\n");
            strcpy(pagamento, "Inválido");
            break;
    }
}

void FormaP(char *pagamento) {
    int formaPagamento;
    printf("Forma de Pagamento:\n");
    printf("1. Dinheiro\n");
    printf("2. Cartão de Crédito\n");
    printf("3. Cartão de Débito\n");
    printf("4. Pix\n");
    printf("5. Vale Alimentação\n");
    printf("Selecione uma opção: ");
    if (scanf("%d", &formaPagamento) != 1) {
        while (getchar() != '\n');
        printf("Entrada inválida!\n");
        strcpy(pagamento, "Inválido");
        return;
    }
    getchar();
    switch (formaPagamento) {
        case 1:
            strcpy(pagamento, "Dinheiro");
            break;
        case 2:
            strcpy(pagamento, "Cartão de Crédito");
            break;
        case 3:
            strcpy(pagamento, "Cartão de Débito");
            break;
        case 4:
            strcpy(pagamento, "Pix");
            break;
        case 5:
            strcpy(pagamento, "Vale Alimentação");
            break;
        default:
            printf("Opção inválida!\n");
            strcpy(pagamento, "Inválido");
            break;
    }
}