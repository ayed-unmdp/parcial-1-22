#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Crear una función recursiva para obtener el puntero del nodo 
 * con mínimo valor de una lista dinámica  simplemente enlazada de 
 * valores enteros (sin usar TDA). 
 * 
 * Utilizar la siguiente definición: 
 * 
 */

typedef struct _nodo {
	int value;
	struct _nodo* next;
} nodo;


nodo* min_nodo_lista (nodo* head){
    if (head == NULL) return NULL;
    nodo* res = head;
    nodo* min = min_nodo_lista (head->next);
    if ((min != NULL) && (min->value < res->value)) 
        res = min; 
    return res;
}

nodo* new_nodo (int value){
    nodo* n = malloc(sizeof(nodo));
    n->value = value;
    n->next = NULL;
}

void main(){
    nodo* head = new_nodo(10);
    nodo** aux = &head->next;
    *aux = new_nodo(2);
    aux = &(*aux)->next;
    *aux = new_nodo(3);

    nodo* min = min_nodo_lista(head);
    printf("%d\n", min->value);

}
