#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sistema.h"

// Função para validar data
int validarData(char *dia, char *mes, char *ano) {
    int d = atoi(dia);
    int m = atoi(mes);
    int a = atoi(ano);

    // Verifica se ano, mês e dia estão em intervalos válidos
    if (a < 2024 || a > 2100) return 0;
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > 31) return 0;

    // Verifica o número de dias por mês
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return 0;
    if (m == 2) {
        // Ano bissexto
        int bissexto = (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0));
        if (bissexto && d > 29) return 0;
        if (!bissexto && d > 28) return 0;
    }
    return 1;
}

// Função para salvar a compra
void saveCompra(Compra compra) {
    FILE *arquivo = fopen("dados/compra.dat", "ab");
    if (arquivo != NULL) {
        fwrite(&compra, sizeof(Compra), 1, arquivo);
        fclose(arquivo);
        printf("Compra salva com sucesso!\n");
    } else {
        printf("Erro ao salvar a compra.\n");
    }
}

void compra() {
    Compra compra;
    int repetir = 1;

    while (repetir) {
        
        printf("1-Frutas, 2-Hortalicas, 3-Bebidas, 4-Cereais, 5-Laticinios\n");
        printf("Digite o tipo do produto: ");
        scanf("%d", &compra.tipo);
        getchar();

        //Pega o nome do fornecedor 
        printf("Digite o nome do fornecedor: ");
        fgets(compra.fornecedor, sizeof(compra.fornecedor), stdin);
        compra.fornecedor[strcspn(compra.fornecedor, "\n")] = '\0';

        printf("Digite o nome do produto: ");
        fgets(compra.produto, sizeof(compra.produto), stdin);
        compra.produto[strcspn(compra.produto, "\n")] = '\0';

        printf("Digite a quantidade: ");
        scanf("%d", &compra.quantidade);

        printf("Digite o preco unitario: ");
        scanf("%f", &compra.preco);

        compra.valorTotal = compra.quantidade * compra.preco;
        printf("Valor total da compra: %.2f\n", compra.valorTotal);

        // Solicitar data e validar
        int dataValida;
        do {
            printf("Digite a data de compra (dd/mm/yyyy): ");
            scanf("%2s/%2s/%4s", compra.valid.dia, compra.valid.mes, compra.valid.ano);
            dataValida = validarData(compra.valid.dia, compra.valid.mes, compra.valid.ano);
            if (!dataValida) {
                printf("Erro: Data inválida. Tente novamente.\n");
            }
        } while (!dataValida);

        int opcaoSalvar;
        printf("Deseja salvar esta compra? (1-Sim, 0-Nao): ");
        scanf("%d", &opcaoSalvar);

        if (opcaoSalvar == 1) {
            saveCompra(compra);
        }

        printf("Deseja realizar outra compra? (1-Sim, 0-Nao): ");
        scanf("%d", &repetir);
    }
}

