#pragma once

#include "Menu.h"
#include "MenuAgendasMedicas.h"
#include "MenuEspecialidades.h"
#include "MenuMedicos.h"
#include "MenuObrasSociales.h"
#include "MenuPacientes.h"
#include "MenuPagos.h"
#include "MenuRoles.h"
#include "MenuTurnos.h"
#include "MenuUsuarios.h"
#include "MenuListados.h"
#include "MenuConsultas.h"
#include "MenuReportes.h"

class MenuRolAdministrador : public Menu{
    private:
    MenuAgendasMedicas _menuAgendasMedicas;
    MenuEspecialidades _menuEspecialidades;
    MenuMedicos _menuMedicos;
    MenuObrasSociales _menuObrasSociales;
    MenuPacientes _menuPacientes;
    MenuPagos _menuPagos;
    MenuRoles _menuRoles;
    MenuTurnos _menuTurnos;
    MenuUsuarios _menuUsuarios;
    MenuListados _menuListados;
    MenuConsultas _menuConsultas;
    MenuReportes _menuReportes;

    public:
        MenuRolAdministrador();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};