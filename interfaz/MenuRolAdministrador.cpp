#include <iostream>
#include "MenuRolAdministrador.h"

using namespace std;

MenuRolAdministrador::MenuRolAdministrador(){
    setCantidadItems(13);
}

void MenuRolAdministrador::mostrarOpciones(){
    cout << "----------------------------" << endl;
    cout << "---MENU ROL ADMINISTRADOR---" << endl;
    cout << "----------------------------" << endl;
    cout << "1. Agendas medicas" << endl;
    cout << "2. Especialidades" << endl;
    cout << "3. Medicos" << endl;
    cout << "4. Obras sociales" << endl;
    cout << "5. Pacientes" << endl;
    cout << "6. Pagos" << endl;
    cout << "7. Roles" << endl;
    cout << "8. Turnos" << endl;
    cout << "9. Usuarios" << endl;
    cout << "----------------------------" << endl;
    cout << "10. Listados" << endl;
    cout << "11. Consultas" << endl;
    cout << "12. Reportes" << endl;
    cout << "----------------------------" << endl;
    cout << "0. Salir" << endl;
}

void MenuRolAdministrador::ejecutarOpciones(int opcion){
    switch(opcion){
    case 1:
        _menuAgendasMedicas.ejecutarMenu();
        break;
    case 2:
        _menuEspecialidades.ejecutarMenu();
        break;
    case 3:
        _menuMedicos.ejecutarMenu();
        break;
    case 4:
        _menuObrasSociales.ejecutarMenu();
        break;
    case 5:
        _menuPacientes.ejecutarMenu();
        break;
    case 6:
        _menuPagos.ejecutarMenu();
        break;
    case 7:
        _menuRoles.ejecutarMenu();
        break;
    case 8:
        _menuTurnos.ejecutarMenu();
        break;
    case 9:
        _menuUsuarios.ejecutarMenu();
        break;
    case 10:
        _menuListados.ejecutarMenu();
        break;
    case 11:
        _menuConsultas.ejecutarMenu();
        break;
    case 12:
        _menuReportes.ejecutarMenu();
        break;
    case 0:
        return;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
