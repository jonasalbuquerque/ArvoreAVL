#include "avl.hpp"

int main()
{
    struct DicAVL d;
    inicializar(d);
    Noh* n;
    inserir(d,14,1);
    inserir(d,12,1);
    inserir(d,17,1);
    inserir(d,11,1);
    inserir(d,13,1);
    inserir(d,16,1);
    inserir(d,19,1);
    n=procurar(d,16);
    cout << "Altura do procurado: "<<n->h << endl;
    n=procurar(d,14);
    cout << "Altura do procurado: "<<n->h << endl;
    remover(d,n);
    n=procurar(d,12);
    cout << "Altura do procurado: "<<n->h << endl;
    n=procurar(d,17);
    cout << "Altura do procurado: "<<n->h << endl;
    n=procurar(d,16);
    cout << "Raiz MASTER: "<< d.raiz->chave << endl;
    cout << "ESQ_RM: " << d.raiz->esq->chave << " DIR_RM: " << d.raiz->dir->chave << endl;
    cout << "Altura do procurado: "<<n->h << n->chave << endl;
    //cout << n->esq->chave << n->dir->chave << endl;
    //cout << n->pai->chave;
    return 0;
}
