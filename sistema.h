#ifndef SISTEMA_H
#define SISTEMA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 5 // Limite de produtos

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

// Funções para gerenciar produtos
void editProd(Cadastro *prod, int totalProd);
void removeProd(Cadastro *prod, int *totalProd);
void visuArmz(); // Visualiza o estoque

void doaProd(Cadastro *prod, int totalProd);
void saveDoa(Doacao doacao); // Salva doações em doaca.dat
int visuDoa(Cadastro *prod, int totalProd); // Visualiza doações existentes

void descProd(Cadastro *prod, int totalProd);
void saveDesc(Descarte descarte); // Salva descartes em descarte.dat
int visuDesc(Cadastro *prod, int totalProd); // Visualiza descartes existentes


// Funções para validação e operações com arquivos
int validData(char *mes, char *ano); // Verifica validade da data (somente mês e ano)
void saveCad(Cadastro prod[], int totalProd); // Salva cadastros no arquivo
int loadCad(Cadastro prod[]); // Carrega cadastros do arquivo

// Funções adicionais para gerenciamento de cadastro
int compareCad(Cadastro prod[], int totalProd, char nome[]);
void listCad(Cadastro prod[], int totalProd); // Lista os cadastros
void cad(int tipoProd); // Função de cadastro de produtos

// Funções para gerenciar doações
void doaProd(Cadastro *prod, int totalProd);
void rmvProd(Cadastro *prod, int totalProd);
void saveDoa(Doacao doacao); // Salva doações em doaca.dat
int visuDoa(); // Visualiza doações existentes

// Funções para gerenciar colaboradores
void saveCadColab(Colaborador func[], int totalFunc);
int loadCadColab(Colaborador func[]);

int compCadColab (Colaborador func[], int totalFunc, char colabName[]);

void cadColab(int tipoFunc, char *funcao); // Adiciona parâmetro funcao para o nome da função

void editFunc(Colaborador *func, int totalFunc);
void rmvFunc(Colaborador *func, int *totalFunc);
void visuColab();

int check = 0, checkColab = 1;

#endif // SISTEMA_H