#include <iostream>
#include "MenuPagos.h"

using namespace std;

MenuPagos::MenuPagos() {
    setCantidadItems(6);
}

void MenuPagos::mostrarOpciones() {
    cout << "-------------------" << endl;
    cout << "---MENU DE PAGOS---" << endl;
    cout << "-------------------" << endl;
    cout << "1. Agregar pago" << endl;
    cout << "2. Modificar pago" << endl;
    cout << "3. Listados" << endl;
    cout << "-------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuPagos::ejecutarOpciones(int opcion) {
    switch(opcion) {
    case 1:
        _managerPago.agregar();
        break;
    case 2:
        _managerPago.modificar();
        break;
    case 3:
        _managerPago.listados();
        break;
    case 0:
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}