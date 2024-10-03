#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cad/cadastro_menu.c"

void menu(){
    printf("***************************\n");
    printf("*   Menu Raizes da Terra  *\n");
    printf("* 1- Cadastro de Produtos *\n");
    printf("* 2- Fluxo de Caixa       *\n");
    printf("* 3- Estoque              *\n");
    printf("* 4- Relatorio Doacao     *\n");
    printf("***************************\n");
    printf("\n");
}

int main() {

    int opção, rep=0;

    do{
        menu();

        printf("Por favor selecione uma opcao: ");
        scanf("%d", &opção);
        
        switch (opção){

            case 1: {
                cad_menu();
                rep = 0;
                break;
            }

            case 2:
                printf("\nFluxo de Caixa\n\n");
                rep = 0;
                break;

            case 3:
                printf("\nEstoque\n\n");
                rep = 0;
                break;

            case 4:
                printf("\nRelatorio Doacao\n\n");
                rep = 0;
                break;

            default:
                printf("\nOpção invalida\n\n");
                rep = 1;
                break;
        }

    } while (rep == 1);
    
    return 0;
} 
