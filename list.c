#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list *list_new(int maxsize) {
  list *L = malloc(sizeof(list));

  L->head = NULL;
  L->maxsize = maxsize;
  L->count = 0;

  return L;
}

bool list_isempty(list *L) {
  return L->count == 0;
}

bool list_isfull(list *L) {
  return L->count == L->maxsize;
}

int list_length(list *L) {
  return L->count;
}

t_elem_list list_get(list *L, int index) {
  list_node *node = L->head;

  while (node != NULL && index > 0) {
    node = node->next;
    index--;
  }

  if (node == NULL) {
    printf("Index out of bounds\n");
    exit(1);
  }

  return node->value;
}

int list_search(list *L, t_elem_list elem) {
  list_node *node = L->head;
  int index = 0;

  while (node != NULL && node->value != elem) {
    node = node->next;
    index++;
  }

  return node == NULL ? -1 : index;
}

void list_insert(list *L, int index, t_elem_list elem) {
  if (list_isfull(L)){
    printf("List overflow\n");
    exit(1);
  }

  list_node *node = malloc(sizeof(list_node));
  list_node *next = L->head;
  list_node *prev = NULL;

  node->value = elem;
  node->next = NULL;

  if (index == 0) {
    node->next = L->head;
    L->head = node;
  } else {
    while (next != NULL && index > 0) {
      prev = next;
      next = next->next;
      index--;
    }

    node->next = next;
    prev->next = node;
  }

  L->count++;
}

void list_delete(list *L, int index) {
  list_node *node = L->head;
  list_node *prev = NULL;

  if (index == 0 && node != NULL) {
    L->head = node->next;
    free(node);
  } else {
    while (node != NULL && index > 0) {
      prev = node;
      node = node->next;
      index--;
    }

    if (node != NULL) {
      prev->next = node->next;
      free(node);
    }
  }

  L->count--;
}

void list_traverse(list *L, bool look(t_elem_list elem, int index, void *ctx), void *ctx) {
  list_node *node = L->head;
  int index = 0;

  while (node != NULL && look(node->value, index, ctx)) {
    node = node->next;
    index++;
  }
}