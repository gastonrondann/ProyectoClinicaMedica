#pragma once

#include "Menu.h"
#include "../controladores/ManagerTurno.h"

class MenuRolPaciente : public Menu{
    private:
        ManagerTurno _repoTurno;
        int _idPacienteLogueado;

    public:
        MenuRolPaciente(int idPaciente);

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};