#pragma once

#include "Menu.h"
#include "../controladores/ManagerPago.h"

class MenuPagos : public Menu {
    private:
        ManagerPago _managerPago;

    public:
        MenuPagos();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};