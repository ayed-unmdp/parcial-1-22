#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "vector.h"
#include "queue_static.h"

/**
 * Crear una función que mueva todos los ceros al final de un vector, 
 * dejando los demás elementos en orden. 
 * Utilizar el TDA vector  en donde cada elemento es un puntero a int. 
 */


void vector_zero_to_end (vector* v){
    void* aux;
    for (int i = vector_size(v)-1; i>=0; i--){
        if (*(int*)vector_get(v, i) == 0){
            aux = vector_remove(v, i);
            vector_add(v, aux);
        }
    }
}

// t_elem_quque = void*
void vector_zero_to_end2 (vector* v){
    int size = vector_size(v);
    queue* q = queue_new(size);
    int count = 0;    
         
    for (int i = 0; i < size; i++){
        void* e = vector_get(v, i);
        if (*(int*)e == 0){
            enqueue(q, e);            
        } else {
            vector_set(v, count, e);
            count++;
        }        
    }

    while (!queue_isempty(q) && count < size){
        vector_set(v, count, dequeue(q));
        count++;
    }

    queue_free(q);
}

void v_print(void* e){
    printf("%d ", *(int*)e);
}

void main(){
    vector* v = vector_new(10);
    srand(time(NULL));
    for (int i = 0; i < 10; i++){
        vector_add(v, malloc(sizeof(int)));
        int aux = rand() % 100;
        if (aux < 50){
            *(int*)vector_get(v, i) = 0;
        }else{
            *(int*)vector_get(v, i) = aux/2;
        }
    }
    vector_print(v,v_print);
    printf("\n\n");
    vector_zero_to_end2(v);
    vector_print(v,v_print);
    printf("\n\n");
}

