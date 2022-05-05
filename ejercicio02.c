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
    i->cantidad = 0;
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
    list_insert(f->items, list_size(f->items), i);    
}

time_t factura_getfecha(factura* f){
    return f->fecha;
}

int factura_get_nro_cliente (factura* f){
    return f->cliente;
}

int factura_get_nombre_cliente (factura* f){
    return f->nombre;
}

float factura_get_total (factura* f){
    return f->total;
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

    for (int i = 0; i < list_size(facturas); i++) {
        factura* f = list_get(facturas, i);
        if (factura_get_nro_cliente(f) == cliente) {
            total += factura_get_total(f);
        }
    }
    
    return total;
}





