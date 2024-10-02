#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include "Central.h"

char* CodigoRandon(){

    char *cod;
    int aux = 0;

    cod = (char*) malloc(5 * sizeof(char));

    for (int i = 0; i<4; i++){
        aux = rand()%2;
        if(aux == 0){
            cod[i] = '0' + rand()%10;
        } else{
            cod[i] = 'A' + rand()%26;
        }
    }
    cod[4] = '\0';

    return cod;
}

int passageirosRandon(){
    int pas;

    do{
        pas = rand()%201;
    }while(pas <= 50);

    return pas;
}

void cadastraVoo(Fila *C, Fila *E){

    int passageiros;
    bool flag;
    char *codigo;
    char resp, emerg;

    do{
    printf("\n\t\t----Cadastro de Voo---");
    passageiros = passageirosRandon();
    codigo = CodigoRandon();
    Horas chegada = HoraRandon();

    printf("\n\t->N�mero de Passageiros: %d", passageiros);
    printf("\n\t->C�digo de Voo: %s", codigo);
    if(chegada.minuto<10){
    printf("\n\t->Hor�rio de Chegada: %d:0%d", chegada.hora, chegada.minuto);
    }
    else{
    printf("\n\t->Hor�rio de Chegada: %d:%d", chegada.hora, chegada.minuto);
    }
    printf("\n\n\t->Emergencia? (S/N)");
    fflush(stdin);
    emerg=getchar();

    if(toupper(emerg) == 'N'){
    flag = false;
    InsereFila(C, passageiros, codigo, chegada, flag);
    } else {
    flag = true;
    InsereFila(E, passageiros, codigo, chegada, flag);
    }

    printf("\n\t-> Deseja inserir mais um voo? (S/N)");
    fflush(stdin);
    resp=getchar();

    free(codigo);
    }while(toupper(resp)!='N');

}

void relatorio(Fila *C, Fila *E){
    printf("\n\tFila de Voos Emergenciais!!");
    imprimeFila(E);

    printf("\n\tFila de Voos!!");
    imprimeFila(C);

}

void proxPouso(Fila *C, Fila *E){
    Voo* q;
    if(!VaziaFila(E)){
        q=E->ini;
        printf("\n\tPrioridade � da Fila Emergencial");
        printf("\n\n\t->Passageiros: %d - ",q->passageiros);
        printf("\n\t->C�digo de Voo: %s - ",q->codigoVoo);
        printf("\n\t->Check-Hora: %d - ",q->checkHora);
        if(q->horario.minuto<10){
        printf("\n\t->Hor�rio: %d:0%d - ",q->horario.hora, q->horario.minuto);
        }
        else{
        printf("\n\t->Hor�rio: %d:%d - ",q->horario.hora, q->horario.minuto);
        }
    } else {
        q=C->ini;
        printf("\n\tProximo para o Pouso");
        printf("\n\n\t->Passageiros: %d - ",q->passageiros);
        printf("\n\t->C�digo de Voo: %s - ",q->codigoVoo);
        printf("\n\t->Check-Hora: %d - ",q->checkHora);
        if(q->horario.minuto<10){
        printf("\n\t->Hor�rio: %d:0%d - ",q->horario.hora, q->horario.minuto);
        }
        else{
        printf("\n\t->Hor�rio: %d:%d - ",q->horario.hora, q->horario.minuto);
        }
    }
}

void autorizarPouso(Fila *C, Fila *E, Fila *P){
    Voo* q;
    if (VaziaFila(E) && VaziaFila(C)){
        printf("\n\tN�o a Voos para pousar\n\n");
    } else {
        if(!VaziaFila(E)){
            q=E->ini;
            printf("\n\tPrioridade � da Fila Emergencial");
            printf("\n\t->C�digo de Voo: %s - ",q->codigoVoo);
            printf("\n\t->Check-Hora: %d - ",q->checkHora);
            printf("\n\t->Voo autorizado para pouso");

            InsereFila(P, q->passageiros, q->codigoVoo, q->horario, true);
            RetiraFila(E);

        }else {
            q=C->ini;
            printf("\n\t->C�digo de Voo: %s - ",q->codigoVoo);
            printf("\n\t->Check-Hora: %d - ",q->checkHora);

            if(q->checkHora == 0){
                printf("\n\t->Voo Atrasado");
            }else {
                printf("\n\t->Voo no Hor�rio");
            }
            printf("\n\t->Voo autorizado para pouso");
            InsereFila(P, q->passageiros, q->codigoVoo, q->horario, false);
            RetiraFila(C);
        }
    }
}

void imprimePousos(Fila *P){
    if(VaziaFila(P)){
        printf("\n\tN�o h� Voos em Solo");
    } else {
        printf("\n\tVoos Pousados!!");
        imprimeFilaCheck(P);
    }
}

int main(){
    int seed = 0;
    int op;
    Fila *Chegadas = CriaFila();
    Fila *Emergencia = CriaFila();
    Fila *Pousados = CriaFila();

    setlocale(LC_ALL,"portuguese");

    printf("\n\tInsira sua seed: ");
    scanf("%d", &seed);

    srand(seed);

    do{
    printf("\n\t\t----Menu----");
    printf("\n\t[1]. Inserir ");
    printf("\n\t[2]. Autorizar ");
    printf("\n\t[3]. Relat�rio");
    printf("\n\t[4]. Proximo pouso ");
    printf("\n\t[5]. Fila de Voos");
    printf("\n\t[6]. Simula��o de Pouso");
    printf("\n\t[7]. Sair ");

    do{
    fflush(stdin);
    printf("\n\t\t ->Op��o desejada:");
    scanf("%d",&op);
    }while(op < 0  || op > 7);

    switch(op){
        case 1:
            cadastraVoo(Chegadas, Emergencia);
            break;
        case 2:
            autorizarPouso(Chegadas, Emergencia, Pousados);
            break;
        case 3:
            relatorio(Chegadas, Emergencia);
            break;
        case 4:
            proxPouso(Chegadas, Emergencia);
            break;
        case 5:
            imprimePousos(Pousados);
            break;
        case 6:
            break;
        case 7:
            break;
        default:
            printf("\n\tOp��o Invalida...");
            break;
    }
    }while(op != 7);
return 0;
}


