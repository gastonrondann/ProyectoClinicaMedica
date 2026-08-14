#include <iostream>
#include "MenuRolPaciente.h"
using namespace std;

MenuRolPaciente::MenuRolPaciente(int idPaciente){
    _idPacienteLogueado = idPaciente;
    setCantidadItems(4);
}

void MenuRolPaciente::mostrarOpciones(){
    cout << "-----------------------" << endl;
    cout << "---MENU ROL PACIENTE---" << endl;
    cout << "-----------------------" << endl;
    cout << "1. Agendar turno" << endl;
    cout << "2. Modificar turno" << endl;
    cout << "3. Listar mis turnos" << endl;
    cout << "-----------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuRolPaciente::ejecutarOpciones(int opcion){
    switch(opcion){
        case 1:
            _repoTurno.solicitarTurno(_idPacienteLogueado);
            break;
        case 2:
            _repoTurno.modificar();
            break;
        case 3:
            _repoTurno.listarMisTurnos(_idPacienteLogueado);
            break;
        case 0:
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
    }
}
