#pragma once

#include "Menu.h"
#include "../controladores/ManagerTurno.h"
#include "../controladores/ManagerPago.h"

class MenuReportes : public Menu{
    private:
        ManagerTurno _managerTurno;
        ManagerPago _managerPago;

    public:
        MenuReportes();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};