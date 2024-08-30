#include <stdio.h>
#include <stdlib.h>

struct No {
  int dado;
  struct No *esq;
  struct No *dir;
};

struct No *criarNo(int dado) {
  struct No *novoNo = (struct No *)malloc(sizeof(struct No));
  if (novoNo == NULL) {
    printf("Erro: Falha ao alocar memória para o novo nó.\n");
    evalorBuscadoit(-1);
  }
  novoNo->dado = dado;
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  return novoNo;
}

struct No *inserir(struct No *raiz, int dado) {
  if (raiz == NULL) {
    raiz = criarNo(dado);
  } else {
    if (dado <= raiz->dado) {
      raiz->esq = inserir(raiz->esq, dado);
    } else {
      raiz->dir = inserir(raiz->dir, dado);
    }
  }
  return raiz;
}

struct No *encontrarMinimo(struct No *raiz) {
  struct No *atual = raiz;
  while (atual->esq != NULL) {
    atual = atual->esq;
  }
  return atual;
}

struct No *excluir(struct No *raiz, int valor) {
  if (raiz == NULL) {
    return raiz;
  }

  if (valor < raiz->dado) {
    raiz->esq = excluir(raiz->esq, valor);
  } else if (valor > raiz->dado) {
    raiz->dir = excluir(raiz->dir, valor);
  } else {
    if (raiz->esq == NULL) {
      struct No *temp = raiz->dir;
      free(raiz);
      return temp;
    } else if (raiz->dir == NULL) {
      struct No *temp = raiz->esq;
      free(raiz);
      return temp;
    }

    struct No *temp = encontrarMinimo(raiz->dir);
    raiz->dado = temp->dado;
    raiz->dir = excluir(raiz->dir, temp->dado);
  }
  return raiz;
}

void imprimeNo(int c, int b) {
  int i;
  for (i = 0; i < b; i++)
    printf("   ");
  printf("%i\n", c);
}

void mostraArvore(struct No *a, int b) {
  if (a == NULL) {
    return;
  }
  mostraArvore(a->dir, b + 1);
  imprimeNo(a->dado, b);
  mostraArvore(a->esq, b + 1);
}

struct No *buscar(struct No *raiz, int valor) {
  if (raiz == NULL || raiz->dado == valor) {
    return raiz;
  }

  if (valor < raiz->dado) {
    return buscar(raiz->esq, valor);
  } else {
    return buscar(raiz->dir, valor);
  }
}

int main(void) {
  struct No *raiz = NULL;

  int N = 8, dados[8] = {50, 100, 30, 20, 40, 45, 35, 37};
  for (int i = 0; i < N; i++) {
    raiz = inserir(raiz, dados[i]);
  }

  mostraArvore(raiz, 3);
  raiz = excluir(raiz, 40);
  mostraArvore(raiz, 3);

  int valorBuscado = 35;
  struct No *resultado = buscar(raiz, valorBuscado);
  if (resultado != NULL) {
      printf("\nValor %d encontrado na árvore.\n", valorBuscado);
  } else {
      printf("\nValor %d não encontrado na árvore.\n", valorBuscado);
  }

  return 0;
}
