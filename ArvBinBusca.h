#ifndef ARVBINBUSCA_H_INCLUDED
#define ARVBINBUSCA_H_INCLUDED
#include "NoArv.h"

class ArvBinBusca
{
public:
    ArvBinBusca();
    ~ArvBinBusca();
    bool vazia(); // verifica se a árvore está vazia
    bool busca(int val);
    void insere(int val);
    void remove(int val);
    void imprime();
    float mediaCaminho(int ch);
    int maior();
    int menor();
    void removeMaior();
    void removeMenor();
    int contaParesCaminho(int x);
    void imprimeMaioresVal(int val);
    void imprimeMenoresVal(int val);
    void alocaVetor(int a, int b);
    void nosParesImpares(int chave);
    void imprimeFilhos(int val);

private:
    NoArv* raiz; // ponteiro para o No raiz da árvore
    bool auxBusca(NoArv *p, int val);
    NoArv* auxInsere(NoArv *p, int val);
    NoArv* auxRemove(NoArv *p, int val);
    NoArv* menorSubArvDireita(NoArv *p);
    NoArv* maiorSubArvEsquerda(NoArv *p);
    NoArv* removeFolha(NoArv *p);
    NoArv* remove1Filho(NoArv *p);
    void imprimePorNivel(NoArv* p, int nivel);
    NoArv* libera(NoArv *p);
    int auxMaior(NoArv *p);
    int auxMenor(NoArv *P);
    NoArv* auxRemoveMaior(NoArv *p);
    NoArv* auxRemoveMenor(NoArv *p);
    void auxContaParesCaminho(NoArv *p, int *pares, int x);
    void auxImprimeMaioresVal(NoArv *p, int val);
    void auxImprimeMenoresVal(NoArv *p, int val);
    void auxAlocaVetor(NoArv *p, int *vet, int *i, int a, int b);
    void auxContaNos(NoArv *p, int *nos);
    void auxNosParesImpares(int *impares, int *pares, int chave);
    void auxImprimeFilhos(NoArv *p, int val);
};

#endif // ARVBINBUSCA_H_INCLUDED
