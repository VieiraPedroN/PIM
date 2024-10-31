#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Fluxo.h"

void IFC(Fluxo *transacoes, int NumF, const char *dataDesejada) {
    float saldo = 0.0, totalRecebido = 0.0, totalGasto = 0.0;
    printf("|==================================================================================================================\n");
    printf("|                                FLUXO DE CAIXA PARA O DIA %s\n", dataDesejada);
    printf("|====|=====================================|============|=================|===============|============|=======================\n");
    printf("| ID |           Transação                 |  Unidades  |  Valor Unitário |  Valor Total  |    Data    |  Pagamento            \n");
    printf("|====|=====================================|============|=================|===============|============|=======================\n");
    int id = 1;
    for (int i = 0; i < NumF; i++) {
        if (strcmp(transacoes[i].data, dataDesejada) == 0) {
            int unidadesVendidas = -1;
            float valorUnitario = -1;
            float valorTotal = transacoes[i].valor;
            char nomeProduto[31] = "";
            char pagamento[26];

            strncpy(transacoes[i].data, dataDesejada, sizeof(transacoes[i].data) - 1);
            transacoes[i].data[sizeof(transacoes[i].data) - 1] = '\0';
            strncpy(pagamento, transacoes[i].pagamento, sizeof(pagamento) - 1);
            pagamento[sizeof(pagamento) - 1] = '\0';

            if (strcasecmp(transacoes[i].tipo, "Gasto") == 0) {
                strncpy(nomeProduto, transacoes[i].movimentacao, sizeof(nomeProduto) - 1);
                nomeProduto[sizeof(nomeProduto) - 1] = '\0';
                saldo -= transacoes[i].valor;
                totalGasto += transacoes[i].valor;
                printf("| %-3d| %-35s | %-10s | %-15s | %-13.2f | %-10s | %-21s \n", id++, nomeProduto, "---", "---", valorTotal, transacoes[i].data, pagamento);
            } else if (strcasecmp(transacoes[i].tipo, "Recebimento") == 0) {
                sscanf(transacoes[i].movimentacao, "%[^()] (ID: %*d, Unidades Vendidas: %d)", nomeProduto, &unidadesVendidas);
                valorUnitario = transacoes[i].valor / unidadesVendidas;
                saldo += transacoes[i].valor;
                totalRecebido += transacoes[i].valor;
                printf("| %-3d| %-35s | %-10d | %-15.2f | %-13.2f | %-10s | %-21s \n", id++, nomeProduto, unidadesVendidas, valorUnitario, valorTotal, transacoes[i].data, pagamento);
            }
        }
    }
    printf("|==============================================================================================================================\n");
    printf("| %-71s | %-10.2f  \n", "Total Recebido:", totalRecebido);
    printf("| %-71s | %-10.2f  \n", "Total Gasto:", totalGasto);
    printf("| %-71s | %-10.2f  \n", "Saldo do Dia:", saldo);
    printf("|==============================================================================================================================\n");
}