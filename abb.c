#include "pila.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Definicion de un nodo del abb */

typedef struct nodo {
	void* dato;
	char* clave;
	nodo_t* izq;
	nodo_t* der;
}nodo_t;

/* Definicion del abb */ 

struct abb {
	nodo_t* nodo;
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
	abb->nodo = NULL;
	return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	if(!arbol->nodo){
		nodo_t nodo = malloc(sizeof(nodo_t));
		if(!nodo) return false;
		nodo->clave = clave;
		nodo->dato = dato;
		nodo->izq = NULL;
		nodo->der = NULL;
		arbol->nodo = nodo;
		arbol->cantidad++;
		return true;
	}

	
	if(arbol->comparar(arbol->nodo->clave,clave) < 0){
		abb_guardar(arbol->nodo->izq,clave,dato);
	}
	else if (arbol->comparar(arbol->nodo->clave,clave) > 0){
		abb_guardar(arbol->nodo->der,clave,dato);	
	}
	else if (arbol->destructor) arbol->destructor(arbol->nodo->dato);
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

void abb_destruir(abb_t *arbol){

}