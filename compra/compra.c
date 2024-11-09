#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sistema.h"


void menu_compra(){
    printf("\n");
    printf("***************************\n");
    printf("*   Menu de Cadastro      *\n");
    printf("* 1- Cadastro de compra   *\n");
    printf("* 2- Historicos de compra *\n");
    printf("* 3- Edição de compra     *\n");
    printf("* 0- Sair da aplicacao    *\n");
    printf("***************************\n");
    printf("\n");
}

void compra(){
    Compra compra[MAX_COMPRA];
    int totalCompra = loadCompra(compra);
    int opcao;

    do {
        menu_compra();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            cad_compra();
            break;
        case 2:
            visuCompra();
            break;
        case 3:
            menuCompra();
            break;
        case 0:
            /* code */
            break;
        default:
            break;
        }
    } while (opcao != 0);
    
}