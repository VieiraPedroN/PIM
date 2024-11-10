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
        int opt, tipo;
            do {

                if (check == 1){
                    return;
                }

                printf("***********************\n");
                printf("* 1- Frutas           *\n");
                printf("* 2- Hortalicas       *\n");
                printf("* 3- Bebidas          *\n");
                printf("* 4- Cereais          *\n");
                printf("* 5- Laticineos       *\n");
                printf("* 0- Sair da operacao *\n");
                printf("***********************\n");
                printf("Selecione um tipo de produto para cadastro: ");
                scanf("%d", &tipo);

                if (tipo == 0) {
                    printf("Saindo da operação de cadastro.\n");
                    return; // Retorna ao menu principal
                }
                
                if (tipo < 1 || tipo > 5) {
                    printf("Tipo inválido. Tente novamente.\n");
                    continue;
                }

                cad_compra(tipo);
            } while (1);    
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