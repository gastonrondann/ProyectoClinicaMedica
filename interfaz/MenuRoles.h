#pragma once

#include "Menu.h"
#include "../controladores/ManagerRol.h"

class MenuRoles : public Menu {
    private:
        ManagerRol _managerRol;

    public:
        MenuRoles();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};