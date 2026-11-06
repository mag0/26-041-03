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
    int codigo;
    int cantidadEnvios {};
};

struct Ciudad {
    string nombre;
    int unidades {};
    float montoTotal {};
    Nodo<Transportista>* transportistas {};
};

const int lNombreCiudad = 14;
const int lProducto = 10;

int critCiudad(Ciudad a, Ciudad b) {
    return a.nombre.compare(b.nombre);
}

int critTransportista(Transportista a, Transportista b) {
    return a.codigo - b.codigo;
}

fstream& operator >> (fstream& fs, Envio& env) {
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

void listadoDeCadaCiudad(Nodo<Ciudad>* listaCiudades, string transportistas[]) {
    Transportista transportista {};
    Transportista* ptransportista {};

    while (listaCiudades) {
        cout << "Ciudad: " << listaCiudades->dato.nombre << endl;

        cout << "Total de unidades: " << listaCiudades->dato.unidades
             << " - Monto Total: " << listaCiudades->dato.montoTotal << endl;

        for (int i = 0; i < 6; i++) {
            transportista.codigo = i;

            ptransportista = buscar_lno(
                transportista,
                listaCiudades->dato.transportistas,
                critTransportista
            );

            cout << "Transportista: " << transportistas[i]
                 << " - Envios: ";

            if (ptransportista != nullptr) {
                cout << ptransportista->cantidadEnvios << endl;
            } else {
                cout << 0 << endl;
            }
        }

        cout << endl;
        listaCiudades = listaCiudades->sig;
    }
}

int main() {
    const int dimTransportistas = 6;

    Nodo<Ciudad>* ciudades {};
    Nodo<Ciudad>* pciudad {};
    Nodo<Transportista>* ptransportista {};

    Envio envio {};
    Ciudad ciudad {};
    Transportista transportista {};

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

    while (archilec >> envio) {
        ciudad.nombre = envio.nombreCiudad;

        pciudad = insertar_unico(ciudad, ciudades, critCiudad);

        pciudad->dato.unidades += envio.unidades;
        pciudad->dato.montoTotal += envio.monto;

        transportista.codigo = envio.codigoTransportista;

        ptransportista = insertar_unico(transportista, pciudad->dato.transportistas, critTransportista);

        ptransportista->dato.cantidadEnvios++;
    }

    archilec.close();

    // Configuracion para que se muestre el monto total con dos decimales
    cout << fixed << setprecision(2);

    // Punto 2
    listadoDeCadaCiudad(ciudades, nombresTransportistas);

    // Punto 3

    // Punto 4

    return 0;
}