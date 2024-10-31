#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"
#include  "menu.c"


void main(){

    char login[15] = "teste";
    char login1[15];
    char senha[15] = "teste";
    char senha1[15];        
    int login_efetuado = 0; //0 - Falso e  1 - Verdadeiro

    while(!login_efetuado){
        printf("\nDigite o Login: ");
        scanf("%s", login1);

        printf("Digite a Senha: ");
        scanf("%s", senha1);

        if (strcmp(login, login1) == 0 && strcmp(senha, senha1) == 0){
            printf("\nLOGADO!\n");
            login_efetuado = 1;
            menu();
        }
        else
            printf("\nDADOS INVALIDOS!\n");    
    }

}