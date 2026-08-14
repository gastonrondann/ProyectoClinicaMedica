#include <iostream>
#include "MenuConsultas.h"

using namespace std;

MenuConsultas::MenuConsultas(){
    setCantidadItems(12);
}

void MenuConsultas::mostrarOpciones(){
    cout << "--------------------" << endl;
    cout << "---MENU CONSULTAS---" << endl;
    cout << "--------------------" << endl;
    cout << "1. Consulta de paciente por DNI" << endl;
    cout << "2. Consulta de paciente por numero de afiliado" << endl;
    cout << "--------------------" << endl;
    cout << "3. Consulta de disponibilidad de agenda" << endl;
    cout << "4. Consulta de disponibilidad de agenda por fecha" << endl;
    cout << "5. Consulta de disponibilidad de agenda por especialidad" << endl;
    cout << "--------------------" << endl;
    cout << "6. Consultas de turnos" << endl;
    cout << "--------------------" << endl;
    cout << "7. Consultas de pagos" << endl;
    cout << "--------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuConsultas::ejecutarOpciones(int opcion){
    switch(opcion){
    case 1:
        _repoPaciente.consultarPacientePorDni();
        break;
    case 2:
        _repoPaciente.consultarPacientePorAfiliado();
        break;
    case 3:
        _repoAgendaMedico.consultarPorMedico();
        break;
    case 4:
        _repoAgendaMedico.consultarPorFecha();
        break;
    case 5:
        _repoAgendaMedico.consultarPorEspecialidad();
        break;
    case 6:
        _repoTurno.consultas();
        break;
    case 7:
        _repoPago.consultas();
        break;
    case 0:
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
