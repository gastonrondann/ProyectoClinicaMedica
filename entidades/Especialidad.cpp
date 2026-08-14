#include <iostream>
#include <cstring>
#include "Especialidad.h"
#include "../funciones/validaciones.h"
using namespace std;

//CONSTRUCTORES:
Especialidad::Especialidad(){
    _idEspecialidad = 0;
    strcpy(_nombre, "SIN DATOS");
    _estado = true;
}

Especialidad::Especialidad(int idEspecialidad, const char* nombre, bool estado){
    setIdEspecialidad(idEspecialidad);
    setNombre(nombre);
    setEstado(estado);
}

//GETTERS Y SETTERS:
    int Especialidad::getIdEspecialidad(){
        return _idEspecialidad;
    }
    void Especialidad::setIdEspecialidad(int idEspecialidad){
        _idEspecialidad = idEspecialidad;
    }

    const char* Especialidad::getNombre(){
        return _nombre;
    }
    void Especialidad::setNombre(const char* nombre){
        strcpy(_nombre, nombre);
    }

    bool Especialidad::getEstado(){
        return _estado;
    }
    void Especialidad::setEstado(bool estado){
        _estado = estado;
    }

//METODOS:
    void Especialidad::mostrar(){

        cout << "------------------------------" << endl;
        cout << "---DATOS DE LA ESPECIALIDAD---" << endl;
        cout << "------------------------------" << endl;
        cout << "ID de la especilidad: " << getIdEspecialidad() << endl;
        cout << "Nombre de la especialidad: " << getNombre() << endl;
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
