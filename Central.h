#ifndef CENTRAL_H_INCLUDED
#define CENTRAL_H_INCLUDED

//Funções para a manipulação de filas

//Fila * CriaFila()

//int VaziaFila (Fila* f) VERIFICA SE A FILA ESTÁ VAIZA

//void InsereFila (Fila* f, int v) INSERÇÃO

//int RetiraFila (Fila* f) REMOÇÃO

//Fila* liberaFila (Fila* f) LIBERA A FILA

//void imprimeFila (Fila* f)IMPRIME A FILA

typedef struct horas
{
    int hora;
    int minuto;
}Horas;

typedef struct DadosVoo//dados do voo
{
    int passageiros;
    int checkHora;
    char codigoVoo[4];
    Horas hora;
    struct DadosVoo *prox;
}Voo;

typedef struct fila//cria a TAD
{
    Voo *ini;
    Voo *fim;
}Fila;

int VaziaFila (Fila* f)
{
    if (f->ini==NULL) return 1;
    return 0;

}

Fila* CriaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

Voo* ins_fim (Voo *fim, int p_aux, int c_aux, Horas h_aux, char *cod_aux)
{
    Voo *p = (Voo*)malloc(sizeof(Voo));
    p->passageiros = p_aux;
    p->checkHora = c_aux;
    p->hora.hora = h_aux.hora;
    p->hora.minuto = h_aux.minuto;
    strcpy(p->codigoVoo, cod_aux);
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista não estava vazia */
    fim->prox = p;
    return p;
}

void InsereFila (Fila* f, int pessoas, int atraso, Horas h, char *cod)
{
    f->fim = ins_fim(f->fim, pessoas, atraso, h, cod);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

Voo* retira_ini (Voo* ini)
{
    Voo* p = ini->prox;
    free(ini);
    return p;
}

Voo* RetiraFila (Fila* f)
{
    Voo *v;
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    v = f->ini;
    f->ini = retira_ini(f->ini);
    if (f->ini == NULL) /* fila ficou vazia? */
    f->fim = NULL;
    return v;
}

void imprimeFila (Fila* f)
{
    Voo* q;
    printf("\n\t\t");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        printf("\npas: %d - ",q->passageiros);
        printf("\nchek: %d - ",q->checkHora);
        printf("\ncod: %s - ",q->codigoVoo);
        printf("\ntempo: %d:%d - ",q->hora.hora, q->hora.minuto);
    }
    printf("\n");
}

Fila* liberaFila (Fila* f)
{
    Voo* q = f->ini;
    while (q!=NULL)
    {
        Voo* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}

Horas HoraRandon (int s)
{
    Horas aux;
    int h, minu;
    for(int i = 0; i<s;i++){
    h = rand()%24;
    minu = rand()%60;
    }

    aux.hora = h;
    aux.minuto = minu;

    return aux;
}

#endif // CENTRAL_H_INCLUDED
