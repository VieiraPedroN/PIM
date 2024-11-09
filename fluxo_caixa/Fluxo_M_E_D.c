#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../sistema.h"

void DeletV(Fluxo *transacoes, int *NumT, int IndiceT, Cadastro *produtos, int TotalProdts) {
    if (IndiceT < 0 || IndiceT >= *NumT) {
        printf("Índice inválido.\n");
        return;
    }
    IndiceT--;
    if (strcasecmp(transacoes[IndiceT].tipo, "Recebimento") != 0) {
        printf("Apenas Vendas podem ser deletadas.\n");
        return;
    }
    int IndiceP = -1;
    for (int i = 0; i < TotalProdts; i++) {
        if (strstr(transacoes[IndiceT].mov, produtos[i].nome) != NULL) {
            int UniV = (int)(transacoes[IndiceT].valor / produtos[i].valor);
            produtos[i].qtd += UniV;
            IndiceP = i;
            break;
        }
    }
    if (IndiceP == -1) {
        printf("Erro: Produto não encontrado na transação.\n");
        return;
    }
    char confirmacao;
    printf("Tem certeza que deseja deletar a transação de %s no valor de %.2f? (Sim(S) / Não(N)): ", produtos[IndiceP].nome, transacoes[IndiceT].valor);
    scanf(" %c", &confirmacao);
    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = IndiceT; i < *NumT - 1; i++) {
            transacoes[i] = transacoes[i + 1];
        }
        (*NumT)--;
        Fluxo vazio = {"", 0.0, "", "", ""};
        transacoes[*NumT] = vazio;

        saveCad(produtos, TotalProdts);
        saveFluxo(transacoes, *NumT);
        printf("Venda Deletada com Sucesso. Estoque atualizado.\n");
    } else {
        printf("Operação de exclusão cancelada.\n");
    }
}

void DeletP(Fluxo *transacoes, int *NumT, int IndiceT) {
    if (IndiceT <= 0 || IndiceT > *NumT) {
        printf("Índice inválido.\n");
        return;
    }
    IndiceT--;
    if (strcasecmp(transacoes[IndiceT].tipo, "Gasto") != 0) {
        printf("Apenas Pagamentos podem ser deletados.\n");
        return;
    }
    char confirmacao;
    printf("Tem certeza que deseja deletar o Pagamento '%s' no valor de %.2f? (S/N): ", transacoes[IndiceT].mov, transacoes[IndiceT].valor);
    scanf(" %c", &confirmacao);
    if (confirmacao == 'S' || confirmacao == 's') {
        for (int i = IndiceT; i < *NumT - 1; i++) {
            transacoes[i] = transacoes[i + 1];
        }
        (*NumT)--;
        memset(&transacoes[*NumT], 0, sizeof(Fluxo));
        saveFluxo(transacoes, *NumT);
        printf("Pagamento Deletado com Sucesso.\n");
    } else {
        printf("Operação de exclusão cancelada.\n");
    }
}

void EditV(Fluxo *transacoes, int NumT, Cadastro *produtos, int TotalProdts) {
    int IndiceT, NewUniV, id = -1;
    float NewV;
    char NewMov[50], NewData[11], NewPag[20], dia[3], mes[3], ano[5];

    printf("ID da Venda Para Editar: ");
    scanf("%d", &IndiceT);

    if (IndiceT <= 0 || IndiceT > NumT) {
        printf("Índice inválido.\n");
        return;
    }
    IndiceT--;
    if (strcasecmp(transacoes[IndiceT].tipo, "Recebimento") != 0) {
        printf("Apenas Vendas podem ser editadas.\n");
        return;
    }
    for (int i = 0; i < TotalProdts; i++) {
        if (strstr(transacoes[IndiceT].mov, produtos[i].nome) != NULL) {
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
            scanf("%d", &NewUniV);
            int UniV = (int)(transacoes[IndiceT].valor / produtos[id - 1].valor);
            produtos[id - 1].qtd += UniV;
            produtos[id - 1].qtd -= NewUniV;

            NewV = produtos[id - 1].valor * NewUniV;
            snprintf(NewMov, sizeof(NewMov), "%s (ID: %d, Unidades Vendidas: %d)", produtos[id - 1].nome, id, NewUniV);

            strncpy(transacoes[IndiceT].mov, NewMov, sizeof(transacoes[IndiceT].mov) - 1);
            transacoes[IndiceT].mov[sizeof(transacoes[IndiceT].mov) - 1] = '\0';
            transacoes[IndiceT].valor = NewV;
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
            snprintf(NewData, sizeof(NewData), "%s/%s/%s", dia, mes, ano);
            strncpy(transacoes[IndiceT].data, NewData, sizeof(transacoes[IndiceT].data) - 1);
            transacoes[IndiceT].data[sizeof(transacoes[IndiceT].data) - 1] = '\0';
            break;
        }
        case 3: {
            printf("Nova ");
            FormaPV(NewPag);
            strncpy(transacoes[IndiceT].Pag, NewPag, sizeof(transacoes[IndiceT].Pag) - 1);
            transacoes[IndiceT].Pag[sizeof(transacoes[IndiceT].Pag) - 1] = '\0';
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

    saveCad(produtos, TotalProdts);
    saveFluxo(transacoes, NumT);
    printf("Venda editada com sucesso.\n");
}

void EditP(Fluxo *transacoes, int NumT, int IndiceT) {
    if (IndiceT <= 0 || IndiceT > NumT) {
        printf("Índice inválido.\n");
        return;
    }
    IndiceT--;
    if (strcasecmp(transacoes[IndiceT].tipo, "Gasto") != 0) {
        printf("Apenas Pagamentos podem ser editados.\n");
        return;
    }
    printf("Editando o Pagamento: %s\n", transacoes[IndiceT].mov);

    printf("O que você gostaria de editar?\n");
    printf("1. Nome do Pagamento\n");
    printf("2. Valor do Pagamento\n");
    printf("3. Data\n");
    printf("4. Forma de Pagamento\n");
    printf("5. Sair\n");

    int escolha;
    printf("Selecione uma opção: ");
    scanf("%d", &escolha);

    float NewV;
    char NewMov[50], NewData[11], NewPag[20], dia[3], mes[3], ano[5];

    switch (escolha) {
        case 1: {
            printf("Novo Nome do Pagamento: ");
            getchar();
            fgets(NewMov, sizeof(NewMov), stdin);
            NewMov[strcspn(NewMov, "\n")] = '\0';
            strncpy(transacoes[IndiceT].mov, NewMov, sizeof(transacoes[IndiceT].mov) - 1);
            transacoes[IndiceT].mov[sizeof(transacoes[IndiceT].mov) - 1] = '\0';
            break;
        }
        case 2: {
            printf("Novo Valor do Pagamento: ");
            scanf("%f", &NewV);
            transacoes[IndiceT].valor = NewV;
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
            snprintf(NewData, sizeof(NewData), "%s/%s/%s", dia, mes, ano);
            strncpy(transacoes[IndiceT].data, NewData, sizeof(transacoes[IndiceT].data) - 1);
            transacoes[IndiceT].data[sizeof(transacoes[IndiceT].data) - 1] = '\0';
            break;
        }
        case 4: {
            printf("Nova ");
            FormaPP(NewPag);
            strncpy(transacoes[IndiceT].Pag, NewPag, sizeof(transacoes[IndiceT].Pag) - 1);
            transacoes[IndiceT].Pag[sizeof(transacoes[IndiceT].Pag) - 1] = '\0';
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

    saveFluxo(transacoes, NumT);
    printf("Pagamentos editado com sucesso.\n");
}

void MenuED(Fluxo *transacoes, int TotalF, Cadastro *produtos, int totalProd) {
    int acao, IndiceT;
    do {
        printf("\nMenu de Edição e Exclusão:\n");
        printf("***************************\n");
        printf("1. Editar Venda\n");
        printf("2. Deletar Venda\n");
        printf("3. Editar Pagamentos\n");
        printf("4. Deletar Pagamentos\n");
        printf("5. Voltar ao Financeiro\n");
        printf("***************************\n");
        printf("Selecione uma Ação: ");
        scanf("%d", &acao);
        switch (acao) {
            case 1:
                EditV(transacoes, TotalF, produtos, totalProd);
                break;
            case 2:
                printf("ID da Venda para deletar: ");
                scanf("%d", &IndiceT);
                DeletV(transacoes, &TotalF, IndiceT, produtos, totalProd);
                break;
            case 3:
                printf("ID do Pagamaneto para editar: ");
                scanf("%d", &IndiceT);
                EditP(transacoes, TotalF, IndiceT);
                break;
            case 4:
                printf("ID do Pagamento para deletar: ");
                scanf("%d", &IndiceT);
                DeletP(transacoes, &TotalF, IndiceT);
                break;
            case 5:
                printf("Saindo do menu de edição e exclusão.\n");
                break;
            default:
                printf("Opção inválida! Digite uma opção válida\n");
        }
    } while (acao != 5);
}