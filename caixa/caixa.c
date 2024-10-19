#include <stdio.h>
#include "../sistema.h"

void menu_caixa(){
        printf("**************************\n");
        printf("* 1- Add Produto         *\n");
        printf("* 2- Rmv Produto         *\n");
        printf("* 3- Formas de pagamento *\n");
        printf("* 4- Desconto            *\n");
        printf("* 5- Sair da operacao    *\n");
        printf("**************************\n");
}


void main(){

    menu_caixa();

    Cadastro prod[MAX_PRODUTOS];
    int totalProd = loadCad(prod); // Carrega produtos existentes
    int opcao;

    if (totalProd == 0) {
        printf("\nNenhum item no estoque\n");
        return;
    }

    printf("Por favor selecione uma opção");
    scanf("%d", &opcao);

    switch (opcao){

    case 1:
        printf("Add Produto");
        break;

    case 2:
        printf("Rmv Produto");
        break;

    case 3:
        printf("Pagamento");
        break;

    case 4:
        printf("Desconto");
        break;

    case 5:
        printf("Saindo da operação");
        break;

    default:
        printf("Opção invalida");
        break;
    }
}