#pragma once

#include "Menu.h"
#include "../controladores/ManagerPaciente.h"
#include "../controladores/ManagerMedico.h"
#include "../controladores/ManagerEspecialidad.h"
#include "../controladores/ManagerTurno.h"

class MenuListados : public Menu{
    private:
        ManagerPaciente _pacienteManager;
        ManagerMedico _medicoManager;
        ManagerEspecialidad _especialidadManager;
        ManagerTurno _turnoManager;

    public:
        MenuListados();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};