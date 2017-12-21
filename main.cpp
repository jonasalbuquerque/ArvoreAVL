#include "avl.hpp"

int main()
{
    struct DicAVL d;
    inicializar(d);
    Noh* n;
    n=inserir(d,3,1);
    remover(d,n);
    cout << d.raiz;
    return 0;
}
