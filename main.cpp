#include <iostream>
#include "interfaz/MenuPrincipal.h"
#include "controladores/ManagerAgendaMedico.h"
#include "controladores/ManagerEspecialidad.h"
#include "controladores/ManagerMedico.h"
#include "controladores/ManagerObraSocial.h"
#include "controladores/ManagerPaciente.h"
#include "controladores/ManagerPago.h"
#include "controladores/ManagerRol.h"
#include "controladores/ManagerTurno.h"
#include "controladores/ManagerUsuario.h"

using namespace std;

int main(){

    MenuPrincipal mp;
    mp.ejecutarMenu();

    system("pause");

    return 0;
}
