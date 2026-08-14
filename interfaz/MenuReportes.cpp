#include <iostream>
#include "MenuReportes.h"

using namespace std;

MenuReportes::MenuReportes(){
    setCantidadItems(3);
}

void MenuReportes::mostrarOpciones(){
    cout << "--------------------" << endl;
    cout << " ---MENU REPORTES---" << endl;
    cout << "--------------------" << endl;
    cout << "1. Especialidad con mayor recaudacion" << endl;
    cout << "2. Promedio de pacientes atendidos por dia" << endl;
    cout << "--------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuReportes::ejecutarOpciones(int opcion){
    switch(opcion){
    case 1:
        _managerPago.reporteEspecialidadMayorRecaudacion();
        break;
    case 2:
        _managerTurno.reportePromedioPacientesPorDia();
        break;
    case 0:
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
