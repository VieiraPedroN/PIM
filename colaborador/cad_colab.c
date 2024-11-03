#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../sistema.h"

#define MAX_FUNCIONARIOS 100 // Limite de descartes

void saveCadColab(Colaborador func[], int totalFunc) {
    FILE *arquivo = fopen("colab.dat", "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar os produtos.\n");
        return;
    }

    fwrite(func, sizeof(Colaborador), totalFunc, arquivo);
    fclose(arquivo);
    printf("Produtos salvos com sucesso no banco de dados!\n");
}

int loadCadColab(Colaborador func[]) {
    FILE *arquivo = fopen("colab.dat", "rb");

    if (arquivo == NULL) {
        printf("Nenhum arquivo de produtos encontrado. Iniciando novo cadastro.\n");
        return 0;
    }

    int totalFunc = fread(func, sizeof(Colaborador), MAX_PRODUTOS, arquivo);
    fclose(arquivo);
    printf("Abrindo o banco de dados!\n");
    return totalFunc;
}

void cadColab(){
    Colaborador func[MAX_FUNCIONARIOS];
    Colaborador newFunc[MAX_FUNCIONARIOS];
    int  totalFunc = loadCadColab(func);
    int total NewFunc = 0;
    int opcao = 0;

    do {
        if (totalFunc >= MAX_FUNCIONARIOS) {
            printf("Limite de colaboradores cadastrados atingido!\n");
            break;
        }

    Colaborador newFunc;

    do {
        printf("\nNome do colaborador: ");
        scanf(" %100[^\n]", newFunc.colabName);
    
        if (strlen(newFunc.colabName) == 0){
            printf("Erro:  Nome do colaborador não pode ser vazio!\n");
        }
        
    } while (/* condition */);
    

    } while ();
    
}