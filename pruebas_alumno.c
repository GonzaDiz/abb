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
#include <time.h>


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

static void pruebas_abb_guardar_claves_iguales(){
	printf("---------------------------PRUEBAS ABB GUARDAR CLAVES IGUALES---------------------------\n");
	abb_t* abb = abb_crear(strcmp,NULL);
	char* claves[] = {"f","a","f","a"};
	char* datos[] = {"f","a","f2","a2"};
	print_test("Prueba crear abb vacio", abb);
    print_test("Prueba la cantidad de nodos en el abb es igual a 0", abb_cantidad(abb) == 0);

  // Prueba guardar el primer elemento
	print_test("Prueba guardar un nodo de raiz",abb_guardar(abb,claves[0],datos[0]) == true);
	print_test("Prueba la cantidad de nodos en el abb es igual a 1", abb_cantidad(abb) == 1);
	print_test("Prueba abb obtener devuelve f",abb_obtener(abb,claves[0]) == datos[0]);
	print_test("Prueba abb pertenece devuelve true con clave f", abb_pertenece(abb,claves[0]) == true);

	print_test("Prueba abb pertenee devuelve false con clave a", abb_pertenece(abb,claves[1]) == false);
	print_test("Prueba guardar un nodo con clave a", abb_guardar(abb,claves[1],datos[1]) == true);
	print_test("Prueba la cantidad de nodos en el abb es igual a 2", abb_cantidad(abb) == 2);
	print_test("Prueba abb obtener de clave a devuelve a", abb_obtener(abb,claves[1]) == datos[1]);
	print_test("Prueba abb pertence devuelve true con clave a", abb_pertenece(abb,claves[1]) == true);

	//	Prueba guardar un tercer elemento el cual es menor, hijo izquierdo
	print_test("Prueba guardar un nodo con clave f", abb_guardar(abb,claves[2],datos[2]) == true);
	print_test("Prueba la cantidad de nodos en el abb es igual a 2", abb_cantidad(abb) == 2);
	print_test("Prueba abb obtener de clave f devuelve f", abb_obtener(abb,claves[2]) == datos[2]);
	print_test("Prueba abb pertence devuelve true con clave d", abb_pertenece(abb,claves[2]) == true);

	print_test("Prueba guardar un nodo con clave a", abb_guardar(abb,claves[3],datos[3]) == true);
	print_test("Prueba la cantidad de nodos en el abb es igual a 2", abb_cantidad(abb) == 2);
	print_test("Prueba abb obtener de clave a devuelve a", abb_obtener(abb,claves[3]) == datos[3]);
	print_test("Prueba abb pertence devuelve true con clave a", abb_pertenece(abb,claves[3]) == true);

	abb_destruir(abb);
	print_test("El arbol se destruyo correctamente",true);

}

static void pruebas_abb_borrar_hojas(){
	printf("---------------------------PRUEBAS ABB BORRAR---------------------------\n");
	abb_t* abb = abb_crear(strcmp,NULL);
	char* claves[] = {"f","z","d","a"};
	char* datos[] = {"f","z","d","a"};
	print_test("Guardar clave f en el abb",abb_guardar(abb,claves[0],datos[0]) == true);
	print_test("Guardar clave z en el abb",abb_guardar(abb,claves[1],datos[1]) == true);
	print_test("Guardar clave d en el abb",abb_guardar(abb,claves[2],datos[2]) == true);
	print_test("Guardar clave a en el abb",abb_guardar(abb,claves[3],datos[3]) == true);
	print_test("Prueba cantidad es igual a 4", abb_cantidad(abb) == 4);
	print_test("Intento borrar una clave que no existe es NULL", abb_borrar(abb,"i") == NULL);
	print_test("Prueba cantidad es igual a 4", abb_cantidad(abb) == 4);
	print_test("Prueba borrar hoja a", abb_borrar(abb,claves[3]) == claves[3]);
	print_test("Prueba a ya no pertenece al arbol", abb_pertenece(abb,claves[3]) == false);
	print_test("Prueba cantidad es igual a 3", abb_cantidad(abb) == 3);
	print_test("Prueba borrar hoja z", abb_borrar(abb,claves[1]) == claves[1]);
	print_test("Prueba z ya no pertenece al arbol", abb_pertenece(abb,claves[1]) == false);
	print_test("Prueba cantidad es igual a 2", abb_cantidad(abb) == 2);
	print_test("Prueba borrar hoja d", abb_borrar(abb,claves[2]) == claves[2]);
	print_test("Prueba d ya no pertenece al arbol", abb_pertenece(abb,claves[2]) == false);
	print_test("Prueba cantidad es igual a 1", abb_cantidad(abb) == 1);

	print_test("Prueba borrar raiz/hoja f", abb_borrar(abb,claves[0]) == claves[0]);
	print_test("Prueba f ya no pertenece al arbol", abb_pertenece(abb,claves[0]) == false);
	print_test("Prueba cantidad es igual a 0", abb_cantidad(abb) == 0);

	abb_destruir(abb);
	print_test("El arbol se destruyo correctamente",true);
}

static void pruebas_abb_borrar_nodo_con_un_hijo(){
	printf("-------------------PRUEBAS ABB BORRAR UN HIJO---------------------------\n");
	abb_t* abb = abb_crear(strcmp,NULL);
	char* claves[] = {"f","x","d","a","z"};
	char* datos[] = {"f","x","d","a","z"};
	print_test("Guardar clave f en el abb",abb_guardar(abb,claves[0],datos[0]) == true);
	print_test("Guardar clave x en el abb",abb_guardar(abb,claves[1],datos[1]) == true);
	print_test("Guardar clave d en el abb",abb_guardar(abb,claves[2],datos[2]) == true);
	print_test("Guardar clave a en el abb",abb_guardar(abb,claves[3],datos[3]) == true);
	print_test("Guardar clave z en el abb",abb_guardar(abb,claves[4],datos[4]) == true);
	print_test("Prueba cantidad es igual a 5", abb_cantidad(abb) == 5);
	print_test("Prueba borrar nodo con un hijo y devuelve d", abb_borrar(abb,claves[2]) == datos[2]);
	print_test("Comprobar que d ya no pertenece al arbol", abb_pertenece(abb,claves[2]) == false);
	print_test("Comprobar que a pertenece al arbol", abb_pertenece(abb,claves[3]) == true);
	print_test("Prueba cantidad es igual a 4", abb_cantidad(abb) == 4);
	print_test("Prueba borrar nodo con un hijo x", abb_borrar(abb,claves[1]) == datos[1]);
	print_test("Prueba cantidad es igual a 3", abb_cantidad(abb) == 3);
	print_test("Prueba borrar hoja z", abb_borrar(abb,claves[4]) == datos[4]);
	print_test("Prueba z no pertenece al arbol", abb_pertenece(abb,claves[4]) == false);
	print_test("Prueba borrar raiz f", abb_borrar(abb,claves[0]) == datos[0]);
	print_test("Prueba cantidad es igual a 1", abb_cantidad(abb) == 1);
	abb_destruir(abb);
	print_test("El arbol se destruyo correctamente",true);

}

static void pruebas_abb_borrar_nodo_con_dos_hijos(){
	printf("-------------------PRUEBAS ABB BORRAR NODO CON DOS HIJOS------------------------\n");
	abb_t* abb = abb_crear(strcmp,NULL);
	char* claves[] = {"40","30","50","15","35","60","10","20","38"};
	char* datos[] = {"40","30","50","15","35","60","10","20","38"};
	
	bool ok = true;
	for (int i = 0; i<9; i++){
		ok = abb_guardar(abb,claves[i],datos[i]);
		if (!ok) break;
	}
	print_test("Prueba almacenar elementos", ok);
	print_test("Prueba cantidad es igual a 9", abb_cantidad(abb) == 9);
	print_test("Prueba borrar nodo 30 con dos hijos", abb_borrar(abb,claves[1]) == datos[1]);
	print_test("Prueba cantidad es igual a 8", abb_cantidad(abb) == 8);
	print_test("Pruebo que el nodo 30 ya no existe", abb_pertenece(abb,claves[1]) == false);
	print_test("Prueba borrar nodo 35 con dos hijos", abb_borrar(abb,claves[4]) == datos[4]);
	print_test("Prueba cantidad es igual a 7", abb_cantidad(abb) == 7);
	print_test("Pruebo que el nodo 35 ya no pertenece", abb_pertenece(abb,claves[4]) == false);
	print_test("Pruebo borrar nodo 15 con dos hijos", abb_borrar(abb,claves[3]) == datos[3]);
	print_test("Prueba cantidad es igual a 6",abb_cantidad(abb) == 6);
	print_test("Pruebo que 15 ya no pertenece", abb_pertenece(abb,claves[3]) == false);
	abb_destruir(abb);
	print_test("El arbol se destruyo correctamente",true);
}

static void pruebas_abb_volumen(size_t largo){
	printf("-------------------PRUEBAS ABB VOLUMEN ------------------------\n");
	abb_t* abb = abb_crear(strcmp,NULL);

	const size_t largo_clave = 10;
	char (*claves)[largo_clave] = malloc (largo * largo_clave);
	char (*datos)[largo_clave] = malloc (largo * largo_clave);

	time_t t;
	srand((unsigned) time(&t));
	bool ok = true;
	for (int i = 0;i <largo;i++){
		sprintf(claves[i], "%08d",(rand() % 500000));

		//Me aseguro que no haya claves repetidas asi puedo probar pertenece y obtener sin tantos problemas
		while (abb_pertenece(abb,claves[i])){
			sprintf(claves[i], "%08d", (rand() % 500000));
		}
		strcpy(datos[i],claves[i]);
		//sprintf(datos[i],"%08d", claves[i]);
		ok = abb_guardar(abb,claves[i],datos[i]);
		if (!ok) break;
		//printf("%08d\n",rand() % i);
	}
	print_test("Prueba abb guardar muchos elementos", ok);
	print_test("Prueba abb cantidad",abb_cantidad(abb) == largo);

	for (int i = 0;i < largo; i++){
		ok = abb_pertenece(abb,claves[i]);
		if (!ok) break;

		ok = abb_obtener(abb,claves[i]) == datos[i];
		if (!ok) break; 
 	}

 	print_test("Las claves y los datos pertenecen al abb",ok);

 	for (int i=0; i<(largo/2);i++){
 		ok = abb_borrar(abb,claves[i]) == datos[i];
 		if (!ok) break;
 	}

 	print_test("Borrar la mitad del abb es ok",ok);

	abb_destruir(abb);
	free(claves);
	free(datos);
}


bool buscar_dato(const char* clave, void* datos, void* extra){
  if(datos == extra) return false;
  return true;
 }

static void pruebas_abb_iterador_interno(){
printf("-------------------PRUEBAS ABB ITERARDOR INTERNO-----------------------\n");
  abb_t* abb = abb_crear(strcmp,NULL);
  char* claves[] = {"40","30","50","15","35","60","10","20","38"};
  char* datos[] = {"40","30","50","15","35","60","10","20","38"};
  
  bool ok = true;
  for (int i = 0; i<9; i++){
    ok = abb_guardar(abb,claves[i],datos[i]);
    if (!ok) break;
  }
  print_test("Prueba almacenar elementos", ok);
  abb_in_order(abb,buscar_dato,datos[4]);
  print_test("No se modifico la posicion inicial de abb",abb_obtener(abb,claves[0]) == datos[0]);
  abb_destruir(abb);
  print_test("El arbol se destruyo correctamente",true);
}

/* ******************************************************************
 *                        FUNCIÓN PRINCIPAL
 * ******************************************************************/


void pruebas_abb_alumno()
{
  /* Ejecuta todas las pruebas unitarias. */
	prueba_crear_abb_vacio();
	pruebas_abb_guardar();
	pruebas_abb_guardar_claves_iguales();
	pruebas_abb_borrar_hojas();
	pruebas_abb_borrar_nodo_con_un_hijo();
	pruebas_abb_borrar_nodo_con_dos_hijos();
	pruebas_abb_volumen(5000);
  pruebas_abb_iterador_interno();
}
