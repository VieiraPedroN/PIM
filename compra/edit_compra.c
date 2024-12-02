#include <stdio.h>
#include <stdlib.h>
#include "../sistema.h"

void editCompra(Compra *compra, int totalCompra){
    int index;
    printf("Digite o número do produto que deseja editar (1 a %d): ", totalCompra);
    scanf("%d", &index);
    index--; // Ajusta para índice de array

    if (index < 0 || index >= totalCompra)
    {
        printf("Erro: Produto inválido!\n");
        return;
    }

    Compra *editCompra = &compra[index]; // Usa ponteiro para acessar o produto

    printf("Fornecedor: %s, Produto: %s, Quantidade: %d %s, Valor Total: %.2f, Data de compra: %2s/%2s/%4s, Tipo: %s\n",
            editCompra->fornecedor, editCompra->produto,
            editCompra->quantidade, tipoUnidCompra(editCompra->unidade), 
            editCompra->valorTotal, editCompra->valid.dia, editCompra->valid.mes, 
            editCompra->valid.ano, tipoCompra(editCompra->tipo));
    
    int opt;
    printf("Deseja editar esse produto? (1-Sim, 0-Cancelar): ");
    scanf("%d",&opt);

    do { 
        if (opt == 1) {
            int opcao;

            do {
                printf("\nO que deseja editar?\n");
                printf("1. Fonecedor\n2. Produto\n3. Unidade\n4. Quantidade\n5. Preço\n6. Data de compra\n7. Tipo\n0. Sair\n");
                printf("Escolha uma opção: ");
                scanf("%d", &opcao);

                switch (opcao)
                {
                case 1:
                    printf("Novo nome do fornecedor: ");
                    scanf(" %100[^\n]", editCompra->fornecedor);
                    break;
                case 2:
                    printf("Novo nome do produto: ");
                    scanf(" %100[^\n]", editCompra->produto);
                    break;
                case 3:
                    do {
                        printf("Escolha a unidade (1 - Unidade, 2 - Kg): ");
                        scanf("%d", &editCompra->unidade); // Salve a unidade diretamente

                        if (editCompra->unidade != 1 && editCompra->unidade != 2) {
                            printf("Erro: Unidade inválida. Tente novamente.\n");
                        }
                    } while (editCompra->unidade != 1 && editCompra->unidade != 2);  
                    break;
                case 4:
                    do{
                        printf("Nova quantidade: ");
                        scanf("%d", &editCompra->quantidade);
                        if (editCompra->quantidade < 0){
                            printf("Erro: Quantidade deve ser maior que zero.\n");
                        }
                    } while (editCompra->quantidade < 0);
                    break;
                case 5:
                    do
                    {
                        printf("Novo preço: ");
                        scanf("%f", &editCompra->preco);
                        if (editCompra->preco <= 0)
                        {
                            printf("Erro: O preço deve ser positivo.\n");
                        }
                    } while (editCompra->preco <= 0);
                    break;
                case 6:
                    do
                    {
                        printf("Nova data de compra (dd/mm/yyyy): ");
                        scanf("%2s/%2s/%4s", editCompra->valid.dia, editCompra->valid.mes, editCompra->valid.ano);
                    } while (!validarData(editCompra->valid.dia, editCompra->valid.mes, editCompra->valid.ano));
                    break;
                case 7:
                    printf("Novo tipo (1-Frutas, 2-Hortaliças, 3-Bebidas, 4-Cereais, 5-Laticínios): ");
                    scanf("%d", &editCompra->tipo);
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

            editCompra->valorTotal = editCompra->quantidade * editCompra->preco;

            printf("As alterações feitas foram: \n");

            printf("Fornecedor: %s, Produto: %s, Quantidade: %d %s, Valor Total: %.2f, Data de compra: %2s/%2s/%4s, Tipo: %s\n",
                    editCompra->fornecedor, editCompra->produto,
                    editCompra->quantidade, tipoUnidCompra(editCompra->unidade), 
                    editCompra->valorTotal, editCompra->valid.dia, editCompra->valid.mes, 
                    editCompra->valid.ano, tipoCompra(editCompra->tipo));

            printf("Deseja salvar? (1-Sim, 0-Não): ");
            scanf("%d",&salvar);
            printf("\n");
            do {
                if (salvar == 1) {
                    printf("Alterações salvas com sucesso!\n");
                    saveCompra(compra, totalCompra);
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

void removeCompra(Compra *compra, int *totalCompra){
    int index;

    if (index == 0){
        printf("Não contem nenhum produto para ser removido.");
        return;
    }
    

    printf("Digite o número do produto que deseja remover (1 a %d): ", *totalCompra);
    scanf("%d", &index);
    index--; // Ajusta para índice de array

    if (index < 0 || index >= *totalCompra)
    {
        printf("Erro: Produto inválido!\n");
        return;
    }

    printf("Fornecedor: %s, Produto: %s, Quantidade: %d %s, Valor Total: %.2f, Data de compra: %2s/%2s/%4s, Tipo: %s\n",
            compra[index].fornecedor, compra[index].produto,
            compra[index].quantidade, tipoUnidCompra(compra[index].unidade), 
            compra[index].valorTotal, compra[index].valid.dia, compra[index].valid.mes, 
            compra[index].valid.ano, tipoCompra(compra[index].tipo));

    int opt;
    printf("Deseja remover esse produto? (1-Sim, 0-Cancelar): ");
    scanf("%d",&opt);

    do {
        if (opt == 1) {

        // Remover o produto deslocando os demais
        for (int i = index; i < *totalCompra - 1; i++) {
            compra[i] = compra[i + 1];
        }

        (*totalCompra)--; // Reduz o número total de produtos
        printf("Produto removido com sucesso!\n");

        saveCompra(compra, *totalCompra);
        break;
        } else {
            printf("Opção invalida");
        }
        
    } while (opt !=0);
}

void visuCompra(){
    Compra compra[MAX_PRODUTOS];
    int totalCompra = loadCompra(compra); // Carrega produtos existentes
    int visu;

    printf("\nHistorico de compras:\n");
    printf("\nComo deseja visualizar?");

    do{
        printf("\n1. Tipo\n2. Todo o estoque\n0. sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &visu);
        switch (visu){ 
        int opcTipo;    
        case 1:

            printf("\n\n1.Frutas\n2.Hortaliças\n3.Bebidas\n4.Cereais\n5.Laticíneos\n");
            printf("Escolha um Tipo: ");
            scanf("%d", &opcTipo);
        
            int busca = 0; // Variável para verificar se foi busca

            for (int i = 0; i < totalCompra; i++){

                if (compra[i].tipo == opcTipo){
                    printf("%d. Fornecedor: %s, Produto: %s, Quantidade: %d %s, Valor Total: %.2f, Data de compra: %2s/%2s/%4s, Tipo: %s\n",
                        i + 1, compra[i].fornecedor, compra[i].produto,
                        compra[i].quantidade, tipoUnidCompra(compra[i].unidade), 
                        compra[i].valorTotal, compra[i].valid.dia, compra[i].valid.mes, 
                        compra[i].valid.ano, tipoCompra(compra[i].tipo));
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
            for (int i = 0; i < totalCompra; i++){
                printf("%d. Fornecedor: %s, Produto: %s, Quantidade: %d %s, Valor Total: %.2f, Data de compra: %2s/%2s/%4s, Tipo: %s\n",
                        i + 1, compra[i].fornecedor, compra[i].produto,
                        compra[i].quantidade, tipoUnidCompra(compra[i].unidade), 
                        compra[i].valorTotal, compra[i].valid.dia, compra[i].valid.mes, 
                        compra[i].valid.ano, tipoCompra(compra[i].tipo));
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

void menuCompra(){
    Compra compra[MAX_COMPRA];
    int totalCompra = loadCompra(compra); // Carrega produtos existentes
    int opcao;

   do {

    if (totalCompra == 0){
        printf("O estoque não contém nenhum produto. Por favor, adicione produtos.\n");
        opcao  = 0;
        return;
    }

    printf("\nO que deseja fazer?\n");
    
        printf("\n1. Editar produto\n2. Remover produto\n0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao){
            case 1:
                editCompra(compra, totalCompra);
                break;
            case 2:
                removeCompra(compra, &totalCompra);
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
