#ifndef FLUXO_H
#define FLUXO_H
#include "../sistema.h"
#define Max_Fluxos 100

typedef struct {
    char movimentacao[50];
    float valor;
    char tipo[12];
    char data[11];
    char pagamento[20];
} Fluxo;

void Venda(Fluxo *transacoes, int *numTransacoes, Cadastro *produtos, int totalProdutos);
void DeletV(Fluxo *transacoes, int *numTransacoes, int indiceTransacao, Cadastro *produtos, int totalProdutos);
void EditV(Fluxo *transacoes, int numTransacoes, Cadastro *produtos, int totalProdutos);
void EditP(Fluxo *transacoes, int numTransacoes, int indiceTransacao);
void DeletP(Fluxo *transacoes, int *numTransacoes, int indiceTransacao);
void FormaP(char *pagamento);
void FormaPP(char *pagamento);
void GerarR_M(Fluxo *transacoes, int numTransacoes, char *mesAno);
void IFC(Fluxo *transacoes, int numTransacoes, const char *dataDesejada);
void ImprimirF(Fluxo *transacoes, int numTransacoes);
void Pagamentos(Fluxo *transacoes, int *numTransacoes);
void MenuED(Fluxo *transacoes, int totalTransacoes, Cadastro *produtos, int totalProdutos);
void saveFluxo(Fluxo *transacoes, int totalTransacoes);
int loadFluxo(Fluxo *transacoes);
int validarD(char *dia, char *mes, char *ano);

#endif