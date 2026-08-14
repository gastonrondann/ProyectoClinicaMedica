#pragma once

#include "../interfaz/Menu.h"
#include "../controladores/ManagerPaciente.h"
#include "../controladores/ManagerAgendaMedico.h"
#include "../controladores/ManagerTurno.h"
#include "../controladores/ManagerPago.h"

class MenuConsultas : public Menu{
    private:
        ManagerPaciente _repoPaciente;
        ManagerAgendaMedico _repoAgendaMedico;
        ManagerTurno _repoTurno;
        ManagerPago _repoPago;

    public:
        MenuConsultas();

    protected:
        void mostrarOpciones() override;
        void ejecutarOpciones(int opcion) override;
};
