#include <stdio.h>
#include "../cad/cadastro.h"

void visuArmz() {
    Cadastro prod[MAX_PRODUTOS];
    int totalProd = loadCad(prod); // Carrega produtos existentes
    listCad(prod, totalProd);
}
