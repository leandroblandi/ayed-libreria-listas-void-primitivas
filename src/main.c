#include <stdio.h>
#include "lista.h"

int compararEnteros(DatoPtr d1, DatoPtr d2);
void mostrarEntero(DatoPtr d1);
void crearLista_debeInsertarDatosYMostrarCorrectamente();

int main () {
    crearLista_debeInsertarDatosYMostrarCorrectamente();
    return 0;
}

void crearLista_debeInsertarDatosYMostrarCorrectamente() {
    ListaPtr lista = crearLista();

    int n1 = 2;
    insertarUltimo(lista, &n1);

    int n2 = 1;
    insertarPrimero(lista, &n2);

    int n3 = 32;
    insertarPrimero(lista, &n2);

    int n4 = 12;
    insertarEnPosicion(lista, &n4, 1);

    ordenarMedianteBurbuja(lista, &compararEnteros);
    mostrarLista(lista, &mostrarEntero);

    liberarLista(lista);
}

int compararEnteros(DatoPtr d1, DatoPtr d2) {
    if (!d1 || !d2) return -1;

    int n1 = *((int*) d1);
    int n2 = *((int*) d2);

    if (n1 == n2) {
        return 0;
    }

    if (n1 > n2) {
        return 1;
    }

    return -1;
}

void mostrarEntero(DatoPtr d1) {
    if (!d1) return;
    int n1 = *((int*) d1);
    printf("%d, ", n1);
}