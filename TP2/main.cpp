#include <iostream>
#include <fstream>
#include <string>
#include "rwstring.hpp"
#include "listas.hpp"
#include <iomanip>

using namespace std;

struct Registro {
    string nombreCiudad;
    int codigoTransportista;
    string producto;
    int unidades;
    float monto;
};

struct Transportista {
    int codigo;
    int cantidadEnvios {};
};

struct Envio {
    string producto;
    int unidades;
    float monto;
};

struct Ciudad {
    string nombre;
    int unidades {};
    float montoTotal {};
    Nodo<Transportista>* transportistas {};
    Nodo<Envio>* envios {};
};

const int lNombreCiudad = 14;
const int lProducto = 10;

int critPorTransportista(Transportista a, Transportista b) {
    return a.codigo - b.codigo;
}

int critCiudad(Ciudad a, Ciudad b) {
    return a.nombre.compare(b.nombre);
}

int critEnvio(Envio a, Envio b) {
    return a.producto.compare(b.producto);
}

fstream& operator >> (fstream& fs, Registro& env) {
    env.nombreCiudad = readstring(fs, lNombreCiudad);
    fs.read(reinterpret_cast<char*>(&env.codigoTransportista), sizeof(env.codigoTransportista));
    env.producto = readstring(fs, lProducto);
    fs.read(reinterpret_cast<char*>(&env.unidades), sizeof(env.unidades));
    fs.read(reinterpret_cast<char*>(&env.monto), sizeof(env.monto));
    return fs;
}

bool leerArchivoTxt(string transportistas[], int dimTransportistas) {
    ifstream archivoDeTexto;
    archivoDeTexto.open("Nombres.txt");

    if (!archivoDeTexto) {
        cout << "No se pudo abrir el archivo Nombres.txt" << endl;
        return false;
    }

    for (int i = 0; i < dimTransportistas; i++) {
        getline(archivoDeTexto, transportistas[i]);
    }

    archivoDeTexto.close();

    return true;
}

void mostrarTransportistas(Nodo<Transportista>* listaTransportistas, string transportistas[], int dimTransportistas){
    Nodo<Transportista>* ptransportista {};
    Transportista transportista {};

    for(int i = 0; i < dimTransportistas; i++){
        transportista.codigo = i;
        ptransportista = buscar(transportista, listaTransportistas, critPorTransportista);
        int envios = ptransportista ? ptransportista->dato.cantidadEnvios : 0;
        cout << transportistas[i]
        << " | Unidades: " << envios << endl;
    }
}

void mostrarEnvios(Nodo<Envio>* listaEnvios){
    int unidadesTotal = 0;
    int montoTotal = 0;
    while(listaEnvios){
            cout << listaEnvios->dato.producto
            << " | Unidades: " << listaEnvios->dato.unidades
            << " | Monto: " << listaEnvios->dato.monto << endl;

            unidadesTotal += listaEnvios->dato.unidades;
            montoTotal += listaEnvios->dato.monto;

            if(!listaEnvios->sig || listaEnvios->dato.producto != listaEnvios->sig->dato.producto){
                cout << "---------------------------------------------------" << endl;
                cout << listaEnvios->dato.producto
                << " | Total Unidades: " << unidadesTotal
                << " | Total Monto: " << montoTotal << endl << endl;
                unidadesTotal = 0;
                montoTotal = 0;
            }

            listaEnvios = listaEnvios->sig;
        }
}

void mostrarListadoDeCadaCiudad(Nodo<Ciudad>* ciudades, string transportistas[], int dimTransportistas){
    while(ciudades){
        cout << "\n" << ciudades->dato.nombre << endl;
        cout << "Total de unidades: " << ciudades->dato.unidades
        << " | Monto Total: " << ciudades->dato.montoTotal << endl << endl;

        mostrarTransportistas(ciudades->dato.transportistas, transportistas, dimTransportistas);

        cout << endl << endl;

        mostrarEnvios(ciudades->dato.envios);

        ciudades = ciudades->sig;
    }
}

int main() {
    const int dimTransportistas = 6;

    Nodo<Ciudad>* ciudades {};
    Nodo<Ciudad>* pciudad {};
    Nodo<Transportista>* ptransportista {};

    Registro reg {};
    Ciudad ciudad {};
    Transportista transportista {};
    Envio envio {};

    string nombresTransportistas[dimTransportistas] {};

    if (!leerArchivoTxt(nombresTransportistas, dimTransportistas)) {
        return EXIT_FAILURE;
    }

    fstream archilec;
    archilec.open("Datos.bin", ios::in | ios::binary);

    if (!archilec) {
        cout << "No se pudo abrir el archivo Datos.bin" << endl;
        return EXIT_FAILURE;
    }

    while (archilec >> reg) {
        ciudad.nombre = reg.nombreCiudad;
        pciudad = insertar_unico(ciudad, ciudades, critCiudad);
        pciudad->dato.unidades += reg.unidades;
        pciudad->dato.montoTotal += reg.monto;

        transportista.codigo = reg.codigoTransportista;
        ptransportista = insertar_unico(transportista, pciudad->dato.transportistas, critPorTransportista);
        ptransportista->dato.cantidadEnvios++;

        envio.producto = reg.producto;
        envio.unidades = reg.unidades;
        envio.monto = reg.monto;
        insertar(envio, pciudad->dato.envios, critEnvio);
    }

    archilec.close();

    // Configuracion para que se muestre el monto total con dos decimales
    cout << fixed << setprecision(2);

    // Punto 2
    cout << "Listado de datos" << endl << endl;
    mostrarListadoDeCadaCiudad(ciudades, nombresTransportistas, dimTransportistas);

    // Punto 3

    // Punto 4

    return 0;
}