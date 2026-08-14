#include <iostream>
#include "MenuListados.h"

using namespace std;

MenuListados::MenuListados(){
    setCantidadItems(8);
}

void MenuListados::mostrarOpciones(){
    cout << "-------------------" << endl;
    cout << "---MENU LISTADOS---" << endl;
    cout << "-------------------" << endl;
    cout << "1. Listado de pacientes por apellido" << endl;
    cout << "2. Listado de pacientes por edad" << endl;
    cout << "3. Lstado de pacientes por obra social" << endl;
    cout << "-------------------" << endl;
    cout << "4. Listado de medicos por apellido" << endl;
    cout << "5. Listado de medicos por especialidad" << endl;
    cout << "-------------------" << endl;
    cout << "6. Listado de especialidades" << endl;
    cout << "-------------------" << endl;
    cout << "7. Listados de turnos" << endl;
    cout << "-------------------" << endl;
    cout << "0. Salir" << endl;

}

void MenuListados::ejecutarOpciones(int opcion){
    switch(opcion){
    case 1:
        _pacienteManager.listarPorApellido();
        break;
    case 2:
        _pacienteManager.listarPorEdad();
        break;
    case 3:
        _pacienteManager.listarPorObraSocial();
        break;
    case 4:
        _medicoManager.listarPorApellido();
        break;
    case 5:
        _medicoManager.listarPorEspecialidad();
        break;
    case 6:
        _especialidadManager.listarPorEspecialidad();
        break;
    case 7:
        _turnoManager.listados();
        break;
    case 0:
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
