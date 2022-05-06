#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "list.h"

/**
 * Diseñar un TDA para modelar una factura que consta de:
 * fecha de emisión (time_t),
 * total (float),
 * nº de cliente (int),
 * nombre de cliente (String),
 * items (lista de items).
 *
 * Cada ítem tiene:
 * cantidad (int),
 * descripcion (String) y
 * precio unitario (float)
 *
 */

typedef struct _item {
    int cantidad;
    char* descripcion;
    float precio_unitario;
} item;

typedef struct _factura {
    time_t fecha;
    float total;
    int cliente;
    char* nombre;
    list* items;
} factura;

/**
 * al crear la factura se indica el cliente y la fecha se asigna por sistema;
 * se deben poder agregar items a la factura;
 * se deben poder obtener: la fecha de emisión,
 * el número y el nombre del cliente, y
 * el total de la factura.
 */

item* item_new(int cantidad, char* descripcion, float precio_unitario) {
    item* i = malloc(sizeof(item));
    i->cantidad = cantidad;
    i->descripcion = malloc(strlen(descripcion) + 1);
    strcpy(i->descripcion, descripcion);
    i->precio_unitario = precio_unitario;    
}

float item_get_precio_unitario(item* i) {
    return i->precio_unitario;
}

int item_get_cantidad(item* i) {
    return i->cantidad;
}

char* item_get_descripcion(item* i) {
    return i->descripcion;
}


factura* factura_new(int cliente, char* nombre) {
    factura* f = malloc(sizeof(factura));
    f->fecha = time(NULL);
    f->total = 0;
    f->cliente = cliente;
    f->nombre = malloc(strlen(nombre) + 1);
    strcpy(f->nombre, nombre);
    f->items = list_new(50);
    return f;
}

void factura_item_add (factura* f, item* i){
    list_insert(f->items, list_length(f->items), i); 
    f->total +=  item_get_precio_unitario(i) * item_get_cantidad(i);  
}

time_t factura_getfecha(factura* f){
    return f->fecha;
}

int factura_get_nro_cliente (factura* f){
    return f->cliente;
}

char* factura_get_nombre_cliente (factura* f){
    return f->nombre;
}

float factura_get_total (factura* f){
    return f->total;
}

list* factura_get_items (factura* f){
    return f->items;
}

typedef struct _total_ctx {
    int nro_cliente;
    float total;
} total_ctx;

bool look_total_cliente (t_elem_list elem, int index, void *ctx) {
    total_ctx* c = (total_ctx*) ctx;
    factura* f = (factura*) elem;
    if (factura_get_nro_cliente(f) == c->nro_cliente) {
        c->total += factura_get_total(f);        
    }
    return true;
}


float total_cliente (list* facturas, int cliente){
    float total = 0;

    total_ctx ctx;
    ctx.nro_cliente = cliente;
    ctx.total = 0;
    
    list_traverse(facturas, look_total_cliente, &ctx);

    return ctx.total;
}


float total_cliente2 (list* facturas, int cliente){
    float total = 0;
    int size =  list_length(facturas);
    for (int i = 0; i < size; i++) {
        factura* f = list_get(facturas, i);
        if (factura_get_nro_cliente(f) == cliente) {
            total += factura_get_total(f);
        }
    }
    
    return total;
}

bool item_print (t_elem_list elem, int index, void *ctx){
    item* i = (item*) elem;
    printf("%3d %-20s $%.2f\n", item_get_cantidad(i), item_get_descripcion(i), item_get_precio_unitario(i));
    return true;
}


void items_print (list* items){
    list_traverse(items, item_print, NULL);
}



bool factura_print (t_elem_list elem, int index, void *ctx){  
    factura* f = (factura*) elem;  
    time_t fecha = factura_getfecha(f);
    printf("Factura de %s con número %d emitida el %s", factura_get_nombre_cliente(f), factura_get_nro_cliente(f), ctime(&fecha));
    printf("Total: $%.2f\n", factura_get_total(f));
    printf("Items:\n");
    items_print(factura_get_items(f));
    printf("\n");
    return true;
}


void facturas_print (list* facturas){
    list_traverse(facturas, factura_print, NULL);
}

void main(){
    list* facturas = list_new(50);

    char* clientes[] = {"Juan", "Franco", "Ariel", "Gonzalo", "Santiago", "Mauro", "Nazareno"};
    int clientes_size = sizeof(clientes) / sizeof(char*);

    char* compras[] = {"Arroz", "Fideos", "Gaseosa", "Leche", "Pan", "Queso", "Tomate", "Yogurt", "Zanahoria", "Aceite"};
    int compras_size = sizeof(compras) / sizeof(char*);

    float precios[] = {110.0, 125.0, 300.0, 125.0, 70.0, 240.0, 55.0, 80.0, 90.0, 220.0};
    int precios_size = sizeof(precios) / sizeof(float);

    int cant_items = (compras_size<precios_size)?compras_size:precios_size;
    
    srand(time(NULL));
    int cant_facturas = rand() % 10 + 20;
    for (int i = 0; i < cant_facturas; i++){
        int cliente = rand() % clientes_size;
        factura* f = factura_new(cliente, clientes[cliente]);
        int count_items = rand() % 3 + 1; // entre 1 y 3 items
        for (int j = 0; j < count_items; j++){
            int item_index = rand() % cant_items;
            int cantidad = rand() % 10 + 1;
            item* item = item_new(cantidad, compras[item_index], precios[item_index]);
            factura_item_add(f, item);
        }
        list_insert(facturas, list_length(facturas), f);
    }

    facturas_print(facturas);

    printf ("\n\n Totales por cliente\n\n");
    for (int i = 0; i < clientes_size; i++){
        printf("%10s: $%10.2f\n", clientes[i], total_cliente(facturas, i));
    }

}





