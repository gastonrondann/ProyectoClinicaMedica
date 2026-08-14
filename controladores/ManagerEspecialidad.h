#pragma once
#include "../persistencia/ArchivoEspecialidad.h"

class ManagerEspecialidad{
    private:
        ArchivoEspecialidad _repoEspecialidad;
        
    public:
        //CONSTRUCTOR:
            ManagerEspecialidad();

        //METODOS:
            void agregar();
            void modificar();
            void bajaLogica();
            void altaLogica();

        //LISTADOS:
            void listar(int opcion = 3);
            void listar(Especialidad reg); //lista solo una especialidad especifica
            void listarPorEspecialidad();
};
