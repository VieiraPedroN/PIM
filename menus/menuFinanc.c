/*#include <stdio.h>
#include <stdlib.h>
#include "../sistema.h"
#include "../cad/cadastro_menu.c"
#include "../armz/estoque.c"
#include "../doacao/menu_doa.c"
#include "../doacao/menu_desc.c"
#include "../compra/compra.c"
#include "../colaborador/colab.c"
#include "../fluxo_caixa/Fluxo_menu.c"

void menu_print_Financ() {
    printf("\n");
    printf("********************************\n");
    printf("*   Menu Raizes da Terra       *\n");
    printf("* 1- Compra de Produtos        *\n");
    printf("* 2- Fluxo de Caixa            *\n");
    printf("* 0- Sair da aplicacao         *\n");
    printf("********************************\n");
    printf("\n");
}

void menuFinanc() {

    int opcao;
    
    do {
        check = 0;
        menu_print_Financ();
        printf("Por favor selecione uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                printf("\nCompra de Produtos\n");
                compra();
                break;
            case 2:
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