#include <iostream>
#include <cstring>
#include "ObraSocial.h"
#include <limits>

using namespace std;

//CONSTRUCTOR:
ObraSocial::ObraSocial()
{
    _idObraSocial = 0;
    strcpy(_nombreObraSocial, "SIN DATOS");
    _estado = true;
}

ObraSocial::ObraSocial(int idObraSocial, const char* nombreObraSocial, bool estado)
{
    setIdObraSocial(idObraSocial);
    setNombre(nombreObraSocial);
    setEstado(estado);

}

//GETTERS Y SETTERS:
  
void ObraSocial::setIdObraSocial(int idObraSocial)
{
        _idObraSocial = idObraSocial;
}
int ObraSocial::getIdObraSocial()
{
    return _idObraSocial;
}

void ObraSocial::setNombre(const char* nombreObraSocial)
{
        strcpy(_nombreObraSocial, nombreObraSocial);
}
const char* ObraSocial::getNombre()
{
    return _nombreObraSocial;
}

void ObraSocial::setEstado(bool estado)
{
    _estado = estado;
}
bool ObraSocial::getEstado()
{
    return _estado;
}

//METODOS:
    void ObraSocial::mostrar(){
        cout << "-----------------------------" << endl;
        cout << "---DATOS DE LA OBRA SOCIAL---" << endl;
        cout << "-----------------------------" << endl;
        cout << "ID de la obra social: " << getIdObraSocial() << endl;
        cout << "Nombre de la obra social: " << getNombre() << endl;
        cout << endl;

        cout << "Estado: ";
    if(getEstado()){
        cout<< "Activo" <<endl;
    }
    else{
        cout<< "Inactivo" <<endl;
    }
        cout << endl;
    }