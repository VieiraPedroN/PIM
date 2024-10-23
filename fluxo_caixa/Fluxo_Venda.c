#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "Fluxo.h"
#include "../cad/cadastro.h"

void Venda(Fluxo *transacoes, int *NumF, Cadastro *produtos, int totalProd) {
    int id, unidadesVendidas;
    char data[11], pagamento[20];
    char cont;

    do {
        printf("ID do Produto que será vendido: ");
        scanf("%d", &id);

        if (id > 0 && id <= totalProd) {
            printf("Produto selecionado: %s\n", produtos[id - 1].nome);
        } else {
            printf("ID inválido. Por favor, tente novamente.\n");
            continue;
        }

        printf("Quantidades a serem Vendidas: ");
        scanf("%d", &unidadesVendidas);

        if (*NumF >= Max_Fluxos) {
            printf("Limite de transações alcançado!\n");
            return;
        }
        if (unidadesVendidas <= 0) {
            printf("Erro: A quantidade de unidades vendidas deve ser maior que zero.\n");
            continue;
        }
        int prodIndex = id - 1;
        if (prodIndex < 0 || prodIndex >= totalProd) {
            printf("Erro: Produto não encontrado!\n");
            continue;
        }
        if (produtos[prodIndex].qtd < unidadesVendidas) {
            printf("Erro: Quantidade insuficiente no estoque!\n");
            continue;
        }
        
        printf("Data (DD/MM/YYYY): ");
        scanf("%s", data);
        FormaP(pagamento);

        float produtoValor = produtos[prodIndex].valor;
        float valorTotal = produtoValor * unidadesVendidas;
        Fluxo NovoF;

        snprintf(NovoF.movimentacao, sizeof(NovoF.movimentacao), "%s (ID: %d, Unidades Vendidas: %d)", produtos[prodIndex].nome, id, unidadesVendidas);
        NovoF.valor = valorTotal;
        strcpy(NovoF.tipo, "Recebimento");
        strncpy(NovoF.data, data, sizeof(NovoF.data) - 1);
        NovoF.data[sizeof(NovoF.data) - 1] = '\0';
        strncpy(NovoF.pagamento, pagamento, sizeof(NovoF.pagamento) - 1);
        NovoF.pagamento[sizeof(NovoF.pagamento) - 1] = '\0';
        transacoes[*NumF] = NovoF;
        (*NumF)++;
        produtos[prodIndex].qtd -= unidadesVendidas;
        if (produtos[prodIndex].qtd < 0) {
            produtos[prodIndex].qtd = 0;
        }

        printf("Venda realizada com sucesso! Quantidade restante de %s: %d\n", produtos[prodIndex].nome, produtos[prodIndex].qtd);
        printf("Deseja adicionar outra venda? (S/N): ");
        scanf(" %c", &cont);
    } while (cont == 'S' || cont == 's');
    
    saveFluxo(transacoes, *NumF);
    saveCad(produtos, totalProd);
}