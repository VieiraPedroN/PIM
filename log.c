#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"


int main() {
    char login1[101];
    char senha1[101];        
    int login_efetuado = 0; // 0 - Falso, 1 - Verdadeiro
    Colaborador colab;
    FILE *file;

    // Loop até o login ser efetuado com sucesso

    while (1){
    login_efetuado = 0;
        while (!login_efetuado) {
            printf("\nDigite o Login: ");
            scanf("%s", login1);

            printf("Digite a Senha: ");
            scanf("%s", senha1);

            // Abre o arquivo colab.dat para leitura binária
            file = fopen("dados/colab.dat", "rb");
            if (file == NULL) {
                printf("Erro ao abrir o arquivo de colaboradores.\n");
                return 1;
            }

            // Percorre todos os registros no arquivo para verificar as credenciais
            int encontrou = 0; // 0 - Não encontrou, 1 - Encontrou
            while (fread(&colab, sizeof(Colaborador), 1, file) == 1) {
                // Verifica se o login e a senha coincidem
                if (strcmp(colab.colabUser, login1) == 0 && strcmp(colab.colabPass, senha1) == 0) {
                    if (colab.tipo == 1){
                        printf("\nLogado como Caixa\n");
                        printf("\nSeja bem vindo %s", colab.colabName);
                        login_efetuado = 1;
                        encontrou = 1;
                        menuCaixa();
                        break;
                    } else if (colab.tipo == 2){
                        printf("\nLogado como Almoxarife\n");
                        printf("\nSeja bem vindo %s", colab.colabName);
                        login_efetuado = 1;
                        encontrou = 1;
                        menuAlmox();
                        break;
                    } else if (colab.tipo == 3){
                        printf("\nLogado como Financeiro\n");
                        printf("\nSeja bem vindo %s", colab.colabName);
                        login_efetuado = 1;
                        encontrou = 1;
                        menuFinanc();
                        break;
                    } else if (colab.tipo == 4){
                        printf("\nLogado como Gerente\n");
                        printf("\nSeja bem vindo %s", colab.colabName);
                        login_efetuado = 1;
                        encontrou = 1;
                        menuAdm();
                        break;
                    } 
                    
                }
            }

            // Fecha o arquivo
            fclose(file);

            // Mensagem de erro caso não tenha encontrado as credenciais
            if (!encontrou) {
                printf("\nDADOS INVALIDOS!\n");
            }
        }

    }
    

    return 0;
}
