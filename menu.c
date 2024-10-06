#include <stdio.h>
#include <stdlib.h>
#include "cad/cadastro.h"
#include "cad/cadastro_menu.c"
#include "armz/estoque.c"

void menu() {
    printf("\n");
    printf("***************************\n");
    printf("*   Menu Raizes da Terra  *\n");
    printf("* 1- Cadastro de Produtos *\n");
    printf("* 2- Fluxo de Caixa       *\n");
    printf("* 3- Estoque              *\n");
    printf("* 4- Relatorio Doacao     *\n");
    printf("* 5- Sair da aplicação    *\n");
    printf("***************************\n");
    printf("\n");
}

void main() {
    int opção, rep = 0;

    do {
        menu();
        printf("Por favor selecione uma opcao: ");
        scanf("%d", &opção);

        switch (opção) {
            case 1: {
                printf("\nCadastro de Produtos\n");
                cad_menu();
                rep = 1;
                break;
            }
            case 2:
                printf("\nFluxo de Caixa\n");
                rep = 1;
                break;
            case 3:
                printf("\nEstoque\n");
                visuArmz();
                rep = 1;
                break;
            case 4:
                printf("\nRelatorio Doacao\n");
                rep = 1;
                break;
            case 5:
                printf("\nSaindo da aplicação\n");
                rep = 0;
                break;
            default:
                printf("\nOpção inválida\n");
                rep = 1;
                break;
        }
    } while (rep == 1);
}