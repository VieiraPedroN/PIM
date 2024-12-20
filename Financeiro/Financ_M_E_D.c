#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../sistema.h"

void DeletV(Fluxo *transacoes, int *NumT, int IndiceT, Cadastro *produtos, int TotalProdts)
{
    if (IndiceT < 0 || IndiceT >= *NumT)
    {
        printf("Índice inválido.\n");
        return;
    }
    IndiceT--; // Ajusta o índice para começar de 0
    if (strcasecmp(transacoes[IndiceT].tipo, "Recebimento") != 0)
    {
        printf("Apenas Vendas podem ser deletadas.\n");
        return;
    }
    int IndiceP = -1;
    for (int i = 0; i < TotalProdts; i++)
    { // Verifica se o nome do produto está presente na descrição da transação
        if (strstr(transacoes[IndiceT].mov, produtos[i].nome) != NULL)
        {
            int UniV = (int)(transacoes[IndiceT].valor / produtos[i].valor); // Calcula as unidades vendidas
            produtos[i].qtd += UniV;                                         // Atualiza a quantidade no estoque
            IndiceP = i;                                                     // Salva o índice do produto encontrado
            break;
        }
    }
    if (IndiceP == -1)
    {
        printf("Erro: Produto não encontrado na transação.\n");
        return;
    }
    char confirmacao;
    printf("Tem certeza que deseja deletar a transação de %s no valor de %.2f? (Sim(S) / Não(N)): ", produtos[IndiceP].nome, transacoes[IndiceT].valor);
    scanf(" %c", &confirmacao);
    if (confirmacao == 'S' || confirmacao == 's')
    {
        for (int i = IndiceT; i < *NumT - 1; i++)
        {
            transacoes[i] = transacoes[i + 1]; // Move todas as transações para trás
        }
        (*NumT)--;                           // reduz o número total de transações
        Fluxo vazio = {"", 0.0, "", "", ""}; // Cria uma transação vazia
        transacoes[*NumT] = vazio;           // Define a última transação como vazia

        saveCad(produtos, TotalProdts);
        saveFluxo(transacoes, *NumT);
        printf("Venda Deletada com Sucesso. Estoque atualizado.\n");
    }
    else
    {
        printf("Operação de exclusão cancelada.\n");
    }
}

void DeletP(Fluxo *transacoes, int *NumT, int IndiceT)
{
    if (IndiceT <= 0 || IndiceT > *NumT)
    {
        printf("Índice inválido.\n");
        return;
    }
    IndiceT--; // Ajusta o índice para começar de 0
    if (strcasecmp(transacoes[IndiceT].tipo, "Gasto") != 0)
    {
        printf("Apenas Pagamentos podem ser deletados.\n");
        return;
    }
    char confirmacao;
    printf("Tem certeza que deseja deletar o Pagamento '%s' no valor de %.2f? (S/N): ", transacoes[IndiceT].mov, transacoes[IndiceT].valor);
    scanf(" %c", &confirmacao);
    if (confirmacao == 'S' || confirmacao == 's')
    {
        for (int i = IndiceT; i < *NumT - 1; i++)
        {
            transacoes[i] = transacoes[i + 1]; // Move todas as transações para trás
        }
        (*NumT)--;                                    // reduz o número total de transações
        memset(&transacoes[*NumT], 0, sizeof(Fluxo)); // Limpa a última transação
        saveFluxo(transacoes, *NumT);
        printf("Pagamento Deletado com Sucesso.\n");
    }
    else
    {
        printf("Operação de exclusão cancelada.\n");
    }
}

void EditV(Fluxo *transacoes, int NumT, Cadastro *produtos, int TotalProdts)
{
    int IndiceT, NewUniV, id = -1;
    float NewV;
    char NewMov[50], NewData[11], NewPag[20], dia[3], mes[3], ano[5];

    printf("ID da Venda Para Editar: ");
    scanf("%d", &IndiceT); // Lê o índice da venda a ser editada

    if (IndiceT <= 0 || IndiceT > NumT)
    {
        printf("Índice inválido.\n");
        return;
    }
    IndiceT--; // Ajusta o índice para começar de 0

    if (strcasecmp(transacoes[IndiceT].tipo, "Recebimento") != 0)
    { // Verifica se a transação é um recebimento
        printf("Apenas Vendas podem ser editadas.\n");
        return;
    }

    for (int i = 0; i < TotalProdts; i++)
    {
        // Verifica se o nome do produto está presente na descrição da transação
        if (strstr(transacoes[IndiceT].mov, produtos[i].nome) != NULL)
        {
            id = i + 1; // Salva o índice do produto encontrado
            break;
        }
    }
    if (id == -1)
    {
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

    switch (escolha)
    {
    case 1:
    { // Edita a quantidade de produtos
        printf("Nova Quantidade de Produtos: ");
        scanf("%d", &NewUniV);
        int UniV = (int)(transacoes[IndiceT].valor / produtos[id - 1].valor); // Calcula a quantidade original
        produtos[id - 1].qtd += UniV;                                         // Devolve a quantidade original ao estoque
        produtos[id - 1].qtd -= NewUniV;                                      // Subtrai a nova quantidade do estoque

        NewV = produtos[id - 1].valor * NewUniV; // Calcula o novo valor
        snprintf(NewMov, sizeof(NewMov), "%s (ID: %d, Unidades Vendidas: %d)", produtos[id - 1].nome, id, NewUniV);

        strncpy(transacoes[IndiceT].mov, NewMov, sizeof(transacoes[IndiceT].mov) - 1); // Atualiza o nome da transação
        transacoes[IndiceT].mov[sizeof(transacoes[IndiceT].mov) - 1] = '\0';
        transacoes[IndiceT].valor = NewV; // Atualiza o valor da transação
        break;
    }
    case 2:
    { // Edita a data da transação
        int dataValida = 0;
        while (!dataValida)
        {
            printf("Nova data (DD/MM/YYYY): ");
            if (scanf("%2s/%2s/%4s", dia, mes, ano) != 3)
            {
                printf("Erro: Formato de data inválido. Por favor, tente novamente.\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            dataValida = validarD(dia, mes, ano); // Valida a nova data
            if (!dataValida)
            {
                printf("Erro: Data inválida. Tente novamente.\n");
            }
        }
        snprintf(NewData, sizeof(NewData), "%s/%s/%s", dia, mes, ano);
        strncpy(transacoes[IndiceT].data, NewData, sizeof(transacoes[IndiceT].data) - 1); // Atualiza a data da transação
        transacoes[IndiceT].data[sizeof(transacoes[IndiceT].data) - 1] = '\0';
        break;
    }
    case 3:
    { // Edita a forma de pagamento
        printf("Nova ");
        FormaPV(NewPag);                                                               // Lê a nova forma de pagamento
        strncpy(transacoes[IndiceT].Pag, NewPag, sizeof(transacoes[IndiceT].Pag) - 1); // Atualiza a forma de pagamento
        transacoes[IndiceT].Pag[sizeof(transacoes[IndiceT].Pag) - 1] = '\0';
        break;
    }
    case 4:
    {
        printf("Saindo da edição.\n");
        return;
    }
    default:
    {
        printf("Opção inválida!\n");
        return;
    }
    }

    saveCad(produtos, TotalProdts);
    saveFluxo(transacoes, NumT);
    printf("Venda editada com sucesso.\n");
}

void EditP(Fluxo *transacoes, int NumT, int IndiceT)
{
    // Verifica se o índice fornecido é válido
    if (IndiceT <= 0 || IndiceT > NumT)
    {
        printf("Índice inválido.\n");
        return;
    }
    IndiceT--; // Ajusta o índice para começar de 0

    // Verifica se a transação é um gasto
    if (strcasecmp(transacoes[IndiceT].tipo, "Gasto") != 0)
    {
        printf("Apenas Pagamentos podem ser editados.\n");
        return;
    }

    // Exibe o nome do pagamento que está sendo editado
    printf("Editando o Pagamento: %s\n", transacoes[IndiceT].mov);

    // Apresenta opções de edição ao usuário
    printf("O que você gostaria de editar?\n");
    printf("1. Nome do Pagamento\n");
    printf("2. Valor do Pagamento\n");
    printf("3. Data do Pagamento\n");
    printf("4. Forma de Pagamento\n");
    printf("5. Sair\n");

    int escolha;
    printf("Selecione uma opção: ");
    scanf("%d", &escolha); // Lê a escolha do usuário

    float NewV;
    char NewMov[50], NewData[11], NewPag[20], dia[3], mes[3], ano[5];

    switch (escolha)
    {
    case 1:
    { // Edita o nome do pagamento
        printf("Novo Nome do Pagamento: ");
        getchar();                                                                     // Limpa o buffer
        fgets(NewMov, sizeof(NewMov), stdin);                                          // Lê o novo nome do pagamento
        NewMov[strcspn(NewMov, "\n")] = '\0';                                          // Remove o caractere de nova linha
        strncpy(transacoes[IndiceT].mov, NewMov, sizeof(transacoes[IndiceT].mov) - 1); // Atualiza o nome do pagamento
        transacoes[IndiceT].mov[sizeof(transacoes[IndiceT].mov) - 1] = '\0';
        break;
    }
    case 2:
    { // Edita o valor do pagamento
        printf("Novo Valor do Pagamento: ");
        scanf("%f", &NewV);               // Lê o novo valor do pagamento
        transacoes[IndiceT].valor = NewV; // Atualiza o valor do pagamento
        break;
    }
    case 3:
    { // Edita a data do pagamento
        int dataValida = 0;
        while (!dataValida)
        {
            printf("Nova data (DD/MM/YYYY): ");
            if (scanf("%2s/%2s/%4s", dia, mes, ano) != 3)
            {
                printf("Erro: Formato de data inválido. Por favor, tente novamente.\n");
                while (getchar() != '\n')
                    ;
                continue;
            }
            dataValida = validarD(dia, mes, ano); // Valida a nova data
            if (!dataValida)
            {
                printf("Erro: Data inválida. Tente novamente.\n");
            }
        }
        snprintf(NewData, sizeof(NewData), "%s/%s/%s", dia, mes, ano);                    // Formata a nova data
        strncpy(transacoes[IndiceT].data, NewData, sizeof(transacoes[IndiceT].data) - 1); // Atualiza a data do pagamento
        transacoes[IndiceT].data[sizeof(transacoes[IndiceT].data) - 1] = '\0';
        break;
    }
    case 4:
    {
        printf("Nova ");
        FormaPP(NewPag);                                                               // Lê a nova forma de pagamento
        strncpy(transacoes[IndiceT].Pag, NewPag, sizeof(transacoes[IndiceT].Pag) - 1); // Atualiza a forma de pagamento
        transacoes[IndiceT].Pag[sizeof(transacoes[IndiceT].Pag) - 1] = '\0';
        break;
    }
    case 5:
    {
        printf("Saindo da edição.\n");
        return;
    }
    default:
    {
        printf("Opção inválida!\n");
        return;
    }
    }

    saveFluxo(transacoes, NumT);
    printf("Pagamentos editado com sucesso.\n");
}

void MenuED(Fluxo *transacoes, int TotalF, Cadastro *produtos, int totalProd)
{
    int acao, IndiceT;
    do
    {
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
        switch (acao)
        {
        case 1:
            EditV(transacoes, TotalF, produtos, totalProd);
            break;
        case 2:
            printf("ID da Venda para deletar: ");
            scanf("%d", &IndiceT);
            DeletV(transacoes, &TotalF, IndiceT, produtos, totalProd);
            break;
        case 3:
            printf("ID do Pagamento para editar: ");
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