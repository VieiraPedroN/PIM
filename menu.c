#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include "cad/cadastro_menu.c"
#include "armz/estoque.c"
#include "doacao/menu_doa.c"
#include "doacao/menu_desc.c"
#include "compra/compra.c"
#include "fluxo_caixa/Fluxo_menu.c"

void menu_print() {
    printf("\n");
    printf("***************************\n");
    printf("*   Menu Raizes da Terra  *\n");
    printf("* 1- Cadastro de Produtos *\n");
    printf("* 2- Compra de Produtos   *\n");
    printf("* 3- Fluxo de Caixa       *\n");
    printf("* 4- Estoque              *\n");
    printf("* 5- Doacao de Produtos   *\n");
    printf("* 6- Descarte de Produtos *\n");
    printf("* 0- Sair da aplicacao    *\n");
    printf("***************************\n");
    printf("\n");
}

void menu() {

    int opcao, rep = 0;
    
    do {
        check = 0;
        menu_print();
        printf("Por favor selecione uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                printf("\nCadastro de Produtos\n");
                cad_menu();
                rep = 1;
                break;
            case 2: 
                printf("\nCompra de Produtos\n");
                compra();
                rep = 1;
                break;
            case 3:
                printf("\nFluxo de Caixa\n");
                fluxo();
                rep = 1;
                break;
            case 4:
                printf("\nEstoque\n");
                menuArmz();
                rep = 1;
                break;
            case 5:
                printf("\nDoacao\n");
                menu_doa();
                rep = 1;
                break;
            case 6:
                printf("\nDescarte\n");
                menu_desc();
                rep = 1;
                break;
            case 0:
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