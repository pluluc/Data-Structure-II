#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum Cor { VERMELHO, PRETO };

typedef struct node {
  struct node *esq = NULL;
  struct node *dir = NULL;
  struct node *pai = NULL;
  int num = 0;
  Cor cor = VERMELHO;
} No;

No *remover(No *node, int num);

No *criar_no(int num = -1) {
  No *node = new No;

  if (num == -1) {
    node->num = rand() % 100;
    printf("%d, ", node->num);
  } else {
    node->num = num;
  }

  node->esq = NULL;
  node->dir = NULL;

  return node;
}

No *buscar_no(No *node, int num) {
  if (node == NULL) {
    // printf("Número não encontrado\n");
    return NULL;
  }

  if (node->num == num) {
    return node;
  }

  if (node->num < num) {
    return buscar_no(node->dir, num);
  } else {
    return buscar_no(node->esq, num);
  }
}

void imprimir(No *node, int tab = 0) {
  if (node == NULL)
    return;

  imprimir(node->dir, tab + 1);
  for (int i = 0; i < tab; i++) {
    printf("\t");
  }
  printf("%d - %i\n", node->num, node->cor);
  imprimir(node->esq, tab + 1);
}


void buscar_raiz(No *raiz) {
  int num = 0;
  printf("Digite o numero: ");
  scanf("%d", &num);
  No *res = buscar_no(raiz, num);
  if (res == NULL) {
    printf("Numero não encontrado");
  } else {
    imprimir(res);
  }
}

No *buscar_pai(No *node, int num) {
  if (node == NULL)
    return NULL;

  if ((node->esq != NULL) && (node->esq->num == num)) {
    return node;
  }

  if ((node->dir != NULL) && (node->dir->num == num)) {
    return node;
  }

  if (node->num < num) {
    return buscar_pai(node->dir, num);
  } else {
    return buscar_pai(node->esq, num);
  }
}

bool um_filho(No *node) {
  // return (node->esq == NULL) && (node->dir == NULL);
  if ((node->esq == NULL) && (node->dir != NULL)) {
    return true;
  }

  if ((node->esq != NULL) && (node->dir == NULL)) {
    return true;
  }

  return false;
}

bool eh_folha(No *node) {
  // return (node->esq == NULL) && (node->dir == NULL);
  if ((node->esq == NULL) && (node->dir == NULL)) {
    return true;
  } else {
    return false;
  }
}

No *maior(No *node) {
  if (node == NULL)
    return NULL;
  if (node->dir == NULL)
    return node;
  return maior(node->dir);
}

No *menor(No *node) {
  if (node == NULL)
    return NULL;
  if (node->esq == NULL)
    return node;
  return menor(node->esq);
}

int soma(No *node) {
  if (node == NULL)
    return 0;

  return node->num + soma(node->dir) + soma(node->esq);
}

int cont(No *node) {
  if (node == NULL)
    return 0;

  return 1 + cont(node->dir) + cont(node->esq);
}

float media(No *node) {
  float total = soma(node);
  float qnt = cont(node);
  return total / qnt;
}

int altura(No *node) {
  if (node == NULL)
    return 0;

  if (node->cor == VERMELHO) {
    return fmax(altura(node->esq), altura(node->dir));
  } else
    return 1 + fmax(altura(node->esq), altura(node->dir));
}

void substituir(No *pai, No *removido) {
  if (um_filho(removido)) {
    if (removido->esq != NULL) {
      pai->esq = removido->esq;
    } else {
      pai->dir = removido->dir;
    }
  } else {
    No *substituto = maior(removido->esq);
    remover(pai, substituto->num);
    substituto->esq = removido->esq;
    substituto->dir = removido->dir;
    if (pai->num < substituto->num) {
      pai->dir = substituto;
    } else {
      pai->esq = substituto;
    }
    removido->dir = NULL;
    removido->esq = NULL;
  }
}

No *remover(No *node, int num) {
  No *pai = buscar_pai(node, num);
  if (pai == NULL) {
    printf("Numero não encontrado");
    return NULL;
  } else {
    // printf("Pai: %d\n", pai->num);
    No *removido = NULL;
    if (pai->num < num) {
      removido = pai->dir;
      if (eh_folha(removido)) {
        pai->dir = NULL;
      } else {
        substituir(pai, removido);
      }
    } else {
      removido = pai->esq;
      if (eh_folha(removido)) {
        pai->esq = NULL;
      } else {
        substituir(pai, removido);
      }
    }
    // printf("Removido: %d\n", removido->num);
    return removido;
  }
}

void remover_raiz(No **raiz) {
  int num = 0;
  printf("Digite o numero: ");
  scanf("%d", &num);

  if (*raiz == NULL) {
    printf("Árvore vazia\n");
    return;
  }

  if ((*raiz)->num == num) {
    if (eh_folha(*raiz)) {
      free(*raiz);
      *raiz = NULL;
      return;
    }

    if (um_filho(*raiz)) {
      No *remover = *raiz;
      if ((*raiz)->esq != NULL) {
        *raiz = (*raiz)->esq;
      } else {
        *raiz = (*raiz)->dir;
      }
      free(remover);
    } else {
      No *substituto = maior((*raiz)->esq);
      remover(*raiz, substituto->num);
      substituto->esq = (*raiz)->esq;
      substituto->dir = (*raiz)->dir;
      (*raiz)->esq = NULL;
      (*raiz)->dir = NULL;
      free(*raiz);
      *raiz = substituto;
    }
  } else {
    remover(*raiz, num);
  }
}

void altura_no(No *raiz) {
  int num = 0;
  printf("Digite o numero: ");
  scanf("%d", &num);
  No *res = buscar_no(raiz, num);
  if (res == NULL) {
    printf("Numero não encontrado");
  } else {
    printf("Altura nó:%d\n", altura(res));
  }
}

int fb_no(No *no) {
  if (no == NULL)
    return 0;
  return altura(no->esq) - altura(no->dir);
}

void fb_raiz(No *raiz) {
  int num = 0;
  printf("Digite o numero: ");
  scanf("%d", &num);
  No *res = buscar_no(raiz, num);
  if (res == NULL) {
    printf("Numero não encontrado");
  } else {
    printf("FB do nó:%d\n", altura(res->esq) - altura(res->dir));
  }
}

void imprimir_fb(No *node, int tab = 0) {
  if (node == NULL)
    return;

  imprimir_fb(node->dir, tab + 1);
  for (int i = 0; i < tab; i++) {
    printf("\t");
  }
  printf("%d\n", altura(node->esq) - altura(node->dir));
  imprimir_fb(node->esq, tab + 1);
}


void rot_simples_esq(No **raiz, No *no, bool dupla = false) {
  No *filho = no->dir;
  if (filho == NULL) {
    printf("Rotação errada\n");
    return;
  }

  No *esq_filho = filho->esq;
  no->dir = esq_filho;
  filho->esq = no;

  No *pai = buscar_pai(*raiz, no->num);
  if (pai == NULL) {
    *raiz = filho;
  } else {
    if (dupla == true) {
      pai->esq = filho;
    } else {
      pai->dir = filho;
    }
  }
}

void rot_simples_dir(No **raiz, No *no, bool dupla = false) {
  No *filho = no->esq;
  if (filho == NULL) {
    printf("Rotação errada\n");
    return;
  }

  No *dir_filho = filho->dir;
  no->esq = dir_filho;
  filho->dir = no;

  No *pai = buscar_pai(*raiz, no->num);
  if (pai == NULL) {
    *raiz = filho;
  } else {
    if (dupla == true) {
      pai->dir = filho;
    } else {
      pai->esq = filho;
    }
  }
}

void rot_dupla_dir(No **raiz, No *no) {
  No *filho = no->esq;
  if (filho == NULL) {
    printf("Rotação errada\n");
    return;
  }
  rot_simples_esq(raiz, filho, true);
  rot_simples_dir(raiz, no);
}

void rot_dupla_esq(No **raiz, No *no) {
  No *filho = no->dir;
  if (filho == NULL) {
    printf("Rotação errada\n");
    return;
  }
  rot_simples_dir(raiz, filho, true);
  rot_simples_esq(raiz, no);
}

void balancear(No **raiz, No *no) {
  if (no == NULL)
    return;

  if (fb_no(no) <= -2) {      // Rotacão esquerda
    if (fb_no(no->dir) < 1) { // Rotação simples
      rot_simples_esq(raiz, no);
    } else { // Rotação dupla
      rot_dupla_esq(raiz, no);
    }
  }

  if (fb_no(no) >= 2) { // Rotacão direita

    if (fb_no(no->esq) > -1) { // Rotação simples
      rot_simples_dir(raiz, no);
    } else { // Rotação dupla
      rot_dupla_dir(raiz, no);
    }
  }
}

void inserir_no(No *node, No *novo) {
  if (node == NULL) {
    printf("Erro\n");
    return;
  }

  if (node->num == novo->num) {
    printf("Numero ja existe\n");
    return;
  }

  if (node->num < novo->num) {
    if (node->dir == NULL) {
      node->dir = novo;

      if (node->cor == PRETO) {
        novo->pai = node;
        return;
      }
      if (node->cor == VERMELHO && node->pai->esq->cor == VERMELHO) {
        node->cor = PRETO;
        node->pai->esq->cor = PRETO;
        if (node->pai->pai == NULL) {
          novo->pai = node;
          return;
        }
        node->pai->cor = VERMELHO;
        novo->pai = node;
        return;
      }
      if (node->cor == VERMELHO && (node->pai->esq->cor == PRETO || node->pai->esq == NULL)) {
        if (node->pai == NULL) return;
        if (node == node->pai->dir && novo == node->dir) {
          node->cor = PRETO;
          node->pai->cor = VERMELHO;
          rot_simples_esq(&node->pai,node);
          novo->pai = node;
          return;
        }
        if (node == node->pai->esq && novo == node->dir){
          novo->cor = PRETO;
          node->pai->cor = VERMELHO;
          rot_dupla_dir(&node->pai, node);
          novo->pai = node;
          return;
        }
      }
    }
    inserir_no(node->dir, novo);
  } else {
    if (node->esq == NULL) {
      node->esq = novo;

      if (node->cor == PRETO) {
        novo->pai = node;
        return;
      }

      if (node->cor == VERMELHO && node->pai->dir->cor == VERMELHO) {
        node->cor = PRETO;
        node->pai->dir->cor = PRETO;
        if (node->pai->pai == NULL) {
          novo->pai = node;
          return;
        }
        node->pai->cor = VERMELHO;
        novo->pai = node;
        return;
      }
      if (node->cor == VERMELHO && (node->pai->dir->cor == PRETO || node->pai->dir == NULL)) {
        if (node->pai == NULL) return;
        if (node == node->pai->esq && novo == node->esq) {
          node->cor = PRETO;
          node->pai->cor = VERMELHO;
          rot_simples_dir(&node->pai,node);
          novo->pai = node;
          return;
        }
        if (node == node->pai->esq && novo == node->dir){
          novo->cor = PRETO;
          node->pai->cor = VERMELHO;
          rot_dupla_esq(&node->pai, node);
          novo->pai = node;
          return;
        }
      }

    }
    inserir_no(node->esq, novo);
  }
  //
}


void inserir_raiz(No **raiz) {
  if (*raiz == NULL) {
    *raiz = criar_no();
    (*raiz)->cor = PRETO;
    return;
  }
  No *novo = criar_no();

  inserir_no(*raiz, novo);
}

void arvore_aleatoria(No **root) {
  for (int i = 0; i < 10; i++) {
    inserir_raiz(root);
  }
}

void menu() {
  printf("MENU\n");
  printf("1-Inserir\n");
  printf("2-Buscar\n");
  printf("3-Imprimir Arvore\n");
  printf("4-Remover\n");
  printf("5-Arvore aleatoria\n");
  printf("6-Maior, menor e media\n");
  printf("7-Altura arvore\n");
  printf("8-Altura no\n");
  printf("9-FB do no\n");
  printf("10-Imprimir FB\n");
  printf("0-Sair\n");
}

int main(void) {
  srand(time(NULL));

  No *root = NULL;

  int opc = 1;
  while (opc != 0) {
    menu();
    scanf("%d", &opc);
    switch (opc) {
    case 1:
      inserir_raiz(&root);
      break;
    case 2:
      buscar_raiz(root);
      break;
    case 3:
      imprimir(root);
      break;
    case 4:
      remover_raiz(&root);
      break;
    case 5:
      arvore_aleatoria(&root);
      break;
    case 6:
      printf("Maior:%d, Menor:%d, Média:%.2f\n", maior(root)->num,
             menor(root)->num, media(root));
      break;
    case 7:
      printf("Altura: %d\n", altura(root));
      break;
    case 8:
      altura_no(root);
      break;
    case 9:
      fb_raiz(root);
      break;
    case 10:
      imprimir_fb(root);
      break;
    case 0:
      break;
    default:
      break;
    }
  }

  return 0;
}