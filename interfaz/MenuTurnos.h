#pragma once

#include "Menu.h"
#include "../controladores/ManagerTurno.h"

class MenuTurnos : public Menu {
    private:
        ManagerTurno _managerTurno;

    public:
        MenuTurnos();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};