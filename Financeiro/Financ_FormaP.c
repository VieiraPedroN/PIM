#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../sistema.h"

void FormaPP(char *Pag)
{ // Função para selecionar a forma de pagamento para pagamentos
    int FormaPag;
    printf("1. Dinheiro\n");
    printf("2. Cartão de Crédito\n");
    printf("3. Cartão de Débito\n");
    printf("4. Pix\n");
    printf("5. Boleto\n");
    printf("Selecione uma opção: ");

    if (scanf("%d", &FormaPag) != 1)
    { // Verifica se a opção é válida
        while (getchar() != '\n')
            ;
        printf("Entrada inválida!\n");
        strcpy(Pag, "Inválido"); // Define a forma de pagamento como inválida
        return;
    }
    getchar();

    // Define a forma de pagamento com base na opção escolhida
    switch (FormaPag)
    {
    case 1:
        strcpy(Pag, "Dinheiro");
        break;
    case 2:
        strcpy(Pag, "Cartão de Crédito");
        break;
    case 3:
        strcpy(Pag, "Cartão de Débito");
        break;
    case 4:
        strcpy(Pag, "Pix");
        break;
    case 5:
        strcpy(Pag, "Boleto");
        break;
    default:
        printf("Opção inválida!\n");
        strcpy(Pag, "Inválido"); // Define a forma de pagamento como inválida se a opção não for válida
        break;
    }
}

void FormaPV(char *Pag)
{ // Função para selecionar a forma de pagamento para vendas
    int FormaPag;
    printf("Forma de Pagamento:\n");
    printf("1. Dinheiro\n");
    printf("2. Cartão de Crédito\n");
    printf("3. Cartão de Débito\n");
    printf("4. Pix\n");
    printf("5. Vale Alimentação\n");
    printf("Selecione uma opção: ");

    if (scanf("%d", &FormaPag) != 1)
    { // Verifica se a opção é válida
        while (getchar() != '\n')
            ;
        printf("Entrada inválida!\n");
        strcpy(Pag, "Inválido");
        return;
    }
    getchar(); // Limpa o buffer do teclado

    switch (FormaPag)
    {
    case 1:
        strcpy(Pag, "Dinheiro");
        break;
    case 2:
        strcpy(Pag, "Cartão de Crédito");
        break;
    case 3:
        strcpy(Pag, "Cartão de Débito");
        break;
    case 4:
        strcpy(Pag, "Pix");
        break;
    case 5:
        strcpy(Pag, "Vale Alimentação");
        break;
    default:
        printf("Opção inválida!\n");
        strcpy(Pag, "Inválido");
        break;
    }
}