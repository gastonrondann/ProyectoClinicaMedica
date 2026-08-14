#include <iostream>
#include "MenuRolMedico.h"

using namespace std;

MenuRolMedico::MenuRolMedico(){
    setCantidadItems(5);
}

void MenuRolMedico::mostrarOpciones(){
    cout << "---------------------" << endl;
    cout << "---MENU ROL MEDICO---" << endl;
    cout << "---------------------" << endl;
    cout << "1. Agregar agenda" << endl;
    cout << "2. Modificar agenda" << endl;
    cout << "3. Dar de baja una agenda" << endl;
    cout << "4. Listar agendas" << endl;
    cout << "---------------------" << endl;
    cout << "0.Salir" << endl;
}

void MenuRolMedico::ejecutarOpciones(int opcion){
    switch(opcion)
    {
    case 1:
        _repoAgendaMedico.agregar();
        break;
    case 2:
        _repoAgendaMedico.modificar();
        break;
    case 3:
        _repoAgendaMedico.bajaLogica();
        break;
    case 4:
        _repoAgendaMedico.listarTodos();
        break;
    case 0:
        break;
    default:
        cout << "Opcion invalida." << endl;
        break;
    }
}
