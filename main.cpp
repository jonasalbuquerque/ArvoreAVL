#include "avl.hpp"

int main()
{
    struct DicAVL d;
    inicializar(d);
    Noh* n;
    inserir(d,5,1);
    inserir(d,6,1);
    inserir(d,4,1);
    inserir(d,3,1);
    inserir(d,2,1);
    //inserir(d,9,1);
    n=procurar(d,2);
    cout << "Raiz MASTER: "<< d.raiz->chave << endl;
    cout << "Altura do procurado: "<<n << endl;
    //cout << n->esq->chave << n->dir->chave << endl;
    return 0;
}
