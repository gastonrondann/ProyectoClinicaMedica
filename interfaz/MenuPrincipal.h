#pragma once

#include "Menu.h"
#include "../controladores/ManagerUsuario.h"
#include "../controladores/ManagerRol.h"
#include "MenuRolAdministrador.h"
#include "MenuRolMedico.h"
#include "MenuRolPaciente.h"
#include "../controladores/ManagerObraSocial.h"
#include "../controladores/ManagerEspecialidad.h"

class MenuPrincipal : public Menu{
    private:
        ManagerUsuario _managerUsuario;
        ManagerRol _managerRol;
        ManagerObraSocial _managerObraSocial;
        ManagerEspecialidad _managerEspecialidad;
        int _idPacienteLogueado;

    public:
        MenuPrincipal();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};
