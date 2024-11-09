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
    int opcao;

    do
    {
        printf("\nO que deseja editar?\n");
        printf("1. Fonecedor\n2. Produto\n3. Quantidade\n4. Preço\n5. Data de compra\n6. Tipo\n0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Novo nome do Fornecedor: ");
            scanf(" %100[^\n]", editCompra->fornecedor);
            break;
        case 2:
            printf("Novo nome do produto: ");
            scanf(" %100[^\n]", editCompra->produto);
            break;
        case 3:
            do{
                printf("Nova quantidade: ");
                scanf("%d", &editCompra->quantidade);
                if (editCompra->quantidade < 0){
                    printf("Erro: Quantidade deve ser maior que zero.\n");
                }
            } while (editCompra->quantidade < 0);
            break;
        case 4:
            do
            {
                printf("Novo preco: ");
                scanf("%f", &editCompra->preco);
                if (editCompra->preco <= 0)
                {
                    printf("Erro: O preco deve ser positivo.\n");
                }
            } while (editCompra->preco <= 0);
            break;
        case 5:
            do
            {
                printf("Nova data de compra (dd/mm/yyyy): ");
                scanf("%2s/%2s/%4s", editCompra->valid.dia, editCompra->valid.mes, editCompra->valid.ano);
            } while (!validarData(editCompra->valid.dia, editCompra->valid.mes, editCompra->valid.ano));
            break;
        case 6:
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

    // Remover o produto deslocando os demais
    for (int i = index; i < *totalCompra - 1; i++)
    {
        compra[i] = compra[i + 1];
    }

    (*totalCompra)--; // Reduz o número total de produtos
    printf("Produto removido com sucesso!\n");
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

            printf("\n\n1.Frutas\n2.Hortalicas\n3.Bebidas\n4.Cereais\n5.Laticineos\n");
            printf("Escolha um Tipo: ");
            scanf("%d", &opcTipo);
        
            int busca = 0; // Variável para verificar se foi busca

            for (int i = 0; i < totalCompra; i++){


                if (compra[i].tipo == opcTipo){
                    printf("%d. Fornecedor: %s, Produto: %s, Quantidade: %d, Valor Total: %.2f, Data de compra: %2s/%2s/%4s.",
                    i + 1, compra[i].fornecedor, compra[i].produto,
                    compra[i].quantidade, compra[i].valorTotal, 
                    compra[i].valid.dia, compra[i].valid.mes, compra[i].valid.ano);
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
                printf("%d. Fornecedor: %s, Produto: %s, Quantidade: %d, Valor Total: %.2f, Data de compra: %2s/%2s/%4s.",
                    i + 1, compra[i].fornecedor, compra[i].produto,
                    compra[i].quantidade, compra[i].valorTotal, 
                    compra[i].valid.dia, compra[i].valid.mes, compra[i].valid.ano);
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
    Cadastro compra[MAX_PRODUTOS];
    int totalCompra = loadCompra(compra); // Carrega produtos existentes
    int opcao;

   do {

    if (totalCompra == 0){
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
                editCompra(compra, totalCompra);
                saveCad(compra, totalCompra);
                break;
            case 3:
                removeProd(compra, &totalCompra);
                saveCad(compra, totalCompra);
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
    saveCompra(compra, totalCompra);
}
