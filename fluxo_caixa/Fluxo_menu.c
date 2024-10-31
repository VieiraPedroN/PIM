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

void MenuF() {
    printf("\n======== Menu do Financeiro =============\n");
    printf("| 1. Iniciar Venda                      |\n");
    printf("| 2. Realizar Pagamentos                |\n");
    printf("| 3. Ver Histórico de Transações        |\n");
    printf("| 4. Editar ou Deletar Transações       |\n");
    printf("| 5. Relatório Diário                   |\n");
    printf("| 6. Relatório Mensal                   |\n");
    printf("| 7. Voltar ao Menu Principal           |\n");
    printf("=========================================\n");
}

void saveFluxo(Fluxo *transacoes, int totalFluxo) {
    FILE *arquivo = fopen("fluxo.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar as transações.\n");
        return;
    }
    fwrite(transacoes, sizeof(Fluxo), totalFluxo, arquivo);
    fclose(arquivo);
}

int loadFluxo(Fluxo *transacoes)
{
    FILE *arquivo = fopen("fluxo.dat", "rb");
    if (arquivo == NULL)
    {
        printf("Nenhum arquivo de transações encontrado. Iniciando novo registro.\n");
        return 0;
    }
    int totalFluxo = fread(transacoes, sizeof(Fluxo), Max_Fluxos, arquivo);
    fclose(arquivo);
    return totalFluxo;
}

int fluxo()
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001 > nul");
    Fluxo transacoes[Max_Fluxos];
    int totalFluxo = loadFluxo(transacoes);
    Cadastro produtos[MAX_PRODUTOS];
    int totalProd = loadCad(produtos);
    int acao;
    char dataDesejada[11];

    do
    {
        MenuF();
        printf("Selecione uma Ação: ");
        scanf("%d", &acao);
        switch (acao)
        {
        case 1:
            Venda(transacoes, &totalFluxo, produtos, totalProd);
            break;
        case 2:
        {
            printf("\nÁrea de Pagamentos\n");
            char transacao[50], data[11], pagamento[20];
            float valorPago;
            printf("Informe o que deseja Pagar: ");
            getchar();
            fgets(transacao, sizeof(transacao), stdin);
            transacao[strcspn(transacao, "\n")] = '\0';
            printf("Informe o custo desse Pagamento: ");
            scanf("%f", &valorPago);
            FormaPP(pagamento);
            printf("Data (DD/MM/YYYY): ");
            scanf("%s\n", data);
            Pagamentos(transacoes, &totalFluxo, transacao, valorPago, data, pagamento);
            saveFluxo(transacoes, totalFluxo);
            printf("Pagamento Salvo com Sucesso!");
            break;
        }
        case 3:
            ImprimirF(transacoes, totalFluxo);
            break;
        case 4:
            MenuED(transacoes, totalFluxo, produtos, totalProd);
            break;
        case 5:
            printf("Digite o Dia do Relatório (DD/MM/YYYY): ");
            scanf("%s", dataDesejada);
            IFC(transacoes, totalFluxo, dataDesejada);
            break;
        case 6:
        {
            char MesAno[8];
            printf("Digite o Mês e o Ano do Relatório (MM/YYYY): ");
            scanf("%s", MesAno);
            GerarR_M(transacoes, totalFluxo, MesAno);
            break;
        }
        case 7:
            printf("Retornando...\n");
            saveFluxo(transacoes, totalFluxo);
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (acao != 7);
    return 0;
}