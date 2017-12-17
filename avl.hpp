#ifndef AVL_HPP_INCLUDED
#define AVL_HPP_INCLUDED
#include <iostream>
#include <new>
#include <stdlib.h>
using namespace std;

typedef double TC;
typedef float TV;

struct Noh { TC chave; TV valor; Noh *esq, *dir, *pai; int h; };

struct DicAVL { Noh *raiz; };

void inicializar (DicAVL &D); // Inicializa D como uma arvore vazia.

void RotacaoLL(DicAVL &D);
void RotacaoRR(DicAVL &D);
void RotacaoLR(DicAVL &D);
void RotacaoRL(DicAVL &D);
int maior(int a, int b);
int get_altura(Noh *n);
int fatorBalanceamento(Noh *n);
int balancear(DicAVL &D,TC c);
Noh* procuraMenor(Noh *p);
int remove_AVL(DicAVL &D,TC c);
int remove_AVL2(DicAVL &D,TC c);
void libera_no(Noh *n);

Noh* inserir (DicAVL &D, TC c, TV v); // Retorna um ponteiro para o novo nó, ou nulo se erro de alocacao
Noh* procurar (DicAVL &D, TC c); // Retorna um ponteiro para o nó da chave procurada, ou nulo se a chave não estiver em D.
void remover (DicAVL &D, Noh *n); // 'n' aponta para o nó a ser removido
void terminar (DicAVL &D); // Desaloca os nós da arvore.


#endif // AVL_HPP_INCLUDED
