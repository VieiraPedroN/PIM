#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../sistema.h"

void Pags(Fluxo *transacoes, int *NumT) {
    if (*NumT >= Max_Fluxos) {
        printf("Limite de transações alcançado!\n");
        return;
    }

    Fluxo NewT;
    printf("Informe o que deseja pagar: ");
    getchar();
    fgets(NewT.mov, sizeof(NewT.mov), stdin);
    NewT.mov[strcspn(NewT.mov, "\n")] = '\0';

    printf("Informe o valor desse Pagamento: ");
    scanf("%f", &NewT.valor);
    getchar();
    strcpy(NewT.tipo, "Gasto");

    printf("Forma de Pagamneto:\n");
    FormaPP(NewT.Pag);

    int dataValida = 0;
    char dia[3], mes[3], ano[5];
    while (!dataValida) {
        printf("Informe a Data do Pagamento (DD/MM/YYYY): ");
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

    snprintf(NewT.data, sizeof(NewT.data), "%s/%s/%s", dia, mes, ano);

    transacoes[*NumT] = NewT;
    (*NumT)++;

    printf("Pagamento registrado com Sucesso!\n");
    saveFluxo(transacoes, *NumT); // garantir que as transações sejam salvas após o pagamento
}