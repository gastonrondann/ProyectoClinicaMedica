#pragma once
#include "../persistencia/ArchivoEspecialidad.h"
#include "../persistencia/ArchivoMedico.h"
#include "../entidades/Medico.h"
#include "../controladores/ManagerEspecialidad.h"

class ManagerMedico{
    private:
        ArchivoMedico _repoMedico;
        ArchivoEspecialidad _repoEspecialidad;
        ManagerEspecialidad _managerEspecialidad;

    public:
        //CONSTRUCTOR:
            ManagerMedico();
        //METODOS:
            void agregar();
            void modificar();
            void bajaLogica();
            void altaLogica();

        //LISTADOS:
            void listar(int opcion = 3);//1 LISTA LOS ACTIVOS, 2 INACTIVOS, 3 TODOS
            void listar(Medico reg); //solo muestra un medico especifico)
            void listarPorApellido();
            void listarPorEspecialidad();
};
