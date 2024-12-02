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

    printf("Nome: %s, Login: %s, Senha: %s, Função: %s\n",
            editFunc->colabName, editFunc->colabUser, 
            editFunc->colabPass, getFuncaoNome(editFunc->tipo));

    int opt;
    printf("Deseja editar esse colobarador? (1-Sim, 0-Cancelar): ");
    scanf("%d",&opt);

    do { 
        if (opt == 1) {
            int opcao;

            do {
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
                    printf("Finalizar a edição.\n");
                    break;
                default:
                    printf("Opção inválida!\n");
                    break;
                }
            } while (opcao != 0);
            int salvar;
            printf("As alterações feitas foram: \n");

            printf("Nome: %s, Login: %s, Senha: %s, Função: %s\n",
                    editFunc->colabName, editFunc->colabUser, 
                    editFunc->colabPass, getFuncaoNome(editFunc->tipo));

            printf("Deseja salvar? (1-Sim, 0-Não): ");
            scanf("%d",&salvar);
            printf("\n");
            do {
                if (salvar == 1) {
                    printf("Alterações salvas com sucesso!\n");
                    saveCadColab(func, totalFunc);
                    break;
                } else if (salvar == 0){
                    printf("Alterações não salvas.\n");
                } else {
                    printf("Opção inválida!\n");
                }
            } while (salvar != 0);
                break; 
        } 
    }while (opt !=0);    
}

void rmvFunc(Colaborador *func, int *totalFunc){
    int index;
    
    printf("Digite o número do colaborador que deseja remover (1 a %d): ", *totalFunc);
    scanf("%d", &index);
    index--; // Ajusta para índice de array

    if (index < 0 || index >= *totalFunc)
    {
        printf("Erro: Colaborador inválido!\n");
        return;
    }

    printf("Nome: %s, Login: %s, Senha: %s, Função: %s\n",
            func[index].colabName, func[index].colabUser, 
            func[index].colabPass, getFuncaoNome(func[index].tipo));


    int opt;
    printf("Deseja remover esse colaborador? (1-Sim, 0-Cancelar): ");
    scanf("%d",&opt);

    do {
        if (opt == 1) {

        // Remover o produto deslocando os demais
        for (int i = index; i < *totalFunc- 1; i++) {
            func[i] = func[i + 1];
        }

        (*totalFunc)--; // Reduz o número total de produtos
        printf("Colaborador removido com sucesso!\n");

        saveCadColab(func, *totalFunc);
        break;
        } else {
            printf("Opção invalida");
        }
        
    } while (opt !=0);
}
 
void visuColab() {
    Colaborador func[MAX_FUNCIONARIOS];
    int totalFunc = loadCadColab(func);
    int visu;
    
    printf("\nRegistros de Colaboradores:\n");

    do {
        printf("\n1. Visualizar por Função\n2. Visualizar Todos\n0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &visu);
        printf("\n");

        switch (visu) {
            int opcTipo;    
            case 1:
                printf("Funções:\n\n1. Caixa\n2. Almoxarife\n3. Financeiro\n4. Gerente\n");
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
                    printf("\nNenhum cadastro de colaborador encontrado com a função escolhido.\n");
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
                    printf("\nNenhum cadastro de colaborador encontrado com a função escolhido.\n");
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

void menuColab(){
    Colaborador func[MAX_FUNCIONARIOS];
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
                break;
            case 2:
                rmvFunc(func, &totalFunc);
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

    } while (opt != 0);
}