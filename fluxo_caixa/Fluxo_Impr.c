#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../sistema.h"

void ImprimirF(Fluxo *transacoes, int NumT) {
    printf("===================================================================================================================\n");
    printf("| ID |         Transação          |  Unidades  |  Valor Unitário |  Valor Total |    Data    |     Pagamento     \n");
    printf("===================================================================================================================\n");
    int id = 1;
    for (int i = 0; i < NumT; i++) {
        if (strcmp(transacoes[i].mov, "") == 0) continue;

        int UniV = -1;
        float ValorUnit = -1;
        float valorTotal;
        char NomeProdt[31] = "";

        if (strcasecmp(transacoes[i].tipo, "Gasto") == 0) {
            strncpy(NomeProdt, transacoes[i].mov, sizeof(NomeProdt) - 1);
            NomeProdt[sizeof(NomeProdt) - 1] = '\0';
            valorTotal = transacoes[i].valor;
            printf("| %-3d | %-26s | %-10s | %-14s | %-12.2f | %-10s | %-16s\n", id++, NomeProdt, "---", "---", valorTotal, transacoes[i].data, transacoes[i].Pag);
        } else {
            sscanf(transacoes[i].mov, "%[^()] (ID: %*d, Unidades Vendidas: %d)", NomeProdt, &UniV);
            ValorUnit = transacoes[i].valor / UniV;
            valorTotal = transacoes[i].valor;
            printf("| %-3d | %-26s | %-10d | %-14.2f | %-12.2f | %-10s | %-16s\n", id++, NomeProdt, UniV, ValorUnit, valorTotal, transacoes[i].data, transacoes[i].Pag);
        }
    }
    printf("===================================================================================================================\n");
}