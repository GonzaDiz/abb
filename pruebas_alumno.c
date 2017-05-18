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
static void prueba_crear_abb_vacio(){
	printf("---------------------------PRUEBAS CREAR ABB VACIO---------------------------\n");
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
	printf("---------------------------PRUEBAS ABB GUARDAR---------------------------\n");
	abb_t* abb = abb_crear(strcmp,NULL);
	char* claves[] = {"f","z","d","a"};
	char* datos[] = {"f","z","d","a"};
	print_test("Prueba crear abb vacio", abb);
    print_test("Prueba la cantidad de nodos en el abb es igual a 0", abb_cantidad(abb) == 0);

    // Prueba guardar el primer elemento
	print_test("Prueba guardar un nodo de raiz",abb_guardar(abb,claves[0],datos[0]) == true);
	print_test("Prueba la cantidad de nodos en el abb es igual a 1", abb_cantidad(abb) == 1);
	print_test("Prueba abb obtener devuelve f",abb_obtener(abb,claves[0]) == datos[0]);
	print_test("Prueba abb pertenece devuelve true con clave f", abb_pertenece(abb,claves[0]) == true);

	// Prueba guardar un segundo elemento el cual es mayor, hijo derecho
	print_test("Prueba abb pertenee devuelve false con clave z", abb_pertenece(abb,claves[1]) == false);
	print_test("Prueba guardar un nodo con clave z", abb_guardar(abb,claves[1],datos[1]) == true);
	print_test("Prueba la cantidad de nodos en el abb es igual a 2", abb_cantidad(abb) == 2);
	print_test("Prueba abb obtener de clave z devuelve z", abb_obtener(abb,claves[1]) == datos[1]);
	print_test("Prueba abb pertence devuelve true con clave z", abb_pertenece(abb,claves[1]) == true);

	//	Prueba guardar un tercer elemento el cual es menor, hijo izquierdo
	print_test("Prueba guardar un nodo con clave d", abb_guardar(abb,claves[2],datos[2]) == true);
	print_test("Prueba la cantidad de nodos en el abb es igual a 3", abb_cantidad(abb) == 3);
	print_test("Prueba abb obtener de clave d devuelve d", abb_obtener(abb,claves[2]) == datos[2]);
	print_test("Prueba abb pertence devuelve true con clave d", abb_pertenece(abb,claves[2]) == true);

	print_test("Prueba guardar un nodo con clave a", abb_guardar(abb,claves[3],datos[3]) == true);
	print_test("Prueba la cantidad de nodos en el abb es igual a 4", abb_cantidad(abb) == 4);
	print_test("Prueba abb obtener de clave a devuelve a", abb_obtener(abb,claves[3]) == datos[3]);
	print_test("Prueba abb pertence devuelve true con clave a", abb_pertenece(abb,claves[3]) == true);

	abb_destruir(abb);
	print_test("El arbol se destruyo correctamente",true);

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
