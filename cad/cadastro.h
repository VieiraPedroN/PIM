#ifndef CADASTRO_H
#define CADASTRO_H

#define MAX_PRODUTOS 5 // Limite de produtos que podem ser cadastrados

typedef struct {
    char dia[3];
    char mes[3];
    char ano[5];
} Data;

typedef struct {
    char nome[101];
    float valor;
    int qtd;
    Data valid;
    int tipo; // 1-Frutas, 2-Hortaliças, 3-Bebidas, 4-Cereais, 5-Laticínios
} Cadastro;

int validData(char *dia, char *mes, char *ano);
int compareCad(Cadastro prod[], int totalProd, char nome[]);
void saveCad(Cadastro prod[], int totalProd);
int loadCad(Cadastro prod[]);
void listCad(Cadastro prod[], int totalProd);
void cad(int tipoProd);

#endif // CADASTRO_H
