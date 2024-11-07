#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct NoTreap {
  int chave, prioridade;
  struct NoTreap *esq, *dir;
};

struct NoTreap *criarNo(int chave) {
  struct NoTreap *novo = malloc(sizeof(struct NoTreap));
  novo->chave = chave;
  novo->prioridade = rand() % 100;
  novo->esq = novo->dir = NULL;
  return novo;
}

struct NoTreap *rotacaoPBaixo(struct NoTreap **no, int dir) {
  struct NoTreap *filho = dir ? (*no)->dir : (*no)->esq;
  if (dir) {
    (*no)->dir = filho->esq;
    filho->esq = *no;
  } else {
    (*no)->esq = filho->dir;
    filho->dir = *no;
  }
  *no = filho;
  return filho;
}

struct NoTreap *inserirTreap(struct NoTreap *raiz, int chave) {
  if (raiz == NULL)
    return criarNo(chave);

  struct NoTreap **atual = &raiz;
  while (*atual != NULL) {
    if (chave < (*atual)->chave) {
      if ((*atual)->esq == NULL) {
        (*atual)->esq = criarNo(chave);
        if ((*atual)->esq->prioridade > (*atual)->prioridade)
          raiz = rotacaoPBaixo(atual, 0);
        break;
      } else
        atual = &(*atual)->esq;
    } else {
      if ((*atual)->dir == NULL) {
        (*atual)->dir = criarNo(chave);
        if ((*atual)->dir->prioridade > (*atual)->prioridade)
          raiz = rotacaoPBaixo(atual, 1);
        break;
      } else
        atual = &(*atual)->dir;
    }
  }

  return raiz;
}

struct NoTreap *removerTreap(struct NoTreap *raiz, int chave) {
  if (raiz == NULL)
    return NULL;

  if (chave < raiz->chave) {
    raiz->esq = removerTreap(raiz->esq, chave);
  } else if (chave > raiz->chave) {
    raiz->dir = removerTreap(raiz->dir, chave);
  } else {
    if (raiz->esq == NULL || raiz->dir == NULL) {
      struct NoTreap *temp = raiz->esq ? raiz->esq : raiz->dir;
      free(raiz);
      return temp;
    }

    struct NoTreap **maiorPrioridade =
        raiz->esq->prioridade > raiz->dir->prioridade ? &raiz->esq : &raiz->dir;
    raiz = rotacaoPBaixo(maiorPrioridade, maiorPrioridade == &raiz->dir);
    *maiorPrioridade = removerTreap(*maiorPrioridade, chave);
  }
  return raiz;
}

int buscarChave(struct NoTreap *raiz, int chave) {
  return raiz == NULL
             ? 0
             : (raiz->chave == chave ||
                buscarChave(chave < raiz->chave ? raiz->esq : raiz->dir,
                            chave));
}

void mostrarTreap(struct NoTreap *raiz, int nivel) {
  if (!raiz)
    return;
  mostrarTreap(raiz->dir, nivel + 1);
  for (int i = 0; i < nivel; i++)
    printf("   ");
  printf("%d (P:%d)\n", raiz->chave, raiz->prioridade);
  mostrarTreap(raiz->esq, nivel + 1);
}

int main() {
  srand(time(0));
  struct NoTreap *raiz = NULL;

  int N = 8, dados[8] = {50, 100, 30, 20, 40, 45, 35, 37};

  for (int i = 0; i < N; i++) {
    raiz = inserirTreap(raiz, dados[i]);
  }

  printf("Treap após inserções:\n");
  mostrarTreap(raiz, 0);

  return 0;
}
