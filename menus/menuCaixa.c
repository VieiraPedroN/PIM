/*#include <stdio.h>
#include <stdlib.h>
#include "../sistema.h"
#include "../fluxo_caixa/Fluxo_menu.c"

void menu_print_Caixa() {
    printf("\n");
    printf("********************************\n");
    printf("*   Menu Raizes da Terra       *\n");
    printf("* 1- Fluxo de Caixa            *\n");
    printf("* 0- Sair da aplicacao         *\n");
    printf("********************************\n");
    printf("\n");
}

void menuCaixa() {

    int opcao;
    
    do {
        check = 0;
        menu_print_Caixa();
        printf("Por favor selecione uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("\nFluxo de Caixa\n");
                fluxo();
                break;
            case 0:
                printf("\nSaindo da aplicacao\n");
                break;;
            default:
                printf("\nOpcao inválida\n");
                break;
        }
    } while (opcao != 0);
}