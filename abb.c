#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

/* Definicion de un nodo del abb */

typedef struct nodo {
	void* dato;
	char* clave;
	struct abb* izq;
	struct abb* der;
}nodo_t;

/* Definicion del abb */ 

struct abb {
	struct nodo_t* node;
	abb_comparar_clave_t* comparar;
	abb_destruir_dato_t* destructor;
};
/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/
// crear abb
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb) return NULL;
	abb->comparar = cmp;
	abb->destructor = destruir_dato;
	return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	if(!arbol->izq && !arbol->der){
		abb->node->clave = clave;
		abb->node->dato = dato;
		return true;
	}
}

void *abb_borrar(abb_t *arbol, const char *clave);
