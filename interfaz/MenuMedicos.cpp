#include <iostream>
#include "MenuMedicos.h"

using namespace std;

MenuMedicos::MenuMedicos(){
    setCantidadItems(10);
}

void MenuMedicos::mostrarOpciones(){
    cout << "------------------" << endl;
    cout << "---MENU MEDICOS---" << endl;
    cout << "------------------" << endl;
    cout << "1. Agregar medico" << endl;
    cout << "2. Modificar medico" << endl;
    cout << "3. Dar de baja medico" << endl;
    cout << "4. Dar de alta medico" << endl;
    cout << "5. Listar medicos activos" << endl;
    cout << "6. Listar medicos inactivos" << endl;
    cout << "7. Listar todos los medicos" << endl;
    cout << "------------------" << endl;
    cout << "8. Listar medicos por apellido" << endl;
    cout << "9. Listar medicos por especialidad" << endl;
    cout << "------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuMedicos::ejecutarOpciones(int opcion){
    switch(opcion){
    case 1:
        _managerMedico.agregar();
        break;
    case 2:
        _managerMedico.modificar();
        break;
    case 3:
        _managerMedico.bajaLogica();
        break;
    case 4:
        _managerMedico.altaLogica();
        break;
    case 5:
        _managerMedico.listar(1);
        break;
    case 6:
        _managerMedico.listar(2);
        break;
    case 7:
        _managerMedico.listar();
        break;
        case 8:
        _managerMedico.listarPorApellido();
        break;
    case 9:
        _managerMedico.listarPorEspecialidad();
        break;
    case 0:
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
