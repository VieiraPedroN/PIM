#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../sistema.h"

void menu_principal(){
    printf("\n");
    printf("*******************************\n");
    printf("*   Menu de Cadastro          *\n");
    printf("* 1- Cadastro Colaborador     *\n");
    printf("* 2- Visualizar Colaboradores *\n");
    printf("* 3- Edição de Colaborador    *\n");
    printf("* 0- Sair da aplicacao        *\n");
    printf("*******************************\n");
    printf("\n");
}

void colab_menu() {
    Colaborador func[MAX_FUNCIONARIOS];
    int totalFunc = loadCadColab(func); // Carrega colaboradores existentes
    int op, tipo;

    do {

        menu_principal();
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                {
                    do {

                        if (check == 1){
                            return;
                        }
                        
                        printf("\n");
                        printf("***********************\n");
                        printf("* 1- Caixa            *\n");
                        printf("* 2- Almoxarife       *\n");
                        printf("* 3- Financeiro       *\n");
                        printf("* 4- Gerente          *\n");
                        printf("* 0- Sair da operacao *\n");
                        printf("***********************\n");
                        printf("Escolha o tipo de colaborador para cadastrar: ");
                        scanf("%d", &tipo);

                        if (tipo == 0) {
                            printf("\nSaindo da operação de cadastro.\n");
                            break;
                        }

                        cadColab(tipo); // Atualiza o cadastro no array e incrementa totalFunc
                    } while (tipo != 0);
                }
                break;

            case 2:
                visuColab(tipo, func, totalFunc);  // Função para visualizar colaboradores
                break;

            case 3:
                menuColab(func, &totalFunc);
                break;

            case 0:
                printf("Saindo do sistema.\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (op != 0);
}
