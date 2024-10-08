#include <stdio.h>
#include "cadastro.c"
#include "cadastro.h"

void cad_menu() {
    int tipo;
    printf("*****************\n");
    printf("* 1- Frutas     *\n");
    printf("* 2- Hortalicas *\n");
    printf("* 3- Bebidas    *\n");
    printf("* 4- Cereais    *\n");
    printf("* 5- Laticineos *\n");
    printf("*****************\n");
    printf("Selecione um tipo de produto para cadastro: ");
    scanf("%d", &tipo);
    
    if (tipo < 1 || tipo > 5) {
        printf("Tipo inválido. Retornando ao menu principal.\n");
        return;
    }
    
    cad(tipo);
}
