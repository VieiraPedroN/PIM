#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Fluxo.h"

void Pagamentos(Fluxo *transacoes, int *NumF, char *transacao, float valor, char *data, char *pagamento) {
    if (*NumF >= Max_Fluxos) {
        printf("Limite de transações alcançado!\n");
        return;
    }
    Fluxo NovoF;
    strncpy(NovoF.movimentacao, transacao, sizeof(NovoF.movimentacao) - 1);
    NovoF.movimentacao[sizeof(NovoF.movimentacao) - 1] = '\0';
    NovoF.valor = valor;
    strcpy(NovoF.tipo, "Gasto");
    strncpy(NovoF.data, data, sizeof(NovoF.data) - 1);
    NovoF.data[sizeof(NovoF.data) - 1] = '\0';
    strncpy(NovoF.pagamento, pagamento, sizeof(NovoF.pagamento) - 1);
    NovoF.pagamento[sizeof(NovoF.pagamento) - 1] = '\0';
    transacoes[*NumF] = NovoF;
    (*NumF)++;
}