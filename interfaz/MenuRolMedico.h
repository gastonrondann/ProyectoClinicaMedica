#pragma once

#include "Menu.h"
#include "../controladores/ManagerAgendaMedico.h"
#include "../controladores/ManagerEspecialidad.h"

class MenuRolMedico : public Menu{
    private:
        ManagerAgendaMedico _repoAgendaMedico;
        ManagerEspecialidad _repoEspecialidad;

    public:
        MenuRolMedico();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};