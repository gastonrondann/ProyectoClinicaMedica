#pragma once

#include "Menu.h"
#include "../controladores/ManagerEspecialidad.h"

class MenuEspecialidades : public Menu{
    private:
        ManagerEspecialidad _managerEspecialidad;

    public:
        MenuEspecialidades();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};