#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Fluxo.h"
#include "../cad/cadastro.h"

void DeletV(Fluxo *transacoes, int *NumF, int IndiceT, Cadastro *produtos, int totalProd) {
    if (IndiceT < 0 || IndiceT >= *NumF) {
        printf("Índice inválido.\n");
        return;
    }
    if (strcasecmp(transacoes[IndiceT].tipo, "Recebimento") != 0) {
        printf("Apenas Vendas podem ser deletadas.\n");
        return;
    }
    int prodIndex = -1;
    for (int i = 0; i < totalProd; i++) {
        if (strstr(transacoes[IndiceT].movimentacao, produtos[i].nome) != NULL) {
            int unidadesVendidas = (int)(transacoes[IndiceT].valor / produtos[i].valor);
            produtos[i].qtd += unidadesVendidas;
            prodIndex = i;
            break;
        }
    }
    if (prodIndex == -1) {
        printf("Erro: Produto não encontrado na transação.\n");
        return;
    }
    char confirmacao;
    printf("Tem certeza que deseja deletar a transação de %s no valor de %.2f? (S/N): ", produtos[prodIndex].nome, transacoes[IndiceT].valor);
    scanf(" %c", &confirmacao);
    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = IndiceT; i < *NumF - 1; i++) {
            transacoes[i] = transacoes[i + 1];
        }
        (*NumF)--;
        Fluxo vazio = {"", 0.0, "", "", ""};
        transacoes[*NumF] = vazio;

        saveCad(produtos, totalProd);
        saveFluxo(transacoes, *NumF);
        printf("Venda deletada com sucesso. Estoque atualizado.\n");
    } else {
        printf("Operação de exclusão cancelada.\n");
    }
}

void DeletP(Fluxo *transacoes, int *NumF, int IndiceT) {
    if (IndiceT <= 0 || IndiceT > *NumF) {
        printf("Índice inválido.\n");
        return;
    }
    IndiceT--;
    if (strcasecmp(transacoes[IndiceT].tipo, "Gasto") != 0) {
        printf("Apenas Pagamentos podem ser deletados.\n");
        return;
    }
    char confirmacao;
    printf("Tem certeza que deseja deletar a transação de %s no valor de %.2f? (S/N): ", transacoes[IndiceT].movimentacao, transacoes[IndiceT].valor);
    scanf(" %c", &confirmacao);
    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = IndiceT; i < *NumF - 1; i++) {
            transacoes[i] = transacoes[i + 1];
        }
        (*NumF)--;
        memset(&transacoes[*NumF], 0, sizeof(Fluxo));
        saveFluxo(transacoes, *NumF);
        printf("Pagamento deletado com sucesso.\n");
    } else {
        printf("Operação de exclusão cancelada.\n");
    }
}

void EditV(Fluxo *transacoes, int NumF, Cadastro *produtos, int totalProd) {
    int IndiceT, novasUnidadesVendidas, id = -1;

    printf("ID da Venda para editar: ");
    scanf("%d", &IndiceT);

    if (IndiceT <= 0 || IndiceT > NumF) {
        printf("Índice inválido.\n");
        return;
    }
    IndiceT--;
    if (strcasecmp(transacoes[IndiceT].tipo, "Recebimento") != 0) {
        printf("Apenas Vendas podem ser editadas.\n");
        return;
    }
    for (int i = 0; i < totalProd; i++) {
        if (strstr(transacoes[IndiceT].movimentacao, produtos[i].nome) != NULL) {
            id = i + 1;
            break;
        }
    }
    if (id == -1) {
        printf("Produto não encontrado.\n");
        return;
    }
    printf("Produto atual: %s\n", produtos[id - 1].nome);
    printf("Nova quantidade de unidades vendidas: ");
    scanf("%d", &novasUnidadesVendidas);

    int unidadesVendidas = (int)(transacoes[IndiceT].valor / produtos[id - 1].valor);
    produtos[id - 1].qtd += unidadesVendidas;
    produtos[id - 1].qtd -= novasUnidadesVendidas;

    char novaMovimentacao[50], novaData[11], novoPagamento[20];
    float novoValor = produtos[id - 1].valor * novasUnidadesVendidas;

    printf("Nova forma de pagamento: ");
    FormaP(novoPagamento);

    printf("Nova data (DD/MM/YYYY): ");
    scanf("%s", novaData);

    snprintf(novaMovimentacao, sizeof(novaMovimentacao), "%s (ID: %d, Unidades Vendidas: %d)", produtos[id - 1].nome, id, novasUnidadesVendidas);
    strncpy(transacoes[IndiceT].movimentacao, novaMovimentacao, sizeof(transacoes[IndiceT].movimentacao) - 1);
    transacoes[IndiceT].movimentacao[sizeof(transacoes[IndiceT].movimentacao) - 1] = '\0';
    transacoes[IndiceT].valor = novoValor;
    strncpy(transacoes[IndiceT].data, novaData, sizeof(transacoes[IndiceT].data) - 1);
    transacoes[IndiceT].data[sizeof(transacoes[IndiceT].data) - 1] = '\0';
    strncpy(transacoes[IndiceT].pagamento, novoPagamento, sizeof(transacoes[IndiceT].pagamento) - 1);
    transacoes[IndiceT].pagamento[sizeof(transacoes[IndiceT].pagamento) - 1] = '\0';

    saveCad(produtos, totalProd);
    saveFluxo(transacoes, NumF);
    printf("Estoque atualizado.\n");
}

void EditP(Fluxo *transacoes, int NumF, int IndiceT) {
    if (IndiceT <= 0 || IndiceT > NumF) {
        printf("Índice inválido.\n");
        return;
    }
    IndiceT--;
    if (strcasecmp(transacoes[IndiceT].tipo, "Gasto") != 0) {
        printf("Apenas Pagamento podem ser editados.\n");
        return;
    }
    printf("Editar transação de pagamento: %s\n", transacoes[IndiceT].movimentacao);

    char novaMovimentacao[50], novaData[11], novoPagamento[20];
    float novoValor;

    printf("Novo valor do pagamento: ");
    scanf("%f", &novoValor);

    printf("Nova forma de pagamento: ");
    FormaPP(novoPagamento);

    printf("Nova data (DD/MM/YYYY): ");
    scanf("%s", novaData);

    snprintf(novaMovimentacao, sizeof(novaMovimentacao), "%s", transacoes[IndiceT].movimentacao);
    strncpy(transacoes[IndiceT].movimentacao, novaMovimentacao, sizeof(transacoes[IndiceT].movimentacao) - 1);
    transacoes[IndiceT].movimentacao[sizeof(transacoes[IndiceT].movimentacao) - 1] = '\0';
    transacoes[IndiceT].valor = novoValor;
    strncpy(transacoes[IndiceT].data, novaData, sizeof(transacoes[IndiceT].data) - 1);
    transacoes[IndiceT].data[sizeof(transacoes[IndiceT].data) - 1] = '\0';
    strncpy(transacoes[IndiceT].pagamento, novoPagamento, sizeof(transacoes[IndiceT].pagamento) - 1);
    transacoes[IndiceT].pagamento[sizeof(transacoes[IndiceT].pagamento) - 1] = '\0';

    saveFluxo(transacoes, NumF);
    printf("Pagamento editado com sucesso.\n");
}

void MenuED(Fluxo *transacoes, int totalFluxo, Cadastro *produtos, int totalProd) {
    int acao, IndiceT;
    do {
        printf("\nMenu de Edição e Exclusão:\n");
        printf("***************************\n");
        printf("1. Editar Venda\n");
        printf("2. Deletar Venda\n");
        printf("3. Editar Pagamento\n");
        printf("4. Deletar Pagamento\n");
        printf("5. Voltar ao Fluxo de Caixa\n");
        printf("***************************\n");
        printf("Selecione uma Ação: ");
        scanf("%d", &acao);
        switch (acao) {
            case 1:
                EditV(transacoes, totalFluxo, produtos, totalProd);
                break;
            case 2:
                printf("ID da Venda para deletar: ");
                scanf("%d", &IndiceT);
                DeletV(transacoes, &totalFluxo, IndiceT, produtos, totalProd);
                break;
            case 3:
                printf("ID do Pagamento para editar: ");
                scanf("%d", &IndiceT);
                EditP(transacoes, totalFluxo, IndiceT);
                break;
            case 4:
                printf("ID do Pagamento para deletar: ");
                scanf("%d", &IndiceT);
                DeletP(transacoes, &totalFluxo, IndiceT);
                break;
            case 5:
                printf("Saindo do menu de edição e exclusão.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (acao != 5);
}