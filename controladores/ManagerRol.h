#pragma once

#include "../persistencia/ArchivoRol.h"
#include "../entidades/Rol.h"

class ManagerRol{
    private:
        ArchivoRol _repoRol;

    public:
        //CONSTRUCTOR:
            ManagerRol();
            
        //METODOS:
            void agregar();
            void modificar();

        //LISTADO:
            void listados();
            void listar();
            void listarActivos();
            void listarInactivos();
};
