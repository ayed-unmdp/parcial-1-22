#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "queue_static.h"
#include "stack_static.h"


//Crear una función para invertir el orden los primeros N elementos de una cola (queue) Q.
void queue_reverse (queue* q, int n){
    stack* s = stack_new(queue_getmaxsize(q));
    
    while ((n > 0) && (!queue_isempty(q)) ){
        push(s, dequeue(q));
        n--;
    }
    
    int count = queue_getsize(q);
    while (!stack_isempty(s)){ 
        enqueue(q, pop(s));
    }

    for (; count > 0; count--){
        enqueue(q, dequeue(q));
    }
    stack_free(s);
}

void queue_print(queue* q){
    t_elem e;
    printf("[ ");
    int count = queue_getsize(q);
    while (count>0){
        e = dequeue(q);
        printf("%d ", e);
        enqueue(q, e);
        count--;
    }
    printf("]\n");
}



void main (){

    queue* q = queue_new(10);
    srand(time(NULL));
    int i;
    for (i = 0; i < 10; i++){
        enqueue(q, rand() % 100);
    }
    printf("\n\n");
    queue_print(q);

    queue_reverse(q, 5);
    printf("\n\n");
    queue_print(q);


}