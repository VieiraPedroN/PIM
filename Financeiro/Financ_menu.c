#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "../sistema.h"

int validarD(char *dia, char *mes, char *ano)
{
    int d = atoi(dia); // Converte a string dia para inteiro
    int m = atoi(mes); // Converte a string mes para inteiro
    int a = atoi(ano); // Converte a string ano para inteiro

    if (a < 2024 || a > 2100)
        return 0; // Verifica se o ano está entre 2024 e 2100
    if (m < 1 || m > 12)
        return 0; // Verifica se o mês é válido
    if (d < 1 || d > 31)
        return 0; // Verifica se o dia é válido
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
        return 0; // Verifica meses com 30 dias
    if (m == 2)
    {
        if ((a % 4 == 0 && a % 100 != 0) || a % 400 == 0)
        { // Verifica se é ano bissexto
            if (d > 29)
                return 0; // Fevereiro em ano bissexto
        }
        else
        {
            if (d > 28)
                return 0; // Fevereiro em ano não bissexto
        }
    }

    return 1; // Retorna 1 se a data for válida
}

void MenuF()
{
    printf("\n");
    printf("==========  Menu do Financeiro  =========\n");
    printf("| 1- Realizar Pagametos                 |\n");
    printf("| 2- Ver Histórico de Transações        |\n");
    printf("| 3- Editar ou Deletar Transações       |\n");
    printf("| 4- Relatório Diário                   |\n");
    printf("| 5- Relatório Mensal                   |\n");
    printf("| 6- Voltar ao Menu Principal           |\n");
    printf("=========================================\n");
}

// modifição para localizar a pasta dados
void saveFluxo(Fluxo *transacoes, int TotalT){
    FILE *arquivo = fopen("dados/fluxo.dat", "wb");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo para salvar as transações");
        return;
    }
    fwrite(transacoes, sizeof(Fluxo), TotalT, arquivo);
    fclose(arquivo);
}

int loadFluxo(Fluxo *transacoes){
    FILE *arquivo = fopen("dados/fluxo.dat", "rb");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo de transações");
        return 0;
    }
    int TotalT = fread(transacoes, sizeof(Fluxo), Max_Fluxos, arquivo);
    fclose(arquivo);
    return TotalT;
}
// modifição para localizar a pasta dados

void fluxo(){
    setlocale(LC_ALL, "pt_BR.UTF-8");
    system("chcp 65001 > nul");
    Fluxo transacoes[Max_Fluxos];
    int TotalT = loadFluxo(transacoes); // Carrega as transações
    Cadastro produtos[MAX_PRODUTOS];
    int TotalProdts = loadCad(produtos); // Carrega os produtos cadastrados
    int acao;
    char DataEsc[11];
    Compra compras[MAX_COMPRA];
    int totalCompra = loadCompra(compras); // Carrega as compras

    do
    {
        MenuF(); // Exibe o menu financeiro
        printf("Selecione uma Ação: ");
        scanf("%d", &acao);
        switch (acao)
        {
        case 1:
            Pags(transacoes, &TotalT);     // Realiza pagamentos
            saveFluxo(transacoes, TotalT); // Salva as transações
            break;
        case 2:
            ImprimirF(transacoes, TotalT, compras, totalCompra); // Imprime o histórico de transações
            break;
        case 3:
            MenuED(transacoes, TotalT, produtos, TotalProdts); // Edita ou deleta transações
            break;
        case 4:
            printf("Digite o Dia do Relatório (DD/MM/YYYY): ");
            scanf("%s", DataEsc);
            IFC(transacoes, TotalT, DataEsc, compras, totalCompra); // Gera o relatório diário
            break;
        case 5:
        {
            char MesAno[8];
            printf("Digite o Mês e o Ano do Relatório (MM/YYYY): ");
            scanf("%s", MesAno);
            GerarR_M(transacoes, TotalT, MesAno, compras, totalCompra); // Gera o relatório mensal
            break;
        }
        case 6:
            printf("Retornando...\n");
            saveFluxo(transacoes, TotalT); // Salva as transações
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (acao != 6);
}