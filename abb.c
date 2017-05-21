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

/* Definicion del iterador externo */
struct abb_iter {
	abb_t* arbol;
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
		void* dato = nuevoNodo->dato;
		nodo->dato = dato;
		//free(nodo->clave);
		//free(nodo);
		free(nuevoNodo->clave);
		free(nuevoNodo);
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

bool es_hoja(nodo_t* nodo){
	if (nodo->izq == NULL && nodo->der == NULL) return true;
	return false;
}

void* liberar_nodo(nodo_t* nodo,abb_t* arbol){
	void* dato = nodo->dato;
	if (arbol->destructor) arbol->destructor(arbol->nodo->dato);
	arbol->cantidad--;
	free(nodo->clave);
	free(nodo);
	return dato;
}

void* buscar_minimo(nodo_t* nodo){
	if (nodo->izq == NULL) return nodo;
	return buscar_minimo(nodo->izq);
}

void* abb_borrar_recursivo(nodo_t* nodo,nodo_t* nodoAnterior,abb_t* arbol,const char *clave){
	//PRE: La clave esta en el arbol
	//Si entro en esta funcion entonces es por que la clave si esta en el arbol.

	if(arbol->comparar(nodo->clave,clave) == 0){
		// caso1: borrar una hoja (nodo que no tiene hijos)
		if (es_hoja(nodo)){
			if (nodoAnterior){
				if (nodoAnterior->izq == nodo) nodoAnterior->izq = NULL;
				else nodoAnterior->der = NULL;
			}
			void* dato = liberar_nodo(nodo,arbol);
			if (nodoAnterior == NULL) arbol->nodo = NULL;
			return dato;
		}
		// caso2: borrar un nodo con solamente un hijo
		else if((nodo->izq == NULL && nodo->der != NULL) || (nodo->der == NULL && nodo->izq !=NULL)){
			if(!nodoAnterior){ 
				if (nodo->izq != NULL){
					arbol->nodo = nodo->izq;
				}
				else arbol->nodo = nodo->der;
				void* dato = liberar_nodo(nodo,arbol);
				return dato;
			}
			if (arbol->comparar(nodoAnterior->clave,clave) < 0){
				if (nodo->izq == NULL) nodoAnterior->der = nodo->der;
				else nodoAnterior->der = nodo->izq;
			}
			else {
				if(nodo->izq == NULL) nodoAnterior->izq = nodo->der;
				else nodoAnterior->izq = nodo->izq;
			}
			void* dato = liberar_nodo(nodo,arbol);
			return dato; 			
		}
		// caso3: borrar un nodo con 2 hijos
		else {
			nodo_t* nodoMinimo = buscar_minimo(nodo->der); // devuelve el 
			// entonces quiero hacer un swap entre nodoMinimo y nodo
			void* dato = nodo->dato;
			char* claveAux = strdup(nodoMinimo->clave);
			void* datoAux = abb_borrar(arbol,claveAux);
			free(nodo->clave);
			nodo->clave = claveAux;
			nodo->dato = datoAux;
			return dato;
		}
	}
	else if (arbol->comparar(nodo->clave,clave) > 0){ 
		return abb_borrar_recursivo(nodo->izq,nodo,arbol,clave);
	}
	else if (arbol->comparar(nodo->clave,clave) <0){
		return abb_borrar_recursivo(nodo->der,nodo,arbol,clave);
	}
	return NULL;
}

void abb_destruir_recursivo(nodo_t* nodo,abb_t* arbol){
	if (nodo == NULL) return;
	abb_destruir_recursivo(nodo->der,arbol);
	abb_destruir_recursivo(nodo->izq,arbol);
	if (arbol->destructor) arbol->destructor(arbol->nodo->dato);
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
	return abb_guardar_recursivo(arbol,arbol->nodo,nodo,clave);
}

void *abb_borrar(abb_t *arbol, const char *clave){
	if (!abb_pertenece(arbol,clave)) return NULL;
	return abb_borrar_recursivo(arbol->nodo,NULL,arbol,clave);
}

size_t abb_cantidad(abb_t *arbol){
	return arbol->cantidad;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	// esto se valida en la primer linea de abb buscar
	// if (arbol->nodo == NULL) return NULL;
	nodo_t* nodo = abb_buscar_recursivo(arbol->nodo,arbol,clave); //busco nodo segun clave
	if (nodo == NULL) return NULL;
	return nodo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	//esto se valida en la primer linea de abb buscar
	// if (arbol->nodo == NULL) return NULL;
	nodo_t* nodo = abb_buscar_recursivo(arbol->nodo,arbol,clave); //busco nodo segun clave
	if (nodo != NULL) return true; // Si la la clave no existe en el arbol entonces el nodo sera NULL.
	return false;
}

void abb_destruir(abb_t *arbol){
	// esta ya se valida en la primer linea de abb_destruir_recursivo!
	// if (arbol->nodo == NULL){
	// 	free(arbol);
	// 	return;
	// }
	abb_destruir_recursivo(arbol->nodo,arbol);
	free(arbol);
}

/* *****************************************************************
 *                       ITERADOR INTERNO 						   *
 * *****************************************************************/

void iterar_inorder(nodo_t* nodo, bool visitar(const char *, void *, void *), void *extra){
	if(!nodo) return;
	iterar_inorder(nodo->izq,visitar,extra);
	visitar(nodo->clave,nodo->dato,extra);
	iterar_inorder(nodo->der,visitar,extra);
}


void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	if (!arbol->nodo) return;
	iterar_inorder(arbol->nodo,visitar,extra);
}

/* *****************************************************************
 *                       ITERADOR EXTERNO 						   *
 * *****************************************************************/

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	abb_iter_t* iter = malloc(sizeof(abb_iter_t));
	if(!iter) return NULL;
	iter->arbol = arbol;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){

}
const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	return !iter->arbol->nodo ? NULL : iter->arbol->nodo>clave; 
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return !iter->arbol->nodo
}

void abb_iter_in_destruir(abb_iter_t* iter){
	free(iter);
}