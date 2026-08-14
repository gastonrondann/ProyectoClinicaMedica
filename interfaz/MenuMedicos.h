#pragma once

#include "Menu.h"
#include "../controladores/ManagerMedico.h"
#include "../controladores/ManagerAgendaMedico.h"

class MenuMedicos : public Menu{
    private:
        ManagerMedico _managerMedico;
        ManagerAgendaMedico _managerAgendaMedico;

    public:
        MenuMedicos();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};