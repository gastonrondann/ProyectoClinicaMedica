#include <iostream>
#include "MenuAgendasMedicas.h"

using namespace std;

MenuAgendasMedicas::MenuAgendasMedicas(){
    setCantidadItems(8);
}

void MenuAgendasMedicas::mostrarOpciones() {
    cout << "--------------------------" << endl;
    cout << "---MENU AGENDAS MEDICAS---" << endl;
    cout << "--------------------------" << endl;
    cout << "1. Agregar agenda medica" << endl;
    cout << "2. Modificar agenda" << endl;
    cout << "3. Dar de baja agenda medica" << endl;
    cout << "4. Dar de alta agenda medica" << endl;
    cout << "5. Listar agendas medicas activas" << endl;
    cout << "6. Listar agendas medicas inactivas" << endl;
    cout << "7. Listar todas las agendas medicas" << endl;
    cout << "--------------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuAgendasMedicas::ejecutarOpciones(int opcion) {
    switch(opcion) {
    case 1:
        _managerAgendaMedico.agregar();
        break;
    case 2:
        _managerAgendaMedico.modificar();
        break;
    case 3:
        _managerAgendaMedico.bajaLogica();
        break;
    case 4:
        _managerAgendaMedico.altaLogica();
        break;
    case 5:
        _managerAgendaMedico.listarActivos();
        break;
    case 6:
        _managerAgendaMedico.listarInactivos();
        break;
    case 7:
        _managerAgendaMedico.listarTodos();
        break;
    case 0:
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
