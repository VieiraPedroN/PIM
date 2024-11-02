#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Fluxo.h"
#include "../sistema.h"

void Pagamentos(Fluxo *transacoes, int *numTransacoes) {
    if (*numTransacoes >= Max_Fluxos) {
        printf("Limite de transações alcançado!\n");
        return;
    }

    Fluxo novaTransacao;
    printf("Informe o que deseja pagar: ");
    getchar();
    fgets(novaTransacao.movimentacao, sizeof(novaTransacao.movimentacao), stdin);
    novaTransacao.movimentacao[strcspn(novaTransacao.movimentacao, "\n")] = '\0';

    printf("Informe o valor desse pagamento: ");
    scanf("%f", &novaTransacao.valor);
    getchar();
    strcpy(novaTransacao.tipo, "Gasto");

    printf("Forma de Pagamento:\n");
    FormaPP(novaTransacao.pagamento);

    int dataValida = 0;
    char dia[3], mes[3], ano[5];
    while (!dataValida) {
        printf("Data (DD/MM/YYYY): ");
        if (scanf("%2s/%2s/%4s", dia, mes, ano) != 3) {
            printf("Erro: Formato de data inválido. Por favor, tente novamente.\n");
            while (getchar() != '\n');
            continue;
        }
        dataValida = validarD(dia, mes, ano);
        if (!dataValida) {
            printf("Erro: Data inválida. Por favor, tente novamente.\n");
        }
    }

    snprintf(novaTransacao.data, sizeof(novaTransacao.data), "%s/%s/%s", dia, mes, ano);

    transacoes[*numTransacoes] = novaTransacao;
    (*numTransacoes)++;

    printf("Pagamento registrado: %s\n", novaTransacao.data);
}