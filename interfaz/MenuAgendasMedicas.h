#pragma once

#include "Menu.h"
#include "../controladores/ManagerAgendaMedico.h"

class MenuAgendasMedicas : public Menu {
    private:
        ManagerAgendaMedico _managerAgendaMedico;

    public:
        MenuAgendasMedicas();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};