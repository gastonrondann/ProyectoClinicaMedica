#pragma once

#include "Menu.h"
#include "../controladores/ManagerPaciente.h"

class MenuPacientes : public Menu{
    private:
        ManagerPaciente _managerPaciente;

    public:
        MenuPacientes();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};