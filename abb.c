#include "abb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* FIJARSE BIEN QUE AL HACER FUNCOINES RECURSIVAS DEBO IMPLEMENTAR
/ FUNCIONES AUXILIARES A LAS CUALES LES PUEDA PASAR UN NODO COMO SI 
/ FUESE UN ARBOL POR QUE LAS PRIMITIVAS ORIGINALES NO ACEPTAN NODOS
/ SINO ARBOLES*/

/* Definicion de un nodo del abb */

struct nodo {
	void* dato;
	char* clave;
	nodo_t* izq;
	nodo_t* der;
};

/* Definicion del abb */ 

struct abb {
	nodo_t* nodo;
	size_t cantidad;
	abb_comparar_clave_t comparar;
	abb_destruir_dato_t destructor;
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES						   *
 * *****************************************************************/

char *strdup (const char *str) {
    char *copia = malloc (strlen (str) + 1);   
    if (copia == NULL) return NULL;          
    strcpy (copia,str);                      
    return copia;                            
}

bool abb_guardar_recursivo(abb_t *arbol,nodo_t* nodo, nodo_t* nuevoNodo, const char *clave){

	// Si el arbol recien esta creado entcones el primer nodo/raiz es Null
	if (arbol->nodo == NULL ) {
		arbol->nodo = nuevoNodo;
		arbol->cantidad++;
		return true;
	}
	else if(arbol->comparar(nodo->clave,clave) < 0){
		if (nodo->der == NULL){
			nodo->der = nuevoNodo;
			arbol->cantidad++;
		return true;
		}
		return abb_guardar_recursivo(arbol,nodo->der,nuevoNodo,clave);
	}
	else if (arbol->comparar(nodo->clave,clave) > 0){
		if (nodo->izq == NULL){
			nodo->izq = nuevoNodo;
			arbol->cantidad++;
			return true;
		}
		return abb_guardar_recursivo(arbol,nodo->izq,nuevoNodo,clave);	
	}
	else if (arbol->comparar(nodo->clave,clave) == 0){
		if (arbol->destructor) arbol->destructor(arbol->nodo->dato);
		nodo->dato = nuevoNodo->dato;
		free(nodo->clave);
		free(nodo);
		return true;
	}
	return false;
}

// Busca un nodo en un arbol segun la clave, en caso de existir devuelve el nodo y en caso contrario devuelve null.
nodo_t* abb_buscar_recursivo(nodo_t* nodo,const abb_t* arbol, const char *clave){
	if (nodo == NULL){
		return NULL;
	} 
	if (arbol->comparar(nodo->clave,clave) == 0){
		return nodo;
	}
	else if (arbol->comparar(nodo->clave,clave) > 0){ 
		return abb_buscar_recursivo(nodo->izq,arbol,clave);
	}
	else if (arbol->comparar(nodo->clave,clave) <0){
		return abb_buscar_recursivo(nodo->der,arbol,clave);
	}

	return NULL; //SI EL NODO NO EXISTE EN EL ARBOL DEVUELVE NULL
}

void abb_destruir_recursivo(nodo_t* nodo){
	if (nodo == NULL) return;
	abb_destruir_recursivo(nodo->der);
	abb_destruir_recursivo(nodo->izq);
	free(nodo->clave);
	free(nodo);
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ABB 						   *
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
	abb_t* abb = malloc(sizeof(abb_t));
	if(abb == NULL) return NULL;
	abb->comparar = cmp;
	abb->destructor = destruir_dato;
	abb->cantidad = 0;
	abb->nodo = NULL;
	return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	if (arbol == NULL) return false;
	//Creo un nodo
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(nodo == NULL) return false;
	nodo->clave =  strdup(clave);
	nodo->dato = dato;
	nodo->izq = NULL;
	nodo->der = NULL;		
	if (abb_guardar_recursivo(arbol,arbol->nodo,nodo,clave)) return true;
	return false;
}

void *abb_borrar(abb_t *arbol, const char *clave){
	return	NULL;
}

size_t abb_cantidad(abb_t *arbol){
	return arbol->cantidad;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	if (arbol->nodo == NULL) return NULL;
	nodo_t* nodo = abb_buscar_recursivo(arbol->nodo,arbol,clave); //busco nodo segun clave
	if (nodo == NULL) return NULL;
	return nodo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	if (arbol->nodo == NULL) return NULL;
	nodo_t* nodo = abb_buscar_recursivo(arbol->nodo,arbol,clave); //busco nodo segun clave
	if (nodo != NULL) return true; // Si la la clave no existe en el arbol entonces el nodo sera NULL.
	return false;
}

void abb_destruir(abb_t *arbol){
	if (arbol->nodo == NULL){
		free(arbol);
		return;
	}
	abb_destruir_recursivo(arbol->nodo);
	free(arbol);
}

/* *****************************************************************
 *                       ITERADOR INTERNO 						   *
 * *****************************************************************/

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	if (!arbol->nodo) return;
	if(arbol->nodo->izq) arbol->nodo = arbol->nodo->izq;
	abb_in_order(arbol,visitar,extra);
	// hacer algo
	if(arbol->nodo->der) arbol->nodo = arbol->nodo->der;
	abb_in_order(arbol,visitar,extra);
}