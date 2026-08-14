#pragma once
#include "../persistencia/ArchivoPaciente.h"
#include "../persistencia/ArchivoObraSocial.h"

class ManagerPaciente{
    private:
        ArchivoPaciente _repoPaciente;
        ArchivoObraSocial _repoObraSocial;
        
    public:
        //CONSTRUCTOR:    
            ManagerPaciente();
        //METODOS:
            void agregar();
            void modificar();
            void bajaLogica();
            void altaLogica();
        //LISTADOS:
            void listarActivos();
            void listarInactivos();
            void listarTodos();
            
            void listarPorApellido();
            void listarPorObraSocial();
            void listarPorEdad();
        //CONSULTAS:
            void consultarPacientePorDni();
            void consultarPacientePorAfiliado();

};