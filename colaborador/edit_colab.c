#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../sistema.h"

void editFunc(Colaborador *func, int totalFunc){
    int index;
    printf("Digite o número do funcionario que deseja editar (1 a %d): ", totalFunc);
    scanf("%d", &index);
    index--; // Ajusta para índice de array

    if (index < 0 || index >= totalFunc)
    {
        printf("Erro: Colaborador inválido!\n");
        return;
    }

    Colaborador *editFunc = &func[index]; // Usa ponteiro para acessar o Colaborador
    int opcao;

    do
    {
        printf("\nO que deseja editar?\n");
        printf("1. Nome\n2. Login\n3. Senha\n4. Função\n0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Novo Nome: ");
            scanf(" %100[^\n]", editFunc->colabName);
            break;
        case 2:
            printf("Novo Login: ");
            scanf(" %100[^\n]", editFunc->colabUser);
            break;
        case 3:
            printf("Nova Senha: ");
            scanf(" %100[^\n]", editFunc->colabPass);
            break;
        case 4:
            printf("Nova Função (1-Caixa, 2-Almoxarife, 3-Financeiro, 4-Gerente): ");
            scanf("%d", &editFunc->tipo);
            break;
        case 0:
            printf("Saindo da edição.\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    } while (opcao != 0);
}

void rmvFunc(Colaborador *func, int *totalFunc){
    int index;

    if (index == 0){
        printf("Não contem nenhum colaborador para ser removido.");
        return;
    }
    

    printf("Digite o número do colaborador que deseja remover (1 a %d): ", *totalFunc);
    scanf("%d", &index);
    index--; // Ajusta para índice de array

    if (index < 0 || index >= *totalFunc)
    {
        printf("Erro: Colaborador inválido!\n");
        return;
    }

    // Remover o Colaborador deslocando os demais
    for (int i = index; i < *totalFunc - 1; i++)
    {
        func[i] = func[i + 1];
    }

    (*totalFunc)--; // Reduz o número total de Colaboradors
    printf("Colaborador removido com sucesso!\n");
}
 
void visuColab(int tipoFunc, Colaborador func[], int totalFunc) {
    int visu;
    printf("\nRegistros de Colaboradores:\n");

    do {
        printf("\n1. Visualizar por Função\n2. Visualizar Todos\n0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &visu);

        switch (visu) {
            int opcTipo;    
            case 1:
                printf("\nFunções:\n1. Caixa\n2. Almoxarife\n3. Financeiro\n4. Gerente\n");
                printf("Escolha um tipo: ");
                scanf("%d", &opcTipo);

                int busca = 0; // Variável para verificar se foi busca

                for (int i = 0; i < totalFunc; i++) {
                    if (func[i].tipo == opcTipo) {
                        printf("Nome: %s, Login: %s, Função: %s\n",
                            func[i].colabName, func[i].colabUser, 
                            getFuncaoNome(func[i].tipo));
                        busca = 1; // Marca como busca
                    }
                }

                // Se não encontrou nenhum registro, exibe a mensagem
                if (!busca) {
                    printf("\nNenhum cadastro busca com o tipo escolhido.\n");
                }
                break;

            case 2:

                busca = 0; // Variável para verificar se foi busca

                for (int i = 0; i < totalFunc; i++) {
                    printf("Nome: %s, Login: %s, Função: %s\n",
                           func[i].colabName, func[i].colabUser, 
                           getFuncaoNome(func[i].tipo));
                    busca = 1; // Marca como busca
                }
                if (!busca) {
                    printf("\nNenhum cadastro busca com o tipo escolhido.\n");
                }
                break;

            case 0:
                printf("Saindo da visualização.\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (visu != 0);
}

void editColab(){
    Colaborador func[MAX_PRODUTOS];
    int totalFunc = loadCadColab(func); // Carrega produtos existentes
    int opt;

    do {

        if (totalFunc == 0){
            printf("Não contém nenhum colaborador no banco de dados.\nPor favor, adicione um colaborador.\n");
            opt = 0;
            return;
        }

        printf("\n1. Editar Colaborador\n2. Remover Colaborador\n0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opt);
        
        switch (opt){
            case 1:
                editFunc(func, totalFunc);
                saveCadColab(func, totalFunc);
                break;
            case 2:
                rmvFunc(func, &totalFunc);
                saveCadColab(func, totalFunc);
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

    } while (opt != 0);
    // Salvar produtos no arquivo após alterações
    saveCadColab(func, totalFunc);    
}