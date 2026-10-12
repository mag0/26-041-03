#include <iostream>
#include <string>

using namespace std;

struct Arribo {
    int codigoPais;
    int codigoAerolinea;
    string codigoIATA;
    int cantidadPasajeros;
    int codigoDia;
};

struct Aeropuerto {
    string codigoIATA;
    string nombre;
};

template<typename T> struct Nodo {
    T dato;
    Nodo<T>* sig;
};

int main() {
    
    // Punto 1 : Armado de las estructuras de datos.

    const int dimPaises = 5;
    const int dimAerolineas = 8;
    const int dimAeropuertos = 15;

    string paises[dimPaises];
    string aerolineas[dimAerolineas];
    Aeropuerto aeropuertos[dimAeropuertos];

    /* Lista enlazada para almacenar los arribos, ya que no conocemos 
    de antemano la cantidad de registros del archivo binario */ 
    Nodo<Arribo>* arribos = nullptr;

    // Punto 2: Lectura de archivos.

    // Punto 3: Total de pasajeros por país y aerolínea.

    // Punto 4: Aeropuerto con menor cantidad de pasajeros.

    // Punto 5: Combinación con mayor cantidad de pasajeros y distribución por día.



    return 0;

}