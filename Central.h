#ifndef CENTRAL_H_INCLUDED
#define CENTRAL_H_INCLUDED

//Funções para a manipulação de filas

//Fila * CriaFila()

//int VaziaFila (Fila* f) VERIFICA SE A FILA ESTÁ VAIZA

//void InsereFila (Fila* f, int v) INSERÇÃO

//int RetiraFila (Fila* f) REMOÇÃO

//Fila* liberaFila (Fila* f) LIBERA A FILA

//void imprimeFila (Fila* f)IMPRIME A FILA

typedef struct DadosVoo//dados do voo
{
    int passageiros;
    int checkHora;
    char codigoVoo[4];
}Voo;

typedef struct no//struct que armazena os elementos da fila
{
    Voo info;
    struct No *prox;
}Nos;

typedef struct fila//cria a TAD
{
    Nos *ini;
    Nos *fim;
}Fila;

Fila* CriaFila ()
{
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->ini = f->fim = NULL;
    return f;
}

Nos* ins_fim (Nos *fim, Voo A)
{
    Nos *p = (Nos*)malloc(sizeof(Nos));
    p->info = A;
    p->prox = NULL;
    if (fim != NULL) /* verifica se lista não estava vazia */
    fim->prox = p;
    return p;
}

void InsereFila (Fila* f, int v)
{
    f->fim = ins_fim(f->fim,v);
    if (f->ini==NULL) /* fila antes vazia? */
    f->ini = f->fim;
}

Nos* retira_ini (Nos* ini)
{
    Nos* p = ini->prox;
    free(ini);
    return p;
}

int RetiraFila (Fila* f)
{
    int v;
    if (VaziaFila(f))
    {
        printf("Fila vazia.\n");
        exit(0); /* aborta programa */
    }
    v = f->ini->info;
    f->ini = retira_ini(f->ini);
    if (f->ini == NULL) /* fila ficou vazia? */
    f->fim = NULL;
    return v;
}

void imprimeFila (Fila* f)
{
    Nos* q;
    printf("\n\t\t");
    for (q=f->ini; q!=NULL; q=q->prox)
    {
        printf("%d - ",q->info);
    }
    printf("\n");
}


Fila* liberaFila (Fila* f)
{
    Nos* q = f->ini;
    while (q!=NULL)
    {
        Nos* t = q->prox;
        free(q);
        q = t;
    }
    free(f);
    return NULL;
}

#endif // CENTRAL_H_INCLUDED
