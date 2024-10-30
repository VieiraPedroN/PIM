#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include "cad/cadastro_menu.c"
#include "armz/estoque.c"
#include "doacao/menu_doa.c"

void menu() {
    printf("\n");
    printf("***************************\n");
    printf("*   Menu Raizes da Terra  *\n");
    printf("* 1- Cadastro de Produtos *\n");
    printf("* 2- Fluxo de Caixa       *\n");
    printf("* 3- Estoque              *\n");
    printf("* 4- Relatorio Doacao     *\n");
    printf("* 5- Sair da aplicacao    *\n");
    printf("***************************\n");
    printf("\n");
}

void main() {

    int opcao, rep = 0;
    
    do {
        check = 0;
        menu();
        printf("Por favor selecione uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
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
                menuArmz();
                rep = 1;
                break;
            case 4:
                printf("\nRelatorio Doacao\n");
                menu_doa();
                rep = 1;
                break;
            case 5:
                printf("\nSaindo da aplicacao\n");
                rep = 0;
                break;
            default:
                printf("\nOpcao inválida\n");
                rep = 1;
                break;
        }
    } while (rep == 1);
}