#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Fluxo.h"

void ImprimirF(Fluxo *transacoes, int NumF) {
    printf("===================================================================================================================\n");
    printf("| ID |         Transação          |  Unidades  |  Valor Unitário |  Valor Total |    Data    |     Pagamento       \n");
    printf("===================================================================================================================\n");
    int id = 1;
    for (int i = 0; i < NumF; i++) {
        if (strcmp(transacoes[i].movimentacao, "") == 0) continue;

        int unidadesVendidas = -1;
        float valorUnitario = -1;
        float valorTotal;
        char nomeProduto[31] = "";

        if (strcasecmp(transacoes[i].tipo, "Gasto") == 0) {
            strncpy(nomeProduto, transacoes[i].movimentacao, sizeof(nomeProduto) - 1);
            nomeProduto[sizeof(nomeProduto) - 1] = '\0';
            valorTotal = transacoes[i].valor;
            printf("| %-3d | %-26s | %-10s | %-14s | %-12.2f | %-10s | %-16s\n", id++, nomeProduto, "---", "---", valorTotal, transacoes[i].data, transacoes[i].pagamento);
        } else {
            sscanf(transacoes[i].movimentacao, "%[^()] (ID: %*d, Unidades Vendidas: %d)", nomeProduto, &unidadesVendidas);
            valorUnitario = transacoes[i].valor / unidadesVendidas;
            valorTotal = transacoes[i].valor;
            printf("| %-3d | %-26s | %-10d | %-14.2f | %-12.2f | %-10s | %-16s\n", id++, nomeProduto, unidadesVendidas, valorUnitario, valorTotal, transacoes[i].data, transacoes[i].pagamento);
        }
    }
    printf("===================================================================================================================\n");
}