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

void cadastraVoo(Fila *C, Fila *E, int s){

    int passageiros;
    bool flag;
    char *codigo;
    char resp, emerg;

    do{
    printf("\n\t\t----Dados do Voo----");
    printf("\n\t->QTD passageiros: ");
    scanf("%d", &passageiros);

    printf("\n\t->Emergencia? (S/N)");
    fflush(stdin);
    emerg=getchar();

    codigo = CodigoRandon();

    if(toupper(emerg) == 'N'){
    flag = false;
    InsereFila(C, passageiros, codigo, HoraRandon(s), flag);
    } else {
    flag = true;
    InsereFila(E, passageiros, codigo, HoraRandon(s), flag);
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
        printf("\n\tPrioridade é da Fila Emergencial");
        printf("\n\n\t->Passageiros: %d - ",q->passageiros);
        printf("\n\t->Código de Voo: %s - ",q->codigoVoo);
        printf("\n\t->Check-Hora: %d - ",q->checkHora);
        printf("\n\t->Horário: %d:%d - ",q->horario.hora, q->horario.minuto);

    } else {
        q=C->ini;
        printf("\n\tProximo para o Pouso");
        printf("\n\n\t->Passageiros: %d - ",q->passageiros);
        printf("\n\t->Código de Voo: %s - ",q->codigoVoo);
        printf("\n\t->Check-Hora: %d - ",q->checkHora);
        printf("\n\t->Horário: %d:%d - ",q->horario.hora, q->horario.minuto);
    }
}

void autorizarPouso(Fila *C, Fila *E, Fila *P){
    Voo* q;
    if(!VaziaFila(E)){
        q=E->ini;
        printf("\n\tPrioridade é da Fila Emergencial");
        printf("\n\t->Código de Voo: %s - ",q->codigoVoo);
        printf("\n\t->Check-Hora: %d - ",q->checkHora);
        printf("\n\t->Voo autorizado para pouso");

        InsereFila(P, q->passageiros, q->codigoVoo, q->horario, true);
        RetiraFila(E);

    }else {
        q=C->ini;
        printf("\n\t->Código de Voo: %s - ",q->codigoVoo);
        printf("\n\t->Check-Hora: %d - ",q->checkHora);

        if(q->checkHora == 0){
            printf("\n\t->Voo Atrasado");
        }else {
            printf("\n\t->Voo no Horário");
        }
        printf("\n\t->Voo autorizado para pouso");
        InsereFila(P, q->passageiros, q->codigoVoo, q->horario, false);
        RetiraFila(C);
    }
}

void imprimePousos(Fila *P){
    if(VaziaFila(P)){
        printf("\n\tNão há Voos em Solo");
    } else {
        printf("\n\tVoos Pousados!!");
        imprimeFilaCheck(P);
    }
}

int main(){
    int seed = 2104;
    int op;
    Fila *Chegadas = CriaFila();
    Fila *Emergencia = CriaFila();
    Fila *Pousados = CriaFila();

    setlocale(LC_ALL,"portuguese");

    srand(seed);

    do{
    printf("\n\t\t----Menu----");
    printf("\n\t[1]. Inserir ");
    printf("\n\t[2]. Autorizar ");
    printf("\n\t[3]. Relatório");
    printf("\n\t[4]. Proximo pouso ");
    printf("\n\t[5]. Fila de Voos");
    printf("\n\t[6]. Simulação de Pouso");
    printf("\n\t[7]. Sair ");
    printf("\n\t\t ->Opção desejada:");
    scanf("%d",&op);

    switch(op){
        case 1:
            cadastraVoo(Chegadas, Emergencia, seed);
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
            printf("\n\tOpção Invalida...");
            break;
    }
    }while(op != 7);
return 0;
}


