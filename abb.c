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

bool abb_guardar_recursivo(abb_t *arbol, nodo_t* nodo, const char *clave, void *dato){
	if(arbol->comparar(arbol->nodo->clave,clave) < 0){
		abb_guardar_recursivo(arbol,arbol->nodo->izq,clave,dato);
	}
	else if (arbol->comparar(arbol->nodo->clave,clave) > 0){
		abb_guardar_recursivo(arbol,arbol->nodo->der,clave,dato);	
	}
	else if (arbol->destructor) arbol->destructor(arbol->nodo->dato);

	return true; // PARA QUE COMPILE
}

// Busca un nodo en un arbol segun la clave, en caso de existir devuelve el nodo y en caso contrario devuelve null.
nodo_t* buscar_nodo(nodo_t* nodo,const abb_t* arbol, const char *clave){
	if (!nodo) return NULL;
	if (arbol->comparar(nodo->clave,clave) == 0){
		return nodo;
	}
	else if (arbol->comparar(nodo->clave,clave) > 0){
		return buscar_nodo(nodo->izq,arbol,clave);
	}
	else if (arbol->comparar(nodo->clave,clave) <0){
		buscar_nodo(nodo->der,arbol,clave);
	}
	return NULL; //SI EL NODO NO EXISTE EN EL ARBOL DEVUELVE NULL
}

/* *****************************************************************
 *                    PRIMITIVAS DEL ABB 						   *
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
	//Creo un nodo
	if(!arbol->nodo){
		nodo_t* nodo = malloc(sizeof(nodo_t));
		if(!nodo) return false;
		nodo->clave =  strdup(clave);
		nodo->dato = dato;
		nodo->izq = NULL;
		nodo->der = NULL;
		arbol->nodo = nodo;
		arbol->cantidad++;
		return true;
	}

	if (abb_guardar_recursivo(arbol,arbol->nodo,clave,dato)) return true;

	return true; // Para que compile
}

size_t abb_cantidad(abb_t *arbol){
	return arbol->cantidad;
}

void *abb_borrar(abb_t *arbol, const char *clave){
	return	NULL;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	if (!arbol->nodo) return NULL;
	nodo_t* nodo = buscar_nodo(arbol->nodo,arbol,clave);
	if (!nodo) return NULL;
	return nodo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	if (!arbol->nodo) return NULL;
	nodo_t* nodo = buscar_nodo(arbol->nodo,arbol,clave);
	if (!nodo) return true; // Si la la clave no existe en el arbol entonces el nodo sera NULL.
	return false;
}

void abb_destruir(abb_t *arbol){
	return;
}