#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include "Central.h"

int main(){
    int seed = 5, passageiros, checkhora;
    char codigo[4];
    char resp;
    Fila *F;
    setlocale(LC_ALL,"portuguese");


    F = CriaFila();
    do{
    printf("\n\t\t----Dados do Voo----");
    printf("\n\t->QTD passageiros: ");
    scanf("%d", &passageiros);

    fflush(stdin);
    printf("\n\t->Codigo do Voo: ");
    scanf("%s", &codigo);

    printf("\n\t->Atrasado: ");
    scanf("%d", &checkhora);
    InsereFila(F,passageiros, checkhora, HoraRandon(seed), codigo);

    printf("\n\t-> Deseja inserir mais um número? (S/N)");
    fflush(stdin);
    resp=getchar();
    }while(toupper(resp)!='N');

    imprimeFila(F);

return 0;
}


