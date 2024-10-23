#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../sistema.h"

// Função para validar data (somente mês e ano)
int validData(char *mes, char *ano) {
    int m = atoi(mes);
    int a = atoi(ano);

    if (a < 2024 || a > 2100) return 0;
    if (m < 1 || m > 12) return 0;

    return 1;
}

int compareCad
(Cadastro prod[], int totalProd, char nome[]) {
    for (int i = 0; i < totalProd; i++) {
        if (strcmp(prod[i].nome, nome) == 0) {
            return 1; // Produto já cadastrado
        }
    }
    return 0; // Produto nao cadastrado
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
    printf("Abrindo o banco de dados!\n");
    return totalProd;
}

void listCad(Cadastro prod[], int totalProd) {
    if (totalProd == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\nProdutos cadastrados:\n");
    for (int i = 0; i < totalProd; i++) {
        printf("%d. Nome: %s, Quantidade: %d, Valor: %.2f, Validade: %s/%s, Tipo: %d\n",
               i + 1, prod[i].nome, prod[i].qtd, prod[i].valor,
               prod[i].valid.mes, prod[i].valid.ano,
               prod[i].tipo);
    }
}


// Funcao de cadastro com tipo de produto automático
void cad(int tipoProd) {
    Cadastro prod[MAX_PRODUTOS];
    int totalProd = loadCad(prod); // Carrega produtos existentes
    int conti = 1;

    do {
        if (totalProd >= MAX_PRODUTOS) {
            printf("Limite de produtos cadastrados atingido!\n");
            break;
        }

        Cadastro newProd;
        char unidTipo[10];
        
        // Validar o nome do produto e verificar se já está cadastrado
        do {
            printf("\nNome do produto: ");
            scanf(" %100[^\n]", newProd.nome);

            if (strlen(newProd.nome) == 0) {
                printf("Erro: Nome não pode estar vazio. Tente novamente.\n");
            } else if (compareCad(prod, totalProd, newProd.nome)) {
                printf("Erro: Produto já cadastrado. Insira outro nome.\n");
                newProd.nome[0] = '\0'; // Limpar nome
            }
        } while (strlen(newProd.nome) == 0);

        // Solicitar quantidade e escolher entre unidades ou quilos
        do{
            printf("Escolha a unidade (1 - Unidade, 2 - Kg): ");
            scanf("%d", &newProd.unid); // Salve a unidade diretamente

             if (newProd.qtd != 1 && newProd.unid != 2) {
                printf("Erro: Unidade inválida. Tente novamente.\n");
            }

            printf("Quantidade %s: ", unidTipo);
            scanf("%d", &newProd.qtd);

            if (newProd.qtd <= 0) {
                printf("Erro: Quantidade deve ser maior que zero. Tente novamente.\n");
            }
        } while (newProd.qtd <= 0 && newProd.unid != 1 && newProd.unid != 2);

        // Solicitar valor
        do {
            printf("Valor: ");
            scanf("%f", &newProd.valor);
            if (newProd.valor <= 0) {
                printf("Erro: O valor deve ser positivo. Tente novamente.\n");
            }
        } while (newProd.valor <= 0);

        // Validar a data de validade (mes e ano)
        int dataValida;
        do {
            printf("Data de validade (mm/yyyy): ");
            scanf("%2s/%4s", newProd.valid.mes, newProd.valid.ano);
            dataValida = validData(newProd.valid.mes, newProd.valid.ano);
            if (!dataValida) {
                printf("Erro: Data inválida. Tente novamente.\n");
            }
        } while (!dataValida);

        // Atribuir o tipo de produto
        newProd.tipo = tipoProd;
        prod[totalProd] = newProd; // Adiciona o novo produto ao array

        totalProd++; // Incrementa o total de produtos

        printf("\nProduto cadastrado com sucesso!\n");

        // Perguntar se o usuário deseja visualizar os produtos cadastrados
        int visu;
        printf("Deseja visualizar os produtos cadastrados? (1-Sim, 0-Não): ");
        scanf("%d", &visu);

        if (visu == 1) {
            printf("\nProdutos cadastrados:\n");
            for (int i = 0; i < totalProd; i++) {
                printf("%d. Nome: %s, Quantidade: %d %s, Valor: %.2f, Validade: %s/%s, Tipo: %d\n",
                       i + 1, prod[i].nome, prod[i].qtd, unidTipo, prod[i].valor,
                       prod[i].valid.mes, prod[i].valid.ano, prod[i].tipo);
            }
        }

        // Perguntar se o usuário deseja cadastrar mais produtos
        int contiCad;
        printf("Deseja continuar cadastrando produtos? (1-Sim, 0-Não): ");
        scanf("%d", &contiCad);

        if (contiCad == 1) {
            // Perguntar se deseja cadastrar o mesmo produto
            int cadMesmo;
            printf("Deseja cadastrar o mesmo produto? (1-Sim, 0-Outro produto): ");
            scanf("%d", &cadMesmo);

            if (cadMesmo == 0) {
                conti = 0; // Se escolher outro, saia do loop
            }
        } else {
            conti = 0; // Se escolher não continuar, saia do loop
        }

        } while (conti == 1);

        // Salvar produtos no arquivo
        saveCad(prod, totalProd);
        printf("Produtos salvos com sucesso!\n");
}