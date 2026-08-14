#pragma once

#include "../entidades/Rol.h"

class ArchivoRol{
    private:
        char _nombreArchivo[30];
    public:
        //CONSTRUCTOR:
            ArchivoRol();

        //GETTERS:
            int getNuevoId();
            int getCantidadRegistros();

        //METODOS:
            bool guardar(Rol reg);
            Rol leer(int posicion);
            int buscarPosicion(int id);
            int buscarPorNombre(const char* nombre);
            bool modificar(Rol reg, int posicion);
            bool bajaLogica(int posicion);
};
