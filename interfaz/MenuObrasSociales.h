#pragma once

#include "Menu.h"
#include "../controladores/ManagerObraSocial.h"

class MenuObrasSociales : public Menu{
    private:
        ManagerObraSocial _managerObraSocial;

    public:
        MenuObrasSociales();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};