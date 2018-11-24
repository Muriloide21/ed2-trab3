#ifndef RBT_H
#define RBT_H

#include <stdbool.h>

typedef int Key;
typedef int Value;

#define NULL_Key   -1
#define NULL_Value -1

#define COMPARE(A, B) (A - B)

#define RED     true
#define BLACK   false

// STRUCT DO NÓ
typedef struct node RBT;

// CRIA UMA ÁRVORE VAZIA
RBT* RBT_CREATE ();

// DESTROI A ÁRVORE
void RBT_DESTROY (RBT*);

// VERIFICA O TAMANHO DA ÁRVORE
int RBT_HEIGHT (RBT*);

// CRIA UM NÓ
RBT* CREATE_NODE (Key key, Value val, bool color);

// VERIFICA SE A ARESTA QUE LIGA DOIS NÓS É VERMELHA
bool IS_RED (RBT *x);

// FAZ ROTAÇÃO PELA DIREITA
RBT* ROTATE_RIGHT (RBT *h);

// FAZ ROTAÇÃO PELA ESQUERDA
RBT* ROTATE_LEFT (RBT *h);

// FAZ UM FLIP COM AS CORES
void FLIP_COLORS (RBT *h);

// INSERE UM NÓ NA ÁRVORE
RBT* RBT_INSERT (RBT*, Key, Value);

// RETORNA O VALOR DE UMA KEY PASSADA
Value SEARCH (RBT *n, Key key);

#endif
