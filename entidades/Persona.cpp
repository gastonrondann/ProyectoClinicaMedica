#include <iostream>
#include <cstring>
#include "Persona.h"

using namespace std;

//CONSTRUCTOR:
Persona::Persona(){
    strcpy(_dni, "SIN DATOS");
    strcpy(_nombre, "SIN DATOS");
    strcpy(_apellido, "SIN DATOS");
    strcpy(_telefono, "SIN DATOS");
    _estado = true;
}

Persona::Persona(const char* dni, const char* nombre, const char* apellido, const char* telefono, bool estado)
{
    setDni(dni);
    setNombre(nombre);
    setApellido(apellido);
    setTelefono(telefono);
    setEstado(estado);
}

//GETTERS Y SETTERS:
    const char* Persona::getDni(){
        return _dni;
    }
    void Persona::setDni(const char* dni){
        strcpy(_dni, dni);
    }

    const char* Persona::getNombre(){
        return _nombre;
    }
    void Persona::setNombre(const char* nombre){
        strcpy(_nombre, nombre);
    }

    const char* Persona::getApellido(){
        return _apellido;
    }
    void Persona::setApellido(const char* apellido){
        strcpy(_apellido, apellido);
    }

    const char* Persona::getTelefono(){
        return _telefono;
    }
    void Persona::setTelefono(const char* telefono){
        strcpy(_telefono, telefono);
    }

    bool Persona::getEstado(){
        return _estado;
    }
    void Persona::setEstado(bool estado){
        _estado = estado;
    }

//METODOS
    void Persona::mostrar(){
        cout << "DNI: " << getDni() << endl;
        cout << "Nombre: " << getNombre() << endl;
        cout << "Apellido: " << getApellido() << endl;
        cout << "Telefono: " << getTelefono() << endl;
        cout << "Estado: " << (getEstado() ? "Activo" : "Inactivo") << endl;
    }
