#pragma once
#include "../persistencia/ArchivoAgendaMedico.h"
#include "../persistencia/ArchivoMedico.h"
#include "../persistencia/ArchivoEspecialidad.h"
class ManagerAgendaMedico{
    private:
    ArchivoAgendaMedico _repoAgendaMedico;
    ArchivoMedico _repoMedico;
    ArchivoEspecialidad _repoEspecialidad;
    public:
        //CONSTRUCTOR:
            ManagerAgendaMedico();

        //METODOS
            void agregar();
            void modificar();
            void bajaLogica();
            void altaLogica(); 

        //LISTADO:
            void listar();    
            void listarActivos();
            void listarInactivos();
            void listarTodos();

        //CONSULTAS:
            void consultarPorMedico();
            void consultarPorFecha();
            void consultarPorEspecialidad();
};
