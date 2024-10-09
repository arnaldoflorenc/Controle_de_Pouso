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
    printf("\n\n----------------------------------------------------\n");
    printf("\n\t\t>>>>>Cadastro de Voo<<<<<");
    passageiros = passageirosRandon();
    codigo = CodigoRandon();
    Horas chegada = HoraRandon();

    printf("\n\t->Número de Passageiros: %d", passageiros);
    printf("\n\t->Código de Voo: %s", codigo);
    if(chegada.minuto<10){
    printf("\n\t->Horário de Chegada: %d:0%d", chegada.hora, chegada.minuto);
    }
    else{
    printf("\n\t->Horário de Chegada: %d:%d", chegada.hora, chegada.minuto);
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
    if(VaziaFila(C)&&VaziaFila(E)){
        printf("\n\t~~~~~~Não existem voos para pouso~~~~~~");
    } else{
        if(VaziaFila(E)){
            printf("\n\tFila de Voos!!");
            imprimeFila(C);
        } else {
            printf("\n\tFila de Voos Emergenciais!!");
            imprimeFila(E);

            printf("\n\tFila de Voos!!");
            imprimeFila(C);
        }
    }
}

void proxPouso(Fila *C, Fila *E){
    Voo* q;
    if(VaziaFila(E) && VaziaFila(C)){
        printf("\n\n\t~~~~~~Não existe voo em espera~~~~~~");
        return;
    }
    if(!VaziaFila(E)){
        q=E->ini;
        printf("\n\tPrioridade é da Fila Emergencial");
        printf("\n\n\t->Passageiros: %d - ",q->passageiros);
        printf("\n\t->Código de Voo: %s - ",q->codigoVoo);
        printf("\n\t->Check-Hora: %d - ",q->checkHora);
        if(q->horario.minuto<10){
        printf("\n\t->Horário: %d:0%d - ",q->horario.hora, q->horario.minuto);
        }
        else{
        printf("\n\t->Horário: %d:%d - ",q->horario.hora, q->horario.minuto);
        }
    } else {
        q=C->ini;
        printf("\n\tProximo para o Pouso");
        printf("\n\n\t->Passageiros: %d - ",q->passageiros);
        printf("\n\t->Código de Voo: %s - ",q->codigoVoo);
        printf("\n\t->Check-Hora: %d - ",q->checkHora);
        if(q->horario.minuto<10){
        printf("\n\t->Horário: %d:0%d - ",q->horario.hora, q->horario.minuto);
        }
        else{
        printf("\n\t->Horário: %d:%d - ",q->horario.hora, q->horario.minuto);
        }
    }
}

void autorizarPouso(Fila *C, Fila *E, Fila *P){
    Voo* q;
    if (VaziaFila(E) && VaziaFila(C)){
        printf("\t~~~~~ Não a Voos para pousar ~~~~~\n\n");
    } else{
        if(!VaziaFila(E)){
            q=E->ini;
            printf("\n\tPrioridade é da Fila Emergencial\n");
            printf("\n\t->Código de Voo: %s - ",q->codigoVoo);
            printf("\n\t->Check-Hora: %d - ",q->checkHora);
            printf("\n\t->Voo autorizado para pouso");

            InsereFila(P, q->passageiros, q->codigoVoo, q->horario, true);
            RetiraFila(E);

        } else{
            q=C->ini;
            printf("\n\t->Código de Voo: %s - ",q->codigoVoo);

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
}

void imprimePousos(Fila *P){
    if(VaziaFila(P)){
        printf("\n\t~~~~~~Não há Voos em Solo~~~~~~");
    } else {
        printf("\n\tVoos Pousados!!\n");
        imprimeFilaCheck(P);
    }
}

void simulacaodeVoo(Fila *C, Fila *E, int n){
    Voo *q;
    int qtd = 0;
    if(n > 10){
        while(n > 9){
            n -= 10;
            qtd++;
        }

        printf("\n\tNesse intervalo de tempo poderão pousar no máximo %d voos.", qtd);
        printf("\n\n\tSão eles:");

        for(int i = 0; i < qtd; i++){
            if (!VaziaFila(E)){
                q = E->ini;
                printf("\n\n\t >>>>>%d° Voo<<<<<", i+1);
                printf("\n\n\tPrioridade é da Fila Emergencial");
                printf("\n\n\t->Código de Voo: %s", q->codigoVoo);
                printf("\n\n\t->Voo de emergência.");
                printf("\n\n\t->Número de passageiros: %d \n\n", q->passageiros);
                E->ini = q->prox;
            } else if (!VaziaFila(C)){
                q = C->ini;
                printf("\n\n\t >>>>>%d° Voo<<<<<", i+1);
                printf("\n\n\t->Código de Voo: %s", q->codigoVoo);
                if(q->checkHora == 0){
                printf("\n\n\t->Voo Atrasado");
                }else {
                printf("\n\n\t->Voo no Horário");
                }
                printf("\n\n\t->Número de passageiros: %d\n\n", q->passageiros);
                C->ini = q->prox;

            } else if(VaziaFila(E) && VaziaFila(C)){
                printf("\n\n\t~~~~Não existem tantos voos para esse intervalo de simulação.~~~~\n\n");
                return;
            }

        }
    } else{
        printf("\n\n\tIntervalo muito pequeno!\n\n");
    }
}
int main(){
    int seed = 0;
    int op;
    int n = 0;
    Fila *Chegadas = CriaFila();
    Fila *Emergencia = CriaFila();
    Fila *Pousados = CriaFila();

    setlocale(LC_ALL,"portuguese");

    printf("\n\tInsira a seed desejada: ");
    scanf("%d", &seed);

    srand(seed);

    do{
    printf("\n\n----------------------------------------------------\n");
    printf("\n\t\t>>>>>Menu<<<<<");
    printf("\n\t[1]. Inserir ");
    printf("\n\t[2]. Autorizar ");
    printf("\n\t[3]. Relatório");
    printf("\n\t[4]. Proximo pouso ");
    printf("\n\t[5]. Fila de Voos pousados");
    printf("\n\t[6]. Simulação de Pouso");
    printf("\n\t[7]. Sair ");

    do{
    fflush(stdin);
    printf("\n\t\t ->Opção desejada:");
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
            printf("\n\tQuantos minutos você gostaria de simular? ");
            scanf("%d", &n);
            simulacaodeVoo(Chegadas, Emergencia, n);
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
