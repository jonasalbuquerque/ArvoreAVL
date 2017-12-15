#include "avl.hpp"

void inicializar (DicAVL &D){
    D.raiz = NULL;
}
int get_altura(Noh *n){
    if (n==NULL)
        return 0;
    else
        return n->h;
}
int fatorBalanceamento(Noh *n){
    return abs(get_altura(n->esq) - get_altura(n->dir));
}
int maior(int a, int b){
    if(a > b) return a;
    else return b;
}

void RotacaoLL(DicAVL &D){
    //cout << "ROTACAO LL NO "<<D.raiz->chave << endl;
    Noh *raiz = D.raiz;
    Noh *no = new(std::nothrow) Noh;
    no = raiz->esq;
    raiz->esq = no->dir;
    if (raiz->pai!=NULL){
        if (no->esq!=NULL){
            if(raiz->pai->dir==raiz)
                raiz->pai->dir = no;//6
            else
                raiz->pai->esq = no;//CASO 2
        }
        else
            raiz->pai->dir = no;//caso 1
    }
    no->dir = raiz;
    no->pai = raiz->pai;
    raiz->pai = no;
    raiz->h = maior(get_altura(raiz->esq), get_altura(raiz->dir)) + 1;
    no->h = maior(get_altura(no->esq), raiz->h) + 1;
    if(D.raiz->chave == raiz->chave){
        D.raiz=no;
    }
    raiz = no;
}
void RotacaoRR(DicAVL &D){
    //cout << "ROTACAO RR NO "<< D.raiz->chave <<endl;
    Noh *raiz = D.raiz;
    Noh *no = new(std::nothrow) Noh;
    no = raiz->dir;
    raiz->dir = no->esq;
    no->esq = raiz;
    if (raiz->pai!=NULL){
        if (no->dir!=NULL){
            if (raiz->pai->esq==raiz)
                raiz->pai->esq=no;//5
            else
                raiz->pai->dir = no;//4
        }
        else
            raiz->pai->esq = no;//3
    }
    no->pai=raiz->pai;
    raiz->pai = no;
    raiz->h = maior(get_altura(raiz->esq), get_altura(raiz->dir)) + 1;
    no->h = maior(get_altura(no->dir), get_altura(raiz)) + 1;
    cout << "ANTES : " << raiz->chave << endl;
    if(D.raiz->chave == raiz->chave){
        D.raiz=no;
    }
    raiz = no;
    /*cout << "DEPOIS : " << raiz->chave << endl;
    cout << "RAIZ_temporaria" << raiz->chave << endl;
    //cout << "ESQ: " << raiz->esq->chave << " DIR: " << raiz->dir->chave << endl;
    cout << "ESQ: " << raiz->esq->chave << " DIR: " << raiz->dir << endl;
    //cout << "ESQ_PAI: " << raiz->esq->pai->chave << " DIR_PAI: " << raiz->dir->pai->chave << endl;
    cout << "Raiz_PAI_esq: " << raiz->pai->esq->chave <<endl;*/
}
void RotacaoLR(DicAVL &D){
    DicAVL di = D;
    di.raiz = D.raiz->esq;
    RotacaoRR(di);
    RotacaoLL(D);
}
void RotacaoRL(DicAVL &D){
    DicAVL di = D;
    di.raiz = D.raiz->dir;
    RotacaoLL(di);
    RotacaoRR(D);
}

int balancear(DicAVL &D,TC c){
    if (D.raiz->chave == c){
        return 1;
    }
    int res;
    DicAVL di = D;
    if (c < D.raiz->chave){
        di.raiz = D.raiz->esq;
        if ((res=balancear(di, c))==1) {
            if(fatorBalanceamento(D.raiz)>=2){
                if (c < D.raiz->esq->chave){
                    RotacaoLL(D);
                }
                else
                    RotacaoLR(D);
            }
        }
    }else {
        di.raiz = D.raiz->dir;
        if ((res=balancear(di, c))==1) {
            if(fatorBalanceamento(D.raiz)>=2){
                if (c > D.raiz->dir->chave){
                    RotacaoRR(D);
                }
                else
                    RotacaoRL(D);
            }
        }
    }
    D.raiz->h = maior(get_altura(D.raiz->esq), get_altura(D.raiz->dir)) + 1;
    return res;
}

Noh* inserir (DicAVL &D, TC c, TV v){
    Noh *n = new(std::nothrow) Noh;
    if (n == NULL){
        cout << "Erro de alocacao!" << endl;
        return n;
    }
    n->chave = c;
    n->valor = v;
    n->h = 1;
    n->esq = n->dir = NULL;
    if (D.raiz == NULL){
        D.raiz = n;
        n->pai = NULL;
        return n;
    }
    Noh *p = D.raiz;
    for (;;){
        if (c < p->chave){
            if (p->esq == NULL){
                p->esq = n;
                n->pai = p;
                break;
            }else
                p = p->esq;
        }
        else if (c > p->chave){
            if (p->dir == NULL){
                p->dir = n;
                n->pai = p;
                break;
            }
            else
                p = p->dir;
        }else{
            cout << "ERRO! VALOR DUPLICADO!" << endl;
            return NULL;
        }
    }
    balancear(D,n->chave);
    return n;
}

Noh* procurar (DicAVL &D, TC c){
    if (D.raiz == NULL){
        return D.raiz;
    }
    Noh *p = D.raiz;
    while (p != NULL){
        if(c==p->chave)
            return p;
        else if (c > p->chave){
            p=p->dir;
        }
        else{
            p=p->esq;
        }
    }
    return NULL;
}
Noh* procuraMenor(Noh *p){
    Noh *n1 = p;
    Noh *n2 = p->esq;
    while (n2!=NULL){
        n1=n2;
        n2=n2->esq;
    }
    return n1;
}

int remove_AVL(DicAVL &D,TC c){
    if (D.raiz==NULL)
        return 0;
    int res;
    DicAVL di = D;
    if (c < D.raiz->chave){
        di.raiz=D.raiz->esq;
        if ((res=remove_AVL(di, c))==1) {
            if(fatorBalanceamento(D.raiz)>=2){
                if (get_altura(D.raiz->dir->esq)<=get_altura(D.raiz->dir->dir)){
                    RotacaoRR(D);
                }
                else
                    RotacaoRL(D);
            }
        }
    }else if (c > D.raiz->chave) {
        di.raiz=D.raiz->dir;
        if ((res=remove_AVL(di, c))==1) {
            if(fatorBalanceamento(D.raiz)>=2){
                if (get_altura(D.raiz->esq->dir) <= get_altura(D.raiz->esq->esq))
                    RotacaoLL(D);
                else
                    RotacaoLR(D);
            }
        }
    }else if (c == D.raiz->chave){
        if ((D.raiz->esq==NULL) || (D.raiz->dir==NULL)){
            Noh *old = D.raiz;
            if (D.raiz->esq!=NULL){
                if (D.raiz->pai!=NULL){
                    if (D.raiz->pai->esq==D.raiz)
                        D.raiz->pai->esq = D.raiz->esq;
                    else
                        D.raiz->pai->dir = D.raiz->esq;
                }
                D.raiz->esq->pai = D.raiz->pai;
                D.raiz=D.raiz->esq;
            }
            else{
                if (D.raiz->pai!=NULL)
                    if (D.raiz->pai->esq==D.raiz)
                        D.raiz->pai->esq = D.raiz->dir;
                    else
                        D.raiz->pai->dir = D.raiz->dir;
                if (D.raiz->dir!=NULL)
                    D.raiz->dir->pai = D.raiz->pai;
                D.raiz=D.raiz->dir;
            }
            free(old);
        }else{//2 filhos
            Noh *temp = procuraMenor(D.raiz->dir);
            D.raiz->chave = temp->chave;
            di.raiz=D.raiz->dir;
            remove_AVL(di,D.raiz->chave);
            if(fatorBalanceamento(D.raiz)>=2){
                if (get_altura(D.raiz->esq->dir) <= get_altura(D.raiz->esq->esq))
                    RotacaoLL(D);
                else
                    RotacaoLR(D);
            }
        }
        return 1;
    }
    return res;
}

void remover(DicAVL &D, Noh *n){
    if(D.raiz==NULL){
        cout << "Valor não existe!" <<endl;
        return;
    }else
        remove_AVL(D, n->chave);
}

void libera_no(Noh *n){
    if (n==NULL)
        return;
    libera_no(n->esq);
    libera_no(n->dir);
    free(n);
    n=NULL;
}
void terminar (DicAVL &D){
    if (D.raiz==NULL)
        return;
    libera_no(D.raiz);
    free(D.raiz);
}
