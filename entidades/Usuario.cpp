#include <iostream>
#include "Usuario.h"
#include <cstring>
#include <limits>
#include "../funciones/validaciones.h"
#include "../persistencia/ArchivoUsuario.h"
#include "../persistencia/ArchivoRol.h"

using namespace std;

//CONSTRUCTOR:
Usuario::Usuario(){
    _idUsuario = 0;
    strcpy(_nombre, "SIN DATOS");
    strcpy(_usuario, "SIN DATOS");
    strcpy(_password, "SIN DATOS");
    _idRol = 0;
    _estado = true;
}

Usuario::Usuario(int idUsuario, const char* nombre, const char* usuario, const char* password, int idRol, bool estado)
{
    setIdUsuario(idUsuario);
    setNombre(nombre);
    setUsuario(usuario);
    setPassword(password);
    setIdRol(idRol);
    setEstado(estado);
}


//GETTERS Y SETTERS:
    int Usuario::getIdUsuario(){
        return _idUsuario;
    }
    void Usuario::setIdUsuario(int idUsuario){
        _idUsuario = idUsuario;
    }

    const char* Usuario::getNombre(){
        return _nombre;
    }
    void Usuario::setNombre(const char* nombre){
        strcpy(_nombre, nombre);
    }

    const char* Usuario::getApellido(){
        return _apellido;
    }
    void Usuario::setApellido(const char* apellido){
        strcpy(_apellido, apellido);
    }

    const char* Usuario::getUsuario(){
        return _usuario;
    }
    void Usuario::setUsuario(const char* usuario){
        strcpy(_usuario, usuario);
    }

    const char* Usuario::getPassword(){
        return _password;
    }
    void Usuario::setPassword(const char* password){
        strcpy(_password, password);
    }

    int Usuario::getIdRol(){
        return _idRol;
    }
    void Usuario::setIdRol(int idRol){
        _idRol = idRol;
    }

    bool Usuario::getEstado(){
        return _estado;
    }
    void Usuario::setEstado(bool estado){
        _estado = estado;
    }

//METODOS:
void Usuario::mostrar(){

    cout<< "-----------------------" <<endl;
    cout<< "--- DATOS DEL USUARIO ---" <<endl;
    cout<< "-----------------------" <<endl;

    cout<< "ID del usuario: " << getIdUsuario() <<endl;
    cout<< "Nombre: " << getNombre() <<endl;
    cout<< "Usuario: " << getUsuario() <<endl;

    ArchivoRol repoRol;

    int pos = repoRol.buscarPosicion(getIdRol());

    if(pos != -1){
        Rol rol = repoRol.leer(pos);
        cout<< "Rol: " << rol.getNombre() <<endl;
    }
    else{
        cout<< "Rol: Desconocido" <<endl;
    }

    cout << "Estado: ";
    if(getEstado()){
        cout<< "Activo" <<endl;
    }
    else{
        cout<< "Inactivo" <<endl;
    }

    cout << endl;
}
