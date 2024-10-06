#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.h"

int validarData(char *dia, char *mes, char *ano) {
    int d = atoi(dia);
    int m = atoi(mes);
    int a = atoi(ano);

    if (a < 2024 || a > 2100) return 0;
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > 31) return 0;

    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return 0;
    if (m == 2) {
        int bissexto = (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0));
        if (bissexto && d > 29) return 0;
        if (!bissexto && d > 28) return 0;
    }
    return 1;
}

int produtoJaCadastrado(Cadastro prod[], int totalProd, char nome[]) {
    for (int i = 0; i < totalProd; i++) {
        if (strcmp(prod[i].nome, nome) == 0) {
            return 1; // Produto já cadastrado
        }
    }
    return 0; // Produto não cadastrado
}

void saveCad(Cadastro prod[], int totalProd) {
    FILE *arquivo = fopen("prod.dat", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os produtos.\n");
        return;
    }

    fwrite(prod, sizeof(Cadastro), totalProd, arquivo);
    fclose(arquivo);
    printf("Produtos salvos com sucesso no arquivo!\n");
}

int loadCad(Cadastro prod[]) {
    FILE *arquivo = fopen("prod.dat", "rb");

    if (arquivo == NULL) {
        printf("Nenhum arquivo de produtos encontrado. Iniciando novo cadastro.\n");
        return 0;
    }

    int totalProd = fread(prod, sizeof(Cadastro), MAX_PRODUTOS, arquivo);
    fclose(arquivo);
    printf("Produtos carregados do arquivo com sucesso!\n");
    return totalProd;
}

void listCad(Cadastro prod[], int totalProd) {
    if (totalProd == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\nProdutos cadastrados:\n");
    for (int i = 0; i < totalProd; i++) {
        printf("%d. Nome: %s, Quantidade: %d, Valor: %.2f, Validade: %s/%s/%s, Tipo: %d\n",
               i + 1, prod[i].nome, prod[i].qtd, prod[i].valor,
               prod[i].validade.dia, prod[i].validade.mes, prod[i].validade.ano,
               prod[i].tipo);
    }
}

// Função de cadastro com tipo de produto automático
void cad(int tipoProd) {
    Cadastro prod[MAX_PRODUTOS];
    int totalProd = loadCad(prod); // Carrega produtos existentes
    int continuar = 1;

    do {
        if (totalProd >= MAX_PRODUTOS) {
            printf("Limite de produtos cadastrados atingido!\n");
            break;
        }

        Cadastro novoProduto;

        // Validar o nome do produto e verificar se já está cadastrado
        do {
            printf("\nNome do produto: ");
            scanf(" %100[^\n]", novoProduto.nome);

            if (strlen(novoProduto.nome) == 0) {
                printf("Erro: Nome não pode estar vazio. Tente novamente.\n");
            } else if (produtoJaCadastrado(prod, totalProd, novoProduto.nome)) {
                printf("Erro: Produto já cadastrado. Insira outro nome.\n");
                novoProduto.nome[0] = '\0'; // Limpar nome
            }
        } while (strlen(novoProduto.nome) == 0);

        // Validar a quantidade
        do {
            printf("Quantidade: ");
            scanf("%d", &novoProduto.qtd);
            if (novoProduto.qtd <= 0) {
                printf("Erro: Quantidade deve ser maior que zero. Tente novamente.\n");
            }
        } while (novoProduto.qtd <= 0);

        // Validar o valor
        do {
            printf("Valor: ");
            scanf("%f", &novoProduto.valor);
            if (novoProduto.valor <= 0) {
                printf("Erro: O valor deve ser positivo. Tente novamente.\n");
            }
        } while (novoProduto.valor <= 0);

        // Validar a data de validade
        int dataValida;
        do {
            printf("Data de validade (dd/mm/yyyy): ");
            scanf("%2s/%2s/%4s", novoProduto.validade.dia, novoProduto.validade.mes, novoProduto.validade.ano);

            dataValida = validarData(novoProduto.validade.dia, novoProduto.validade.mes, novoProduto.validade.ano);
            if (!dataValida) {
                printf("Erro: Data inválida. Tente novamente.\n");
            }
        } while (!dataValida);

        // Atribuir automaticamente o tipo de produto
        novoProduto.tipo = tipoProd;
        prod[totalProd] = novoProduto; // Adiciona o novo produto ao array

        totalProd++; // Incrementa o total de produtos

        printf("\nProduto cadastrado com sucesso!\n");

        // Listar produtos cadastrados
        listCad(prod, totalProd);

        // Perguntar se deseja cadastrar outro produto
        printf("Deseja cadastrar outro produto? (1-Sim, 0-Não): ");
        scanf("%d", &continuar);

    } while (continuar == 1);

    // Salvar produtos no arquivo
    saveCad(prod, totalProd);
}
