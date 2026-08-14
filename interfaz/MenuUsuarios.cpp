#include "MenuUsuarios.h"
#include <iostream>

using namespace std;

MenuUsuarios::MenuUsuarios(){
    setCantidadItems(8);
}

void MenuUsuarios::mostrarOpciones(){
    cout << "-------------------" << endl;
    cout << "---MENU USUARIOS---" << endl;
    cout << "-------------------" << endl;
    cout << "1. Agregar usuario" << endl;
    cout << "2. Modificar usuario" << endl;
    cout << "3. Dar de baja usuario" << endl;
    cout << "4. Dar de alta usuario" << endl;
    cout << "5. Listar usuarios activos" << endl; 
    cout << "6. Listar usuarios inactivos" << endl; 
    cout << "7. Listar todos los usuarios" << endl;
    cout << "-------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuUsuarios::ejecutarOpciones(int opcion){
    switch(opcion){
    case 1:
        _managerUsuario.agregar();
        break;
    case 2:
        _managerUsuario.modificar();
        break;
    case 3:
        _managerUsuario.bajaLogica();
        break;
    case 4:
        _managerUsuario.altaLogica();
        break;
    case 5:
        _managerUsuario.listarActivos();
        break;
    case 6:
        _managerUsuario.listarInactivos();
        break;
    case 7:
        _managerUsuario.listar();
        break;
    case 0:
        return;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
