#include <stdio.h>
#include <stdlib.h>
#include "../sistema.h"



void menu_print_Almox() {
    printf("\n");
    printf("********************************\n");
    printf("*   Menu Raizes da Terra       *\n");
    printf("* 1- Cadastro de Produtos      *\n");
    printf("* 2- Estoque                   *\n");
    printf("* 3- Doacao de Produtos        *\n");
    printf("* 4- Descarte de Produtos      *\n");
    printf("* 0- Sair da aplicacao         *\n");
    printf("********************************\n");
    printf("\n");
}

void menuAlmox() {

    int opcao;
    
    do {
        check = 0;
        menu_print_Almox();
        printf("Por favor selecione uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                printf("\nCadastro de Produtos\n");
                cad_menu();
                break;
            case 2:
                printf("\nEstoque\n");
                menuArmz();
                break;
            case 3:
                printf("\nDoacao\n");
                menu_doa();
                break;
            case 4:
                printf("\nDescarte\n");
                menu_desc();
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