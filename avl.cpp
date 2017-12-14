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

void RotacaoLL(DicAVL &D,Noh *raiz){
    cout << "ROTACAO LL NO "<<raiz->chave << endl;
    Noh *no = new(std::nothrow) Noh;
    no = raiz->esq;
    raiz->esq = no->dir;
    no->dir = raiz;
    no->pai = raiz->pai;
    raiz->pai = no;
    raiz->h = maior(get_altura(raiz->esq), get_altura(raiz->dir)) + 1;
    no->h = maior(get_altura(no->esq), raiz->h) + 1;
    cout << "ANTES : " << D.raiz->chave << endl;
    if(D.raiz->chave == raiz->chave){
        D.raiz=no;
    }
    raiz = no;
    cout << "DEPOIS : " << D.raiz->esq->chave << endl;
    cout << "Chegou aqui oh " << raiz->chave <<endl;
    cout << "ESQ: " << raiz->esq->chave << " DIR: " << raiz->dir->chave << endl;
    cout << "ESQ_PAI: " << raiz->esq->pai->chave << " DIR_PAI: " << raiz->dir->pai->chave << endl;
}
void RotacaoRR(DicAVL &D,Noh *raiz){
    //Noh *raiz_MASTER=D.raiz;
    cout << "ANTES ANTES: " << D.raiz->chave << endl;
    cout << "ROTACAO RR NO "<<raiz->chave <<endl;
    Noh *no = new(std::nothrow) Noh;
    no = raiz->dir;
    raiz->dir = no->esq;
    no->esq = raiz;
    no->pai=raiz->pai;
    raiz->pai = no;
    if (D.raiz != raiz)
        raiz->pai->dir = no;
    raiz->h = maior(get_altura(raiz->esq), get_altura(raiz->dir)) + 1;
    no->h = maior(get_altura(no->dir), get_altura(raiz)) + 1;
    cout << "ANTES : " << D.raiz->chave << endl;
    if(D.raiz->chave == raiz->chave){
        D.raiz=no;
    }
    raiz = no;
    cout << "DEPOIS : " << D.raiz->chave << endl;
    cout << "RAIZ_temporaria" << raiz->chave <<endl;
    cout << "ESQ: " << raiz->esq->chave << " DIR: " <<raiz->dir->chave<< endl;
}
void RotacaoLR(DicAVL &D,Noh *raiz){
    RotacaoRR(D,raiz->esq);
    RotacaoLL(D,raiz);
}
void RotacaoRL(DicAVL &D,Noh *raiz){
    cout << "Chegou aqui RAIZ: " <<raiz->chave<< endl;
    RotacaoLL(D,raiz->dir);
    cout << "Chegou aqui RAIZ: " <<raiz->chave<< endl;
    RotacaoRR(D,raiz);
}

int balancear(DicAVL &D, Noh *raiz,TC c){
    if (raiz->chave == c){
        return 1;
    }
    int res;
    Noh *p = raiz;
    if (c < p->chave){
        if ((res=balancear(D,p->esq, c))==1) {
            if(fatorBalanceamento(p)>=2){
                if (c < raiz->esq->chave){
                    RotacaoLL(D,raiz);
                }
                else
                    RotacaoLR(D,raiz);
            }
        }
    }else {
        if ((res=balancear(D,p->dir, c))==1) {
            if(fatorBalanceamento(p)>=2){
                if (c > raiz->dir->chave){
                    RotacaoRR(D,raiz);
                }
                else
                    RotacaoRL(D,raiz);
            }
        }
    }
    //D.raiz = p;
    p->h = maior(get_altura(p->esq), get_altura(p->dir)) + 1;
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
    balancear(D,D.raiz,n->chave);
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
/*Noh* procuraMenor(Noh *p){
    Noh *n1 = p;
    Noh *n2 = p->esq;
    while (n2!=NULL){
        n1=n2;
        n2=n2->esq;
    }
    return n1;
}

int balancear_2(Noh *raiz,TC c){
    if (raiz==NULL){
        cout << "Valor não existe!" << endl;
        return 0;
    }
    int res;
    if (c < raiz->chave){
        if ((res=balancear_2(raiz->esq, c))==1) {
            if(fatorBalanceamento(raiz)>=2){
                if (get_altura(raiz->dir->esq)<=get_altura(raiz->dir->dir)){
                    RotacaoRR(raiz);
                }
                else
                    RotacaoRL(raiz);
            }
        }
    }else if (c>raiz->chave) {
        if ((res=balancear_2(raiz->dir, c))==1) {
            if(fatorBalanceamento(raiz)>=2){
                if (get_altura(raiz->esq->dir)<=get_altura(raiz->esq->esq)){
                    RotacaoLL(raiz);
                }
                else
                    RotacaoLR(raiz);
            }
        }
    }else if (c == raiz->chave){
        if ((raiz->esq==NULL) || (raiz-dir==NULL)){
            Noh *old = raiz;
            if (raiz->esq!=NULL)
                raiz=raiz-esq;
            else
                raiz=raiz->dir;
            delete old;
        }else{
            Noh *temp = procuraMenor(raiz->dir);
            raiz->chave = temp->chave;
            balancear_2(raiz->dir,raiz->chave);
            if(fatorBalanceamento(raiz)>=2){
                if (get_altura(raiz->esq->dir)<=get_altura(raiz->esq->esq)
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
        }
        return 1;
    }
    return res;
}

void remover(DicAVL &D, Noh *n){
    if(D.raiz==NULL){
        return;
    }
    balancear_2(D.raiz, n->chave);
}*/
int balancear_2(Noh *raiz,TC c){}
Noh* procuraMenor(Noh *p){}
void remover(DicAVL &D, Noh *n){
    /*if (D.raiz==NULL){
        cout << "Valor não existe!" << endl;
    }
    if(balancear_2(D.raiz,n))
        cout << "Sucesso na remoção." << endl;*/
}
void libera_no(Noh *n){
    if (n==NULL)
        return;
    libera_no(n->esq);
    libera_no(n->dir);
    delete n;
    n=NULL;
}
void terminar (DicAVL &D){
    if (D.raiz==NULL)
        return;
    libera_no(D.raiz);
    delete D.raiz;
}
