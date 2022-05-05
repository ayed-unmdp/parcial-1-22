#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

/**
 * @brief Crea el vector vacío reservando el espacio en memoria. Tamaño = 0, Tamaño Máximo = ini_size.
 * 
 * @param ini_size 
 * @return vector* 
 */
vector* vector_new(int ini_size){
   vector* result = malloc(sizeof(vector));
   result->a = malloc(sizeof(void*) * ini_size);
   result->size = 0;
   result->max_size = ini_size;
   return result;
}

/**
 * @brief Eliminar el vector
 * 
 * @param v 
 */
void vector_free(vector* v){
   free(v);   
} 

/**
 * @brief Permite obtener el tamaño actual del vector
 * 
 * @param v 
 * @return int 
 */
int vector_size(vector* v){
   return v->size;   
}

/**
 * @brief Devuelve 0 si no está lleno y 1 si está lleno. 
 * 
 * @param v 
 * @return int 
 */
int vector_isfull(vector* v) {
   return v->size == v->max_size;
}

/**
 * @brief Devuelve 0 si no está vacío y 1 si está vacío. 
 * 
 * @param v 
 * @return int 
 */
int vector_isempty(vector* v){
   return v->size == 0;
}


/**
 * @brief Permite obtener el valor de una posición del vector
 * 
 * @param v 
 * @param index 
 * @return void* 
 */
void* vector_get(vector* v, int index){
   void* r = v->a[index];
   return r;
}  


/**
 * @brief Permite reemplazar el valor de una posición del vector
 * 
 * @param v 
 * @param index 
 * @return void* 
 */
void* vector_set(vector* v, int index, void* value){
   v->a[index] = value;   
}

/**
 * @brief Permite agregar un elemento al final
 * 
 * @param v 
 * @param value 
 */
int vector_add(vector* v, void* value){
   if(vector_isfull(v)){
      return 0;
   }
   v->a[v->size] = value;
   v->size++;
   return 1;
}


/**
 * @brief Permite agregar un elemento en una posición determinada.
 * 
 * @param v 
 * @param index 
 * @param value 
 */
int vector_insert(vector* v, int index, void* value){
   if (index > v->size || index < 0){
      return 0;
   }
   v->size++;
   for(int i = v->size; i > index; i--){
      v->a[i] = v->a[i-1];
   }
   v->a[index] = value;
   return 1;
}


/**
 * @brief Permite eliminar un elemento del vector
 * 
 * @param v 
 * @param index 
 */
void* vector_remove(vector* v, int index){
   if (index > v->size || index < 0){
      return NULL;
   }
   void* result = v->a[index];
   for (int i = index; i < v->size; i++){
      v->a[i] = v->a[i+1];
   }
   if (v->size > 0){
      v->size--;
   }
   return result;   
}

/**
 * @brief print the vector
 * 
 */
void vector_print(vector* v, void (*print)(void*)){
   for (int i = 0; i < v->size; i++){
      print(v->a[i]);
   }
}