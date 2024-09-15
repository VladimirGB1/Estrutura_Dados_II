// Estrutura de Dados II
// Aluno: Vladimir Gama Batista

#include <stdio.h>
#include <stdlib.h>

struct NO {
  int dado;
  struct NO *esq;
  struct NO *dir;
  int altura;
};

typedef struct NO *ArvAVL;

int alturaNo(struct NO *no) {
  if (no == NULL)
    return 0;
  return no->altura;
}

struct NO *criarNo(int dado) {
  struct NO *no = (struct NO *)malloc(sizeof(struct NO));
  no->dado = dado;
  no->esq = NULL;
  no->dir = NULL;
  no->altura = 1;
  return no;
}

struct NO *rotacaoSD(struct NO *raiz) {
  struct NO *filhoEsq = raiz->esq;
  struct NO *subArv = filhoEsq->dir;

  filhoEsq->dir = raiz;
  raiz->esq = subArv;

  if (alturaNo(raiz->esq) > alturaNo(raiz->dir)) {
    raiz->altura = alturaNo(raiz->esq) + 1;
  } else {
    raiz->altura = alturaNo(raiz->dir) + 1;
  }

  if (alturaNo(filhoEsq->esq) > alturaNo(filhoEsq->dir)) {
    filhoEsq->altura = alturaNo(filhoEsq->esq) + 1;
  } else {
    filhoEsq->altura = alturaNo(filhoEsq->dir) + 1;
  }

  return filhoEsq;
}

struct NO *rotacaoSE(struct NO *raiz) {
  struct NO *filhoDir = raiz->dir;
  struct NO *subArv = filhoDir->esq;

  filhoDir->esq = raiz;
  raiz->dir = subArv;

  if (alturaNo(raiz->esq) > alturaNo(raiz->dir)) {
    raiz->altura = alturaNo(raiz->esq) + 1;
  } else {
    raiz->altura = alturaNo(raiz->dir) + 1;
  }

  if (alturaNo(filhoDir->esq) > alturaNo(filhoDir->dir)) {
    filhoDir->altura = alturaNo(filhoDir->esq) + 1;
  } else {
    filhoDir->altura = alturaNo(filhoDir->dir) + 1;
  }

  return filhoDir;
}

int fatBalanceamento(struct NO *no) {
  if (no == NULL)
    return 0;
  return alturaNo(no->esq) - alturaNo(no->dir);
}

struct NO *inserirArvAVL(struct NO *no, int dado) {
  if (no == NULL)
    return criarNo(dado);

  if (dado < no->dado)
    no->esq = inserirArvAVL(no->esq, dado);
  else if (dado > no->dado)
    no->dir = inserirArvAVL(no->dir, dado);
  else
    return no;

  if (alturaNo(no->esq) > alturaNo(no->dir)) {
    no->altura = alturaNo(no->esq) + 1;
  } else {
    no->altura = alturaNo(no->dir) + 1;
  }

  int balanceamento = fatBalanceamento(no);

  if (balanceamento > 1 && dado < no->esq->dado)
    return rotacaoSD(no);

  if (balanceamento < -1 && dado > no->dir->dado)
    return rotacaoSE(no);

  if (balanceamento > 1 && dado > no->esq->dado) {
    no->esq = rotacaoSE(no->esq);
    return rotacaoSD(no);
  }

  if (balanceamento < -1 && dado < no->dir->dado) {
    no->dir = rotacaoSD(no->dir);
    return rotacaoSE(no);
  }

  return no;
}

void imprimirArvore(struct NO *no, int nivel) {
  if (no != NULL) {
    imprimirArvore(no->dir, nivel + 1);

    for (int i = 0; i < nivel; i++)
      printf("    ");
    printf("%d\n", no->dado);

    imprimirArvore(no->esq, nivel + 1);
  }
}

int main() {
  ArvAVL raiz = NULL;

  int N = 8, dados[8] = {50, 100, 30, 20, 40, 45, 35, 37};
  for (int i = 0; i < N; i++) {
    raiz = inserirArvAVL(raiz, dados[i]);
  }

  imprimirArvore(raiz, 0);

  return 0;
}
