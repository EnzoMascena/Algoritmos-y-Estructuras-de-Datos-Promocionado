/*Se desean realizar las siguientes acciones con estructuras dinamicas:
    1) Se carga una lista simplemente enlazada con 50 numeros naturales (L1). La lista mantiene estricto orden descendente.
    2) Se recorre recursivamente la lista L1, cargando los numeros (sin eliminarlos de la lista original L1) en otras dos listas: 
    una lista de numeros impares (L2) y otra de numeros pares (L3). Estas listas mantienen estricto orden ascendente.
    3) Posteriormente, se ingresan por teclado numeros naturales, el ingreso se detiene al ingresar el tercer cero (0). 
    Estos numeros deben cargarse en una y solo una de las tres listas segun los siguientes criterios:
        a. Si el numero es multiplo de 7 o es numero primo, se carga en la lista L1.
        b. Si el numero es par y no cumple con el inciso "b", se carga en la lista L2.
        c. Si el numero es par y no cumple con el inciso "b", se carga en la lista L3.
    4) Calcular el promedio de las listas L2 y L3 e imprimir 
    5) Recorrer recursivamente L1 e imprimir aquellos numeros que no esten ni en L2 ni en L3.
    6) Recorrer recursivamente la lista L1 y cargar en una pila los numeros primos.*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <stdbool.h>

typedef struct nodo_natural{
    int numero;
    struct nodo_natural *sig;
}nodo;

void crear_estructura_dinamica(nodo **lista){*lista=NULL;}
void insertar_ordenado_descendente(nodo **lista, int valor);
void insertar_ordenado_ascendente(nodo **lista, int valor);
void cargar_listas_recursivamente(nodo *L1, nodo **L2, nodo **L3);
bool es_primo(int numero);
void cargar_numeros(nodo **L1, nodo **L2, nodo **L3);
float calcular_promedio(nodo *lista);
void calcular_promedios_y_imprimir(nodo *L2, nodo *L3);
bool esta_en_lista(nodo *lista, int numero);
void ausencia_lista(nodo *L1, nodo *L2, nodo *L3);
void apilar(nodo **pila, int numero);
void cargar_pila_primos_recursivamente(nodo *L1, nodo **pila);
void imprimir_pila(nodo *pila);

int main(){
    nodo *L1 = NULL;
    nodo *L2 = NULL;
    nodo *L3 =NULL;
    nodo *pila = NULL;

    int numero;
    //PUNTO 1
    crear_estructura_dinamica(&L1);

    for (int i = 0; i < 50; i++)
    {
        printf("Ingresa el numero %i", i + 1);
        scanf("%i", &numero);
        insertar_ordenado_descendente(&L1, numero);
    }

    //PUNTO 2
    crear_estructura_dinamica(&L2);
    crear_estructura_dinamica(&L3);
    cargar_listas_recursivamente(L1, &L2, &L3);

    //PUNTO 3
    cargar_numeros(&L1, &L2, &L3);

    //PUNTO 4
    calcular_promedios_y_imprimir(L2, L3);

    //PUNTO 5
    ausencia_lista(L1, L2, L3);
    
    //PUNTO 6
    crear_estructura_dinamica(&pila);
    cargar_pila_primos_recursivamente(L1, &pila);
    imprimir_pila(pila);

    return 0;
}

void insertar_ordenado_descendente(nodo **lista, int valor){
    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    nuevo->numero = valor;
    nuevo->sig = NULL;

    if (*lista == NULL || valor > (*lista)->numero) {
        nuevo->sig = *lista;
        *lista = nuevo;
    } else {
        nodo *actual = *lista;
        while (actual->sig != NULL && actual->sig->numero > valor) {
            actual = actual->sig;
        }
        nuevo->sig = actual->sig;
        actual->sig = nuevo;
    }
}

void insertar_ordenado_ascendente(nodo **lista, int valor) {
    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    nuevo->numero = valor;
    nuevo->sig = NULL;

    if (*lista == NULL || valor < (*lista)->numero) {
        nuevo->sig = *lista;
        *lista = nuevo;
    } else {
        nodo *actual = *lista;
        while (actual->sig != NULL && actual->sig->numero < valor) {
            actual = actual->sig;
        }
        nuevo->sig = actual->sig;
        actual->sig = nuevo;
    }
}

void cargar_listas_recursivamente(nodo *L1, nodo **L2, nodo **L3){
    if (L1 == NULL)
    {
        return;
    }
    
    if (L1->numero % 2 == 0)
    {
        insertar_ordenado_ascendente(L3, L1->numero);
    } else {
        insertar_ordenado_ascendente(L2, L1->numero);
    }
    cargar_listas_recursivamente(L1->sig, L2, L3);
}

void cargar_numeros(nodo **L1, nodo **L2, nodo **L3){

     int numero, ceros = 0;

    while (ceros < 3) {
        printf("Ingresa un numero natural (0 para detener): ");
        scanf("%d", &numero);
        if (numero == 0) {
            ceros++;
            continue;
        }
        if (numero % 7 == 0 || es_primo(numero)) {
            insertar_ordenado_descendente(L1, numero);
        }
        else if (numero % 2 == 0) {
            insertar_ordenado_ascendente(L2, numero); 
        } else {
            insertar_ordenado_ascendente(L3, numero); 
        }
    }
}

bool es_primo(int numero) {
    if (numero <= 1) 
    {
        return false; 
    }
    for (int i = 2; i * i <= numero; i++) {
        if (numero % i == 0) 
        {
            return false;
        }
    }
    return true; 
}

float calcular_promedio(nodo *lista) {
    int suma = 0;
    int cantidad = 0;
    
    while (lista != NULL) {
        suma += lista->numero;
        cantidad++;
        lista = lista->sig;
    }

    if (cantidad == 0) {
        return 0;
    }
    return (float)suma / cantidad;
}

void calcular_promedios_y_imprimir(nodo *L2, nodo *L3) {
    float promedio_L2 = calcular_promedio(L2);
    float promedio_L3 = calcular_promedio(L3);

    printf("Promedio de la lista L2: %.2f\n", promedio_L2);
    printf("Promedio de la lista L3: %.2f\n", promedio_L3);
}

bool esta_en_lista(nodo *lista, int numero) {
    while (lista != NULL) {
        if (lista->numero == numero) {
            return true; 
        }
        lista = lista->sig;
    }
    return false;
}

void ausencia_lista(nodo *L1, nodo *L2, nodo *L3) {
    if (L1 == NULL) {
        return; 
    }

    if (!esta_en_lista(L2, L1->numero) && !esta_en_lista(L3, L1->numero)) {
        printf("%d ", L1->numero); 
    }

   ausencia_lista(L1->sig, L2, L3);
}

void apilar(nodo **pila, int numero) {
    nodo *nuevo = (nodo *)malloc(sizeof(nodo));
    nuevo->numero = numero;
    nuevo->sig = *pila;
    *pila = nuevo;
}

void cargar_pila_primos_recursivamente(nodo *L1, nodo **pila){
    if (L1 == NULL) 
    {
        return; 
    }
    if (es_primo(L1->numero)) {
        apilar(pila, L1->numero); 
    }
    cargar_pila_primos_recursivamente(L1->sig, pila);
};

void imprimir_pila(nodo *pila) {
    if (pila == NULL) {
        printf("La pila está vacía.\n");
        return;
    } else {
        printf("Números primos apilados: ");
        while (pila != NULL) 
        {
        printf("%d ", pila->numero);
        pila = pila->sig;
        }
    printf("\n");
    }
}
