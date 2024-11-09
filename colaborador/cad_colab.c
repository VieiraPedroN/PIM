#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../sistema.h"

#define MAX_FUNCIONARIOS 100 // Limite de colaboradores

void saveCadColab(Colaborador func[], int totalFunc) {
    // Caminho absoluto para a pasta 'dados'
    const char *path = "C:/Users/bhper/OneDrive/Documentos/PIM/dados/colab.dat";
    FILE *arquivo = fopen(path, "wb");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para salvar os colaboradores");
        return;
    }

    fwrite(func, sizeof(Colaborador), totalFunc, arquivo);
    fclose(arquivo);
    printf("Colaboradores salvos com sucesso no banco de dados!\n");
}


int loadCadColab(Colaborador func[]) {
    // Caminho absoluto para a pasta 'dados'
    const char *path = "C:/Users/bhper/OneDrive/Documentos/PIM/dados/colab.dat";
    FILE *arquivo = fopen(path, "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para carregar os colaboradores");
        return 0;
    }

    // Tentativa de leitura dos dados do arquivo
    int totalFunc = fread(func, sizeof(Colaborador), MAX_FUNCIONARIOS, arquivo);
    if (totalFunc == 0 && ferror(arquivo)) {
        printf("Erro ao ler os colaboradores do arquivo.\n");
        fclose(arquivo);
        return 0;
    }

    fclose(arquivo);
    printf("Banco de dados carregado com sucesso!\n");
    return totalFunc;
}


int compCadColab(Colaborador func[], int totalFunc, char colabName[]) {
    for (int i = 0; i < totalFunc; i++) {
        if (strcmp(func[i].colabName, colabName) == 0) {
            return 1; // Colaborador já cadastrado
        }
    }
    return 0; // Colaborador não cadastrado
}

const char* getFuncaoNome(int tipo) {
    switch (tipo) {
        case 1: return "Caixa";
        case 2: return "Almoxarife";
        case 3: return "Financeiro";
        case 4: return "Gerente";
        default: return "Função Desconhecida";
    }
}

void cadColab(int tipoFunc) {
    Colaborador func[MAX_FUNCIONARIOS];
    Colaborador newFunc[MAX_FUNCIONARIOS];
    int totalFunc = loadCadColab(func);
    int totalNewFunc = 0;
    int conti = 1;

    do {
        if (totalFunc >= MAX_FUNCIONARIOS) {
            printf("Limite de colaboradores cadastrados atingido!\n");
            break;
        }

        // Coletar dados do colaborador
        do {
            printf("\nNome do colaborador: ");
            scanf(" %100[^\n]", newFunc[totalNewFunc].colabName);
        
            if (strlen(newFunc[totalNewFunc].colabName) == 0) {
                printf("Erro: Nome do colaborador não pode ser vazio!\n");
            }
            
        } while (strlen(newFunc[totalNewFunc].colabName) == 0);

        do {
            printf("\nLogin do colaborador: ");
            scanf(" %100[^\n]", newFunc[totalNewFunc].colabUser);

            if (strlen(newFunc[totalNewFunc].colabUser) == 0) {
                printf("Erro: Login não pode estar vazio. Tente novamente.\n");
            }
            
        } while (strlen(newFunc[totalNewFunc].colabUser) == 0);

        do {
            printf("\nSenha do colaborador: ");
            scanf(" %100[^\n]", newFunc[totalNewFunc].colabPass);

            if (strlen(newFunc[totalNewFunc].colabPass) == 0) {
                printf("Erro: Senha não pode estar vazia. Tente novamente.\n");
            }
            
        } while (strlen(newFunc[totalNewFunc].colabPass) == 0);

        newFunc[totalNewFunc].tipo = tipoFunc;
        totalNewFunc++;

        // Perguntar se o usuário deseja cadastrar mais colaboradores
        int contiCad;
        printf("Deseja continuar cadastrando colaboradores da mesma funcao? (1-Sim, 0-Não): ");
        scanf("%d", &contiCad);
        
        if (contiCad == 0) {
            break;
        }

    } while (conti == 1);

    // Mostrar colaboradores cadastrados nesta sessão
    if (totalNewFunc > 0) {
        printf("\nColaboradores cadastrados nesta sessão:\n");
        for (int i = 0; i < totalNewFunc; i++) {
            printf("Nome: %s, Login: %s, Senha: %s, Função: %s\n",
                   newFunc[i].colabName, newFunc[i].colabUser, 
                   newFunc[i].colabPass, getFuncaoNome(newFunc[i].tipo));
        }

        // Confirmar salvamento
        int salvar;
        printf("\nDeseja salvar os colaboradores cadastrados? (1-Salvar, 0-Cancelar): ");
        scanf("%d", &salvar);

        if (salvar == 1) {
            // Adiciona os novos colaboradores ao array principal
            for (int i = 0; i < totalNewFunc; i++) {
                func[totalFunc + i] = newFunc[i];
            }
            saveCadColab(func, totalFunc + totalNewFunc);
        } else {
            printf("Operação cancelada. Colaboradores não foram salvos.\n");
        }
    }

    return; // Retorna para o menu de cadastro
}
