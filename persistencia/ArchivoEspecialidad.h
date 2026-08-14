#pragma once
#include "../entidades/Especialidad.h"

class ArchivoEspecialidad{
    private:
        char _nombreArchivo[30];
    public:
        //CONSTRUCTOR:
            ArchivoEspecialidad();

        //GETTERS:
            int getNuevoId();
            int getCantidadRegistros();

        //METODOS ABML
            bool guardar(Especialidad reg);
            Especialidad leer(int pos);
            bool modificar(Especialidad reg, int pos);
            bool bajaLogica(int pos);
            bool altaLogica(int pos);

        //BUSCADORES
            int buscarPosicion(int id);
            int buscarPorNombre(const char* especialidad);
};
