#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../sistema.h"

void GerarR_M(Fluxo *transacoes, int NumT, char *MesAno, Compra *compras, int totalCompra) {
    float saldo = 0.0, totalRecebido = 0.0, totalGasto = 0.0, totalComprado = 0.0;
    printf("|============================================================================================================================\n");
    printf("|                                FLUXO DE CAIXA DO MÊS %s\n", MesAno);
    printf("=============================================================================================================================\n");
    printf("| ID |              Transação              |  Unidades  |  Valor Unitário |  Valor Total  |    Data    |  Pagamento   \n");
    printf("=============================================================================================================================\n");
    int id = 1;

    // Exibir Transações
    for (int i = 0; i < NumT; i++) {
        char MesAnoT[8];
        strncpy(MesAnoT, &transacoes[i].data[3], 7);
        MesAnoT[7] = '\0';
        if (strcmp(MesAnoT, MesAno) == 0) {
            int UniV = -1;
            float ValorUnit = -1;
            float valorTotal = transacoes[i].valor;
            char NomeProdt[31] = "";
            char Pag[26];

            strncpy(Pag, transacoes[i].Pag, sizeof(Pag) - 1);
            Pag[sizeof(Pag) - 1] = '\0';

            if (strcasecmp(transacoes[i].tipo, "Gasto") == 0) {
                strncpy(NomeProdt, transacoes[i].mov, sizeof(NomeProdt) - 1);
                NomeProdt[sizeof(NomeProdt) - 1] = '\0';
                saldo -= transacoes[i].valor;
                totalGasto += transacoes[i].valor;
                printf("| %-3d| %-35s | %-10s | %-15s | %-13.2f | %-10s | %-21s \n", id++, NomeProdt, "---", "---", valorTotal, transacoes[i].data, Pag);
            } else if (strcasecmp(transacoes[i].tipo, "Recebimento") == 0) {
                sscanf(transacoes[i].mov, "%[^()] (ID: %*d, Unidades Vendidas: %d)", NomeProdt, &UniV);
                ValorUnit = transacoes[i].valor / UniV;
                saldo += transacoes[i].valor;
                totalRecebido += transacoes[i].valor;
                printf("| %-3d| %-35s | %-10d | %-15.2f | %-13.2f | %-10s | %-21s \n", id++, NomeProdt, UniV, ValorUnit, valorTotal, transacoes[i].data, Pag);
            }
        }
    }

    // Exibir Compras
    for (int i = 0; i < totalCompra; i++) {
        char MesAnoC[8];
        snprintf(MesAnoC, sizeof(MesAnoC), "%s/%s", compras[i].valid.mes, compras[i].valid.ano);
        if (strcmp(MesAnoC, MesAno) == 0) {
            totalComprado += compras[i].valorTotal;
            saldo -= compras[i].valorTotal;
            printf("| %-3d| %-35s | %-10d | %-15.2f | %-13.2f | %-10s | %s \n", id++, compras[i].produto, compras[i].quantidade, compras[i].preco, compras[i].valorTotal, MesAnoC, "---");
        }
    }

    printf("=============================================================================================================================\n");
    printf("| %-71s | %-10.2f  \n", "Total Recebido:", totalRecebido);
    printf("| %-71s | %-10.2f  \n", "Total Gasto:", totalGasto);
    printf("| %-71s | %-10.2f  \n", "Total Comprado:", totalComprado);
    printf("| %-72s | %-10.2f  \n", "Saldo do Mês:", saldo);
    printf("=============================================================================================================================\n");
}

void IFC(Fluxo *transacoes, int NumT, const char *DataEsc, Compra *compras, int totalCompra) {
    float saldo = 0.0, totalRecebido = 0.0, totalGasto = 0.0, totalComprado = 0.0;
    printf("|==============================================================================================================================\n");
    printf("|                                FLUXO DE CAIXA PARA O DIA %s\n", DataEsc);
    printf("|====|=====================================|============|=================|===============|============|=======================\n");
    printf("| ID |           Transação                 |  Unidades  |  Valor Unitário |  Valor Total  |    Data    |  Pagamento        \n" );
    printf("|====|=====================================|============|=================|===============|============|=======================\n");
    int id = 1;

    // Exibir Transações
    for (int i = 0; i < NumT; i++) {
        if (strcmp(transacoes[i].data, DataEsc) == 0) {
            int UniV = -1;
            float ValorUnit = -1;
            float valorTotal = transacoes[i].valor;
            char NomeProdt[31] = "";
            char Pag[26];

            strncpy(Pag, transacoes[i].Pag, sizeof(Pag) - 1);
            Pag[sizeof(Pag) - 1] = '\0';

            if (strcasecmp(transacoes[i].tipo, "Gasto") == 0) {
                strncpy(NomeProdt, transacoes[i].mov, sizeof(NomeProdt) - 1);
                NomeProdt[sizeof(NomeProdt) - 1] = '\0';
                saldo -= transacoes[i].valor;
                totalGasto += transacoes[i].valor;
                printf("| %-3d| %-35s | %-10s | %-15s | %-13.2f | %-10s | %-21s \n", id++, NomeProdt, "---", "---", valorTotal, transacoes[i].data, Pag);
            } else if (strcasecmp(transacoes[i].tipo, "Recebimento") == 0) {
                sscanf(transacoes[i].mov, "%[^()] (ID: %*d, Unidades Vendidas: %d)", NomeProdt, &UniV);
                ValorUnit = transacoes[i].valor / UniV;
                saldo += transacoes[i].valor;
                totalRecebido += transacoes[i].valor;
                printf("| %-3d| %-35s | %-10d | %-15.2f | %-13.2f | %-10s | %-21s \n", id++, NomeProdt, UniV, ValorUnit, valorTotal, transacoes[i].data, Pag);
            }
        }
    }

    // Exibir Compras
    for (int i = 0; i < totalCompra; i++) {
        char DataCompra[11];
        snprintf(DataCompra, sizeof(DataCompra), "%s/%s/%s", compras[i].valid.dia, compras[i].valid.mes, compras[i].valid.ano);
        if (strcmp(DataCompra, DataEsc) == 0) {
            totalComprado += compras[i].valorTotal;
            saldo -= compras[i].valorTotal;
            printf("| %-3d| %-35s | %-10d | %-15.2f | %-13.2f | %-10s | %s \n", id++, compras[i].produto, compras[i].quantidade, compras[i].preco, compras[i].valorTotal, DataCompra, "---");
        }
    }

    printf("|==============================================================================================================================\n");
    printf("| %-71s | %-10.2f  \n", "Total Recebido:", totalRecebido);
    printf("| %-71s | %-10.2f  \n", "Total Gasto:", totalGasto);
    printf("| %-71s | %-10.2f  \n", "Total Comprado:", totalComprado);
    printf("| %-71s | %-10.2f  \n", "Saldo do Dia:", saldo);
    printf("|==============================================================================================================================\n");
}

void ImprimirF(Fluxo *transacoes, int NumT)
{
    printf("===================================================================================================================\n");
    printf("| ID |         Transação          |  Unidades  |  Valor Unitário |  Valor Total |    Data    |     Pagamento     \n");
    printf("===================================================================================================================\n");
    int id = 1;
    for (int i = 0; i < NumT; i++)
    {
        if (strcmp(transacoes[i].mov, "") == 0)
            continue;

        int UniV = -1;
        float ValorUnit = -1;
        float valorTotal;
        char NomeProdt[31] = "";

        if (strcasecmp(transacoes[i].tipo, "Gasto") == 0)
        {
            strncpy(NomeProdt, transacoes[i].mov, sizeof(NomeProdt) - 1);
            NomeProdt[sizeof(NomeProdt) - 1] = '\0';
            valorTotal = transacoes[i].valor;
            printf("| %-3d | %-26s | %-10s | %-14s | %-12.2f | %-10s | %-16s\n", id++, NomeProdt, "---", "---", valorTotal, transacoes[i].data, transacoes[i].Pag);
        }
        else
        {
            sscanf(transacoes[i].mov, "%[^()] (ID: %*d, Unidades Vendidas: %d)", NomeProdt, &UniV);
            ValorUnit = transacoes[i].valor / UniV;
            valorTotal = transacoes[i].valor;
            printf("| %-3d | %-26s | %-10d | %-14.2f | %-12.2f | %-10s | %-16s\n", id++, NomeProdt, UniV, ValorUnit, valorTotal, transacoes[i].data, transacoes[i].Pag);
        }
    }
    printf("===================================================================================================================\n");
}