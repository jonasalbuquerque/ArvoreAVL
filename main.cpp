#include "avl.hpp"

int main()
{
    struct DicAVL d;
    inicializar(d);
    Noh* n;
    Noh* n1;
    inserir(d,204,-21);
    inserir(d,169.75,59.5);
    inserir(d,246.75,-60);
    inserir(d,-98.75, 53.5);
    inserir(d,-133.25,10.5);
    inserir(d,-13.5,25.5);
    inserir(d,-81,2.5);
    inserir(d,271.25,83);
    inserir(d,81.25,43);
    n=inserir(d,-215,21);
    remover(d,n);
    n=procurar(d,-133.25);
    remover(d,n);
    n=procurar(d,81.25);
    remover(d,n);
    n=procurar(d,271.25);
    remover(d,n);
    n1=procurar(d,246.75);
    cout << "CHAVE DO PROCURADO: " << n1->h<<endl;
    n=procurar(d,169.75);
    remover(d,n);
    cout << "CHAVE DO PROCURADO: " << n1->h<<endl;
    //n=procurar(d,-133.25);
    //remover(d,n);
    //n=procurar(d,-13.5);
    //remover(d,n);
    //n=procurar(d,271.25);
    //terminar(d);
    //cout << "Raiz MASTER: "<< d.raiz << endl;
    //cout << "Raiz MASTER: "<< d.raiz->chave << " ALTURA DA RAIZ: "<< d.raiz->h << endl;
    //cout << "ESQ_RM: " << d.raiz->esq->chave << " DIR_RM: " << d.raiz->dir->chave << endl;
    //cout << "CHAVE DO PROCURADO: " << n->esq->esq<<endl;
    //cout << "Altura do procurado: "<<n->h << " PAI DO PROCURADO: "<<n->pai->chave << endl;
    //cout << "FILHO ESQ PROCURADO: "<<n->esq->chave <<" FILHO DIR PROCURADO: "<< n->dir->chave << endl;
    //cout << "FILHO ESQ PROCURADO: "<<n->esq <<" FILHO DIR PROCURADO: "<< n->dir << endl;
    //cout << "PAI DO PROCURADO: "<<n->pai->chave<<endl;
    return 0;
}
