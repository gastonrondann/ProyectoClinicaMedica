#include <iostream>
#include "ManagerObraSocial.h"
#include <cstring>
#include <limits>
#include "../funciones/validaciones.h"
using namespace std;

//CONSTRUTOR:
    ManagerObraSocial::ManagerObraSocial() {}


void ManagerObraSocial::agregar(){
    system("cls");

    int idObraSocial = _repoObraSocial.getNuevoId();
    char nombreObraSocial[50];

    cout<< "--- REGISTRAR OBRA SOCIAL ---" <<endl;

    // ID
    if(!validarId(idObraSocial)){
        cout<< "Error al generar el ID." <<endl;
        return;
    }


    // NOMBRE
    bool nombreValido = false;

    do{

        cout<< "Nombre de la obra social: ";
        cin.getline(nombreObraSocial, 50);

        if(_repoObraSocial.buscarPorNombre(nombreObraSocial) != -1){
            cout<< "La obra social ya existe." << endl;
        }
        else if(!validarNombreObraSocial(nombreObraSocial)){
            cout<< "Nombre invalido. Solo se permiten letras y espacios." <<endl;
        }
        else{
            nombreValido = true;
        }

    }while(!nombreValido);


    //se crea un objeto Obra Social con todos los datos validos
     ObraSocial reg(idObraSocial, nombreObraSocial, true);

    if(_repoObraSocial.guardar(reg)){
        cout<< "Obra social registrada correctamente." <<endl;
    }
    else{
        cout<< "No se pudo registrar la obra social." <<endl;
    }
}

void ManagerObraSocial::modificar(){

    system("cls");

    char nombreActual[50];
    char nuevoNombre[50];

    cout<< "--- MODIFICACION DE OBRA SOCIAL ---" <<endl;

    cout<< "Ingrese nombre de la obra social a modificar: ";
    cin.getline(nombreActual,50);

    int pos = _repoObraSocial.buscarPorNombre(nombreActual);

    if(pos == -1){
        cout<< "La obra social no existe o se encuentra dada de baja." <<endl;
        return;
    }

    ObraSocial reg = _repoObraSocial.leer(pos);

    reg.mostrar();

    bool nombreValido = false;

    do{

        cout<< "Ingrese nuevo nombre: ";
        cin.getline(nuevoNombre,50);

        int posNueva = _repoObraSocial.buscarPorNombre(nuevoNombre);

        if(posNueva != -1 && posNueva != pos){
            cout<< "Error: Ya existe una obra social con ese nombre." <<endl;
        }
        else if(!validarNombreObraSocial(nuevoNombre)){
            cout<< "Error: Nombre invalido. Solo se permiten letras y espacios." <<endl;
        }
        else if(compararTexto(nuevoNombre, reg.getNombre())){
            cout<< "Error: El nuevo nombre es igual al actual." <<endl;
        }
        else{
            nombreValido = true;
        }

    }while(!nombreValido);

    reg.setNombre(nuevoNombre);

    if(_repoObraSocial.modificar(reg,pos)){
        cout<< "Obra social modificada correctamente." <<endl;
    }
    else{
        cout<< "No se pudo modificar la obra social." <<endl;
    }

    system("pause");
}



void ManagerObraSocial::bajaLogica(){

    system("cls");

    char nombreObraSocial[50];

    cout<< "--- ELIMINAR OBRA SOCIAL (BAJA LOGICA) ---" <<endl;

    cout<< "Ingrese nombre de la obra social a eliminar: ";
    cin.getline(nombreObraSocial,50);

    int pos = _repoObraSocial.buscarPorNombre(nombreObraSocial);

    if(pos == -1){
        cout<< "ERROR: La obra social no existe en el sistema." <<endl;
        return;
    }

    ObraSocial reg = _repoObraSocial.leer(pos);

    if(reg.getEstado() == false){
        cout<< "ERROR: La obra social ya se encuentra inactiva." <<endl;
        return;
    }

    bool exito = _repoObraSocial.bajaLogica(pos);

    if(exito){
        cout<< "La obra social fue dada de baja correctamente."<<endl;
    }
    else{
        cout<< "ERROR: No se pudo realizar la baja de la obra social."<<endl;
    }
}

void ManagerObraSocial::altaLogica(){

    system("cls");

    char nombreObraSocial[50];

    cout<< "--- ACTIVAR OBRA SOCIAL (ALTA LOGICA) ---" <<endl;
    cout<< "Ingrese nombre de la obra social a activar: ";
    cin.getline(nombreObraSocial,50);

    int pos = _repoObraSocial.buscarPorNombre(nombreObraSocial);

    if(pos == -1){
        cout<< "ERROR: La obra social no existe en el sistema." <<endl;
        return;
    }

    ObraSocial reg = _repoObraSocial.leer(pos);

    if(reg.getEstado() == true){
        cout<< "ERROR: La obra social ya se encuentra activa." <<endl;
        return;
    }

    bool exito = _repoObraSocial.altaLogica(pos);

    if(exito){
        cout<< "La obra social fue activada correctamente." <<endl;
    }
    else{
        cout<< "ERROR: No se pudo activar la obra social." <<endl;
    }

}



//LISTADOS:
     void ManagerObraSocial::listar(){

    int cantidad = _repoObraSocial.getCantidadRegistros();
    bool hayObrasSociales = false;

    cout<< "--- LISTADO DE OBRAS SOCIALES ---" <<endl;

    for(int i = 0; i < cantidad; i++){
        ObraSocial reg = _repoObraSocial.leer(i);

        reg.mostrar();
        hayObrasSociales = true;
    }
    if(!hayObrasSociales){
        cout<< endl;
        cout<< "No hay OBRAS SOCIALES registradas en el sistema." <<endl;
    }
}
    void ManagerObraSocial::listarActivas(){
        int cantidad = _repoObraSocial.getCantidadRegistros();
        bool hayObrasSociales = false;
        cout << "-----------------------------------------" << endl;
        cout << "---LISTADO DE TODAS LAS OBRAS SOCIALES---" << endl;
        cout << "-----------------------------------------" << endl;
        for(int i = 0; i < cantidad; i++){
            ObraSocial reg = _repoObraSocial.leer(i);
            if(reg.getEstado() == true){
                reg.mostrar();
                hayObrasSociales = true;
            }
        }

        
        if(!hayObrasSociales){
            cout << endl;
            cout << "No hay OBRAS SOCIALES registradas en el sistema." << endl;
        }
    }


    void ManagerObraSocial::listarInactivas(){

    int cantidad = _repoObraSocial.getCantidadRegistros();
    bool hayObrasSociales = false;

    cout<< "--- LISTADO DE OBRAS SOCIALES INACTIVAS ---" <<endl;

    for(int i = 0; i < cantidad; i++){
        ObraSocial reg = _repoObraSocial.leer(i);

        if(!reg.getEstado() == false){
            reg.mostrar();
            hayObrasSociales = true;
        }
    }

    if(!hayObrasSociales){
        cout<< endl;
        cout<< "No hay OBRAS SOCIALES inactivas en el sistema." <<endl;
    }
}