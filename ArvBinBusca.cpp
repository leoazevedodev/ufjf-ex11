#include <iostream>
#include "ArvBinBusca.h"

using namespace std;

ArvBinBusca::ArvBinBusca()
{
    raiz = NULL;
}

bool ArvBinBusca::vazia()
{
    return raiz == NULL;
}

void ArvBinBusca::insere(int val)
{
    raiz = auxInsere(raiz, val);
}

NoArv* ArvBinBusca::auxInsere(NoArv *p, int val)
{
    if(p == NULL)
    {
        p = new NoArv();
        p->setInfo(val);
        p->setEsq(NULL);
        p->setDir(NULL);
    }
    else if(val < p->getInfo())
        p->setEsq(auxInsere(p->getEsq(), val));
    else
        p->setDir(auxInsere(p->getDir(), val));
    return p;
}

bool ArvBinBusca::busca(int val)
{
    return auxBusca(raiz, val);
}

bool ArvBinBusca::auxBusca(NoArv *p, int val)
{
    if(p == NULL)
        return false;
    else if(p->getInfo() == val)
        return true;
    else if(val < p->getInfo())
        return auxBusca(p->getEsq(), val);
    else
        return auxBusca(p->getDir(), val);
}

void ArvBinBusca::remove(int val)
{
    raiz = auxRemove(raiz, val);
}

NoArv* ArvBinBusca::auxRemove(NoArv *p, int val)
{
    if(p == NULL)
        return NULL;
    else if(val < p->getInfo())
        p->setEsq(auxRemove(p->getEsq(), val));
    else if(val > p->getInfo())
        p->setDir(auxRemove(p->getDir(), val));
    else
    {
        if(p->getEsq() == NULL && p->getDir() == NULL)
            p = removeFolha(p);
        else if((p->getEsq() == NULL) || (p->getDir() == NULL))
            p = remove1Filho(p);
        else
        {
            //NoArv *aux = menorSubArvDireita(p);
            NoArv *aux = maiorSubArvEsquerda(p);
            int tmp = aux->getInfo();
            p->setInfo(tmp);
            aux->setInfo(val);
            //p->setDir(auxRemove(p->getDir(), val));
            p->setEsq(auxRemove(p->getEsq(), val));
        }
    }
    return p;
}

NoArv* ArvBinBusca::removeFolha(NoArv *p)
{
    delete p;
    return NULL;
}

NoArv* ArvBinBusca::remove1Filho(NoArv *p)
{
    NoArv *aux;
    if(p->getEsq() == NULL)
        aux = p->getDir();
    else
        aux = p->getEsq();
    delete p;
    return aux;
}

NoArv* ArvBinBusca::menorSubArvDireita(NoArv *p)
{
    NoArv *aux = p->getDir();
    while(aux->getEsq() != NULL)
        aux = aux->getEsq();
    return aux;
}

NoArv* ArvBinBusca::maiorSubArvEsquerda(NoArv *p)
{
    NoArv *aux = p->getEsq();
    while(aux->getDir() != NULL)
        aux = aux->getDir();
    return aux;
}

void ArvBinBusca::imprime()
{
    imprimePorNivel(raiz, 0);
}

void ArvBinBusca::imprimePorNivel(NoArv *p, int nivel)
{
    if(p != NULL)
    {
        cout << "(" << nivel << ")";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        cout << p->getInfo() << endl;
        imprimePorNivel(p->getEsq(), nivel+1);
        imprimePorNivel(p->getDir(), nivel+1);
    }
}

ArvBinBusca::~ArvBinBusca()
{
    raiz = libera(raiz);
}

NoArv* ArvBinBusca::libera(NoArv *p)
{
    if(p != NULL)
    {
        p->setEsq(libera(p->getEsq()));
        p->setDir(libera(p->getDir()));
        delete p;
        p = NULL;
    }
    return p;
}

float ArvBinBusca::mediaCaminho(int ch)
{
    int soma = 0, cont = 0;
    NoArv *p = raiz;
    while(p != NULL)
    {
        cont++;
        soma += p->getInfo();
        if(ch == p->getInfo())
            break;
        else if(ch > p->getInfo())
            p = p->getDir();
        else
            p = p->getEsq();
    }
    return (float)soma/cont;
}

int ArvBinBusca::maior()
{
    if(raiz == NULL)
        return -1;
    else
        return auxMaior(raiz);
}
int ArvBinBusca::auxMaior(NoArv *p)
{
    if(p->getDir() == NULL)
        return p->getInfo();
    else
        return auxMaior(p->getDir());
}

int ArvBinBusca::menor()
{
    if(raiz == NULL)
        return -1;
    else
        return auxMenor(raiz);
}
int ArvBinBusca::auxMenor(NoArv *p)
{
    if(p->getEsq() == NULL)
        return p->getInfo();
    else
        return auxMenor(p->getEsq());
}

void ArvBinBusca::removeMaior()
{
    auxRemoveMaior(raiz);
}
NoArv * ArvBinBusca::auxRemoveMaior(NoArv *p)
{
    if(p != NULL)
    {
        if(p->getDir() == NULL)
        {
            NoArv *r = p->getEsq();
            delete p;
            return r;
        }
        p->setDir(auxRemoveMaior(p->getDir()));
        return p;
    }
}

void ArvBinBusca::removeMenor()
{
    auxRemoveMenor(raiz);
}
NoArv * ArvBinBusca::auxRemoveMenor(NoArv *p)
{
    if(p != NULL)
    {
        if(p->getEsq() == NULL)
        {
            NoArv *r = p->getDir();
            delete p;
            return r;
        }
        p->setEsq(auxRemoveMenor(p->getEsq()));
        return p;
    }
}

int ArvBinBusca::contaParesCaminho(int x)
{
    int pares = 0;
    auxContaParesCaminho(raiz, &pares, x);
    return pares;
}
void ArvBinBusca::auxContaParesCaminho(NoArv *p, int *pares, int x)
{
    if(p != NULL)
    {
        if(p->getInfo() == x)
        {
            if(p->getInfo() % 2 == 0)
            {
                *pares = *pares + 1;
            }
        }
        else if(x > p->getInfo())
        {
            if(p->getInfo() % 2 == 0)
            {
                *pares = *pares + 1;
            }
            auxContaParesCaminho(p->getDir(), pares, x);
        }
        else if(x < p->getInfo())
        {
            if(p->getInfo() % 2 == 0)
            {
                *pares = *pares + 1;
            }
            auxContaParesCaminho(p->getEsq(), pares, x);
        }
    }
}

void ArvBinBusca::imprimeMaioresVal(int val)
{
    auxImprimeMaioresVal(raiz, val);
}
void ArvBinBusca::auxImprimeMaioresVal(NoArv *p, int val)
{
    if(p != NULL)
    {
        if(p->getInfo() > val)
        {
            auxImprimeMaioresVal(p->getEsq(), val);
            cout << p->getInfo() << " ";
            auxImprimeMaioresVal(p->getDir(), val);
        }
        else
        {
            auxImprimeMaioresVal(p->getDir(), val);
        }
    }
}

void ArvBinBusca::imprimeMenoresVal(int val)
{
    auxImprimeMenoresVal(raiz, val);
}
void ArvBinBusca::auxImprimeMenoresVal(NoArv *p, int val)
{
    if(p != NULL)
    {
        if(p->getInfo() < val)
        {
            auxImprimeMenoresVal(p->getEsq(), val);
            cout << p->getInfo() << " ";
            auxImprimeMenoresVal(p->getDir(), val);
        }
        else
        {
            auxImprimeMenoresVal(p->getEsq(), val);
        }
    }
}

void ArvBinBusca::alocaVetor(int a, int b)
{
    int nos = 0;
    int i = 0;
    auxContaNos(raiz, &nos);
    int *vet = new int[nos];
    auxAlocaVetor(raiz, vet, &i, a , b);
    for(int i = 0; i < nos; i++)
    {
        cout << vet[i] << " ";
    }
    delete [] vet;
}
void ArvBinBusca::auxAlocaVetor(NoArv *p, int *vet, int *i, int a, int b)
{
    if(p != NULL)
    {
        if(p->getInfo() >=a && p->getInfo() <= b)
        {
            auxAlocaVetor(p->getEsq(), vet, i, a, b);
            vet[*i] = p->getInfo();
            *i = *i + 1;
            auxAlocaVetor(p->getDir(), vet, i, a, b);
        }
        else if(p->getInfo() < a)
        {
            auxAlocaVetor(p->getDir(), vet, i, a , b);
        }
        else
        {
            auxAlocaVetor(p->getEsq(), vet, i, a , b);
        }
    }
}
void ArvBinBusca::auxContaNos(NoArv *p, int *nos)
{
    if(p != NULL)
    {
        *nos = *nos + 1;
        auxContaNos(p->getDir(), nos);
        auxContaNos(p->getEsq(), nos);
    }
}

void ArvBinBusca::nosParesImpares(int chave)
{
    int impares = 0;
    int pares = 0;
    auxNosParesImpares(&impares, &pares, chave);
    cout << "A quantidade de valores pares da arvore e: " << pares << endl;
    cout << "A quantidade de valores impares da arvore e: " << impares << endl;
}
void ArvBinBusca::auxNosParesImpares(int *impares, int *pares, int chave)
{
    NoArv *p = raiz;

    while(p != NULL)
    {
        if(p->getInfo() % 2 == 0)
            *pares = *pares + 1;
        else
            *impares = *impares + 1;

        if(chave == p->getInfo())

        if(chave < p->getInfo())
            p = p->getEsq();
        else
            p = p->getDir();
    }
}

void ArvBinBusca::imprimeFilhos(int val)
{
    auxImprimeFilhos(raiz, val);
}
void ArvBinBusca::auxImprimeFilhos(NoArv *p, int val)
{
    if(p != NULL)
    {
        if(p->getInfo() == val)
        {

        }
        else
        {
            auxImprimeFilhos(p->getEsq(), val);
            auxImprimeFilhos(p->getDir(), val);
        }
    }
}
