#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../sistema.h"

// Declaração das funções utilizadas
int validarD(char *dia, char *mes, char *ano);
void FormaPV(char *Pag);
void saveFluxo(Fluxo *transacoes, int TotalT);

int Caixa(Fluxo *transacoes, int *NumT, Cadastro *produtos, int TotalProdts)
{
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001 > nul");
    TotalProdts = loadCad(produtos); // Carrega os produtos cadastrados

    if (TotalProdts == 0)
    {
        printf("Nenhum produto cadastrado encontrado.\n");
        return 1; // Retorna 1 para indicar que houve um problema
    }

    int Prodid, QtdV, InicialT = *NumT;
    char data[11], FormaPag[20], dia[3], mes[3], ano[5];
    char confirmacao;
    float subtotal = 0.0;

    while (1)
    {
        printf("ID do Produto que será vendido (digite 0 para sair): ");
        scanf("%d", &Prodid); // Obtém o ID do produto a ser vendido

        if (Prodid == 0)
        {
            printf("Saindo do Caixa...\n");
            break; // Encerra o loop se o ID do produto for 0
        }

        if (Prodid <= 0 || Prodid > TotalProdts)
        {
            printf("ID inválido. Por favor, tente novamente.\n");
            continue;
        }

        printf("Produto selecionado: %s\n", produtos[Prodid - 1].nome);
        printf("Quantidades a serem Vendidas: ");
        scanf("%d", &QtdV);

        if (QtdV <= 0)
        {
            printf("Erro: A quantidade de unidades vendidas deve ser maior que zero.\n");
            continue;
        }

        if (*NumT >= Max_Fluxos)
        {
            printf("Limite de transações alcançado!\n");
            return 1; // Verifica se o limite de transações foi alcançado
        }

        int IndiceP = Prodid - 1;

        if (produtos[IndiceP].qtd < QtdV)
        {
            printf("Erro: Quantidade insuficiente no estoque!\n");
            continue; // Verifica se há estoque suficiente
        }

        float valorProduto = produtos[IndiceP].valor;
        float valorTotal = valorProduto * QtdV;
        subtotal += valorTotal; // Atualiza o subtotal da compra

        Fluxo NewT;
        char nomeProduto[31]; 
        strncpy(nomeProduto, produtos[IndiceP].nome, sizeof(nomeProduto) - 1); nomeProduto[sizeof(nomeProduto) - 1] = '\0';
        // Formata e armazena uma string na variável NewT.mov com o nome do produto, o ID do produto e a quantidade vendida
        snprintf(NewT.mov, sizeof(NewT.mov), "%s (ID: %d, Unidades Vendidas: %d)", produtos[IndiceP].nome, Prodid, QtdV);
        NewT.valor = valorTotal;          // Atribui o valor total da venda à variável NewT.valor.
        strcpy(NewT.tipo, "Recebimento"); // Prepara a nova transação

        transacoes[*NumT] = NewT;
        (*NumT)++;
        produtos[IndiceP].qtd -= QtdV; // Atualiza a quantidade de produtos no estoque

        printf("Produto adicionado com Sucesso! Quantidade restante de %s: %d\n", produtos[IndiceP].nome, produtos[IndiceP].qtd);
        printf("Subtotal da compra até agora: %.2f\n", subtotal);
        printf("Deseja adicionar Outro Produto? (S/N): ");
        scanf(" %c", &confirmacao);

        if (confirmacao != 'S' && confirmacao != 's')
        {
            break; // Sai do loop se a resposta for diferente de 'S' ou 's'
        }
    }

    if (InicialT != *NumT)
    { // Solicita a data da venda e faz a verificação
        int dataValida = 0;
        while (!dataValida)
        {
            printf("Data Da Venda (DD/MM/YYYY): ");
            if (scanf("%2s/%2s/%4s", dia, mes, ano) != 3)
            {
                printf("Erro: Formato de data inválido. Por favor, tente novamente.\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            dataValida = validarD(dia, mes, ano);
            if (!dataValida)
            {
                printf("Erro: Data inválida. Por favor, tente novamente.\n");
            }
        }

        snprintf(data, sizeof(data), "%s/%s/%s", dia, mes, ano);
        FormaPV(FormaPag); // Solicita a forma de pagamento

        if (strcmp(FormaPag, "Dinheiro") == 0)
        { // Caso selecione dinheiro como forma de pagamento
            float valorPago, troco;
            printf("Valor Pago pelo Cliente: ");
            scanf("%f", &valorPago); // Obtém o valor pago pelo cliente
            troco = valorPago - subtotal;
            printf("Troco: %.2f\n", troco);
            printf("Venda Realizada com Sucesso!\n"); // Calcula e exibe o troco
        }

        for (int i = InicialT; i < *NumT; i++)
        {
            strncpy(transacoes[i].data, data, sizeof(transacoes[i].data) - 1);   // Copia a string data para transacoes[i].data
            transacoes[i].data[sizeof(transacoes[i].data) - 1] = '\0';           // Garante que o último caractere de transacoes[i].data seja '\0'
            strncpy(transacoes[i].Pag, FormaPag, sizeof(transacoes[i].Pag) - 1); // Copia a string FormaPag para transacoes[i].Pag
            transacoes[i].Pag[sizeof(transacoes[i].Pag) - 1] = '\0';             // Garante que o último caractere de transacoes[i].Pag seja '\0'
        }

        saveFluxo(transacoes, *NumT);   // Salva as transações
        saveCad(produtos, TotalProdts); // Salva os produtos atualizados
    }
    else
    {
        printf("Nenhum produto foi vendido.\n");
    }
    return 0;
}