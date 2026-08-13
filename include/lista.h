#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "nodo.h"

// Definiciones

struct Lista;
typedef struct Lista* ListaPtr;

// Constructor y destructor

/// @brief Crea una nueva lista vacía
ListaPtr crearLista();

/// @brief Elimina la lista con sus nodos, liberando la memoria recursivamente
void liberarLista(ListaPtr lista);

// Mostrar y ordenar con callbacks genericos

/// @brief Imprime por consola la lista con sus nodos y datos tomando la función callback mostrar()
void mostrarLista(ListaPtr lista, void(*mostrar)(DatoPtr));

/// @brief Toma una lista existente y con nodos no nulos, y procede a ordenarla mediante el algoritmo Bubble Sort
/// Toma como parámetro una función callback que será de ayuda para comparar los datos y ordenarlos correctamente
void ordenarMedianteBurbuja(ListaPtr lista, int (*comparar)(DatoPtr, DatoPtr));

// Insertar

/// @brief Inserta un nuevo nodo al principio de la lista con el dato especificado por parámetro
void insertarPrimero(ListaPtr lista, DatoPtr dato);

/// @brief Inserta un nuevo nodo al final de la lista con el dato especificado por parámetro
void insertarUltimo(ListaPtr lista, DatoPtr dato);

/// @brief Inserta en una posición válida de la lista el dato especificado por parámetro
void insertarEnPosicion(ListaPtr lista, DatoPtr dato, int posicion);


// Getters

/// @brief Obtiene el primer nodo de una lista no nula
NodoPtr getPrimero(ListaPtr lista);

/// @brief Inserta o reemplaza el valor del primer nodo de una lista no nula
void setPrimero(ListaPtr lista, NodoPtr nodo);

/// @brief Obtiene el ultimo nodo de una lista no nula
NodoPtr getUltimo(ListaPtr lista);

/// @brief Inserta o reemplaza el valor del ultimo nodo de una lista no nula
void setUltimo(ListaPtr lista, NodoPtr nodo);
int getLargo(ListaPtr lista);

// Eliminar

/// @brief Elimina y libera memoria el primer nodo de una lista no nula
void eliminarPrimero(ListaPtr lista);

/// @brief Elimina y libera memoria el ultimo nodo de una lista no nula
void eliminarUltimo(ListaPtr lista);

/// @brief Elimina y libera memoria un nodo de una lista no nula en la posición valida especificada
void eliminarEnPosicion(ListaPtr lista, int posicion);

/// @brief Elimina un nodo no nulo pasado por parámetro de una lista no nula. El metodo de esta eliminacion es por
/// comparación de dirección de memoria
void eliminar(ListaPtr lista, NodoPtr nodo);

/// @brief Elimina un nodo no nulo pasado pr parametro de una lista no nula que cumpla X condicion, siendo esa condicion
/// dictada por la funcion callback condicion(DatoPtr)
void eliminarPorCondicion(ListaPtr lista, int(*condicion)(DatoPtr));

float realizarCalculoEntreNodos(ListaPtr lista, float(*calculo)(DatoPtr, DatoPtr));

#endif // LISTA_H_INCLUDED
