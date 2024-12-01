#include <stdio.h>
#include <stdlib.h>
#include "../sistema.h"

void cad_menu() {
    int tipo;
    
    do {

        if (check == 1){
            return;
        }

        printf("***********************\n");
        printf("* 1- Frutas           *\n");
        printf("* 2- Hortaliças       *\n");
        printf("* 3- Bebidas          *\n");
        printf("* 4- Cereais          *\n");
        printf("* 5- Laticínios       *\n");
        printf("* 0- Sair da operação *\n");
        printf("***********************\n");
        printf("Selecione um tipo de produto para cadastro: ");
        scanf("%d", &tipo);
        
        if (tipo == 0) {
            printf("Saindo da operação de cadastro.\n");
            return; // Retorna ao menu principal
        }
        
        if (tipo < 1 || tipo > 5) {
            printf("Tipo inválido. Tente novamente.\n");
            continue;
        }

        cad(tipo); // Quando retornar daqui, volta para o início do loop
    } while (1); // Loop infinito que só é quebrado quando escolher sair (6)
}
