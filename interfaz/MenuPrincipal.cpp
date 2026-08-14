#include <iostream>
#include "MenuPrincipal.h"
#include "MenuRolAdministrador.h"
#include "MenuRolMedico.h"
#include "MenuRolPaciente.h"
#include "../entidades/Usuario.h"

using namespace std;

MenuPrincipal::MenuPrincipal(){
    setCantidadItems(6);
    int _idPacienteLogueado = 0;
}

void MenuPrincipal::mostrarOpciones(){
    cout << "---------------------" << endl;
    cout << " ---MENU PRINCIPAL---" << endl;
    cout << "---------------------" << endl;
    cout << " 1. Iniciar sesion" << endl;
    cout << " 2. Registrarse" << endl;
    cout << "---------------------" << endl;
    cout << " 0. Salir" << endl;
}

    void MenuPrincipal::ejecutarOpciones(int opcion){
        switch(opcion){
            case 1: {
                Usuario reg = _managerUsuario.login(_idPacienteLogueado);
                switch(reg.getIdRol()){
                    case 1: {
                        MenuRolPaciente menuRolP(_idPacienteLogueado);
                        menuRolP.ejecutarMenu();
                        break;
                    }
                    case 2: {
                        MenuRolMedico menuRolM;
                        menuRolM.ejecutarMenu();
                        break;
                    }
                    case 3: {
                        MenuRolAdministrador menuA;
                        menuA.ejecutarMenu();
                        break;
                    }
                }
                break;
            }
            case 2: {
                _managerUsuario.registrarUsuario();
                break;
            }
            case 3: {
                _managerRol.agregar();
                break;
            }
            case 4: {
                _managerObraSocial.agregar();
                break;
            }
            case 5: {
                _managerEspecialidad.agregar();
                break;
            }
        }
    }