#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../sistema.h"

void doaProd(Cadastro *prod, int totalProd) {
    printf("* Verificar Estoque para seleção de doação de produtos  *\n");

    int index;

    printf("Produtos disponíveis para doação:\n");

    // Exibir produtos
    for (int i = 0; i < totalProd; i++) {
        char *unidadeTipo = (prod[i].unid == 1) ? "Unid" : "Kg"; // Definir unidade

        printf("%d. Nome: %s, Quantidade: %d %s, Validade: %s/%s\n",
            i + 1, prod[i].nome, prod[i].qtd, unidadeTipo, prod[i].valid.mes, prod[i].valid.ano);
    }

    printf("Digite o número do produto que deseja doar (1 a %d): ", totalProd);
    scanf("%d", &index);
    index--; // Ajusta para índice de array

    if (index < 0 || index >= totalProd) {
        printf("Erro: Produto inválido!\n");
        return;
    }

    Doacao newDoa;
    newDoa.qtdDoa = 0;

    // Solicita a quantidade a ser doada
    do {
        char *unidadeTipo = (prod[index].unid == 1) ? "Unidade(s)" : "Kg"; // Ajusta a unidade
        printf("Quantidade a ser doada de %s (máximo %d %s): ", prod[index].nome, prod[index].qtd, unidadeTipo);
        scanf("%d", &newDoa.qtdDoa);
        if (newDoa.qtdDoa < 1 || newDoa.qtdDoa > prod[index].qtd) {
            printf("Erro: Quantidade inválida!\n");
        }
    } while (newDoa.qtdDoa < 1 || newDoa.qtdDoa > prod[index].qtd);

    // Solicita a data de doação
    do {
        printf("Data da doação (mm/yyyy): ");
        scanf("%2s/%4s", newDoa.dataDoa.mes, newDoa.dataDoa.ano);
    } while (!validData(newDoa.dataDoa.mes, newDoa.dataDoa.ano));

    // Registra a doação
    strcpy(newDoa.prodNome, prod[index].nome);
    saveDoa(newDoa);

    // Atualiza o estoque
    prod[index].qtd -= newDoa.qtdDoa;
    char *unidadeTipo = (prod[index].unid == 1) ? "Unidade(s)" : "Kg"; // Define a unidade de exibição
    printf("Foi doado %d %s de %s com sucesso!\n", newDoa.qtdDoa, unidadeTipo, prod[index].nome);

}

void saveDoa(Doacao doacao) {
    FILE *file = fopen("doacao.dat", "ab"); // Abre o arquivo para escrita em modo binário
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de doações!\n");
        return;
    }

    fwrite(&doacao, sizeof(Doacao), 1, file); // Grava a doação
    fclose(file);
}

int visuDoa(Cadastro *prod, int totalProd) {
    Doacao doacao;
    FILE *file = fopen("doacao.dat", "rb");
    if (file == NULL) {
        printf("\nNenhuma doação registrada até o momento.\n");
        return 0;
    }

    printf("\nDoações registradas:\n\n");
    while (fread(&doacao, sizeof(Doacao), 1, file) == 1) {
        // Vamos encontrar o produto correspondente pelo nome para obter a unidade
        char unidadeTipo[10] = "";
        for (int i = 0; i < totalProd; i++) {
            if (strcmp(prod[i].nome, doacao.prodNome) == 0) {
                // Encontramos o produto correspondente
                if (prod[i].unid == 1) {
                    strcpy(unidadeTipo, "Unidade");
                } else if (prod[i].unid == 2) {
                    strcpy(unidadeTipo, "Kg");
                }
                break;
            }
        }

        printf("Produto: %s, Quantidade doada: %d %s, Data da doação: %s/%s\n", 
            doacao.prodNome, 
            doacao.qtdDoa, 
            unidadeTipo, // Exibe a unidade (Unidade ou Kg)
            doacao.dataDoa.mes, 
            doacao.dataDoa.ano);
    }

    fclose(file);
    return 0;
}