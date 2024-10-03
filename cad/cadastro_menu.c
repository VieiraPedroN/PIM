#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cadastro.c"

void produto(){
    printf("*****************\n");
    printf("* 1- Frutas     *\n");
    printf("* 2- Hortaliças *\n");
    printf("* 3- Bebidas    *\n");
    printf("* 4- Cereais    *\n");
    printf("* 5- Laticineos *\n");
    printf("*****************\n");
}

void cad_menu(){
    int produtos;

        printf("\n");
        produto();

        printf("\nSelecione um produto para cadastro: ");
        scanf("%d", &produtos);

            switch (produtos){
                
                case 1: {
                    cad();
                        break;
                    }
                case 2: {
                    cad();
                        break;
                    }
                case 3: {
                    cad();
                        break;
                    }
                case 4: {
                    cad();
                        break;
                    }
                case 5: {
                    cad();
                        break;
                    }
                    default:
                        printf("Opção inválida.\n");
                        break;
                    }
                
}