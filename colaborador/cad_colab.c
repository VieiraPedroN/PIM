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
    FILE *arquivo = fopen("dados/colab.dat", "rb");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo para carregar os colaboradores");
        return 0;
    }

    int totalFunc = fread(func, sizeof(Colaborador), MAX_FUNCIONARIOS, arquivo);
    fclose(arquivo);
    printf("Abrindo o banco de dados!\n");
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
    Colaborador newFuncs[MAX_FUNCIONARIOS];
    int totalFunc = loadCadColab(func);
    int totalNewFunc = 0;
    int conti = 1;

    do {
        if (totalFunc >= MAX_FUNCIONARIOS) {
            printf("Limite de colaboradores cadastrados atingido!\n");
            break;
        }

        Colaborador newFunc;

        // Coletar dados do colaborador
        do {
            printf("\nNome do colaborador: ");
            scanf(" %100[^\n]", newFunc.colabName);
        
            if (strlen(newFunc.colabName) == 0) {
                printf("Erro: Nome do colaborador não pode ser vazio!\n");
            }
            
        } while (strlen(newFunc.colabName) == 0);

        do {
            printf("Login do colaborador: ");
            scanf(" %100[^\n]", newFunc.colabUser);

            if (strlen(newFunc.colabUser) == 0) {
                printf("Erro: Login não pode estar vazio. Tente novamente.\n");
            }
            
        } while (strlen(newFunc.colabUser) == 0);

        do {
            printf("Senha do colaborador: ");
            scanf(" %100[^\n]", newFunc.colabPass);

            if (strlen(newFunc.colabPass) == 0) {
                printf("Erro: Senha não pode estar vazia. Tente novamente.\n");
            }
            
        } while (strlen(newFunc.colabPass) == 0);

        newFunc.tipo = tipoFunc;
        
        newFuncs[totalNewFunc] = newFunc;
        totalNewFunc++;

        // Perguntar se o usuário deseja cadastrar mais colaboradores
        int contiCad;
        printf("\nDeseja continuar cadastrando colaboradores da mesma funcao? (1-Sim, 0-Não): ");
        scanf("%d", &contiCad);
        
        if (contiCad == 1) {
            int cadMesmo;
            printf("Deseja cadastrar a mesmo função do colaborador? (1-Sim, 0-Outra função): ");
            scanf("%d", &cadMesmo);

            if (cadMesmo == 0) {
            if (totalNewFunc > 0) {
                printf("\nColaboradores cadastrados nesta sessão:\n");
                for (int i = 0; i < totalNewFunc; i++){
                    printf("Nome: %s, Login: %s, Senha: %s, Função: %s\n",
                        newFuncs[i].colabName, newFuncs[i].colabUser, 
                        newFuncs[i].colabPass, getFuncaoNome(newFuncs[i].tipo));
                }

                int salvar;
                printf("\nDeseja salvar os colaboradores cadastrados? (1-Sim, 0-Cancelar): ");
                scanf("%d", &salvar);

                if (salvar == 1) {
                    for (int i = 0; i < totalNewFunc; i++) {
                        func[totalFunc + i] = newFuncs[i];
                    }
                    saveCadColab(func, totalFunc + totalNewFunc);
                    printf("Colaboradores salvos!\n");
                } else {
                    printf("Operação cancelada. Colaboradores não foram salvos.\n");
                }
            }
                return;
            }
        } else {
            check = 1;
            break;
        }

    } while (conti == 1);

    // Mostrar colaboradores cadastrados nesta sessão
    if (totalNewFunc > 0) {
        printf("\nColaboradores cadastrados nesta sessão:\n");
        for (int i = 0; i < totalNewFunc; i++) {
            printf("Nome: %s, Login: %s, Senha: %s, Função: %s\n",
                   newFuncs[i].colabName, newFuncs[i].colabUser, 
                   newFuncs[i].colabPass, getFuncaoNome(newFuncs[i].tipo));
        }

        // Confirmar salvamento
        int salvar;
        printf("\nDeseja salvar os colaboradores cadastrados? (1-Salvar, 0-Cancelar): ");
        scanf("%d", &salvar);

        if (salvar == 1) {
            // Adiciona os novos colaboradores ao array principal
            for (int i = 0; i < totalNewFunc; i++) {
                func[totalFunc + i] = newFuncs[i];
            }
            saveCadColab(func, totalFunc + totalNewFunc);
        } else {
            printf("Operação cancelada. Colaboradores não foram salvos.\n");
        }
    }

    return; // Retorna para o menu de cadastro
}
