#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

// Definiciones

struct Nodo;
typedef struct Nodo* NodoPtr;
typedef void* DatoPtr;

// Constructor y Destructor

/// @brief Crea un nuevo nodo con el dato especificado y un nodo siguiente que podrá ser nulo
NodoPtr crearNodo(DatoPtr dato, NodoPtr siguiente);

/// @brief Libera de la memoria un nodo especificado por parámetro, el mismo no debe ser nulo
void liberarNodo(NodoPtr nodo);

// Getters y Setters

/// @brief Obtiene el valor de un nodo especificado por parámetro. El tipo de dato es void*, por lo que debera desreferenciarse
/// con el tipo de dato correcto
DatoPtr getDato(NodoPtr nodo);

/// @brief Reemplaza el valor del dato de un nodo existente
void setDato(NodoPtr nodo, DatoPtr dato);

/// @brief Obtiene la referencia al Nodo siguiente a partir de un nodo especificado por parametro
NodoPtr getSiguiente(NodoPtr nodo);

/// @brief Reemplaza el valor del siguiente nodo por el especificado por parametro
void setSiguiente(NodoPtr nodo, NodoPtr nuevoSiguiente);

#endif // NODO_H_INCLUDED
