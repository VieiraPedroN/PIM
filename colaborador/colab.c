#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "cad_colab.c"
#include "../sistema.h"

void menu_colab(){
    printf("\n");
    printf("****************************\n");
    printf("*   Menu de Cadastro       *\n");
    printf("* 1- Cadastro Colaborador  *\n");
    printf("* 2- Edição de Colaborador *\n");
    printf("* 0- Sair da aplicacao     *\n");
    printf("****************************\n");
    printf("\n");
}

void main(){
    int op;

    do {
        printf("\n");
        menu_colab();

        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch (op){
            case 1:
                printf("Ola");
                break;
            case 2:
                printf("Errou");
                break;
            case 0:
                printf("Saindo");
                break;
            default:
                break;
            }
    } while (op != 0);
    
        

}