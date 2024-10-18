#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto_.c"

#define MAX_PRODUTOS 5 



void menu_doacao() {
    int op;

    printf("************************************\n");
    printf("*Gerenciador de Descartes e Doações*\n");
    printf("************************************\n");
    printf("* 1- Doar Item                     *\n");
    printf("* 2- Descartar Item                *\n");
    printf("* 3- Ponto de coleta               *\n");
    printf("* 4- Sair                          *\n");
    printf("************************************\n");
    printf("\n");
    printf("Selecione uma opção: ");
    scanf("%d", &op);

    switch (op) {
        case 1:
            printf("* Verificar Estoque para seleção de doação de produtos  *\n");

            Cadastro prod[MAX_PRODUTOS];
            int totalProd = loadCad(prod);;
            int opcao;

            if (totalProd == 0) {
            printf("Não ha produtos no estoque.\n");
            return;
            }

            do {
            printf("\nEstoque para verificação de produtos a ser escolhido\n");
            for (int i = 0; i < totalProd; i++) {
            char *unidadeTipo = (prod[i].unid == 1) ? "Unid" : "Kg"; 

            printf("%d. Nome: %s, Quantidade: %d %s, Validade: %s/%s, \n",
           i + 1, prod[i].nome, prod[i].qtd, unidadeTipo, prod[i].valid.mes, prod[i].valid.ano);
        }

        printf("\n\n1. continuar\n2. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                editProdDoacao(prod, totalProd);
                break;
            case 2:
                printf("Saindo do estoque.\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 2);

saveCad(prod, totalProd);
            break;
        case 2:
             printf("* Verificar Estoque para seleção de descarte de produtos  *\n");           

            if (totalProd == 0) {
            printf("Não ha produtos no estoque. Por favor, adicione produtos.\n");
            return;
            }

            do {
            printf("\nEstoque para verificação de produtos a ser escolhido\n");
            for (int i = 0; i < totalProd; i++) {
            char *unidadeTipo = (prod[i].unid == 1) ? "Unid" : "Kg";

            printf("%d. Nome: %s, Quantidade: %d %s, Valor: %.2f, Validade: %s/%s, Tipo: %d\n",
           i + 1, prod[i].nome, prod[i].qtd, unidadeTipo,
           prod[i].valor, prod[i].valid.mes, prod[i].valid.ano, prod[i].tipo);
        }

        printf("\n\n1. continuar\n2. Sair\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                descarteDoacao(prod, totalProd);
                break;
            case 2:
                printf("Saindo do estoque.\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 2);

saveCad(prod, totalProd);
            break;
        case 3:
            exibirLojas();
            break;
        case 4:
            printf("\nVoltar\n");
            return; 
        default:  
            printf("\nOpção inválida. Tente novamente.\n");
            break;
    }
}

