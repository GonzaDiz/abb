#ifndef ABB_H
#define ABB_H

#include <stdbool.h>

/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct abb;  // Definición completa en abb.c.
typedef struct abb abb_t;


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

void *abb_borrar(abb_t *arbol, const char *clave);

void *abb_obtener(const abb_t *arbol, const char *clave);

bool abb_pertenece(const abb_t *arbol, const char *clave);

// Devuelve la cantidad de nodos en el arbol
// PRE: el abb esta creado
size_t abb_cantidad(abb_t *arbol);

void abb_destruir(abb_t *arbol);

/* *****************************************************************
 *                    PRUEBAS PARA EL ABB
 * *****************************************************************/

void pruebas_abb_alumno(void);

#endif // ABB_H
