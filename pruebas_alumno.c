/*
 * prueba_hash.c
 * Pruebas para el tipo de dato abstracto Tabla de Hash
 * Copyright: (2011) Margarita Manterola, Maximiliano Curia
 * Licencia: CC-BY-SA 2.5 (ar) ó CC-BY-SA 3.0
 */

#include "abb.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/
static void prueba_crear_abb_vacio()
{
    abb_t* abb = abb_crear(strcmp,NULL);
    char* str = "test";
    print_test("Prueba crear abb vacio", abb);
    print_test("Prueba la cantidad de nodos en el abb es igual a 0", abb_cantidad(abb) == 0);
    print_test("Prueba buscar una clave en un abb vacio devuelve NULL",!abb_obtener(abb,str));
    print_test("Prueba ver si un valor esta en el abb y la clave no existe devuelve NULL",!abb_pertenece(abb,str));
    abb_destruir(abb);
    print_test("El arbol se destruyo correctamente",true);
}

static void pruebas_abb_guardar(){
	abb_t* abb = abb_crear(strcmp,NULL);
	char* clave = "a";
	char* dato = "a";

	print_test("Prueba crear abb vacio", abb);
    print_test("Prueba la cantidad de nodos en el abb es igual a 0", abb_cantidad(abb) == 0);
	print_test("Prueba guardar un nodo de raiz",abb_guardar(abb,clave,dato) == true);
	print_test("Prueba la cantidad de nodos en el abb es igual a 1", abb_cantidad(abb) == 1);
	print_test("Prueba abb obtener devuelve a",abb_obtener(abb,clave) == dato);
	print_test("Prueba abb pertenece devuelve true con clave a", abb_pertenece(abb,clave) == true);
	print_test("Prueba abb pertenese devuelve false con clave b", abb_pertenece(abb,"b") == false);
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * *****************************************************************/


void pruebas_abb_alumno()
{
    /* Ejecuta todas las pruebas unitarias. */
	prueba_crear_abb_vacio();
	pruebas_abb_guardar();
}
