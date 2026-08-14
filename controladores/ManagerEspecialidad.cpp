#include <iostream>
#include <cstring>
#include "ManagerEspecialidad.h"
#include "../entidades/Especialidad.h"
#include "../funciones/validaciones.h"
using namespace std;

//COMPLETO !!

//CONSTRUCTOR:
    ManagerEspecialidad::ManagerEspecialidad(){}

//METODOS:
    void ManagerEspecialidad::agregar(){
        system("cls");
        char auxNombre[50];
        cout << "---INGRESAR DATOS DE ESPECIALIDAD---" << endl;
        int idEspecialidad = _repoEspecialidad.getNuevoId();
        if(!validarId(idEspecialidad)){
            cout << "Error! No se pudo asignar el ID automatico generado..." << endl;
            return;
        }
        bool nombreValido = false;
        do{
            cout << "Nombre de la especialidad medica: ";
            cin.getline(auxNombre, 50);
            int pos = _repoEspecialidad.buscarPorNombre(auxNombre);
            if(pos >= 0){
                cout << "La especialidad ya existe en el sistema (duplicada)" << endl;
            } else if(!validarNombre(auxNombre)){
                cout << "Error! El nombre es invalido..." << endl;
            } else {
                nombreValido = true;
            }
        } while(!nombreValido);
        Especialidad reg(idEspecialidad, auxNombre, true);
        if(_repoEspecialidad.guardar(reg)){
            cout << "Especialidad guardada correctamente!" << endl;
        } else {
            cout << "Error! No se pudo guardar la especialidad en el disco..." << endl;
        }
    }

    void ManagerEspecialidad::modificar(){
        system("cls");
        char nombreBuscado[50];
        cout << "--- MODIFICAR DATOS DE ESPECIALIDAD ---" << endl;

        cout << "Ingrese el nombre de la Especialidad a modificar: ";
        cin.getline(nombreBuscado, 50);
        int pos = _repoEspecialidad.buscarPorNombre(nombreBuscado);
        if(pos == -1){
            cout << "NO EXISTE LA ESPECIALIDAD EN EL SISTEMA" << endl;
            return;
        }

        //SI LA ESPECIALIDAD EXISTE...

        Especialidad reg = _repoEspecialidad.leer(pos);

        if(!reg.getEstado()){
            cout << "LA ESPECIALIDAD SE ENCUENTRA DADA DE BAJA" << endl;
            return;
        }


        listar(reg);
        cout << "----------------------------------------" << endl;
        int opcion;
        cout << "Que dato desea modificar?" << endl;
        cout << "1. Nombre de la especialidad" << endl;
        cout << "0. Cancelar operacion" << endl;
        cout << "Seleccione una opcion: ";
        cin>> opcion;
        cin.ignore();

        char nombreTemporal[50];
        switch(opcion){
            case 1: {
                bool nombreValido = false;

                do{
                    cout << "Ingrese Nuevo Nombre de la especialida medica: ";
                    cin.getline(nombreTemporal, 50);

                    if(strcmp(nombreTemporal, reg.getNombre()) == 0){
                        cout << "Error! Es el mismo nombre que ya tenia" << endl;
                    }
                    else{
                        int posNueva = _repoEspecialidad.buscarPorNombre(nombreTemporal);
                        if(posNueva >= 0 && posNueva != pos){
                            cout << "EL NUEVO NOMBRE DE ESPECIALIDAD YA EXISTE EN EL SISTEMA" << endl;
                        }


                        else if(!validarNombre(nombreTemporal)){
                            cout << "ERROR: El nombre es invalido" << endl;
                        }
                        else{
                            nombreValido = true;
                        }
                    }
                } while(!nombreValido);
                reg.setNombre(nombreTemporal);
                break;
            }

                case 0:
                cout << "Operacion cancelada por el usuario." << endl;
                return;
            default:
                cout << "Opcion incorrecta." << endl;
                return;
        }


        if(_repoEspecialidad.modificar(reg, pos)){
            cout << "ESPECIALIDAD MODIFICADA CORRECTAMENTE" << endl;
        } else
        {
            cout << "ERROR AL GUARDAR LAS MODIFICACIONES" << endl;
        }
    }




    void ManagerEspecialidad::bajaLogica(){
        system("cls");
        char auxNombre[50];
        cout << "---ELIMINAR ESPECIALIDAD (BAJA LOGICA)---" << endl;
        cout << "Ingrese el nombre de la especialidad a dar de baja: ";
        cin.getline(auxNombre, 50);

        int pos = _repoEspecialidad.buscarPorNombre(auxNombre);

        if(pos == -1){
            cout << "ERROR: La especialidad no existe..." << endl;
            return;
        }

        Especialidad reg = _repoEspecialidad.leer(pos);
        if(reg.getEstado() == false)
        {
            cout << "La especialidad ya se encuentra dada de baja" << endl;
            return;
        }


        if(_repoEspecialidad.bajaLogica(pos)){
            cout << "La especialidad ha sido cancelada/dada de baja con exito!" << endl;
        }
        else
        {
            cout << "ERROR: No se pudo procesar la baja en el archivo..." << endl;
        }
    }


void ManagerEspecialidad::altaLogica(){
        system("cls");
        char auxNombre[50];
        cout << "---ALTA ESPECIALIDAD (ALTA LOGICA)---" << endl;
        cout << "Ingrese el nombre de la especialidad a dar de alta: ";
        cin.getline(auxNombre, 50);

        int pos = _repoEspecialidad.buscarPorNombre(auxNombre);

        if(pos == -1){
            cout << "ERROR: La especialidad no existe..." << endl;
            return;
        }

        Especialidad reg = _repoEspecialidad.leer(pos);
        if(reg.getEstado() == true){
            cout << "Error! La especialidad ya se encuentra dada de alta" << endl;
            return;
        }

        if(_repoEspecialidad.altaLogica(pos)){
            cout << "La especialidad ha sido dada de alta con exito!" << endl;
        }
        else
        {
            cout << "ERROR: No se pudo procesar la alta en el archivo..." << endl;
        }
    }    


//LISTADOS:
void ManagerEspecialidad::listar(Especialidad reg){
    reg.mostrar();
}



    void ManagerEspecialidad::listar(int opcion){
        int cantidad = _repoEspecialidad.getCantidadRegistros();
        bool hayEspecialidades = false;
        cout << "---LISTADO DE ESPECIALIDADES---" << endl;

        if(opcion == 1){
        for(int i = 0; i < cantidad; i++){
            Especialidad reg = _repoEspecialidad.leer(i);
            if(reg.getEstado() == true){
                reg.mostrar();
                hayEspecialidades = true;
            }
        }
    }
    
    else if(opcion == 2)
    {
        for(int i = 0; i < cantidad; i++){
            Especialidad reg = _repoEspecialidad.leer(i);
            if(reg.getEstado() == false){
                reg.mostrar();
                hayEspecialidades = true;
            }
        }
    }

    else
    {
        for(int i = 0; i < cantidad; i++){
            Especialidad reg = _repoEspecialidad.leer(i);
                reg.mostrar();
                hayEspecialidades = true;
        }
    }


        if(!hayEspecialidades){
            cout << endl;
            cout << "No hay ESPECIALIDADES registradas en el sistema." << endl;
        }
    }




    void ManagerEspecialidad::listarPorEspecialidad(){
        //1) ME FIJO SI TENGO REGISTROS
        int cant = _repoEspecialidad.getCantidadRegistros();
        //2) SI EL REGISTRO NO TIENE NADA, ME VOY CON UN RETURN
        if(cant <= 0){
            cout << "El archivo no tiene registros" << endl;
            return;
        }
        //3) SI TIENE REGISTROS PIDO MEMORIA DINAMICA PARA CANT --- > CANT PUEDE SER 5, 20, 50 O 500 REGISTROS
        Especialidad *esp = new Especialidad[cant];
        //4) LEO LO QUE HAY EN CANT Y LO TRAIGO A MEMORIA
        for(int i=0; i<cant; i++){
            esp[i] = _repoEspecialidad.leer(i);
        }
        //5) HAGO LA COMPARACION DE LA PRIMER LETRA DE LA ESPECIALIDAD
        //ORDENADO ALFABETICAMENTE --- > SI DA MENOR A 0 ES PORQUE EL PRIMER NOMBRE VA PRIMERO
        //SE LLAMA METODO BURBUJA
        Especialidad aux;
        for(int i=0; i<cant - 1; i++){
            for(int x= i+1; x<cant; x++){
                if(strcmp(esp[i].getNombre(), esp[x].getNombre()) < 0){
                        aux = esp[i]; //ME CREO UN VARIABLE AUX PARA GUARDAR PROVISORIAMENTE
                        esp[i] = esp[x];
                        esp[x] = aux;
                    }
                }
            }
        //6) MOSTRAR
        for(int i=0; i<cant; i++){
                    esp[i].mostrar();
            cout << "------------------"<< endl;
        }
    //7) CIERRE DE MEMORIA DINAMICA
    delete[] esp;
    }
