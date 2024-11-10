#include <stdio.h>
#include <stdlib.h>
#include "../sistema.h"

void editProd(Cadastro *prod, int totalProd){
    int index;
    printf("Digite o número do produto que deseja editar (1 a %d): ", totalProd);
    scanf("%d", &index);
    index--; // Ajusta para índice de array

    if (index < 0 || index >= totalProd)
    {
        printf("Erro: Produto inválido!\n");
        return;
    }

    Cadastro *editProd = &prod[index]; // Usa ponteiro para acessar o produto

    printf("Nome: %s, Quantidade: %d %s, Valor: %.2f, Validade: %s/%s, Tipo: %s\n",
            editProd->nome, editProd->qtd, tipoUnid(editProd->unid), editProd->valor, 
           editProd->valid.mes,editProd->valid.ano, tipoCad(editProd->tipo));

    int opt;
    printf("Deseja editar esse produto? (1-Sim, 0-Cancelar): ");
    scanf("%d",&opt);

    do { 
        if (opt == 1) {
            int opcao;

            do {
                printf("\nO que deseja editar?\n");
                printf("1. Nome\n2. Unidade\n3. Quantidade\n4. Valor\n5. Data de validade\n6. Tipo\n0. Finalizar edições\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);

                switch (opcao)
                {
                case 1:
                    printf("Novo nome: ");
                    scanf(" %100[^\n]", editProd->nome);
                    break;
                case 2:
                do {
                    printf("Nova tipo de unidade: ");
                    printf("Escolha a unidade (1 - Unidade, 2 - Kg): ");
                    scanf("%d", &editProd->unid); // Salve a unidade diretamente

                    if (editProd->unid != 1 && editProd->unid != 2) {
                        printf("Erro: Unidade inválida. Tente novamente.\n");
                    }
                    break;
                } while (editProd->unid != 1 && editProd->unid != 2);
                    break;
                case 3:
                    do{
                        printf("Nova quantidade: ");
                        scanf("%d", &editProd->qtd);
                        if (editProd->qtd < 0){
                            printf("Erro: Quantidade deve ser maior que zero.\n");
                        }
                    } while (editProd->qtd < 0);
                    break;
                case 4:
                    do
                    {
                        printf("Novo valor: ");
                        scanf("%f", &editProd->valor);
                        if (editProd->valor <= 0)
                        {
                            printf("Erro: O valor deve ser positivo.\n");
                        }
                    } while (editProd->valor <= 0);
                    break;
                case 5:
                    do
                    {
                        printf("Nova data de validade (mm/yyyy): ");
                        scanf("%2s/%4s", editProd->valid.mes, editProd->valid.ano);
                    } while (!validData(editProd->valid.mes, editProd->valid.ano));
                    break;
                case 6:
                    printf("Novo tipo (1-Frutas, 2-Hortaliças, 3-Bebidas, 4-Cereais, 5-Laticínios): ");
                    scanf("%d", &editProd->tipo);
                    break;
                case 0:
                    printf("Saindo da edição.\n");
                    break;
                default:
                    printf("Opção inválida!\n");
                    break;
                }
            } while (opcao != 0);
            int salvar;
            printf("As alterações feitas foram: \n");

            printf("Nome: %s, Quantidade: %d %s, Valor: %.2f, Validade: %s/%s, Tipo: %s\n",
                    editProd->nome, editProd->qtd, tipoUnid(editProd->unid), editProd->valor, 
                    editProd->valid.mes,editProd->valid.ano, tipoCad(editProd->tipo));

            printf("Deseja salvar? (1-Sim, 0-Não): ");
            scanf("%d",&salvar);
            printf("\n");
            do {
                if (salvar == 1) {
                    printf("Alterações salvas com sucesso!\n");
                    saveCad(prod, totalProd);
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

void removeProd(Cadastro *prod, int *totalProd){
    int index;

    if (index == 0){
        printf("Não contem nenhum produto para ser removido.");
        return;
    }
    

    printf("Digite o número do produto que deseja remover (1 a %d): ", *totalProd);
    scanf("%d", &index);
    index--; // Ajusta para índice de array

    if (index < 0 || index >= *totalProd)
    {
        printf("Erro: Produto inválido!\n");
        return;
    }

    printf("Nome: %s, Quantidade: %d %s, Valor: %.2f, Validade: %s/%s, Tipo: %s\n",
            prod[index].nome, prod[index].qtd, tipoUnid(prod[index].unid), prod[index].valor, 
            prod[index].valid.mes, prod[index].valid.ano, tipoCad(prod[index].tipo));

    int opt;
    printf("Deseja editar esse produto? (1-Sim, 0-Cancelar): ");
    scanf("%d",&opt);

    do {
        if (opt == 1) {

        // Remover o produto deslocando os demais
        for (int i = index; i < *totalProd - 1; i++) {
            prod[i] = prod[i + 1];
        }

        (*totalProd)--; // Reduz o número total de produtos
        printf("Produto removido com sucesso!\n");

        saveCad(prod, *totalProd);
        break;
        } else {
            printf("Opção invalida");
        }
        
    } while (opt !=0);
}

void visuArmz(){
    Cadastro prod[MAX_PRODUTOS];
    int totalProd = loadCad(prod); // Carrega produtos existentes
    int visu;

    printf("\nEstoque:\n");
    printf("\nComo deseja visualizar?");

    do{
        printf("\n1. Tipo\n2. Todo o estoque\n0. sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &visu);
        switch (visu){ 
        int opcTipo;    
        case 1:

            printf("\n\n1.Frutas\n2.Hortalicas\n3.Bebidas\n4.Cereais\n5.Laticineos\n");
            printf("Escolha um Tipo: ");
            scanf("%d", &opcTipo);
        
            int busca = 0; // Variável para verificar se foi busca

            for (int i = 0; i < totalProd; i++){

                if (prod[i].tipo == opcTipo){
                    printf("%d. Nome: %s, Quantidade: %d %s, Valor: %.2f, Validade: %s/%s, Tipo: %s\n",
                    i + 1, prod[i].nome, prod[i].qtd, tipoUnid(prod[i].unid),prod[i].valor, 
                    prod[i].valid.mes, prod[i].valid.ano, tipoCad(prod[i].tipo));
                    busca = 1; // Marca como busca    
                }
            }

            // Se não encontrou nenhum registro, exibe a mensagem
            if (!busca) {
                printf("Nenhum cadastro busca com o tipo escolhido.\n");
            }
            break;
        case 2:

            busca = 0; // Variável para verificar se foi busca

            // Exibe todos os produtos cadastrados
            for (int i = 0; i < totalProd; i++){
            printf("%d. Nome: %s, Quantidade: %d %s, Valor: %.2f, Validade: %s/%s, Tipo: %s\n",
               i + 1, prod[i].nome, prod[i].qtd, tipoUnid(prod[i].unid),
               prod[i].valor, prod[i].valid.mes, prod[i].valid.ano, tipoCad(prod[i].tipo));
               busca = 1; // Marca como busca   
            }
            // Se não encontrou nenhum registro, exibe a mensagem
            if (!busca) {
                printf("Nenhum cadastro busca com o tipo escolhido.\n");
            }
            break;
        case 0:
            printf("\nSaindo da operação.\n");
            break;
        default:
            printf("Opção inválida!\n");
            break;
        }
    } while (visu != 0);

}

void menuArmz(){
    Cadastro prod[MAX_PRODUTOS];
    int totalProd = loadCad(prod); // Carrega produtos existentes
    int opcao;

   do {

    if (totalProd == 0){
        printf("O estoque não contém nenhum produto. Por favor, adicione produtos.\n");
        opcao  = 0;
        return;
    }

    printf("\nO que deseja fazer?\n");
    
        printf("\n1. Exibir estoque\n2. Editar produto\n3. Remover produto\n0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                visuArmz();
                break;
            case 2:
                editProd(prod, totalProd);
                break;
            case 3:
                removeProd(prod, &totalProd);
                break;
            case 0:
                printf("Saindo da operação.\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;

        }

    } while (opcao != 0);
}
