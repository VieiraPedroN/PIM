#include <stdio.h>
#include <stdlib.h>
#include "doacao.c"
#include "desc.c"
#include "../sistema.h"

void exb_menu_doa(){
    printf("**************************************\n");
    printf("* Gerenciador de Descartes e Doações *\n");
    printf("* 1- Doar Item                       *\n");
    printf("* 2- Descartar Item                  *\n");
    printf("* 3- Ponto de coleta                 *\n");
    printf("* 4- Visualizar doações e descartes  *\n");
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
                descProd(prod, totalProd);
                break;
            case 3:
                break;
            case 4:
                do{
                    printf("\nDoações-1, Descartes-2, Sair-0\n");
                    printf("Deseja visualizar o historico?: ");
                    scanf("%d",&opvisu);
                    printf("\n");

                    switch (opvisu){
                    case 1:
                        printf("\nHistorico de doações\n");
                        visuDoa(prod, totalProd);
                        break;
                    
                    case 2:
                        printf("\nHistorico de descartes\n");
                        visuDesc();
                        break;
                    case 0:
                        printf("Saindo do sistema.\n");
                        break;
                    
                    default:
                        printf("Opção inválida!\n");
                        break;
                    }
                    break;
                } while (opvisu != 0);          
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
