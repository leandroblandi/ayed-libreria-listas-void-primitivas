#include <stdio.h>
#include <stdlib.h>

#include "../include/lista.h"

struct Lista {
    NodoPtr primero;
    int largo;
};

ListaPtr crearLista() {
    ListaPtr lista = (ListaPtr) malloc(sizeof(struct Lista));

    if (!lista) {
        return NULL;
    }

    lista->primero = NULL;
    lista->largo = 0;

    return lista;
}

void liberarLista(ListaPtr lista) {

    if (!lista) {
        return;
    }

    NodoPtr nodoActual = lista->primero;

    while (nodoActual) {
        NodoPtr nodoAux = nodoActual;
        nodoActual = getSiguiente(nodoActual);
        free(nodoAux);
    }
}

void mostrarLista(ListaPtr lista, void(*mostrar)(DatoPtr)) {
    if (!lista || lista->primero == NULL || lista->largo == 0) {
        printf("\nLa lista esta vacia.");
        return;
    }

    NodoPtr nodoActual = lista->primero;

    while (nodoActual) {
        DatoPtr datoNodo = getDato(nodoActual);
        mostrar(datoNodo);
        nodoActual = getSiguiente(nodoActual);
    }

    printf("\n");
}

void ordenarMedianteBurbuja(ListaPtr lista, int (*comparar)(DatoPtr, DatoPtr)) {
    if (lista == NULL || lista->primero == NULL || lista->largo == 0) {
        printf("La lista esta vacia y no se puede ordenar.");
        return;
    }

    if (comparar == NULL) {
        printf("La funcion de comparacion es nula y no se puede ordenar");
        return;
    }

    if (lista->largo == 1) {
        printf("La lista ya esta ordenada");
        return;
    }

    NodoPtr nodoIterador = lista->primero;

    while (nodoIterador) {
        NodoPtr nodoActual = lista->primero;

        while (nodoActual) {
            NodoPtr nodoSiguiente = getSiguiente(nodoActual);

            if (!nodoSiguiente) {
                break;
            }

            if (comparar(getDato(nodoActual), getDato(nodoSiguiente)) > 0) {
                DatoPtr datoActual = getDato(nodoActual);
                DatoPtr datoSiguiente = getDato(nodoSiguiente);

                setDato(nodoActual, datoSiguiente);
                setDato(nodoSiguiente, datoActual);
            }

            nodoActual = nodoSiguiente;
        }

        nodoIterador = getSiguiente(nodoIterador);
    }
}

void insertarPrimero(ListaPtr lista, DatoPtr dato) {

    if (!lista || dato == NULL) {
        return;
    }

    NodoPtr nuevoNodo;

    if (lista->primero) {
        nuevoNodo = crearNodo(dato, lista->primero);
        lista->primero = nuevoNodo;
        lista->largo++;
        return;
    }

    nuevoNodo = crearNodo(dato, NULL);
    lista->primero = nuevoNodo;
    lista->largo++;
}

void insertarUltimo(ListaPtr lista, DatoPtr dato) {
    if (!lista || !dato) {
        printf("\nLa lista es nula o el dato es nulo");
        return;
    }

    if (lista->largo == 0) {
        insertarPrimero(lista, dato);
        return;
    }

    NodoPtr nodoUltimo = getUltimo(lista);

    if (!nodoUltimo) {
        return;
    }

    NodoPtr nuevoNodo = crearNodo(dato, NULL);
    setSiguiente(nodoUltimo, nuevoNodo);
    lista->largo++;
}

void insertarEnPosicion(ListaPtr lista, DatoPtr dato, int posicion) {
    if (!lista || !dato) {
        printf("\nLa lista es nula o el dato es nulo");
        return;
    }

    if (posicion < 0 || posicion >= lista->largo) {
        printf("\nEl valor de la posicion a insertar es invalido");
        return;
    }

    int largoLista = getLargo(lista);

    if (posicion == 0) {
        insertarPrimero(lista, dato);
    }

    else if (posicion == largoLista) {
        insertarUltimo(lista, dato);
    }

    else if (posicion > 0 && posicion < largoLista) {
        NodoPtr actual = lista->primero;

        // recorro hasta una posicion anterior a la deseada
        for (int i = 0; i < posicion - 1; i++) {
            actual = getSiguiente(actual);
        }

        // seteo la siguiente posicion, q es la deseada, y muevo el nodo al siguiente
        setSiguiente(actual, crearNodo(dato, getSiguiente(actual)));
    }
}

NodoPtr getPrimero(ListaPtr lista) {
    if (!lista) {
        printf("\nLa lista esta vacia");
        return NULL;
    }

    return lista->primero;
}

void setPrimero(ListaPtr lista, NodoPtr nodo) {
    if (!lista) {
        printf("\nLa lista esta vacia");
        return;
    }

    if (!nodo) {
        printf("\nEl nodo a insertar es nulo");
    }

    lista->primero = nodo;
}

NodoPtr getUltimo(ListaPtr lista) {
    if (lista == NULL || lista->primero == NULL) {
        return NULL;
    }

    if (lista->largo == 1) {
        return lista->primero;
    }

    NodoPtr nodoActual = lista->primero;

    while (nodoActual) {
        if (getSiguiente(nodoActual) == NULL) {
            break;
        }
        nodoActual = getSiguiente(nodoActual);
    }

    return nodoActual;
}

void setUltimo(ListaPtr lista, NodoPtr nodo) {
    if (!lista || lista->largo == 0) {
        printf("\nLa lista esta vacia");
        return;
    }

    if (!nodo) {
        printf("\nEl nodo a insertar es nulo");
        return;
    }

    if (lista->largo == 1) {
        setPrimero(lista, nodo);
        return;
    }

    int i = 0;
    NodoPtr nodoActual = lista->primero;

    while (nodoActual) {
        if (i == lista->largo - 2) {
            NodoPtr nodoSiguiente = getSiguiente(nodoActual);  // 1, 2, [3] -> con [] selecciono
            liberarNodo(nodoSiguiente); // libero, entonces queda 1, 2, NULL
            setSiguiente(nodo, NULL); // queda <NUEVO:nodo> y NULL como siguiente
            setSiguiente(nodoActual, nodo); // enlazo, 1, 2 <-> NUEVO, NULL
            break;
        }

        nodoActual = getSiguiente(nodoActual);
        i++;
    }
}

int getLargo(ListaPtr lista) {
    if (!lista) {
        printf("\nLa lista es nula");
        return -1;
    }

    return lista->largo;
}

void eliminarPrimero(ListaPtr lista) {
    if (!lista || lista->primero == NULL || lista->largo == 0) {
        printf("\nLa lista esta vacia");
        return;
    }

    if (lista->largo == 1) {
        liberarNodo(lista->primero);
        lista->primero = NULL;
        lista->largo--;
        return;
    }

    NodoPtr nodoAuxiliar = lista->primero;
    NodoPtr nodoSiguiente = getSiguiente(lista->primero);
    lista->primero = nodoSiguiente;
    liberarNodo(nodoAuxiliar);
    lista->largo--;
}

void eliminarUltimo(ListaPtr lista) {
    if (!lista || lista->primero == NULL || lista->largo == 0) {
        printf("\nLa lista esta vacia");
        return;
    }

    if (lista->largo == 1) {
        eliminarPrimero(lista);
        return;
    }

    NodoPtr nodoActual = lista->primero;
    int i = 0;

    while (nodoActual) {

        if (i == lista->largo - 2) {
            setSiguiente(nodoActual, NULL);
            NodoPtr nodoSiguiente = getSiguiente(nodoActual);
            liberarNodo(nodoSiguiente);
            lista->largo--;
            break;
        }

        nodoActual = getSiguiente(nodoActual);
        i++;
    }
}

void eliminarEnPosicion(ListaPtr lista, int posicion) {
    if (!lista || lista->primero == NULL || lista->largo == 0) {
        printf("\nLa lista esta vacia");
        return;
    }

    if (posicion == 0) {
        eliminarPrimero(lista);
        return;
    }

    // si es el ultimo nodo
    if (posicion == lista->largo - 1) {
        eliminarUltimo(lista);
        return;
    }

    int i = 0;
    NodoPtr nodoActual = lista->primero;

    while (nodoActual) {

        // parado en una posicion anterior a la deseada
        if (i == posicion - 1) {
            // obtengo el nodo a eliminar, y el siguiente a ese
            NodoPtr nodoEliminar = getSiguiente(nodoActual);
            NodoPtr nodoSiguiente = getSiguiente(nodoEliminar);
            // seteo como siguiente del nodo actual, el nodo proximo al nodo a eliminar
            setSiguiente(nodoActual, nodoSiguiente);
            // elimino el nodo y decremento el tam de la lista
            liberarNodo(nodoEliminar);
            lista->largo--;
            break;
        }

        nodoActual = getSiguiente(nodoActual);
        i++;
    }
}

void eliminar(ListaPtr lista, NodoPtr nodo) {
    if (!lista || lista->primero == NULL || lista->largo == 0) {
        printf("\nLa lista esta vacia");
        return;
    }

    if (lista->largo == 1) {
        eliminarPrimero(lista);
        return;
    }

    NodoPtr nodoActual = lista->primero;

    // si el nodo en el q estoy parado es el q quiero eliminar
    if (nodoActual == nodo) {
        setPrimero(lista, getSiguiente(nodoActual));
        liberarNodo(nodoActual);
        lista->largo--;
        return;
    }

    while (nodoActual) {
        NodoPtr nodoProximo = getSiguiente(nodoActual);

        // si el nodo siguiente es el q quiero eliminar
        if (nodoProximo == nodo) {
            // entonces agarro el siguiente al nodo a eliminar
            NodoPtr nodoSiguienteAlEliminar = getSiguiente(nodoProximo);
            // y seteo como nodo proximo al actual el siguiente al eliminar
            setSiguiente(nodoActual, nodoSiguienteAlEliminar);
            // libero el nodo proximo, q es el q hay q eliminar y decremento el tam de la lista
            liberarNodo(nodoProximo);
            lista->largo--;
            break;
        }

        nodoActual = nodoProximo;
    }
}

void eliminarPorCondicion(ListaPtr lista, int(*condicion)(DatoPtr)) {
    if (!lista || lista->primero == NULL || lista->largo == 0) {
        printf("\nLa lista esta vacia");
        return;
    }

    NodoPtr nodoActual = lista->primero;

    // si elimino el nodo actual, no va a haber forma de seguir recorriendo, entonces almaceno por las dudas
    // el nodo proximo, y si tengo q eliminar el actual, no pierdo la referencia
    while (nodoActual) {
        NodoPtr nodoProximo = getSiguiente(nodoActual);

        if (condicion(getDato(nodoActual))) {
            eliminar(lista, nodoActual);
        }

        nodoActual = nodoProximo;
    }
}

float realizarCalculoEntreNodos(ListaPtr lista, float(*calculo)(DatoPtr, DatoPtr)) {
     if (!lista || !calculo) {
         return -999.00f;
     }

    NodoPtr nodoActual = lista->primero;
    float sumatoria = 0.0f;

    while (nodoActual) {
        NodoPtr nodoProximo = getSiguiente(nodoActual);

        if (nodoProximo != NULL) {
            DatoPtr d1 = getDato(nodoActual);
            DatoPtr d2 = getDato(nodoProximo);
            sumatoria = sumatoria + calculo(d1, d2);
        }

        nodoActual = nodoProximo;
    }

    return sumatoria;
}