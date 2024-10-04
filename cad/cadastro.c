#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 5 // Limite de produtos que podem ser cadastrados

typedef struct {
    char dia[3];
    char mes[3];
    char ano[5];
} Data;

typedef struct {
    char nome[101];
    float valor;
    int qtd;
    Data validade;  // Incluindo a estrutura Data dentro de Cadastro
} Cadastro;

// Função para verificar se a data inserida é válida
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

void cad() {
    Cadastro produtos[MAX_PRODUTOS]; // Array para armazenar até 100 produtos
    int totalProdutos = 0;           // Contador para produtos cadastrados
    int continuar = 1;               // Para controlar o loop de cadastro
    int cadProduct;

    do {
        if (totalProdutos >= MAX_PRODUTOS) {
            printf("Limite de produtos cadastrados atingido!\n");
            break;
        }

        Cadastro novoProduto; // Variável para o novo cadastro

        // Validar o nome do produto
        do {
            printf("\nNome do produto: ");
            scanf(" %100[^\n]", novoProduto.nome); // Lê até 100 caracteres, permitindo espaços

            if (strlen(novoProduto.nome) == 0) {
                printf("Erro: Nome não pode estar vazio. Tente novamente.\n");
            }
        } while (strlen(novoProduto.nome) == 0); // Continua pedindo até que o nome seja válido

        // Validar a quantidade
        do {
            printf("Quantidade: ");
            scanf("%d", &novoProduto.qtd);
            if (novoProduto.qtd <= 0) {
                printf("Erro: Quantidade deve ser maior que zero. Tente novamente.\n");
            }
        } while (novoProduto.qtd <= 0); // Continua pedindo até que a quantidade seja válida

        // Validar o valor
        do {
            printf("Valor: ");
            scanf("%f", &novoProduto.valor);
            if (novoProduto.valor <= 0) {
                printf("Erro: O valor deve ser positivo. Tente novamente.\n");
            }
        } while (novoProduto.valor <= 0); // Continua pedindo até que o valor seja válido

        // Validar a data de validade
        int dataValida;
        do {
            printf("Data de validade (dd/mm/yyyy): ");
            scanf("%2s/%2s/%4s", novoProduto.validade.dia, novoProduto.validade.mes, novoProduto.validade.ano);

            dataValida = validarData(novoProduto.validade.dia, novoProduto.validade.mes, novoProduto.validade.ano);
            if (!dataValida) {
                printf("Erro: Data inválida. Tente novamente.\n");
            }
        } while (!dataValida); // Continua pedindo até que a data seja válida

        // Se todas as validações forem bem-sucedidas, armazenamos o produto
        produtos[totalProdutos] = novoProduto;
        totalProdutos++;  // Incrementa o número total de produtos cadastrados

        printf("\nProduto cadastrado com sucesso!\n");
        printf("Nome: %s\n", novoProduto.nome);
        printf("Quantidade: %d\n", novoProduto.qtd);
        printf("Valor: %.2f\n", novoProduto.valor);
        printf("Data de validade: %s/%s/%s\n", novoProduto.validade.dia, novoProduto.validade.mes, novoProduto.validade.ano);

        printf("\nDeseja cadastrar outro produto? (1-Sim, 0-Não): ");
        scanf("%d", &continuar);

    } while (continuar == 1);


    // Exibir todos os produtos cadastrados
    printf("\nGostaria de ver os produtos cadastrados? 1-Sim, 0-Não: ");
    scanf("%d", &cadProduct);

    
    switch (cadProduct){
    case 1:
        int idProduto;
        int verify;

        do {
            printf("\nPor favor, insira o ID do produto (entre 1 e %d): ", totalProdutos);
            scanf("%d", &idProduto);

            // Converta o ID fornecido (que começa de 1) para o índice no array (que começa de 0)
            idProduto--; 

            if (idProduto >= 0 && idProduto < totalProdutos) {
                // Exibir as informações do produto correspondente ao ID
                printf("Nome: %s\n", produtos[idProduto].nome);
                printf("Quantidade: %d\n", produtos[idProduto].qtd);
                printf("Valor: %.2f\n", produtos[idProduto].valor);
                printf("Data de validade: %s/%s/%s\n\n", produtos[idProduto].validade.dia, produtos[idProduto].validade.mes, produtos[idProduto].validade.ano);
                verify = 0;
            } else {
                printf("Erro: ID inválido. Tente novamente.\n");
                verify = 1;
            }

            printf("Gostaria de visualizar mais  produtos? 1-Sim, 0-Não: ");
            scanf("%d", &verify);
            
            do{
                switch (verify){
                case 1:
                    verify = 1;
                    break;
                
                case 0:
                    verify = 0;
                    break;

                default: printf("Erro: Opção inválida. Tente novamente.\n");
                    break;
                }
            } while (verify  != 0 && verify != 1);

        } while (verify == 1); // Repetir enquanto o ID for inválido
    
    default:
        printf("\nSaindo sem exibir os produtos.\n");
        break;
    }
}
