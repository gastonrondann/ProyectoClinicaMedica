#pragma once
#include "../persistencia/ArchivoObraSocial.h"

class ManagerObraSocial{
    private:
        ArchivoObraSocial _repoObraSocial;

    public:
        //CONSTRUCTOR:
            ManagerObraSocial();

        //METODOS ABML
            void agregar();
            void modificar();
            void bajaLogica();
            void altaLogica();

        //LISTADOS:
            void listar();
            void listarActivas();
            void listarInactivas();
            void listarSOsde2();
};
