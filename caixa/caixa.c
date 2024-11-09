
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../sistema.h"

void Venda(Fluxo *transacoes, int *NumT, Cadastro *produtos, int TotalProdts) {
    int Prodid, QtdV;
    char data[11], FormaPag[20], dia[3], mes[3], ano[5];
    char confirmacao;
    float subtotal = 0.0;
    int InicialT = *NumT;

    while (1) {
        printf("ID do Produto que será vendido (digite 0 para sair): ");
        scanf("%d", &Prodid);

        if (Prodid == 0) {
            printf("Saindo da venda...\n");
            break;
        }

        if (Prodid <= 0 || Prodid > TotalProdts) {
            printf("ID inválido. Por favor, tente novamente.\n");
            continue;
        }

        printf("Produto selecionado: %s\n", produtos[Prodid - 1].nome);
        printf("Quantidades a serem Vendidas: ");
        scanf("%d", &QtdV);

        if (QtdV <= 0) {
            printf("Erro: A quantidade de unidades vendidas deve ser maior que zero.\n");
            continue;
        }

        if (*NumT >= Max_Fluxos) {
            printf("Limite de transações alcançado!\n");
            return;
        }

        int IndiceP = Prodid - 1;

        if (produtos[IndiceP].qtd < QtdV) {
            printf("Erro: Quantidade insuficiente no estoque!\n");
            continue;
        }

        float valorProduto = produtos[IndiceP].valor;
        float valorTotal = valorProduto * QtdV;
        subtotal += valorTotal;

        Fluxo NewT;
        snprintf(NewT.mov, sizeof(NewT.mov), "%s (ID: %d, Unidades Vendidas: %d)", produtos[IndiceP].nome, Prodid, QtdV);
        NewT.valor = valorTotal;
        strcpy(NewT.tipo, "Recebimento");

        transacoes[*NumT] = NewT;
        (*NumT)++;
        produtos[IndiceP].qtd -= QtdV;

        printf("Produto adicionado com Sucesso! Quantidade restante de %s: %d\n", produtos[IndiceP].nome, produtos[IndiceP].qtd);
        printf("Subtotal da compra até agora: %.2f\n", subtotal);
        printf("Deseja adicionar Outro Produto? (S/N): ");
        scanf(" %c", &confirmacao);

        if (confirmacao != 'S' && confirmacao != 's') {
            break;
        }
    }

    if (InicialT != *NumT) {
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
        FormaPV(FormaPag);

        if (strcmp(FormaPag, "Dinheiro") == 0) {
            float valorPago, troco;
            printf("Valor Pago pelo Cliente: ");
            scanf("%f", &valorPago);
            troco = valorPago - subtotal;
            printf("Troco: %.2f\n", troco);
            printf("Venda Realizada com Sucesso!\n");
        }

        for (int i = InicialT; i < *NumT; i++) {
            strncpy(transacoes[i].data, data, sizeof(transacoes[i].data) - 1);
            transacoes[i].data[sizeof(transacoes[i].data) - 1] = '\0';
            strncpy(transacoes[i].Pag, FormaPag, sizeof(transacoes[i].Pag) - 1);
            transacoes[i].Pag[sizeof(transacoes[i].Pag) - 1] = '\0';
        }

        saveFluxo(transacoes, *NumT);
        saveCad(produtos, TotalProdts);
    } else {
        printf("Nenhum produto foi vendido.\n");
    }
}