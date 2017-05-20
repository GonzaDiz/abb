#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct abb;  // Definición completa en abb.c.
typedef struct abb abb_t;
typedef struct nodo nodo_t;


/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/
typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

// Crea un abb, recibe la funcion destrur_dato para ser utilizada en abb_destruir y en abb_insertar
// y abb_comparar_clave_t para comparar claves, en caso de fallar devuelve NULL
// POST: Crea un abb
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Guarda una clave y un dato es el nodo del abb que le corresponde
// PRE: el abb esta creado
// POST: guardo la clave y el dato en el lugar correspondiente
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

// Borra un nodo si este se encuentra en el abb
// PRE: el abb esta creado y la clave esta guardad en el abb
// POST: se borra el nodo que contiene la clave
void *abb_borrar(abb_t *arbol, const char *clave);

// Devuelve el valor de la clave en caso de estar en el arbol.
// PRE: el abb esta creado
// POST: busca la clave y si es que existe devuelve el valor que contiene.
void *abb_obtener(const abb_t *arbol, const char *clave);

// Devuelve true si la clave esta en el abb, false en caso contrario
// PRE: el abb esta creado
bool abb_pertenece(const abb_t *arbol, const char *clave);

// Devuelve la cantidad de nodos en el arbol
// PRE: el abb esta creado
size_t abb_cantidad(abb_t *arbol);

// Destruye el abb
// PRE: el abb fue creado
// POST: se libero la memoria consumida por el abb
void abb_destruir(abb_t *arbol);

/* *****************************************************************
 *               PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/


// itera a traves de abb de forma inorder y ejecuta visitar 
// devuelve true si tiene que seguir iterando, false en caso contrario
// PRE: el abb fue creado
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);



/* *****************************************************************
 *                    PRUEBAS PARA EL ABB
 * *****************************************************************/

void pruebas_abb_alumno(void);

#endif // ABB_H
