#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Fluxo.h"
#include "../sistema.h"

void DeletV(Fluxo *transacoes, int *numTransacoes, int indiceTransacao, Cadastro *produtos, int totalProdutos) {
    if (indiceTransacao < 0 || indiceTransacao >= *numTransacoes) {
        printf("Índice inválido.\n");
        return;
    }
    indiceTransacao--;
    if (strcasecmp(transacoes[indiceTransacao].tipo, "Recebimento") != 0) {
        printf("Apenas Vendas podem ser deletadas.\n");
        return;
    }
    int indiceProduto = -1;
    for (int i = 0; i < totalProdutos; i++) {
        if (strstr(transacoes[indiceTransacao].movimentacao, produtos[i].nome) != NULL) {
            int unidadesVendidas = (int)(transacoes[indiceTransacao].valor / produtos[i].valor);
            produtos[i].qtd += unidadesVendidas;
            indiceProduto = i;
            break;
        }
    }
    if (indiceProduto == -1) {
        printf("Erro: Produto não encontrado na transação.\n");
        return;
    }
    char confirmacao;
    printf("Tem certeza que deseja deletar a transação de %s no valor de %.2f? (S/N): ", produtos[indiceProduto].nome, transacoes[indiceTransacao].valor);
    scanf(" %c", &confirmacao);
    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = indiceTransacao; i < *numTransacoes - 1; i++) {
            transacoes[i] = transacoes[i + 1];
        }
        (*numTransacoes)--;
        Fluxo vazio = {"", 0.0, "", "", ""};
        transacoes[*numTransacoes] = vazio;

        saveCad(produtos, totalProdutos);
        saveFluxo(transacoes, *numTransacoes);
        printf("Venda Deletada com Sucesso. Estoque atualizado.\n");
    } else {
        printf("Operação de exclusão cancelada.\n");
    }
}

void DeletP(Fluxo *transacoes, int *numTransacoes, int indiceTransacao) {
    if (indiceTransacao <= 0 || indiceTransacao > *numTransacoes) {
        printf("Índice inválido.\n");
        return;
    }
    indiceTransacao--;
    if (strcasecmp(transacoes[indiceTransacao].tipo, "Gasto") != 0) {
        printf("Apenas Pagamentos podem ser deletados.\n");
        return;
    }
    char confirmacao;
    printf("Tem certeza que deseja deletar o Pagamento '%s' no valor de %.2f? (S/N): ", transacoes[indiceTransacao].movimentacao, transacoes[indiceTransacao].valor);
    scanf(" %c", &confirmacao);
    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = indiceTransacao; i < *numTransacoes - 1; i++) {
            transacoes[i] = transacoes[i + 1];
        }
        (*numTransacoes)--;
        memset(&transacoes[*numTransacoes], 0, sizeof(Fluxo));
        saveFluxo(transacoes, *numTransacoes);
        printf("Pagamento Deletado com Sucesso.\n");
    } else {
        printf("Operação de exclusão cancelada.\n");
    }
}

void EditV(Fluxo *transacoes, int numTransacoes, Cadastro *produtos, int totalProdutos) {
    int indiceTransacao, novasUnidadesVendidas, id = -1;
    float novoValor;
    char novaMovimentacao[50], novaData[11], novoPagamento[20], dia[3], mes[3], ano[5];

    printf("ID da Venda Para Editar: ");
    scanf("%d", &indiceTransacao);

    if (indiceTransacao <= 0 || indiceTransacao > numTransacoes) {
        printf("Índice inválido.\n");
        return;
    }
    indiceTransacao--;
    if (strcasecmp(transacoes[indiceTransacao].tipo, "Recebimento") != 0) {
        printf("Apenas Vendas podem ser editadas.\n");
        return;
    }
    for (int i = 0; i < totalProdutos; i++) {
        if (strstr(transacoes[indiceTransacao].movimentacao, produtos[i].nome) != NULL) {
            id = i + 1;
            break;
        }
    }
    if (id == -1) {
        printf("Produto Não Encontrado.\n");
        return;
    }

    printf("Editando a Venda do Produto: %s\n", produtos[id - 1].nome);

    printf("O que você gostaria de editar?\n");
    printf("1. Quantidade de Produtos\n");
    printf("2. Data\n");
    printf("3. Forma de Pagamento\n");
    printf("4. Sair\n");
    
    int escolha;
    printf("Selecione uma opção: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1: {
            printf("Nova Quantidade de Produtos: ");
            scanf("%d", &novasUnidadesVendidas);
            int unidadesVendidas = (int)(transacoes[indiceTransacao].valor / produtos[id - 1].valor);
            produtos[id - 1].qtd += unidadesVendidas;
            produtos[id - 1].qtd -= novasUnidadesVendidas;

            novoValor = produtos[id - 1].valor * novasUnidadesVendidas;
            snprintf(novaMovimentacao, sizeof(novaMovimentacao), "%s (ID: %d, Unidades Vendidas: %d)", produtos[id - 1].nome, id, novasUnidadesVendidas);

            strncpy(transacoes[indiceTransacao].movimentacao, novaMovimentacao, sizeof(transacoes[indiceTransacao].movimentacao) - 1);
            transacoes[indiceTransacao].movimentacao[sizeof(transacoes[indiceTransacao].movimentacao) - 1] = '\0';
            transacoes[indiceTransacao].valor = novoValor;
            break;
        }
        case 2: {
            int dataValida = 0;
            while (!dataValida) {
                printf("Nova data (DD/MM/YYYY): ");
                if (scanf("%2s/%2s/%4s", dia, mes, ano) != 3) {
                    printf("Erro: Formato de data inválido. Por favor, tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }
                dataValida = validarD(dia, mes, ano);
                if (!dataValida) {
                    printf("Erro: Data inválida. Tente novamente.\n");
                }
            }
            snprintf(novaData, sizeof(novaData), "%s/%s/%s", dia, mes, ano);
            strncpy(transacoes[indiceTransacao].data, novaData, sizeof(transacoes[indiceTransacao].data) - 1);
            transacoes[indiceTransacao].data[sizeof(transacoes[indiceTransacao].data) - 1] = '\0';
            break;
        }
        case 3: {
            printf("Nova ");
            FormaP(novoPagamento);
            strncpy(transacoes[indiceTransacao].pagamento, novoPagamento, sizeof(transacoes[indiceTransacao].pagamento) - 1);
            transacoes[indiceTransacao].pagamento[sizeof(transacoes[indiceTransacao].pagamento) - 1] = '\0';
            break;
        }
        case 4: {
            printf("Saindo da edição.\n");
            return;
        }
        default: {
            printf("Opção inválida!\n");
            return;
        }
    }

    saveCad(produtos, totalProdutos);
    saveFluxo(transacoes, numTransacoes);
    printf("Venda editada com sucesso.\n");
}

void EditP(Fluxo *transacoes, int numTransacoes, int indiceTransacao) {
    if (indiceTransacao <= 0 || indiceTransacao > numTransacoes) {
        printf("Índice inválido.\n");
        return;
    }
    indiceTransacao--;
    if (strcasecmp(transacoes[indiceTransacao].tipo, "Gasto") != 0) {
        printf("Apenas Pagamentos podem ser editados.\n");
        return;
    }
    printf("Editando o Pagamento: %s\n", transacoes[indiceTransacao].movimentacao);

    printf("O que você gostaria de editar?\n");
    printf("1. Nome do Pagamento\n");
    printf("2. Valor do Pagamento\n");
    printf("3. Data\n");
    printf("4. Forma de Pagamento\n");
    printf("5. Sair\n");

    int escolha;
    printf("Selecione uma opção: ");
    scanf("%d", &escolha);

    float novoValor;
    char novaMovimentacao[50], novaData[11], novoPagamento[20], dia[3], mes[3], ano[5];

    switch (escolha) {
        case 1: {
            printf("Novo Nome do Pagamento: ");
            getchar();
            fgets(novaMovimentacao, sizeof(novaMovimentacao), stdin);
            novaMovimentacao[strcspn(novaMovimentacao, "\n")] = '\0';
            strncpy(transacoes[indiceTransacao].movimentacao, novaMovimentacao, sizeof(transacoes[indiceTransacao].movimentacao) - 1);
            transacoes[indiceTransacao].movimentacao[sizeof(transacoes[indiceTransacao].movimentacao) - 1] = '\0';
            break;
        }
        case 2: {
            printf("Novo Valor do Pagamento: ");
            scanf("%f", &novoValor);
            transacoes[indiceTransacao].valor = novoValor;
            break;
        }
        case 3: {
            int dataValida = 0;
            while (!dataValida) {
                printf("Nova data (DD/MM/YYYY): ");
                if (scanf("%2s/%2s/%4s", dia, mes, ano) != 3) {
                    printf("Erro: Formato de data inválido. Por favor, tente novamente.\n");
                    while (getchar() != '\n');
                    continue;
                }
                dataValida = validarD(dia, mes, ano);
                if (!dataValida) {
                    printf("Erro: Data inválida. Tente novamente.\n");
                }
            }
            snprintf(novaData, sizeof(novaData), "%s/%s/%s", dia, mes, ano);
            strncpy(transacoes[indiceTransacao].data, novaData, sizeof(transacoes[indiceTransacao].data) - 1);
            transacoes[indiceTransacao].data[sizeof(transacoes[indiceTransacao].data) - 1] = '\0';
            break;
        }
        case 4: {
            printf("Nova ");
            FormaPP(novoPagamento);
            strncpy(transacoes[indiceTransacao].pagamento, novoPagamento, sizeof(transacoes[indiceTransacao].pagamento) - 1);
            transacoes[indiceTransacao].pagamento[sizeof(transacoes[indiceTransacao].pagamento) - 1] = '\0';
            break;
        }
        case 5: {
            printf("Saindo da edição.\n");
            return;
        }
        default: {
            printf("Opção inválida!\n");
            return;
        }
    }

    saveFluxo(transacoes, numTransacoes);
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
        printf("5. Voltar ao Financeiro\n");
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
                printf("Opção inválida! Digite uma opção válida\n");
        }
    } while (acao != 5);
}