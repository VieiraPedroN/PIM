#include <stdio.h>
#include <stdlib.h>
#include "../sistema.h"


void menu_print() {
    printf("\n");
    printf("********************************\n");
    printf("*   Menu Raizes da Terra       *\n");
    printf("* 1- Cadastro de Produtos      *\n");
    printf("* 2- Compra de Produtos        *\n");
    printf("* 3- Cadastro de Colaboradores *\n");
    printf("* 4- Caixa                     *\n");
    printf("* 5- Financeiro                *\n");
    printf("* 6- Estoque                   *\n");
    printf("* 7- Doacao de Produtos        *\n");
    printf("* 8- Descarte de Produtos      *\n");
    printf("* 0- Sair da aplicacao         *\n");
    printf("********************************\n");
    printf("\n");
}

void menuAdm() {
    Fluxo transacoes[Max_Fluxos];
    int TotalT = loadFluxo(transacoes); Cadastro produtos[MAX_PRODUTOS];
    int TotalProdts = loadCad(produtos);
    int opcao;
    
    do {
        check = 0;
        menu_print();
        printf("Por favor selecione uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: 
                printf("\nCadastro de Produtos\n");
                cad_menu();
                break;
            case 2: 
                printf("\nCompra de Produtos\n");
                compra();
                break;
            case 3: 
                printf("\nCadastro de Colaboradores\n");
                colab_menu();
                break;
            case 4:
                printf("\nCaixa\n");
                Caixa(transacoes, &TotalT, produtos, TotalProdts);
                break;
            case 5:
                fluxo();
                break;
            case 6:
                printf("\nEstoque\n");
                menuArmz();
                break;
            case 7:
                printf("\nDoacao\n");
                menu_doa();
                break;
            case 8:
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