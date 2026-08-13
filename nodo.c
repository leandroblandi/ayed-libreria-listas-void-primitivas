#include <stdlib.h>
#include <string.h>
#include "nodo.h"

struct Nodo {
    DatoPtr dato;
    NodoPtr siguiente;
};

NodoPtr crearNodo(DatoPtr dato, int sizeOfTipoDato, NodoPtr siguiente) {
    NodoPtr nodo = (NodoPtr) malloc(sizeof(struct Nodo));

    if (!nodo) {
        return nodo;
    }

    nodo->dato = malloc(sizeOfTipoDato);
    nodo->siguiente = siguiente;
    memcpy(nodo->dato, dato, sizeOfTipoDato);

    return nodo; 
};

void liberarNodo(NodoPtr nodo) {

    if (!nodo) {
        return;
    }

    free(nodo);
};

DatoPtr getDato(NodoPtr nodo) {
    return nodo->dato;
};

void setDato(NodoPtr nodo, DatoPtr dato) {
    if (!nodo) {
        return;
    }

    nodo->dato = dato;
}

NodoPtr getSiguiente(NodoPtr nodo) {
    return nodo->siguiente;
};

void setSiguiente(NodoPtr nodo, NodoPtr nuevoSiguiente) {
    nodo->siguiente = nuevoSiguiente;
};
