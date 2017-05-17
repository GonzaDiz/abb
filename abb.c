#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Definicion de un nodo del abb */

typedef struct nodo {
	void* dato;
	char* clave;
	struct nodo* izq;
	struct nodo* der;
}nodo_t;

/* Definicion del abb */ 

struct abb {
	struct nodo_t* node;
	size_t cantidad;
	abb_comparar_clave_t* comparar;
	abb_destruir_dato_t* destructor;
};
/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb) return NULL;
	abb->comparar = cmp;
	abb->destructor = destruir_dato;
	abb->cantidad = 0;
	abb->node = NULL;
	return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	if(!arbol->node){
		nodo_t nodo = malloc(sizeof(nodo));
		if(!nodo) return NULL;
		nodo->clave = clave;
		nodo->dato = dato;
		nodo->izq = NULL;
		nodo->der = NULL;
		arbol->node = nodo;
		arbol->cantidad++;
		return true;
	}

	if(arbol->comparar(arbol->node->clave,clave) < 0){
		abb_guardar(arbol->node->izq,clave,dato);
	}
	abb_guardar(arbol->node->der,clave,dato);	
}

size_t abb_cantidad(abb_t *arbol){
	return abb->cantidad;
}

void *abb_borrar(abb_t *arbol, const char *clave){

}

void *abb_obtener(const abb_t *arbol, const char *clave){

}

bool abb_pertenece(const abb_t *arbol, const char *clave){

}