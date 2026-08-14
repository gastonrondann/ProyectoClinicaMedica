#pragma once

#include "../persistencia/ArchivoTurno.h"
#include "../persistencia/ArchivoPaciente.h"
#include "../persistencia/ArchivoAgendaMedico.h"
#include "../persistencia/ArchivoMedico.h"
#include "../controladores/ManagerPago.h"
#include "../entidades/Turno.h"

class ManagerTurno{
    private:
        ArchivoTurno _repoTurno;
        ArchivoPaciente _repoPaciente;
        ArchivoAgendaMedico _repoAgendaMedico;
        ArchivoMedico _repoMedico;
        ManagerPago _managerPago;

    public:
        //CONSTRUCTOR.
            ManagerTurno();

        //METODOS.
            void agregar();
            bool cargarDatosComunesTurno(Turno& reg);
            void solicitarTurno(int idPaciente);
            void asignarTurno();
            void modificar();

        //LISTADOS:
            void listados();
            void listar();
            void listarActivos();
            void listarInactivos();
            void listarPorFecha();
            void listarPorHora();
            void listarMisTurnos(int idPaciente);

        //CONSULTAS:
            void consultas();
            void consultarTurnoPorFecha();
            void consultarTurnoPorPaciante();
            void consultarTurnoPorMedico();

            bool esAnioBisiesto(int anio);
            void reportePromedioPacientesPorDia();
};
