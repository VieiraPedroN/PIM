#include <stdio.h>
#include <stdlib.h>
#include "cadastro.c"
#include "../sistema.h"

void cad_menu() {
    int tipo, resp=0;

    do{
        printf("***********************\n");
        printf("* 1- Frutas           *\n");
        printf("* 2- Hortalicas       *\n");
        printf("* 3- Bebidas          *\n");
        printf("* 4- Cereais          *\n");
        printf("* 5- Laticineos       *\n");
        printf("* 6- Sair da operacao *\n");
        printf("***********************\n");
        printf("Selecione um tipo de produto para cadastro: ");
        scanf("%d", &tipo);
        
        if (tipo < 1 || tipo > 5) {
            printf("Tipo inválido. Retornando ao menu principal.\n");
            return;
        }
        else{
            resp = 1;
        }

        cad(tipo);
    } while (resp == 1);
}
