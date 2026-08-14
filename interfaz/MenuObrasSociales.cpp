#include "MenuObrasSociales.h"
#include <iostream>

using namespace std;

MenuObrasSociales::MenuObrasSociales(){
    setCantidadItems(8);
}

void MenuObrasSociales::mostrarOpciones(){
    cout << "-------------------------" << endl;
    cout << "---MENU OBRAS SOCIALES---" << endl;
    cout << "-------------------------" << endl;
    cout << "1. Agregar obra social" << endl;
    cout << "2. Modificar obra social" << endl;
    cout << "3. Dar de baja obra social" << endl;
    cout << "4. Dar de alta obra social" << endl;
    cout << "5. Listar obras sociales activas" << endl;
    cout << "6. Listar obras sociales inactivas" << endl; 
    cout << "7. Listar todas las obras sociales" << endl;
    cout << "-------------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuObrasSociales::ejecutarOpciones(int opcion){
    switch(opcion){
    case 1:
        _managerObraSocial.agregar();
        break;
    case 2:
        _managerObraSocial.modificar();
        break;
    case 3:
        _managerObraSocial.bajaLogica();
        break;
    case 4:
        _managerObraSocial.altaLogica();
        break;
    case 5:
        _managerObraSocial.listarActivas();
        break;
    case 6:
        _managerObraSocial.listarInactivas();
        break;
    case 7:
        _managerObraSocial.listar();
        break;
    case 0:
        return;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
