#include <iostream>
#include "MenuRoles.h"

using namespace std;

MenuRoles::MenuRoles(){
    setCantidadItems(4);
}

void MenuRoles::mostrarOpciones(){
    cout << "-------------------" << endl;
    cout << "---MENU DE ROLES---" << endl;
    cout << "-------------------" << endl;
    cout << "1. Agregar rol" << endl;
    cout << "2. Modificar rol" << endl;
    cout << "3. Listados" << endl;
    cout << "-------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuRoles::ejecutarOpciones(int opcion){
    switch(opcion){
    case 1:
        _managerRol.agregar();
        break;
    case 2:
        _managerRol.modificar();
        break;
    case 3:
        _managerRol.listados();
        break;
    case 0:
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
