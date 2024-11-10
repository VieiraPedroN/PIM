#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

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
    printf("==========  Menu do Financeiro  =========\n");
    printf("| 1- Realizar Pagametos                 |\n");
    printf("| 2- Ver Histórico de Transações        |\n");
    printf("| 3- Editar ou Deletar Transações       |\n");
    printf("| 4- Relatório Diário                   |\n");
    printf("| 5- Relatório Mensal                   |\n");
    printf("| 6- Voltar ao Menu Principal           |\n");
    printf("=========================================\n");
}

void saveFluxo(Fluxo *transacoes, int TotalT) {
    // Caminho absoluto para a pasta 'dados'
    const char *path = "C:/Users/bhper/OneDrive/Documentos/PIM/dados/fluxo.dat";
    FILE *arquivo = fopen(path, "wb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo para salvar as transações");
        return;
    }
    fwrite(transacoes, sizeof(Fluxo), TotalT, arquivo);
    fclose(arquivo);
}


int loadFluxo(Fluxo *transacoes) {
    // Caminho absoluto para a pasta 'dados'
    const char *path = "C:/Users/bhper/OneDrive/Documentos/PIM/dados/fluxo.dat";
    FILE *arquivo = fopen(path, "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de transações");
        return 0;
    }
    int TotalT = fread(transacoes, sizeof(Fluxo), Max_Fluxos, arquivo);
    fclose(arquivo);
    return TotalT;
}

void fluxo() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001 > nul");
    Fluxo transacoes[Max_Fluxos];
    int TotalT = loadFluxo(transacoes);
    Cadastro produtos[MAX_PRODUTOS];
    int TotalProdts = loadCad(produtos);
    int acao;
    char DataEsc[11];
    Compra compras[MAX_COMPRA];
    int totalCompra = loadCompra(compras);

    do {
        MenuF();
        printf("Selecione uma Ação: ");
        scanf("%d", &acao);
        switch (acao) {
            case 1:
                Pags(transacoes, &TotalT);
                saveFluxo(transacoes, TotalT);
                break;
            case 2:
                ImprimirF(transacoes, TotalT);
                break;
            case 3:
                MenuED(transacoes, TotalT, produtos, TotalProdts);
                break;
            case 4:
                printf("Digite o Dia do Relatório (DD/MM/YYYY): ");
                scanf("%s", DataEsc);
                IFC(transacoes, TotalT, DataEsc, compras, totalCompra);
                break;
            case 5: {
                char MesAno[8];
                printf("Digite o Mês e o Ano do Relatório (MM/YYYY): ");
                scanf("%s", MesAno);
                GerarR_M(transacoes, TotalT, MesAno, compras, totalCompra);
                break;
            }
            case 6:
                printf("Retornando...\n");
                saveFluxo(transacoes, TotalT);
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (acao != 6);
}