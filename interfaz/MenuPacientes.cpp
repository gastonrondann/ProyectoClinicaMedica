#include "MenuPacientes.h"
#include <iostream>

using namespace std;

MenuPacientes::MenuPacientes(){
    setCantidadItems(11);
}

void MenuPacientes::mostrarOpciones(){
    cout << "--------------------" << endl;
    cout << "---MENU PACIENTES---" << endl;
    cout << "--------------------" << endl;
    cout << "1. Agregar paciente" << endl;
    cout << "2. Modificar paciente" << endl;
    cout << "3. Dar de baja paciente" << endl;
    cout << "4. Dar de alta paciente" << endl;
    cout << "5. Listar pacientes activos" << endl; 
    cout << "6. Listar pacientes inactivos" << endl; 
    cout << "7. Listar todos los pacientes" << endl;
    cout << "--------------------" << endl;
    cout << "8. Listar pacientes por apellido" << endl;
    cout << "9. Listar pacientes por obra social" << endl;
    cout << "10. Listar pacientes por edad" << endl;
    cout << "--------------------" << endl;
    cout << "0 - Salir" << endl;
}

void MenuPacientes::ejecutarOpciones(int opcion){
    switch(opcion){
    case 1:
        _managerPaciente.agregar();
        break;
    case 2:
        _managerPaciente.modificar();
        break;
    case 3:
        _managerPaciente.bajaLogica();
        break;
    case 4:
        _managerPaciente.altaLogica();
        break;
    case 5:
        _managerPaciente.listarActivos();
        break;
    case 6:
        _managerPaciente.listarInactivos();
        break;
    case 7:
        _managerPaciente.listarTodos();
        break;
    case 8:
        _managerPaciente.listarPorApellido();
        break;
    case 9:
        _managerPaciente.listarPorObraSocial();
        break;
    case 10:
        _managerPaciente.listarPorEdad();
        break;
    case 0:
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
