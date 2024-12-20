#ifndef SISTEMA_H
#define SISTEMA_H

#define MAX_PRODUTOS 100 // Limite de produtos
#define MAX_COMPRA 100
#define MAX_FUNCIONARIOS 100 // Limite de colaboradores
#define Max_Fluxos 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char mov[50];
    float valor;
    char tipo[12];
    char data[11];
    char Pag[20];
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
    char inst[101];
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
    int unidade;
    float preco;
    float valorTotal;
    DataCompra valid;
} Compra;

int check = 0, checkColab = 0;


#include "cadastro/cadastro.c"
#include "cadastro/cadastro_menu.c"

#include "estoque/estoque.c"


#include "doacao/doacao.c"
#include "doacao/menu_doa.c"

#include "descarte/desc.c"
#include "descarte/menu_desc.c"

#include "colaborador/cad_colab.c"
#include "colaborador/edit_colab.c"
#include "colaborador/colab.c"

#include "compra/cad_compra.c"
#include "compra/edit_compra.c"
#include "compra/compra.c"

#include "caixa/caixa.c"

#include "Financeiro/Financ_FormaP.c"
#include "Financeiro/financ_relatorios.c"
#include "Financeiro/Financ_Pag.c"
#include "Financeiro/Financ_M_E_D.c"
#include "Financeiro/Financ_menu.c"

#include "menus/menuAdm.c"
#include "menus/menuAlmox.c"
#include "menus/menuCaixa.c"
#include "menus/menuFinanc.c"

#endif // SISTEMA_H