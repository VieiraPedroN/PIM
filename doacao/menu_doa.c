#include <stdio.h>
#include <stdlib.h>

#include "../sistema.h"

void exb_menu_doa(){
    printf("**************************************\n");
    printf("* Gerenciador de Descartes e Doações *\n");
    printf("* 1- Doar Item                       *\n");
    printf("* 2- Ponto de Coleta                 *\n");
    printf("* 3- Visualizar doações              *\n");
    printf("* 0- Sair                            *\n");
    printf("**************************************\n");
    printf("\n");
    printf("Selecione uma opção: ");
}

int menu_doa() {
    Cadastro prod[MAX_PRODUTOS];
    int totalProd = loadCad(prod); // Carrega produtos existentes
    int opcao;
    int opvisu;

    // Código do menu de daocao...
    do {
        // Código para exibir opções do menu
        printf("\n");
        exb_menu_doa();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                doaProd(prod, totalProd);
                break;
            case 2:
                break;
            case 3:
                printf("\nHistorico de doações\n");
                visuDoa(prod, totalProd);
                break;                       
            case 0:
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    // Salvar produtos no arquivo após alterações
    saveCad(prod, totalProd);
    return 0;
}
