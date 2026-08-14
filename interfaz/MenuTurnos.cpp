#include <iostream>
#include "MenuTurnos.h"

using namespace std;

MenuTurnos::MenuTurnos(){
    setCantidadItems(4);
}

void MenuTurnos::mostrarOpciones(){
    cout << "--------------------" << endl;
    cout << "---MENU DE TURNOS---" << endl;
    cout << "--------------------" << endl;
    cout << "1. Agregar turno" << endl;
    cout << "2. Modificar turno" << endl;
    cout << "3. Listados" << endl;
    cout << "--------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuTurnos::ejecutarOpciones(int opcion){
    switch(opcion){
    case 1:
        _managerTurno.asignarTurno();
        break;
    case 2:
        _managerTurno.modificar();
        break;
    case 3:
        _managerTurno.listados();
        break;
    case 0:
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}