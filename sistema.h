#ifndef SISTEMA_H
#define SISTEMA_H

#define MAX_PRODUTOS 100 // Limite de produtos

#define Max_Fluxos 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char movimentacao[50];
    float valor;
    char tipo[12];
    char data[11];
    char pagamento[20];
} Fluxo;

// Estrutura de Data
typedef struct {
    char mes[3];
    char ano[5]; // Ajuste para ano com 4 dígitos + terminador nulo
} Data;

// Estrutura de Cadastro
typedef struct {
    char nome[101];
    float valor;
    int qtd;
    Data valid;
    int tipo; // 1-Frutas, 2-Hortaliças, 3-Bebidas, 4-Cereais, 5-Laticínios
    int unid;   // 1-Unidade, 2-Kg
} Cadastro;

// Estrutura de Doação
typedef struct {
    char prodNome[101];
    int qtdDoa;
    Data dataDoa; // Data de doação
} Doacao;

typedef struct {
    char prodNome[101];
    int qtdRmv;
    Data dataRmv; // Data de descarte
} Descarte;

typedef struct {
    int tipo;
    char colabName[101];
    char colabUser[101];
    char colabPass[101];
    char funcao[20]; // Nome da função do colaborador
}  Colaborador;

typedef struct {
    char dia[3];
    char mes[3];
    char ano[5];
} DataCompra;
typedef struct {
    int tipo;
    char fornecedor[101];
    char produto[101];
    int quantidade;
    float preco;
    float valorTotal;
    DataCompra valid;
} Compra;

int check = 0, checkColab = 1;


#include "cad/cadastro.c"
#include "cad/cadastro_menu.c"

#include "armz/estoque.c"

#include "doacao/desc.c"
#include "doacao/doacao.c"
#include "doacao/menu_doa.c"
#include "doacao/menu_desc.c"

#include "colaborador/cad_colab.c"
#include "colaborador/edit_colab.c"
#include "colaborador/colab.c"


#include "compra/compra.c"
//#include "compra/edit_compra.c"

#include "fluxo_caixa/Fluxo_FormaP.c"
#include "fluxo_caixa/Fluxo_GRM.c"
#include "fluxo_caixa/Fluxo_IFC.c"
#include "fluxo_caixa/Fluxo_Impr.c"
#include "fluxo_caixa/Fluxo_Pag.c"
#include "fluxo_caixa/Fluxo_M_E_D.c"
#include "fluxo_caixa/Fluxo_Venda.c"
#include "fluxo_caixa/Fluxo_menu.c"

#include "menus/menuAdm.c"
#include "menus/menuAlmox.c"
#include "menus/menuCaixa.c"
#include "menus/menuFinanc.c"

#endif // SISTEMA_H