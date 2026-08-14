#pragma once
#include "../persistencia/ArchivoPago.h"
#include "../persistencia/ArchivoTurno.h"
#include "../persistencia/ArchivoObraSocial.h"
#include "../persistencia/ArchivoAgendaMedico.h"
#include "../persistencia/ArchivoMedico.h"
#include "../persistencia/ArchivoEspecialidad.h"
#include "../entidades/Pago.h"

class ManagerPago{
    private:
        ArchivoPago _repoPago;
        ArchivoTurno _repoTurno;
        ArchivoObraSocial _repoObraSocial;
        ArchivoAgendaMedico _repoAgendaMedico;
        ArchivoMedico _repoMedico;
        ArchivoEspecialidad _repoEspecialidad;

    public:
        //CONSTRUCTOR:
            ManagerPago();

        //METODOS:
            void agregar();
            bool agregarPagoDeTurno(int idTurno, Fecha fechaTurno);
            void modificar();
            
        //LISTADO:
            void listados();
            void listar();
            void listarActivos();
            void listarInactivos();

        //CONSULTAS:
            void consultas();
            void consultarPagoPorRangoDeFechas();
            void consultarPagoPorObraSocial();
            void consultarPagoPorEspecialidad();

        //REPORTE N1:
            void reporteEspecialidadMayorRecaudacion();
};
