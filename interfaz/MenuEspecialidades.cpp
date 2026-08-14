#include <iostream>
#include "MenuEspecialidades.h"

using namespace std;

MenuEspecialidades::MenuEspecialidades(){
    setCantidadItems(8);
}

void MenuEspecialidades::mostrarOpciones(){
    cout << "-------------------------" << endl;
    cout << "---MENU ESPECIALIDADES---" << endl;
    cout << "-------------------------" << endl;
    cout << "1. Agregar especialidad" << endl;
    cout << "2. Modificar especialidad" << endl;
    cout << "3. Dar de baja especialidad" << endl;
    cout << "4. Dar de alta especialidad" << endl;
    cout << "5. Listar especialidades activas" << endl;
    cout << "6. Listar especialidades inactivas" << endl;
    cout << "7. Listar todas las especialidades" << endl;
    cout << "-------------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuEspecialidades::ejecutarOpciones(int opcion){
    switch(opcion){
    case 1:
        _managerEspecialidad.agregar();
        break;
    case 2:
        _managerEspecialidad.modificar();
        break;
    case 3:
        _managerEspecialidad.bajaLogica();
        break;
    case 4:
        _managerEspecialidad.altaLogica();
        break;
    case 5:
        _managerEspecialidad.listar(1);
        break;
    case 6:
        _managerEspecialidad.listar(2);
        break;
    case 7:
        _managerEspecialidad.listar();
        break;
    case 0:
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
