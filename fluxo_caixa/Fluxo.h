#ifndef FLUXO_H
#define FLUXO_H
#include "../cad/cadastro.h"
#define Max_Fluxos 100

typedef struct {
    char movimentacao[50];
    float valor;
    char tipo[12];
    char data[11];
    char pagamento[20];
} Fluxo;

void Venda(Fluxo *transacoes, int *NumF, Cadastro *produtos, int totalProd);
void DeletV(Fluxo *transacoes, int *NumF, int IndiceT, Cadastro *produtos, int totalProd);
void EditV(Fluxo *transacoes, int NumF, Cadastro *produtos, int totalProd);
void EditP(Fluxo *transacoes, int NumF, int IndiceT);
void DeletP(Fluxo *transacoes, int *NumF, int IndiceT);
void FormaP(char *pagamento);
void GerarR_M(Fluxo *transacoes, int NumF, char *MesAno);
void IFC(Fluxo *transacoes, int NumF, const char *dataDesejada);
void ImprimirF(Fluxo *transacoes, int NumF);
void Pagamentos(Fluxo *transacoes, int *NumF, char *transacao, float valor, char *data, char *pagamento);
void FormaPP(char *pagamento);
void MenuED(Fluxo *transacoes, int totalFluxo, Cadastro *produtos, int totalProd);
void saveFluxo(Fluxo *transacoes, int totalFluxo);
int loadFluxo(Fluxo *transacoes);

#endif