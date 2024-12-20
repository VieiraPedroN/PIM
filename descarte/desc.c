#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sistema.h"

void saveDesc(Descarte descarte) {
    FILE *file = fopen("dados/desc.dat", "ab"); // Abre o arquivo para escrita em modo binário
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de descartes!\n");
        return;
    }

    fwrite(&descarte, sizeof(Descarte), 1, file); // Grava o descarte
    fclose(file);
}

void descProd(Cadastro *prod, int totalProd) {
    printf("* Verificar Estoque para seleção de descarte de produtos  *\n");

    int index;

    printf("Produtos disponíveis para descarte:\n\n");

    // Exibir produtos
    for (int i = 0; i < totalProd; i++) {
        char *unidadeTipo = (prod[i].unid == 1) ? "Unid" : "Kg"; // Define unidade

        printf("%d. Nome: %s, Quantidade: %d %s, Validade: %s/%s\n",
               i + 1, prod[i].nome, prod[i].qtd, unidadeTipo, prod[i].valid.mes, prod[i].valid.ano);
    }

    printf("\nDigite o número do produto que deseja descartar (1 a %d): ", totalProd);
    scanf("%d", &index);
    index--; // Ajusta para índice de array

    if (index < 0 || index >= totalProd) {
        printf("Erro: Produto inválido!\n");
        return;
    }

    Descarte newRmv;
    newRmv.qtdRmv = 0;

    // Solicita a quantidade a ser descartada
    do {
        char *unidadeTipo = (prod[index].unid == 1) ? "Unid" : "Kg"; // Define unidade
        printf("Quantidade a ser descartada de %s (máximo %d %s): ", prod[index].nome, prod[index].qtd, unidadeTipo);
        scanf("%d", &newRmv.qtdRmv);
        if (newRmv.qtdRmv < 1 || newRmv.qtdRmv > prod[index].qtd) {
            printf("Erro: Quantidade inválida!\n");
        }
    } while (newRmv.qtdRmv < 1 || newRmv.qtdRmv > prod[index].qtd);

    // Solicita a data de descarte
    do {
        printf("Data do descarte (mm/yyyy): ");
        scanf("%2s/%4s", newRmv.dataRmv.mes, newRmv.dataRmv.ano);
    } while (!validData(newRmv.dataRmv.mes, newRmv.dataRmv.ano));

    // Registra o descarte
    strcpy(newRmv.prodNome, prod[index].nome);
    saveDesc(newRmv);

    // Atualiza o estoque
    prod[index].qtd -= newRmv.qtdRmv;
    printf("Descarte registrado com sucesso!\n");

    // Se a quantidade do produto chegar a zero, você pode removê-lo do estoque
    if (prod[index].qtd == 0) {
        removeProd(prod, &totalProd);
    }
}

int visuDesc(Cadastro *prod, int totalProd) {
    Descarte descarte;
    FILE *file = fopen("dados/desc.dat", "rb"); // Abre o arquivo para leitura em modo binário
    if (file == NULL) {
        printf("Nenhum descarte registrado até o momento.\n");
        return 0;
    }

    printf("Descartes registrados:\n\n");
    while (fread(&descarte, sizeof(Descarte), 1, file)) {

        char unidadeTipo[10] = "";
        for (int i = 0; i < totalProd; i++) {
            if (strcmp(prod[i].nome, descarte.prodNome) == 0) {
                // Encontramos o produto correspondente
                if (prod[i].unid == 1) {
                    strcpy(unidadeTipo, "Unidade");
                } else if (prod[i].unid == 2) {
                    strcpy(unidadeTipo, "Kg");
                }
                break;
            }
        }

        printf("Produto: %s, Quantidade descartada: %d %s, Data do descarte: %s/%s\n",
               descarte.prodNome, descarte.qtdRmv, unidadeTipo,
               descarte.dataRmv.mes, descarte.dataRmv.ano);
    }
    fclose(file);
    return 0;
}
