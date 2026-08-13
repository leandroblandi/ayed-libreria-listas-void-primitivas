#include <stdlib.h>
#include "../include/nodo.h"

struct Nodo {
    DatoPtr dato;
    NodoPtr siguiente;
};

NodoPtr crearNodo(DatoPtr dato, NodoPtr siguiente) {
    NodoPtr nodo = (NodoPtr) malloc(sizeof(struct Nodo));

    if (!nodo) {
        return nodo;
    }

    nodo->dato = dato;
    nodo->siguiente = siguiente;

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
