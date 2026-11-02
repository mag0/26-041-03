#include <iostream>
#include <fstream>
#include <string>
#include "rwstring.hpp"
#include "listas.hpp"
#include <iomanip>

using namespace std;

struct Envio {
    string nombreCiudad;
    int codigoTransportista;
    string producto;
    int unidades;
    float monto;
};

struct Transportista {
    string nombre;
    int cantidadEnvios;
};

struct Ciudad {
    string nombre;
    int unidades;
    float montoTotal;
    Transportista transportistas[6];
};

const int lNombreCiudad = 14;
const int lProducto = 10;

int critMismoNombreCiudad(Ciudad a, Ciudad b) {
    return a.nombre.compare(b.nombre);
}

fstream& operator >> (fstream &fs, Envio& env) {
    env.nombreCiudad = readstring(fs, lNombreCiudad);
    fs.read(reinterpret_cast<char *>(&env.codigoTransportista), sizeof(env.codigoTransportista));
    env.producto = readstring(fs, lProducto);
    fs.read(reinterpret_cast<char *>(&env.unidades), sizeof(env.unidades));
    fs.read(reinterpret_cast<char *>(&env.monto), sizeof(env.monto));
    return fs;
}

bool leerArchivoTxt(string transportistas[], int dimTransportistas) {
    ifstream archivoDeTexto;
    archivoDeTexto.open("Nombres.txt");

    if(!archivoDeTexto) {
        cout << "No se pudo abrir el archivo Nombres.txt" << endl;
        return false;
    }

    for(int i = 0; i < dimTransportistas; i++) {
        getline(archivoDeTexto, transportistas[i]);
    }

    archivoDeTexto.close();

    return true;
}

bool leerArchivoBinario(Nodo<Ciudad>*& listaCiudades, string transportistas[], int dimTransportistas) {
    fstream archivoBinario;
    archivoBinario.open("Datos.bin", ios::in | ios::binary);

    if(!archivoBinario) {
        cout << "No se pudo abrir el archivo Datos.bin" << endl;
        return false;
    }

    Envio envio;
    while(archivoBinario >> envio){

        Ciudad ciudad;
        ciudad.nombre = envio.nombreCiudad;

        Ciudad* ciudadEncontrada = buscar_lno(ciudad, listaCiudades, critMismoNombreCiudad);

        if(ciudadEncontrada != nullptr) {
            ciudadEncontrada->montoTotal += envio.monto;
            ciudadEncontrada->unidades += envio.unidades;
            ciudadEncontrada->transportistas[envio.codigoTransportista].cantidadEnvios++;
        } else {
            for(int i = 0; i < dimTransportistas; i++) {
                ciudad.transportistas[i].nombre = transportistas[i];
                ciudad.transportistas[i].cantidadEnvios = 0;
            }
            ciudad.transportistas[envio.codigoTransportista].cantidadEnvios = 1;
            ciudad.montoTotal = envio.monto;
            ciudad.unidades = envio.unidades;
            push(listaCiudades, ciudad);
        }
        
    }

    archivoBinario.close();

    return true;
}

void listadoDeCadaCiudad(Nodo<Ciudad>* listaCiudades, int dimTransportistas) {
    while(listaCiudades != nullptr) {
        Ciudad ciudad = listaCiudades->dato;
        cout << "Ciudad: " << ciudad.nombre << endl;
        cout << "Total de unidades: " << ciudad.unidades
        << " - Monto Total: " << ciudad.montoTotal << endl;

        int i = 0;
        for(int i = 0; i < dimTransportistas; i++) {
            Transportista transportista = ciudad.transportistas[i];
            cout << "Transporte: " << transportista.nombre 
            << " - Envios: " << transportista.cantidadEnvios << endl;
        }

        cout << endl;
        listaCiudades = listaCiudades->sig;
    }
}

int main() {

    // Parte 1
    const int dimTransportistas = 6;
    
    Nodo<Ciudad>* listaCiudades = nullptr;
    string transportistas[dimTransportistas]{};

    if(!leerArchivoTxt(transportistas, dimTransportistas)) {
        return 1;
    }

    if(!leerArchivoBinario(listaCiudades, transportistas, dimTransportistas)) {
        return 1;
    }
    
    // Configuracion del cout para poder mostrar el monto con dos decimales
    cout << fixed << setprecision(2);

    // Parte 2
    listadoDeCadaCiudad(listaCiudades, dimTransportistas);

    // Parte 3

    // Parte 4

    return 0;
}