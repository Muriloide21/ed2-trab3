#include <stdio.h>
#include <stdlib.h>
#include "rbt.h"

// STRUCT DO NÓ
struct node {
    Key key;
    Value val;
    bool color;
    RBT *l, *r;
};

// CRIA UMA ÁRVORE VAZIA
RBT* RBT_CREATE () {
    return NULL;
}

// DESTROI A ÁRVORE
void RBT_DESTROY (RBT *h) {
    if (h != NULL) {
        RBT_DESTROY (h->l);
        RBT_DESTROY (h->r);
        free(h);
    }
}

// VERIFICA O TAMANHO DA ÁRVORE
int RBT_HEIGHT (RBT *h) {
    if (h == NULL) {
        return -1;
    }
    int lh = RBT_HEIGHT (h->l);
    int rh = RBT_HEIGHT (h->r);
    if (lh > rh) {
        return lh + 1;
    } else {
        return rh + 1;
    }
}

// CRIA UM NÓ
RBT* CREATE_NODE (Key key, Value val, bool color) {
    RBT *h = malloc(sizeof *h);
    h->key = key;
    h->color = color;
    h->l = h->r = NULL;
    return h;
}

// VERIFICA SE A ARESTA QUE LIGA DOIS NÓS É VERMELHA
bool IS_RED (RBT *x) {
  if (x == NULL) return BLACK;
  return x->color;
}

// FAZ ROTAÇÃO PELA DIREITA
RBT* ROTATE_RIGHT (RBT *h) {
    RBT *x = h->l;
    h->l = x->r;
    x->r = h;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

// FAZ ROTAÇÃO PELA ESQUERDA
RBT* ROTATE_LEFT (RBT *h) {
    RBT *x = h->r;
    h->r = x->l;
    x->l = h;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

// FAZ UM FLIP COM AS CORES
void FLIP_COLORS (RBT *h) {
    h->color = RED;
    h->l->color = BLACK;
    h->r->color = BLACK;
}

// INSERE UM NÓ NA ÁRVORE
RBT* RBT_INSERT (RBT *h, Key key, Value val) {
  if (h == NULL) { return CREATE_NODE (key, val, RED); }

  int cmp = COMPARE (key, h->key);
  if      (cmp < 0) { h->l = RBT_INSERT (h->l, key, val); }
  else if (cmp > 0) { h->r = RBT_INSERT (h->r, key, val); }
  else              { h->val = val; }


  if (IS_RED (h->r) && !IS_RED (h->l))    { h = ROTATE_LEFT (h); }

  if (IS_RED (h->l) &&  IS_RED (h->l->l)) { h = ROTATE_RIGHT (h); }

  if (IS_RED (h->l) &&  IS_RED (h->r))    { FLIP_COLORS (h); }

  return h;
}

// RETORNA O VALOR DE UMA KEY PASSADA
Value SEARCH (RBT *n, Key key) {
  while (n != NULL) {
    int cmp;
    cmp = COMPARE (key, n->key);
    if      (cmp < 0) n = n->l;
    else if (cmp > 0) n = n->r;
    else         return n->val;
  }
  return NULL_Value;
}
