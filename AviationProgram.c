#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include "Central.h"

void cadastraVoo(Fila *C, Fila *E, int s){

    int passageiros, checkhora;
    char codigo[4];
    char resp, emerg;

    do{
    printf("\n\t\t----Dados do Voo----");
    printf("\n\t->QTD passageiros: ");
    scanf("%d", &passageiros);

    fflush(stdin);
    printf("\n\t->Codigo do Voo: ");
    scanf("%s", &codigo);

    printf("\n\t->Atrasado: ");
    scanf("%d", &checkhora);

    printf("\n\t->Emergencia? (S/N)");
    scanf("%d", &emerg);

    if(toupper(emerg) == 'S'){
    InsereFila(C, passageiros, checkhora, HoraRandon(s), codigo);
    } else {
    InsereFila(E, passageiros, checkhora, HoraRandon(s), codigo);
    }

    printf("\n\t-> Deseja inserir mais um número? (S/N)");
    fflush(stdin);
    resp=getchar();
    }while(toupper(resp)!='N');

}



int main(){
    int seed = 36545;
    int op;
    Fila *Chegadas = CriaFila();
    Fila *Emergencia = CriaFila();

    setlocale(LC_ALL,"portuguese");

    do{
    printf("\n\t\t----Menu----");
    printf("\n\t[1]. Inserir ");
    printf("\n\t[2]. Autorizar ");
    printf("\n\t[3]. Relatório");
    printf("\n\t[4]. Proximo pouso ");
    printf("\n\t[5]. Fila de Voos");
    printf("\n\t[6]. Pouso");
    printf("\n\t[7]. Sair ");
    printf("\n\t\t ->Opção desejada:");
    scanf("%d",&op);

    switch(op){
        case 1:
            cadastraVoo(Chegadas, Emergencia, seed);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            printf("\n\tOpção Invalida...");
            break;
    }
    }while(op != 7);
    imprimeFila(Chegadas);
    imprimeFila(Emergencia);

return 0;
}


