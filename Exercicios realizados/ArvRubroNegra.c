#include <stdio.h>
#include <stdlib.h>

#define VERMELHO 1
#define PRETO 0

struct No {
  int dado;
  int cor;
  struct No *esq, *dir, *pai;
};

struct No *criarNo(int dado) {
  struct No *novoNo = (struct No *)malloc(sizeof(struct No));
  novoNo->dado = dado;
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  novoNo->pai = NULL;
  novoNo->cor = VERMELHO;
  return novoNo;
}

void RE(struct No **raiz, struct No *x) {
  struct No *y = x->dir;
  x->dir = y->esq;
  if (y->esq != NULL)
    y->esq->pai = x;
  y->pai = x->pai;
  if (x->pai == NULL)
    *raiz = y;
  else if (x == x->pai->esq)
    x->pai->esq = y;
  else
    x->pai->dir = y;
  y->esq = x;
  x->pai = y;
}

void RD(struct No **raiz, struct No *y) {
  struct No *x = y->esq;
  y->esq = x->dir;
  if (x->dir != NULL)
    x->dir->pai = y;
  x->pai = y->pai;
  if (y->pai == NULL)
    *raiz = x;
  else if (y == y->pai->esq)
    y->pai->esq = x;
  else
    y->pai->dir = x;
  x->dir = y;
  y->pai = x;
}

void ajusteInsercao(struct No **raiz, struct No *z) {
  while (z != *raiz && z->pai->cor == VERMELHO) {
    if (z->pai == z->pai->pai->esq) {
      struct No *tio = z->pai->pai->dir;
      if (tio != NULL && tio->cor == VERMELHO) {
        z->pai->cor = PRETO;
        tio->cor = PRETO;
        z->pai->pai->cor = VERMELHO;
        z = z->pai->pai;
      } else {
        if (z == z->pai->dir) {
          z = z->pai;
          RE(raiz, z);
        }
        z->pai->cor = PRETO;
        z->pai->pai->cor = VERMELHO;
        RD(raiz, z->pai->pai);
      }
    } else {
      struct No *tio = z->pai->pai->esq;
      if (tio != NULL && tio->cor == VERMELHO) {
        z->pai->cor = PRETO;
        tio->cor = PRETO;
        z->pai->pai->cor = VERMELHO;
        z = z->pai->pai;
      } else {
        if (z == z->pai->esq) {
          z = z->pai;
          RD(raiz, z);
        }
        z->pai->cor = PRETO;
        z->pai->pai->cor = VERMELHO;
        RE(raiz, z->pai->pai);
      }
    }
  }
  (*raiz)->cor = PRETO;
}

void inserir(struct No **raiz, int dado) {
  struct No *novoNo = criarNo(dado);
  struct No *y = NULL;
  struct No *x = *raiz;

  while (x != NULL) {
    y = x;
    if (novoNo->dado < x->dado)
      x = x->esq;
    else
      x = x->dir;
  }

  novoNo->pai = y;
  if (y == NULL)
    *raiz = novoNo;
  else if (novoNo->dado < y->dado)
    y->esq = novoNo;
  else
    y->dir = novoNo;

  ajusteInsercao(raiz, novoNo);
}

void imprimirArvore(struct No *raiz, int espaco) {
  if (raiz == NULL)
    return;

  espaco += 5;

  imprimirArvore(raiz->dir, espaco);

  printf("\n");
  for (int i = 5; i < espaco; i++)
    printf(" ");
  printf("%d(%s)\n", raiz->dado, raiz->cor == VERMELHO ? "R" : "P");

  imprimirArvore(raiz->esq, espaco);
}

int main() {
  struct No *raiz = NULL;
  int N = 8, dados[8] = {50, 100, 30, 20, 40, 45, 35, 37};

  for (int i = 0; i < N; i++) {
    inserir(&raiz, dados[i]);
  }

  printf("Estrutura da Árvore Rubro-Negra:\n");
  imprimirArvore(raiz, 0);

  return 0;
}