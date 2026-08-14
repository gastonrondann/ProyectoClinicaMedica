#pragma once

#include "Menu.h"
#include "../controladores/ManagerUsuario.h"

class MenuUsuarios : public Menu{
    private:
        ManagerUsuario _managerUsuario;

    public:
        MenuUsuarios();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};