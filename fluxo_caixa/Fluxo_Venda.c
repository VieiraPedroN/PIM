#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../sistema.h"

void Venda(Fluxo *transacoes, int *numTransacoes, Cadastro *produtos, int totalProdutos) {
    int produtoID, quantidadeVendida;
    char data[11], formaPagamento[20], dia[3], mes[3], ano[5];
    char confirmacao;
    float subtotal = 0.0;
    int transacoesInicial = *numTransacoes;

    while (1) {
        printf("ID do Produto que será vendido (digite 0 para sair): ");
        scanf("%d", &produtoID);

        if (produtoID == 0) {
            printf("Saindo da venda...\n");
            break;
        }

        if (produtoID <= 0 || produtoID > totalProdutos) {
            printf("ID inválido. Por favor, tente novamente.\n");
            continue;
        }

        printf("Produto selecionado: %s\n", produtos[produtoID - 1].nome);
        printf("Quantidades a serem Vendidas: ");
        scanf("%d", &quantidadeVendida);

        if (quantidadeVendida <= 0) {
            printf("Erro: A quantidade de unidades vendidas deve ser maior que zero.\n");
            continue;
        }

        if (*numTransacoes >= Max_Fluxos) {
            printf("Limite de transações alcançado!\n");
            return;
        }

        int indiceProduto = produtoID - 1;

        if (produtos[indiceProduto].qtd < quantidadeVendida) {
            printf("Erro: Quantidade insuficiente no estoque!\n");
            continue;
        }

        float valorProduto = produtos[indiceProduto].valor;
        float valorTotal = valorProduto * quantidadeVendida;
        subtotal += valorTotal;

        Fluxo novaTransacao;
        snprintf(novaTransacao.movimentacao, sizeof(novaTransacao.movimentacao), "%s (ID: %d, Unidades Vendidas: %d)", produtos[indiceProduto].nome, produtoID, quantidadeVendida);
        novaTransacao.valor = valorTotal;
        strcpy(novaTransacao.tipo, "Recebimento");

        transacoes[*numTransacoes] = novaTransacao;
        (*numTransacoes)++;
        produtos[indiceProduto].qtd -= quantidadeVendida;

        printf("Produto adicionado com Sucesso! Quantidade restante de %s: %d\n", produtos[indiceProduto].nome, produtos[indiceProduto].qtd);
        printf("Subtotal da compra até agora: %.2f\n", subtotal);
        printf("Deseja adicionar Outro Produto? (S/N): ");
        scanf(" %c", &confirmacao);

        if (confirmacao != 'S' && confirmacao != 's') {
            break;
        }
    }

    if (transacoesInicial != *numTransacoes) {
        int dataValida = 0;
        while (!dataValida) {
            printf("Data Da Venda (DD/MM/YYYY): ");
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

        snprintf(data, sizeof(data), "%s/%s/%s", dia, mes, ano);
        FormaP(formaPagamento);

        if (strcmp(formaPagamento, "Dinheiro") == 0) {
            float valorPago, troco;
            printf("Valor Pago pelo Cliente: ");
            scanf("%f", &valorPago);
            troco = valorPago - subtotal;
            printf("Troco: %.2f\n", troco);
            printf("Venda Realizada com Sucesso!\n");
        }

        for (int i = transacoesInicial; i < *numTransacoes; i++) {
            strncpy(transacoes[i].data, data, sizeof(transacoes[i].data) - 1);
            transacoes[i].data[sizeof(transacoes[i].data) - 1] = '\0';
            strncpy(transacoes[i].pagamento, formaPagamento, sizeof(transacoes[i].pagamento) - 1);
            transacoes[i].pagamento[sizeof(transacoes[i].pagamento) - 1] = '\0';
        }

        saveFluxo(transacoes, *numTransacoes);
        saveCad(produtos, totalProdutos);
    } else {
        printf("Nenhum produto foi vendido.\n");
    }
}