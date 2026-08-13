# Librería de Listas Enlazadas Genéricas en C

![C](https://img.shields.io/badge/C-11-A8B9CC?style=flat-square&logo=c&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-4.3+-064F8C?style=flat-square&logo=cmake&logoColor=white)
![Build](https://img.shields.io/badge/build-executable-informational?style=flat-square)
![Licencia](https://img.shields.io/badge/licencia-no%20especificada-lightgrey?style=flat-square)

**Patrones y técnicas aplicadas**

![Opaque Pointer](https://img.shields.io/badge/patrón-Opaque%20Pointer-4B5563?style=flat-square)
![ADT](https://img.shields.io/badge/patrón-Abstract%20Data%20Type-4B5563?style=flat-square)
![Encapsulamiento](https://img.shields.io/badge/patrón-Encapsulamiento-4B5563?style=flat-square)
![Callbacks](https://img.shields.io/badge/patrón-Function%20Pointers%20%2F%20Callbacks-4B5563?style=flat-square)
![Void Generics](https://img.shields.io/badge/técnica-void%2A%20Generics-4B5563?style=flat-square)
![Singly Linked List](https://img.shields.io/badge/estructura-Singly%20Linked%20List-4B5563?style=flat-square)
![Bubble Sort](https://img.shields.io/badge/algoritmo-Bubble%20Sort-4B5563?style=flat-square)
![Manual Memory](https://img.shields.io/badge/memoria-malloc%20%2F%20free-4B5563?style=flat-square)

---

## Descripción

Librería en C que implementa una **lista simplemente enlazada de propósito general**, capaz de almacenar cualquier tipo de dato mediante punteros genéricos (`void*`). La estructura no conoce ni interpreta el contenido que almacena: delega toda operación dependiente del tipo (comparar, mostrar, filtrar, calcular) al código cliente a través de **punteros a función**.

El diseño se apoya en dos módulos desacoplados:

- **`Nodo`**: unidad mínima de almacenamiento. Contiene un puntero al dato y un puntero al nodo siguiente.
- **`Lista`**: contenedor que mantiene la referencia al primer nodo y el largo actual. Ofrece las operaciones de alto nivel (inserción, eliminación, recorrido, ordenamiento).

Ambas estructuras están declaradas de forma **incompleta** en sus cabeceras (`struct Lista;`, `struct Nodo;`) y definidas únicamente en sus archivos `.c`. Esto implementa el patrón **Opaque Pointer**: el cliente solo puede manipular `ListaPtr` y `NodoPtr`, nunca sus campos internos, forzando el uso exclusivo de la API pública.

---

## Funcionamiento

### Tipos expuestos

| Tipo | Definición | Rol |
|------|------------|-----|
| `DatoPtr` | `void*` | Dato genérico almacenado en un nodo |
| `NodoPtr` | `struct Nodo*` | Handle opaco a un nodo |
| `ListaPtr` | `struct Lista*` | Handle opaco a una lista |

### Modelo de memoria

La librería **no copia los datos**: almacena únicamente la dirección de memoria que recibe. La responsabilidad sobre el ciclo de vida del dato apuntado queda del lado del cliente. La lista sí administra la memoria de sus propios nodos (`crearNodo` / `liberarNodo`).

```
ListaPtr ──> [ primero ] ──> [ dato | siguiente ] ──> [ dato | siguiente ] ──> NULL
             [ largo   ]          │                        │
                                  v                        v
                             dato del cliente         dato del cliente
```

### Genericidad por callbacks

Las operaciones que requieren conocer el tipo concreto reciben una función del cliente:

| Operación | Firma del callback | Contrato |
|-----------|--------------------|----------|
| `mostrarLista` | `void (*mostrar)(DatoPtr)` | Imprime un dato individual |
| `ordenarMedianteBurbuja` | `int (*comparar)(DatoPtr, DatoPtr)` | Devuelve `>0`, `0` o `<0` según orden |
| `eliminarPorCondicion` | `int (*condicion)(DatoPtr)` | Devuelve valor verdadero si el nodo debe eliminarse |
| `realizarCalculoEntreNodos` | `float (*calculo)(DatoPtr, DatoPtr)` | Opera sobre cada par de nodos consecutivos |

El ordenamiento se resuelve con **Bubble Sort** intercambiando los punteros a dato entre nodos (no los nodos en sí), lo que evita reenlazar la estructura.

---

## Archivos incluidos

```
.
├── CMakeLists.txt          Configuración de build (CMake, C11)
├── include/
│   ├── nodo.h              API pública del nodo: tipos DatoPtr y NodoPtr
│   └── lista.h             API pública de la lista (incluye nodo.h)
├── src/
│   ├── nodo.c              Definición de struct Nodo e implementación de su API
│   ├── lista.c             Definición de struct Lista e implementación de su API
│   └── main.c              Programa de prueba / demostración de uso
└── README.md
```

| Archivo | Contenido |
|---------|-----------|
| `include/nodo.h` | Declaración incompleta de `struct Nodo`, alias `NodoPtr` y `DatoPtr`, constructor, destructor y accesores. |
| `include/lista.h` | Declaración incompleta de `struct Lista`, alias `ListaPtr`, y el conjunto completo de operaciones: creación, liberación, inserción, eliminación, recorrido, ordenamiento y cálculo. |
| `src/nodo.c` | Definición real de `struct Nodo { DatoPtr dato; NodoPtr siguiente; }` y su implementación sobre `malloc` / `free`. |
| `src/lista.c` | Definición real de `struct Lista { NodoPtr primero; int largo; }` y toda la lógica de recorrido y manipulación de enlaces. |
| `src/main.c` | Caso de uso con enteros: define `compararEnteros` y `mostrarEntero`, inserta elementos, ordena y libera la lista. |
| `CMakeLists.txt` | Declara el estándar C11, agrega `include/` a las rutas de búsqueda y compila los tres fuentes en un ejecutable. |

---

## API

### Nodo (`nodo.h`)

| Función | Descripción |
|---------|-------------|
| `NodoPtr crearNodo(DatoPtr dato, NodoPtr siguiente)` | Reserva un nodo con el dato y el enlace indicados. |
| `void liberarNodo(NodoPtr nodo)` | Libera el nodo. No libera el dato apuntado. |
| `DatoPtr getDato(NodoPtr nodo)` | Devuelve el dato genérico; requiere casteo en el cliente. |
| `void setDato(NodoPtr nodo, DatoPtr dato)` | Reemplaza el dato del nodo. |
| `NodoPtr getSiguiente(NodoPtr nodo)` | Devuelve el nodo siguiente. |
| `void setSiguiente(NodoPtr nodo, NodoPtr nuevoSiguiente)` | Reenlaza el nodo siguiente. |

### Lista (`lista.h`)

**Ciclo de vida**

| Función | Descripción |
|---------|-------------|
| `ListaPtr crearLista()` | Crea una lista vacía (`primero = NULL`, `largo = 0`). |
| `void liberarLista(ListaPtr lista)` | Recorre y libera todos los nodos de la lista. |

**Inserción**

| Función | Descripción |
|---------|-------------|
| `void insertarPrimero(ListaPtr lista, DatoPtr dato)` | Inserta al inicio. O(1). |
| `void insertarUltimo(ListaPtr lista, DatoPtr dato)` | Inserta al final. O(n). |
| `void insertarEnPosicion(ListaPtr lista, DatoPtr dato, int posicion)` | Inserta en una posición válida. O(n). |

**Eliminación**

| Función | Descripción |
|---------|-------------|
| `void eliminarPrimero(ListaPtr lista)` | Elimina y libera el primer nodo. |
| `void eliminarUltimo(ListaPtr lista)` | Elimina y libera el último nodo. |
| `void eliminarEnPosicion(ListaPtr lista, int posicion)` | Elimina el nodo en la posición indicada. |
| `void eliminar(ListaPtr lista, NodoPtr nodo)` | Elimina por comparación de dirección de memoria. |
| `void eliminarPorCondicion(ListaPtr lista, int(*condicion)(DatoPtr))` | Elimina todos los nodos que cumplan el predicado. |

**Acceso**

| Función | Descripción |
|---------|-------------|
| `NodoPtr getPrimero(ListaPtr lista)` | Devuelve el primer nodo. |
| `void setPrimero(ListaPtr lista, NodoPtr nodo)` | Reemplaza el primer nodo. |
| `NodoPtr getUltimo(ListaPtr lista)` | Devuelve el último nodo recorriendo la lista. |
| `void setUltimo(ListaPtr lista, NodoPtr nodo)` | Reemplaza el último nodo, liberando el anterior. |
| `int getLargo(ListaPtr lista)` | Devuelve el largo, o `-1` si la lista es nula. |

**Recorrido y procesamiento**

| Función | Descripción |
|---------|-------------|
| `void mostrarLista(ListaPtr lista, void(*mostrar)(DatoPtr))` | Recorre la lista aplicando el callback de impresión. |
| `void ordenarMedianteBurbuja(ListaPtr lista, int(*comparar)(DatoPtr, DatoPtr))` | Ordena in-place con Bubble Sort. O(n²). |
| `float realizarCalculoEntreNodos(ListaPtr lista, float(*calculo)(DatoPtr, DatoPtr))` | Acumula el resultado del cálculo sobre pares consecutivos. Devuelve `-999.00f` ante parámetros nulos. |

---

## Uso

```c
#include <stdio.h>
#include "lista.h"

int compararEnteros(DatoPtr d1, DatoPtr d2) {
    if (!d1 || !d2) return -1;
    int n1 = *((int*) d1);
    int n2 = *((int*) d2);
    if (n1 == n2) return 0;
    return n1 > n2 ? 1 : -1;
}

void mostrarEntero(DatoPtr d1) {
    if (!d1) return;
    printf("%d, ", *((int*) d1));
}

int main(void) {
    ListaPtr lista = crearLista();

    int n1 = 2, n2 = 1, n3 = 12;
    insertarUltimo(lista, &n1);
    insertarPrimero(lista, &n2);
    insertarEnPosicion(lista, &n3, 1);

    ordenarMedianteBurbuja(lista, &compararEnteros);
    mostrarLista(lista, &mostrarEntero);

    liberarLista(lista);
    return 0;
}
```

Para usar otro tipo de dato basta con proveer nuevos callbacks; la librería no requiere modificación alguna.

---

## Compilación

Requiere CMake 4.3 o superior y un compilador con soporte C11.

```bash
cmake -S . -B build
cmake --build build
```

El binario resultante es `ayed_libreria_listas_void_primitivas`.

Compilación directa sin CMake:

```bash
gcc -std=c11 -Iinclude src/nodo.c src/lista.c src/main.c -o lista_demo
```

---

## Consideraciones de diseño y limitaciones actuales

- **Sin validación de tipos**: al usar `void*`, un callback incorrecto para el tipo almacenado produce comportamiento indefinido. La coherencia de tipos es responsabilidad del cliente.
- **Ownership de los datos**: la lista no reserva ni libera la memoria de los datos. Insertar la dirección de una variable local que salga de alcance deja punteros colgantes.
- **`liberarLista`** libera los nodos pero no la estructura `Lista` en sí ni deja los campos en estado consistente.
- **`insertarEnPosicion`** rechaza `posicion >= largo`, por lo que no permite insertar al final a través de esta función; para ese caso debe usarse `insertarUltimo`. Además, la inserción intermedia no actualiza el contador `largo`.
- **`getDato`, `getSiguiente` y `setSiguiente`** no validan que el nodo recibido sea no nulo.
- **`eliminarPorCondicion`** delega en `eliminar`, que recorre la lista desde el inicio en cada llamada, resultando en O(n²) para el peor caso.
- **`ordenarMedianteBurbuja`** intercambia datos y no nodos, por lo que cualquier `NodoPtr` retenido por el cliente antes del ordenamiento apuntará a un dato distinto luego de la operación.
