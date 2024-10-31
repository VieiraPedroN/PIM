#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Fluxo.h"
#include "../sistema.h"

void Venda(Fluxo *transacoes, int *NumF, Cadastro *produtos, int totalProd) {
    int id, unidadesVendidas;
    char data[11], pagamento[20];
    char confirmacao;
    float subtotal = 0.0;
    int numTransacoes = *NumF;

    while (1) {
        printf("ID do Produto que será vendido: ");
        scanf("%d", &id);

        if (id <= 0 || id > totalProd) {
            printf("ID inválido. Por favor, tente novamente.\n");
            continue;
        }

        printf("Produto selecionado: %s\n", produtos[id - 1].nome);
        printf("Quantidades a serem Vendidas: ");
        scanf("%d", &unidadesVendidas);

        if (unidadesVendidas <= 0) {
            printf("Erro: A quantidade de unidades vendidas deve ser maior que zero.\n");
            continue;
        }

        if (*NumF >= Max_Fluxos) {
            printf("Limite de transações alcançado!\n");
            return;
        }

        int prodIndex = id - 1;

        if (produtos[prodIndex].qtd < unidadesVendidas) {
            printf("Erro: Quantidade insuficiente no estoque!\n");
            continue;
        }

        float produtoValor = produtos[prodIndex].valor;
        float valorTotal = produtoValor * unidadesVendidas;
        subtotal += valorTotal;

        Fluxo NovoF;
        snprintf(NovoF.movimentacao, sizeof(NovoF.movimentacao), "%s (ID: %d, Unidades Vendidas: %d)", produtos[prodIndex].nome, id, unidadesVendidas);
        NovoF.valor = valorTotal;
        strcpy(NovoF.tipo, "Recebimento");

        transacoes[*NumF] = NovoF;
        (*NumF)++;
        produtos[prodIndex].qtd -= unidadesVendidas;

        printf("Produto adicionado com Sucesso! Quantidade restante de %s: %d\n", produtos[prodIndex].nome, produtos[prodIndex].qtd);
        printf("Subtotal da compra até agora: %.2f\n", subtotal);
        printf("Deseja adicionar Outro Produto? (S/N): ");
        scanf(" %c", &confirmacao);

        if (confirmacao != 'S' && confirmacao != 's') {
            break;
        }
    }

    printf("Data Da Venda (DD/MM/YYYY): ");
    scanf("%s", data);
    FormaP(pagamento);

    if (strcmp(pagamento, "Dinheiro") == 0) {
        float valorPago, troco;
        printf("Valor Pago pelo Cliente: ");
        scanf("%f", &valorPago);
        troco = valorPago - subtotal;
        printf("Troco: %.2f\n", troco);
        printf("Venda Realizada com Sucesso!\n");
    }

    for (int i = numTransacoes; i < *NumF; i++) {
        strncpy(transacoes[i].data, data, sizeof(transacoes[i].data) - 1);
        transacoes[i].data[sizeof(transacoes[i].data) - 1] = '\0';
        strncpy(transacoes[i].pagamento, pagamento, sizeof(transacoes[i].pagamento) - 1);
        transacoes[i].pagamento[sizeof(transacoes[i].pagamento) - 1] = '\0';
    }

    saveFluxo(transacoes, *NumF);
    saveCad(produtos, totalProd);
}