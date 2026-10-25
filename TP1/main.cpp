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
    // Atributos para el punto 4:
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

bool criterioMenorCantidadPasajerosAeropuerto(Aeropuerto a, Aeropuerto b) {
    return (a.cantidadPasajeros == 0) || (b.cantidadPasajeros != 0 
            && b.cantidadPasajeros < a.cantidadPasajeros);
}

bool criterioMayorCantidadPasajeros(int a, int b) {
    return a > b;
}

bool criterioOrdenDescendente(int a, int b) {
    return a < b;
}

void mostrarPasajerosPorPaisAerolinea(int matriz[][8], string vectorAerolinea[], string vectorPaises[], int dimP, int dimA) {
    cout << "Listado pasajeros" << endl;
    for(int i = 0; i < dimP; i++){
        for(int j = 0; j < dimA; j++){
            cout<< vectorPaises[i] <<" "<< vectorAerolinea[j] <<" "<< matriz[i][j] << endl;
        }
    }
}

template<typename T>
Aeropuerto buscarAeropuertoConMenosPasajeros(Aeropuerto vector[], int dimA, bool (*criterio)(T, T)) {
    Aeropuerto aeropuertoConMenosPasajeros = vector[0];

    for(int i = 1; i < dimA; i++) {
        if(criterio(aeropuertoConMenosPasajeros, vector[i])) {
            aeropuertoConMenosPasajeros = vector[i];
        }
    }

    return aeropuertoConMenosPasajeros;
}

template<typename T>
void buscarCombinacionConMasPasajeros(int matriz[][8], int dimPaises, int dimAerolineas, int& codPais, int& codAerolinea, bool (*criterio)(T, T)) {
    int cantidadPasajeros = 0;
    for(int i = 0; i < dimPaises; i++) {
        for(int j = 0; j < dimAerolineas; j++) {
            if(criterio(matriz[i][j], cantidadPasajeros)) {
                cantidadPasajeros = matriz[i][j];
                codPais = i;
                codAerolinea = j;
            }
        }
    }
}

template<typename T>
void ordenarPasajerosPorDiaDescendente(int pasajerosPorDia[], string dias[], int dimDias, bool (*criterio)(T, T)){
    for(int i = 0; i < dimDias - 1; i++) {
        for(int j = i + 1; j < dimDias; j++) {
            if(criterio(pasajerosPorDia[i], pasajerosPorDia[j])) {
                int aux = pasajerosPorDia[i];
                pasajerosPorDia[i] = pasajerosPorDia[j];
                pasajerosPorDia[j] = aux;

                string auxDia = dias[j];
                dias[j] = dias[i];
                dias[i] = auxDia;
            }
        }
    }
}

void copiarPasajerosPorDia(int pasajerosPorPaisAerolineaPorDia[][8][7], int pasajerosPorDia[], int codPais, int codAerolinea, int dimDias) {
    for(int i = 0; i < dimDias; i++) {
        pasajerosPorDia[i] = pasajerosPorPaisAerolineaPorDia[codPais][codAerolinea][i];
    }
}


int main() {
    
    /*
        Punto 1 : Armar las estructuras de datos necesarias.
    */

    const int dimPaises = 5;
    const int dimAerolineas = 8;
    const int dimAeropuertos = 15;
    const int dimDias = 7;
   
    string str;
    Arribo arri;

    // Para usar en el punto 2:
    string paises[dimPaises]{};
    string aerolineas[dimAerolineas]{};
    Aeropuerto aeropuertos[dimAeropuertos]{};
    string dias[dimDias] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};
    // Para usar en el punto 3 y la primera parte del 5:
    int pasajerosPorPaisAerolinea[dimPaises][dimAerolineas]{};
    int pasajerosPorPaisAerolineaPorDia[dimPaises][dimAerolineas][dimDias]{};
    // Para usar en la segunda parte del 5:
    int pasajerosPorDia[dimDias]{};

    /*
        Punto 2: Leer arribos.bin y nombres.txt, cargando las estructuras convenientes para 
        realizar las operaciones solicitadas.
    */

    ifstream archilec1;
    archilec1.open("nombres.txt");

    //Ingreso de los datos del nombre.txt
    if(!archilec1){
        cout << "Error en conexión del archivo";
        return 1;
    }

    for(int i = 0; i < 5; i++){
        getline(archilec1, str);
        paises[i] = str;
    }

    for(int i = 0; i < 8; i++){
        getline(archilec1, str);
        aerolineas[i] = str;
    }

    for(int i = 0; i < 15; i++){
        archilec1 >> str;
        aeropuertos[i].codigoIATA = str;
        getline(archilec1,str);
        aeropuertos[i].nombre = str;
    }

    archilec1.close();

    fstream archilec2;
    archilec2.open("arribos.bin", ios::in | ios::binary);

    if(!archilec2){
        cout<<"error en conexión del archivo";
        return 1;
    }

    while(archilec2 >> arri){

        pasajerosPorPaisAerolinea[arri.codigoPais][arri.codigoAerolinea] += arri.cantidadPasajeros;
        pasajerosPorPaisAerolineaPorDia[arri.codigoPais][arri.codigoAerolinea][arri.codigoDia] += arri.cantidadPasajeros;

        for(int i = 0; i < dimAeropuertos; i++) {
            if(aeropuertos[i].codigoIATA == arri.codigoIATA) {
                aeropuertos[i].cantidadPasajeros += arri.cantidadPasajeros;
                aeropuertos[i].cantidadVuelos++;
            }
        }
    }

    archilec2.close();

    /*
        Punto 3: Armar un listado con el nombre del país, el nombre de la aerolínea y la cantidad 
        total de pasajeros arribados durante la semana para cada combinación.
    */ 

    mostrarPasajerosPorPaisAerolinea(pasajerosPorPaisAerolinea, aerolineas, paises, dimPaises, dimAerolineas);

    /*
        Punto 4: Informar el nombre del aeropuerto que, habiendo enviado pasajeros durante esa 
        semana, envió la menor cantidad. Indicar cuántos pasajeros fueron y cuántos vuelos salieron de ese aeropuerto.
    */

    Aeropuerto aeropuertoConMenosPasajeros = buscarAeropuertoConMenosPasajeros(aeropuertos, dimAeropuertos, criterioMenorCantidadPasajerosAeropuerto);

    if(aeropuertoConMenosPasajeros.cantidadPasajeros > 0){
        cout << "\nAeropuerto que envió menor cantidad de pasajeros: " << aeropuertoConMenosPasajeros.codigoIATA
        << ": " << aeropuertoConMenosPasajeros.nombre << endl;
        cout << "Pasajeros enviados: " << aeropuertoConMenosPasajeros.cantidadPasajeros << " en " 
        << aeropuertoConMenosPasajeros.cantidadVuelos << " vuelos." << endl;
    }  else {
        cout << "No hubo aeropuertos que enviaran pasajeros." << endl;
    }
    
    /*
        Punto 5: Informar qué combinación de país y aerolínea transportó la mayor cantidad de 
        pasajeros, mostrando sus nombres y el total. Luego, mostrar la distribución de esos pasajeros 
        a lo largo de los días de la semana, ordenada por cantidad en forma descendente.
    */ 

    int codPais = 0;
    int codAerolinea = 0;
    
    buscarCombinacionConMasPasajeros(pasajerosPorPaisAerolinea, dimPaises, dimAerolineas, codPais, codAerolinea, criterioMayorCantidadPasajeros);
    
    cout << "\nLa mayor cantidad de pasajeros " << pasajerosPorPaisAerolinea[codPais][codAerolinea]
    << " se dio para la combinación " << paises[codPais] << " con " << aerolineas[codAerolinea]
    << " según el siguiente detalle diario: " << endl;

    copiarPasajerosPorDia(pasajerosPorPaisAerolineaPorDia, pasajerosPorDia, codPais, codAerolinea, dimDias);

    ordenarPasajerosPorDiaDescendente(pasajerosPorDia, dias, dimDias, criterioOrdenDescendente);
    
    for(int i = 0; i < dimDias; i++) {
        cout << dias[i] << " | " << pasajerosPorDia[i] << endl;
    }

    return 0;

}