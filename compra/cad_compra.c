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
//Salva as compras
void saveCompra(Compra compra[], int totalCompra) {
    FILE *arquivo = fopen("dados/compra.dat", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os produtos.\n");
        return;
    }

    fwrite(compra, sizeof(Compra), totalCompra, arquivo);
    fclose(arquivo);
    printf("Produtos salvos com sucesso no banco de dados!\n");
}
//Carrega as compras
int loadCompra(Compra compra[]) {
    FILE *arquivo = fopen("dados/compra.dat", "rb");

    if (arquivo == NULL) {
        printf("Nenhum arquivo de produtos encontrado. Iniciando novo cadastro.\n");
        return 0;
    }

    int totalCompra = fread(compra, sizeof(Compra), MAX_COMPRA, arquivo);
    fclose(arquivo);
    printf("Abrindo o banco de dados!\n");
    return totalCompra;
}

void cad_compra(){
    Compra compra[MAX_COMPRA];
    Compra newCompras[MAX_COMPRA];
    int totalCompra = loadCompra(compra);
    int totalNewCompra = 0;
    int conti = 1;

    do {
        if (totalCompra >= MAX_COMPRA){
            printf("Limite de compras de produtos atingida");
            break;
        }

        Compra newCompra;

        do {
            printf("1-Frutas, 2-Hortalicas, 3-Bebidas, 4-Cereais, 5-Laticinios\n");
            printf("Digite o tipo do produto: ");
            scanf("%d", &newCompra.tipo);
            getchar();
        } while (newCompra.tipo < 1 || newCompra.tipo > 5);

        do {
            printf("Nome do fornecedor: ");
            scanf(" %100[^\n]", newCompra.fornecedor);
        
            if (strlen(newCompra.fornecedor) == 0) {
                printf("Erro: Nome não pode estar vazio. Tente novamente.\n");
            }
        } while (strlen(newCompra.fornecedor) == 0);

        do {
            printf("Nome do produto: ");
            scanf(" %100[^\n]", newCompra.produto);
        
            if (strlen(newCompra.produto) == 0) {
                printf("Erro: Nome não pode estar vazio. Tente novamente.\n");
            }
        } while (strlen(newCompra.produto) == 0);

        do {
            printf("Quantidade: ");
            scanf("%d", &newCompra.quantidade);
            if (newCompra.quantidade <= 0) {
                printf("Erro: Quantidade deve ser maior que zero. Tente novamente.\n");
            }
        } while (newCompra.quantidade <= 0);    
        

        do {
           printf("Valor de compra: "); 
           scanf("%f", &newCompra.preco);
           if (newCompra.preco <= 0) {  
                printf("Erro: O valor deve ser positivo. Tente novamente.\n");
            }
        } while (newCompra.preco <= 0);

        newCompra.valorTotal = newCompra.quantidade * newCompra.preco;
        
        int dataValida;
        do {
            printf("Data de compra (dd/mm/yyyy): ");
            scanf("%2s/%2s/%4s", newCompra.valid.dia,
            newCompra.valid.mes, newCompra.valid.ano);
            dataValida = validarData(newCompra.valid.dia, 
            newCompra.valid.mes, newCompra.valid.ano);
            if (!dataValida) {
                printf("Erro: Data inválida. Tente novamente.\n");
            }
            
        } while (!dataValida);

        newCompras[totalNewCompra] = newCompra;
        totalNewCompra++;
        
        int contiCompra;
        printf("Deseja continuar cadastrando compras? (1-Sim, 0-Não): ");
        scanf("%d", &contiCompra);

        if (contiCompra == 1) {
            int compraMesmo;
            printf("Deseja cadastrar o mesmo tipo de produto? (1-Sim, 0-Outro produto): ");
            scanf("%d", &compraMesmo);

            if (compraMesmo == 0) {
                if (totalNewCompra > 0){
                    printf("\nCompras cadastradas nesta sessão:\n");
                    for (int i = 0; i < totalNewCompra; i++){
                        printf("%d. Fornecedor: %s, Produto: %s, Quantidade: %d, Valor Total: %.2f, Data de compra: %2s/%2s/%4s.",
                                i + 1, newCompras[i].fornecedor, newCompras[i].produto,
                                newCompras[i].quantidade, newCompras[i].valorTotal, 
                                newCompras[i].valid.dia, newCompras[i].valid.mes, newCompras[i].valid.ano);
                    }
                    int salvar;
                    printf("\nDeseja salvar os produtos antes de mudar de tipo? (1-Sim, 0-Não): ");
                    scanf("%d", &salvar);

                    if (salvar == 1) {
                        for (int i = 0; i < totalNewCompra; i++) {
                            compra[totalCompra + i] = newCompras[i];
                        }
                        saveCompra(compra, totalCompra + totalNewCompra);
                        printf("Compras salvas com sucesso!\n");
                        
                    } else {
                        printf("Operação de compras canceladas. As compras não foram salvas.\n");
                    }
                }
                return;
            }            
        } else {
            check = 1;
            break;
        }
        
    } while (conti == 1);

    if (totalNewCompra > 0){
        printf("\nCompras cadastradas nessa sessão!:\n");
        for (int i = 0; i < totalNewCompra; i++) {
            printf("%d. Fornecedor: %s, Produto: %s, Quantidade: %d, Valor Total: %.2f, Data de compra: %2s/%2s/%4s.",
                                i + 1, newCompras[i].fornecedor, newCompras[i].produto,
                                newCompras[i].quantidade, newCompras[i].valorTotal, 
                                newCompras[i].valid.dia, newCompras[i].valid.mes, newCompras[i].valid.ano);
        }

        int salvar;
        printf("\nDeseja salvar as compras cadastradas? (1-Sim, 0-Cancelar): ");
        scanf("%d", &salvar);

        if (salvar == 1) {
            for (int i = 0; i < totalNewCompra; i++) {
                compra[totalCompra + i] = newCompras[i];
            }
            saveCompra(compra, totalCompra + totalNewCompra);
            printf("Compras salvas com sucesso!\n");
                        
        } else {
            printf("Operação de compras canceladas. As compras não foram salvas.\n");
        }
    }
    return;
}