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

// const int longitudCodigoIATA = 3;

struct Aeropuerto {
    string codigoIATA;
    string nombre;
    // Atributos para ya tenerlos cargados para el punto 4:
    int cantidadPasajeros;
    int cantidadVuelos;
};

fstream& operator >> (fstream &fs, Arribo& arri) {
    fs.read(reinterpret_cast<char *>(&arri.codigoPais), sizeof(Arribo.codigoPais));
    fs.read(reinterpret_cast<char *>(&arri.codigoAerolinea), sizeof(Arribo.codigoAerolinea));
    arri.codigoIATA = readstring(fs, longitudCodigoIATA);
    fs.read(reinterpret_cast<char *>(&arri.cantidadPasajeros), sizeof(Arribo.cantidadPasajeros));
    fs.read(reinterpret_cast<char *>(&arri.codigoDia), sizeof(Arribo.codigoDia));
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
   
    string str,registro;
    int i=0,a=0,b=0,c=0;
    Arribo arri;

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
    ifstream archilec1;
    archilec1.open("nombres.txt");

    fstream archilec2;
    archilec2.open("arribos.bin",ios::binary);
    

//Ingreso de los datos del nombre.txt
    if(!archilec){

        cout<<"Error en conexión del archivo";

    }

        for(i=0;i<5;i++){

            archilec >> str;

            paises[i] = str;
        }

        for(a=0;a<8;a++){
        
            getline(archilec, str);
            
            aerolineas[a] = str;

        }

        for(b=0;b<15;b++){

            archilec >> str;
            aeropuertos[b].codigoIATA = str;
            
            getline(archilec,str);
            aeropuertos[b].nombre >> str;

        }

        if(!archilec2){

        cout<<"error en conexión del archivo";


        }

        
        i=0;
        a=0;

       while(archilec2 >> arri){

cout<<"Registros"<<endl;
       
cout<<""<<arri.codigoPais<<" ";
cout<<""<<arri.codigoAerolinea<<"";
cout<<""<<arri.codigoIATA<<" ";
cout<<""<<arri.cantidadPasajeros<<" ";
cout<<""<<arri.codigoDia<<" ";


        for(i=0;i<8;i++){

            for(a=0;a<5;a++){

                if(arribo.codigoPais == a && arribo.codigoAerolinea == i){


                    int pasajerosPorPaisAerolinea[i][a] =+ arri.cantidadPasajeros;

                }

            }

        }

       }

//

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