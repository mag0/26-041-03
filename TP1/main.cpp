#include <iostream>
#include <fstream>
#include <string>
#include "rwstring.hpp"

using namespace std;

struct Arribo {
    int codigoPais;
    int codigoAerolinea;
    string codigoIATA;
    int cantidadPasajeros;
    int codigoDia;
};

const int longitudCodigoIATA = 3;

struct Aeropuerto {
    string codigoIATA;
    string nombre;
    // Atributos para ya tenerlos cargados para el punto 4:
    int cantidadPasajeros;
    int cantidadVuelos;
};

fstream& operator >> (fstream &fs, Arribo& arri) {
    fs.read(reinterpret_cast<char *>(&arri.codigoPais), sizeof(arri.codigoPais));
    fs.read(reinterpret_cast<char *>(&arri.codigoAerolinea), sizeof(arri.codigoAerolinea));
    arri.codigoIATA = readstring(fs, longitudCodigoIATA);
    fs.read(reinterpret_cast<char *>(&arri.cantidadPasajeros), sizeof(arri.cantidadPasajeros));
    fs.read(reinterpret_cast<char *>(&arri.codigoDia), sizeof(arri.codigoDia));
    return fs;
}

int main() {
    
    /*
        Punto 1 : Armar las estructuras de datos necesarias.
    */ 

    const int cantidadPaises = 5;
    const int cantidadAerolineas = 8;
    const int cantidadAeropuertos = 15;
    const int cantidadDias = 7;

    // Para usar en el punto 2:
    string paises[cantidadPaises]{};
    string aerolineas[cantidadAerolineas]{};
    Aeropuerto aeropuertos[cantidadAeropuertos]{};
    // Para usar en el punto 3 y la primera parte del 5:
    int pasajerosPorPaisAerolinea[cantidadPaises][cantidadAerolineas]{};
    // Para usar en la segunda parte del 5:
    int pasajerosPorDia[cantidadDias]{};

    /*
        Punto 2: Leer arribos.bin y nombres.txt, cargando las estructuras convenientes para 
        realizar las operaciones solicitadas.
    */ 



    /*
        Punto 3: Armar un listado con el nombre del país, el nombre de la aerolínea y la cantidad 
        total de pasajeros arribados durante la semana para cada combinación.
    */ 



    /*
        Punto 4: Informar el nombre del aeropuerto que, habiendo enviado pasajeros durante esa 
        semana, envió la menor cantidad. Indicar cuántos pasajeros fueron y cuántos vuelos salieron de ese aeropuerto.
    */ 



    /*
        Punto 5: Informar qué combinación de país y aerolínea transportó la mayor cantidad de 
        pasajeros, mostrando sus nombres y el total. Luego, mostrar la distribución de esos pasajeros 
        a lo largo de los días de la semana, ordenada por cantidad en forma descendente.
    */ 



    return 0;

}