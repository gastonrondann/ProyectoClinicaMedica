#include "Rol.h"
#include <iostream>
#include <cstring>
#include "../persistencia/ArchivoRol.h"
#include "../funciones/validaciones.h"

using namespace std;

//CONSTRUCTORES:
    Rol::Rol(int idRol, const char* nombreRol, bool estado){
        if(idRol == 999 && strcmp(nombreRol, "SIN DATOS") == 0 && estado == true){
            _idRol = idRol;
            strcpy(_nombre, nombreRol);
        } else {
            setIdRol(idRol);
            setNombre(nombreRol);
        }
        setEstado(true);
    }

//GETTERS Y SETTERS:
    int Rol::getIdRol(){
        return _idRol;
    }
    bool Rol::setIdRol(int idRol){
        if(!validarId(idRol)){
            return false;
        } else {
            _idRol = idRol;
            return true;
        }
    }

    const char* Rol::getNombre(){
        return _nombre;
    }
    bool Rol::setNombre(const char* nombre){
        if(validarNombre(nombre)){
            strcpy(_nombre, nombre);
            return true;
        } else {
            return false;
        }
    }

    bool Rol::getEstado(){
        return _estado;
    }
    bool Rol::setEstado(bool estado){
        _estado = estado;
    }

//METODOS:
    void Rol::mostrar(){
        if(!getEstado()){
            cout << "[Rol inactivo / dado de baja]" << endl;
            return;
        }
        cout << "-------------------" << endl;
        cout << "---DATOS DEL ROL---" << endl;
        cout << "-------------------" << endl;
        cout << "ID del rol: " << getIdRol() << endl;
        cout << "Nombre del rol: " << getNombre() << endl;
        cout << endl;
    }
