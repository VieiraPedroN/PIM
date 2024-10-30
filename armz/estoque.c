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
    int opcao;

    do
    {
        printf("\nO que deseja editar?\n");
        printf("1. Nome\n2. Quantidade\n3. Valor\n4. Data de validade\n5. Tipo\n0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Novo nome: ");
            scanf(" %100[^\n]", editProd->nome);
            break;
        case 2:
            do{
                printf("Nova quantidade: ");
                scanf("%d", &editProd->qtd);
                if (editProd->qtd < 0){
                    printf("Erro: Quantidade deve ser maior que zero.\n");
                }
            } while (editProd->qtd < 0);
            break;
        case 3:
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
        case 4:
            do
            {
                printf("Nova data de validade (mm/yyyy): ");
                scanf("%2s/%4s", editProd->valid.mes, editProd->valid.ano);
            } while (!validData(editProd->valid.mes, editProd->valid.ano));
            break;
        case 5:
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

    // Remover o produto deslocando os demais
    for (int i = index; i < *totalProd - 1; i++)
    {
        prod[i] = prod[i + 1];
    }

    (*totalProd)--; // Reduz o número total de produtos
    printf("Produto removido com sucesso!\n");
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
        
            for (int i = 0; i < totalProd; i++){

            char *unidadeTipo = (prod[i].unid == 1) ? "Unid" : "Kg"; // Define unidade

                if (prod[i].tipo == opcTipo){
                    printf("%d. Nome: %s, Quantidade: %d %s, Valor: %.2f, Validade: %s/%s, Tipo: %d\n",
                    i + 1, prod[i].nome, prod[i].qtd, unidadeTipo,
                    prod[i].valor, prod[i].valid.mes, prod[i].valid.ano, prod[i].tipo);
                    }
            }
            break;
        case 2:
            // Exibe todos os produtos cadastrados
            for (int i = 0; i < totalProd; i++){
            char *unidadeTipo = (prod[i].unid == 1) ? "Unid" : "Kg"; // Define unidade

            printf("%d. Nome: %s, Quantidade: %d %s, Valor: %.2f, Validade: %s/%s, Tipo: %d\n",
               i + 1, prod[i].nome, prod[i].qtd, unidadeTipo,
               prod[i].valor, prod[i].valid.mes, prod[i].valid.ano, prod[i].tipo);
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

   do{

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
                saveCad(prod, totalProd);
                break;
            case 3:
                removeProd(prod, &totalProd);
                saveCad(prod, totalProd);
                break;
            case 0:
                printf("Saindo da operação.\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;

        }

    } while (opcao != 0);
    // Salvar produtos no arquivo após alterações
    saveCad(prod, totalProd);
}