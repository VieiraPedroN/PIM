#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Fluxo.h"
#include "Fluxo_FormaP.c"
#include "Fluxo_GRM.c"
#include "Fluxo_IFC.c"
#include "Fluxo_Impr.c"
#include "Fluxo_Pag.c"
#include "Fluxo_Venda.c"
#include "Fluxo_M_E_D.c"

int validarD(char *dia, char *mes, char *ano) {
    int d = atoi(dia);
    int m = atoi(mes);
    int a = atoi(ano);

    if (a < 2024 || a > 2100) return 0;
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > 31) return 0; 
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return 0;
    if (m == 2) {
        if ((a % 4 == 0 && a % 100 != 0) || a % 400 == 0) {
            if (d > 29) return 0;
        } else {
            if (d > 28) return 0;
        }
    }

    return 1;
}

void MenuF() {
    printf("\n");
    printf("======== Menu do Financeiro =============\n");
    printf("| 1. Iniciar Venda                      |\n");
    printf("| 2. Realizar Pagamentos                |\n");
    printf("| 3. Ver Histórico de Transações        |\n");
    printf("| 4. Editar ou Deletar Transações       |\n");
    printf("| 5. Relatório Diário                   |\n");
    printf("| 6. Relatório Mensal                   |\n");
    printf("| 7. Voltar ao Menu Principal           |\n");
    printf("=========================================\n");
}

void saveFluxo(Fluxo *transacoes, int totalTransacoes) {
    FILE *arquivo = fopen("fluxo.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar as transações.\n");
        return;
    }
    fwrite(transacoes, sizeof(Fluxo), totalTransacoes, arquivo);
    fclose(arquivo);
}

int loadFluxo(Fluxo *transacoes) {
    FILE *arquivo = fopen("fluxo.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhum arquivo de transações encontrado. Iniciando novo registro.\n");
        return 0;
    }
    int totalTransacoes = fread(transacoes, sizeof(Fluxo), Max_Fluxos, arquivo);
    fclose(arquivo);
    return totalTransacoes;
}

void fluxo() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001 > nul");
    Fluxo transacoes[Max_Fluxos];
    int totalTransacoes = loadFluxo(transacoes);
    Cadastro produtos[MAX_PRODUTOS];
    int totalProdutos = loadCad(produtos);
    int acao;
    char dataDesejada[11];

    do {
        MenuF();
        printf("Selecione uma Ação: ");
        scanf("%d", &acao);
        switch (acao) {
            case 1:
                Venda(transacoes, &totalTransacoes, produtos, totalProdutos);
                saveFluxo(transacoes, totalTransacoes);
                printf("Venda Realizada com Sucesso!\n");
                break;
            case 2:
                Pagamentos(transacoes, &totalTransacoes);
                saveFluxo(transacoes, totalTransacoes);
                printf("Pagamento Salvo com Sucesso!\n");
                break;
            case 3:
                ImprimirF(transacoes, totalTransacoes);
                break;
            case 4:
                MenuED(transacoes, totalTransacoes, produtos, totalProdutos);
                break;
            case 5:
                printf("Digite o Dia do Relatório (DD/MM/YYYY): ");
                scanf("%s", dataDesejada);
                IFC(transacoes, totalTransacoes, dataDesejada);
                break;
            case 6: {
                char mesAno[8];
                printf("Digite o Mês e o Ano do Relatório (MM/YYYY): ");
                scanf("%s", mesAno);
                GerarR_M(transacoes, totalTransacoes, mesAno);
                break;
            }
            case 7:
                printf("Retornando...\n");
                saveFluxo(transacoes, totalTransacoes);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (acao != 7);
}