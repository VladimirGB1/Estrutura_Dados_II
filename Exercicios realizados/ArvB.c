#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define Max 4

struct NoB {
  int num_chaves;
  int chaves[Max - 1];
  struct NoB *filhos[Max];
  bool eh_folha;
};

struct NoB *criarNo(bool eh_folha) {
  struct NoB *novoNo = (struct NoB *)malloc(sizeof(struct NoB));
  if (novoNo == NULL) {
    perror("Falha na alocação de memória");
    exit(EXIT_FAILURE);
  }
  novoNo->num_chaves = 0;
  novoNo->eh_folha = eh_folha;
  for (int i = 0; i < Max; i++) {
    novoNo->filhos[i] = NULL;
  }
  return novoNo;
}

void dividirFilho(struct NoB *pai, int indice) {
  struct NoB *filho = pai->filhos[indice];
  struct NoB *novoNo = criarNo(filho->eh_folha);

  novoNo->num_chaves = Max / 2 - 1;

  for (int i = 0; i < Max / 2 - 1; i++) {
    novoNo->chaves[i] = filho->chaves[i + Max / 2];
  }

  if (!filho->eh_folha) {
    for (int i = 0; i < Max / 2; i++) {
      novoNo->filhos[i] = filho->filhos[i + Max / 2];
    }
  }

  filho->num_chaves = Max / 2 - 1;

  for (int i = pai->num_chaves; i > indice; i--) {
    pai->filhos[i + 1] = pai->filhos[i];
  }

  pai->filhos[indice + 1] = novoNo;

  for (int i = pai->num_chaves - 1; i >= indice; i--) {
    pai->chaves[i + 1] = pai->chaves[i];
  }

  pai->chaves[indice] = filho->chaves[Max / 2 - 1];
  pai->num_chaves++;
}

void inserirNaoCheio(struct NoB *no, int chave) {
  int i = no->num_chaves - 1;

  if (no->eh_folha) {
    while (i >= 0 && no->chaves[i] > chave) {
      no->chaves[i + 1] = no->chaves[i];
      i--;
    }
    no->chaves[i + 1] = chave;
    no->num_chaves++;
  } else {
    while (i >= 0 && no->chaves[i] > chave) {
      i--;
    }
    i++;

    if (no->filhos[i]->num_chaves == Max - 1) {
      dividirFilho(no, i);

      if (no->chaves[i] < chave) {
        i++;
      }
    }
    inserirNaoCheio(no->filhos[i], chave);
  }
}

void inserir(struct NoB **raiz, int chave) {
  struct NoB *no = *raiz;

  if (no == NULL) {
    *raiz = criarNo(true);
    (*raiz)->chaves[0] = chave;
    (*raiz)->num_chaves = 1;
  } else {
    if (no->num_chaves == Max - 1) {
      struct NoB *nova_raiz = criarNo(false);
      nova_raiz->filhos[0] = no;
      dividirFilho(nova_raiz, 0);
      *raiz = nova_raiz;
    }
    inserirNaoCheio(*raiz, chave);
  }
}

void imprimirArvore(struct NoB *raiz, int nivel) {
  if (raiz != NULL) {
    for (int i = 0; i < raiz->num_chaves; i++) {
      for (int j = 0; j < nivel; j++) {
        printf("    ");
      }
      printf("%d ", raiz->chaves[i]);
    }
    printf("\n");

    if (!raiz->eh_folha) {
      for (int i = 0; i <= raiz->num_chaves; i++) {
        imprimirArvore(raiz->filhos[i], nivel + 1);
      }
    }
  }
}

int main() {
  struct NoB *raiz = NULL;
  int N = 8, dados[8] = {50, 100, 30, 20, 40, 45, 35, 37};

  for (int i = 0; i < N; i++) {
    inserir(&raiz, dados[i]);
  }

  printf("\nEstrutura da Árvore B:\n");
  imprimirArvore(raiz, 0);

  return 0;
}
