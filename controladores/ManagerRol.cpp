#include <iostream>
#include "ManagerRol.h"
#include <cstring>
#include "../funciones/validaciones.h"

using namespace std;

//CONSTRUCTOR:
    ManagerRol::ManagerRol(){}

//METODOS:
    void ManagerRol::agregar(){
        bool repetirTodo;
        do {
            system("cls");
            Rol reg;
            char auxNombreRol[20];
            bool esValido;
            cout << "---INGRESAR DATOS DE ROL---" << endl;
            do {
                esValido = false;
                int nuevoId = _repoRol.getNuevoId();
                if(!reg.setIdRol(nuevoId)){
                    cout << "\nERROR: No se pudo asignar el ID automatico generado..." << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                } else {
                    esValido = true;
                }
            } while(!esValido);
            do {
                esValido = false;
                cout << "Nombre: ";
                cin.getline(auxNombreRol, 20);
                int pos = _repoRol.buscarPorNombre(auxNombreRol);
                if(pos >= 0){
                    cout << "\nEL ROL YA EXISTE EN EL SISTEMA" << endl;
                    if(!repetirIngreso()){
                    return;
                    }
                    cin.ignore();
                    cout << "\n---Reintentando ingreso de nombre del rol---" << endl;
                } else if(!reg.setNombre(auxNombreRol)){
                    cout << "\nERROR: El nombre del rol es invalido (largo incorrecto)..." << endl;
                    if(!repetirIngreso()){
                    return;
                    }
                    cin.ignore();
                    cout << "\n---Reintentando ingreso de nombre del rol---" << endl;
                } else {
                    esValido = true;
                }
            } while(!esValido);
            reg.setEstado(true);
            do {
                esValido = false;
                if(_repoRol.guardar(reg)){
                    cout << "\nROL guardado correctamente!" << endl;
                    esValido = true;
                } else {
                    cout << "\nERROR: No se pudo guardar el rol en el disco..." << endl;
                    if(!repetirIngreso()){
                    return;
                    }
                }
            } while(!esValido);
            repetirTodo = repetirAgregar();
        } while(repetirTodo);
    }

    void ManagerRol::modificar(){
        bool repetirTodo;
        do {
            system("cls");
            bool esValido;
            repetirTodo = false;
            cout << "--- MODIFICAR DATOS DE ROL ---" << endl;
            cout << "Ingrese ID del rol a modificar: ";
            int idRol;
            cin >> idRol;
            cin.ignore();
            int pos = _repoRol.buscarPosicion(idRol);
            if(pos == -1){
                cout << "\nNO EXISTE EL ROL EN EL SISTEMA" << endl;
                if(!repetirIngreso()){
                    return;
                }
                repetirTodo = true;
            } else {
                system("cls");
                Rol reg = _repoRol.leer(pos);
                cout << "\n--- DATOS ACTUALES DEL ROL ---" << endl;
                cout << "Nombre del Rol: " << reg.getNombre() << endl;
                cout << "Estado actual: " << (reg.getEstado() ? "Activo" : "Dado de baja") << endl;
                cout << "-----------------------------------" << endl;
                cout << "\nQue dato desea modificar?" << endl;
                cout << "1. Nombre del Rol" << endl;
                if (reg.getEstado()) {
                    cout << "2. Dar de BAJA (Baja Logica)" << endl;
                } else {
                    cout << "2. Dar de ALTA (Alta Logica)" << endl;
                }
                cout << "0. Cancelar operacion" << endl;
                cout << "Seleccione una opcion: ";
                int opcion;
                cin >> opcion;
                cin.ignore();
                char nombreTemporal[20];
                strcpy(nombreTemporal, reg.getNombre());
                bool estadoTemporal = reg.getEstado();
                switch(opcion){
                    case 1: {
                        if(!reg.getEstado()){
                            cout << "\nERROR: No se puede modificar el nombre de un rol dado de baja." << endl;
                            if(!repetirIngreso()){
                                return;
                            }
                            repetirTodo = true;
                            break;
                        }
                        do {
                            esValido = false;
                            cout << "\nNombre actual: " << reg.getNombre() << endl;
                            cout << "Ingrese nuevo Nombre: ";
                            char auxNombre[20];
                            cin.getline(auxNombre, 20);

                            if(!reg.setNombre(auxNombre)){
                                cout << "\nERROR: El nombre ingresado es invalido..." << endl;
                                if(!repetirIngreso()){
                                    return;
                                }
                            } else {
                                strcpy(nombreTemporal, auxNombre);
                                esValido = true;
                            }
                        } while(!esValido);
                        break;
                    }
                    case 2: {
                        if (reg.getEstado()) {
                            estadoTemporal = false;
                            cout << "\nEstado cambiado a: BAJA (Se aplica al guardar)" << endl;
                        } else {
                            estadoTemporal = true;
                            cout << "\nEstado cambiado a: ACTIVO (Se aplica al guardar)" << endl;
                        }
                        break;
                    }
                    case 0: {
                        cout << "\nOperacion cancelada por el usuario." << endl;
                        return;
                    }
                    default: {
                        cout << "\nOpcion incorrecta." << endl;
                        if(!repetirIngreso()){
                            return;
                        }
                        repetirTodo = true;
                        break;
                    }
                }
                if(!repetirTodo) {
                    reg.setNombre(nombreTemporal);
                    reg.setEstado(estadoTemporal);
                    do {
                        esValido = false;
                        if(_repoRol.modificar(reg, pos)){
                            cout << "\nROL MODIFICADO CORRECTAMENTE" << endl;
                            esValido = true;
                        } else {
                            cout << "\nERROR AL GUARDAR LAS MODIFICACIONES" << endl;
                            if(!repetirIngreso()){
                                return;
                            }
                        }
                    } while(!esValido);
                    repetirTodo = repetirAgregar();
                }
            }
        } while(repetirTodo);
    }

//LISTADO:
    void ManagerRol::listados(){
        bool repetirMenu;
        do {
            system("cls");
            repetirMenu = false;
            cout << "--------------------------------" << endl;
            cout << "---MENU DE LISTADOS DE ROLES---" << endl;
            cout << "--------------------------------" << endl;
            cout << "1. Listar todos los roles" << endl;
            cout << "2. Listar roles activos" << endl;
            cout << "3. Listar roles inactivos" << endl;
            cout << "--------------------------------" << endl;
            cout << "0. Volver al menu principal" << endl;
            cout << "Seleccione una opcion: ";
            int opcion;
            cin >> opcion;
            cin.ignore();
            switch(opcion){
                case 1: {
                    system("cls");
                    listar();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 2: {
                    system("cls");
                    listarActivos();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 3: {
                    system("cls");
                    listarInactivos();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 0: {
                    break;
                }
                default: {
                    cout << "\nOpcion incorrecta. Intente nuevamente." << endl;
                    system("pause");
                    repetirMenu = true;
                    break;
                }
            }
        } while(repetirMenu);
    }

    void ManagerRol::listar(){
        int cantidad = _repoRol.getCantidadRegistros();
        bool hayRoles = false;
        cout << "---LISTADO DE ROLES---" << endl;
        for(int i = 0; i < cantidad; i++){
            Rol reg = _repoRol.leer(i);
            if(reg.getEstado() == true){
                reg.mostrar();
                hayRoles = true;
            }
        }
        if(!hayRoles){
            cout << endl;
            cout << "No hay ROLES registrados en el sistema." << endl;
        }
    }

    void ManagerRol::listarActivos(){
        int cantidad = _repoRol.getCantidadRegistros();
        bool hayRoles = false;
        cout << "---LISTADO DE ROLES ACTIVOS---" << endl;
        for(int i = 0; i < cantidad; i++){
            Rol reg = _repoRol.leer(i);
            if(reg.getEstado() == true){
                reg.mostrar();
                hayRoles = true;
            }
        }
        if(!hayRoles){
            cout << endl;
            cout << "No hay ROLES activos registrados en el sistema." << endl;
        }
    }

    void ManagerRol::listarInactivos(){
        int cantidad = _repoRol.getCantidadRegistros();
        bool hayRoles = false;
        cout << "---LISTADO DE ROLES INACTIVOS---" << endl;
        for(int i = 0; i < cantidad; i++){
            Rol reg = _repoRol.leer(i);
            if(reg.getEstado() == false){
                reg.mostrar();
                hayRoles = true;
            }
        }
        if(!hayRoles){
            cout << endl;
            cout << "No hay PAGOS inactivos registrados en el sistema." << endl;
        }
    }
