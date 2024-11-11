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

//modifição para localizar a pasta dados
void saveCompra(Compra *compras, int totalCompra) {
    // Caminho absoluto para a pasta 'dados'
    const char *path = "C:/Users/bhper/OneDrive/Documentos/PIM/dados/compra.dat"; 
    FILE *arquivo = fopen(path, "wb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo para salvar as compras");
        return;
    }
    fwrite(compras, sizeof(Compra), totalCompra, arquivo);
    fclose(arquivo);
    printf("Compras salvas com sucesso no banco de dados!\n");
}

int loadCompra(Compra *compras) {
    // Caminho absoluto para a pasta 'dados'
    const char *path = "C:/Users/bhper/OneDrive/Documentos/PIM/dados/compra.dat"; 
    FILE *arquivo = fopen(path, "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de compras");
        return 0;
    }
    int totalCompra = fread(compras, sizeof(Compra), MAX_COMPRA, arquivo);
    fclose(arquivo);
    printf("Compras carregadas com sucesso!\n");
    return totalCompra;
}
//modifição para localizar a pasta dados

const char* tipoUnidCompra(int unid) {
    switch (unid) {
        case 1: return "Unid";
        case 2: return "Kg";
        default: return "Tipo Desconhecido";
    }
}

const char* tipoCompra(int tipo) {
    switch (tipo) {
        case 1: return "Frutas";
        case 2: return "Hortalicas";
        case 3: return "Bebidas";
        case 4: return "Cereias";
        case 5: return "Laticineos";
        default: return "Tipo Desconhecido";
    }
}

void cad_compra(int tipoProd){
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
            printf("Escolha a unidade (1 - Unidade, 2 - Kg): ");
            scanf("%d", &newCompra.unidade); // Salve a unidade diretamente

            if (newCompra.unidade != 1 && newCompra.unidade != 2) {
                printf("Erro: Unidade inválida. Tente novamente.\n");
            }

            printf("Quantidade %s: ", tipoUnidCompra(newCompra.unidade));
            scanf("%d", &newCompra.quantidade);

            if (newCompra.quantidade <= 0) {
                printf("Erro: Quantidade deve ser maior que zero. Tente novamente.\n");
            }
        } while (newCompra.quantidade <= 0 && newCompra.unidade != 1 && newCompra.unidade != 2 <= 0);    
        

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

        newCompra.tipo = tipoProd;

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
                        printf("%d. Fornecedor: %s, Produto: %s, Quantidade: %d %s, Valor Total: %.2f, Data de compra: %2s/%2s/%4s, Tipo: %s\n",
                                i + 1, newCompras[i].fornecedor, newCompras[i].produto,
                                newCompras[i].quantidade, tipoUnidCompra(newCompras[i].unidade), 
                                newCompras[i].valorTotal, newCompras[i].valid.dia, newCompras[i].valid.mes, 
                                newCompras[i].valid.ano, tipoCompra(newCompras[i].tipo));
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
            printf("%d. Fornecedor: %s, Produto: %s, Quantidade: %d %s, Valor Total: %.2f, Data de compra: %2s/%2s/%4s, Tipo: %s\n",
                                i + 1, newCompras[i].fornecedor, newCompras[i].produto,
                                newCompras[i].quantidade, tipoUnidCompra(newCompras[i].unidade), 
                                newCompras[i].valorTotal, newCompras[i].valid.dia, newCompras[i].valid.mes, 
                                newCompras[i].valid.ano, tipoCompra(newCompras[i].tipo));
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