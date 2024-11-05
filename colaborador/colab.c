#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "cad_colab.c"
#include "edit_colab.c"
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

void colab() {
    Colaborador func[MAX_PRODUTOS];
    int totalFunc = loadCadColab(func); // Carrega produtos existentes
    int op, opt;

    do {
        int tipo; 
        char funcao[20]; 

        printf("\n");
        menu_colab();

        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                do {
                    
                    printf("***********************\n");
                    printf("* 1- Caixa            *\n");
                    printf("* 2- Almoxarife       *\n");
                    printf("* 3- Financeiro       *\n");
                    printf("* 4- Gerente          *\n");
                    printf("* 0- Sair da operacao *\n");
                    printf("***********************\n");
                    scanf("%d", &tipo);

                    if (tipo == 0) {
                        printf("Saindo da operação de cadastro.\n");
                        return; // Retorna ao menu principal
                    }

                    cadColab(tipo, funcao); // Passa o tipo e o nome da função
                } while (1);
                break;

            case 2:
                menuColab();
                break;
            case 0:
                printf("Saindo");
                break;
            default:
                break;
        }
    } while (op != 0);

    saveCadColab(func, totalFunc);
}
