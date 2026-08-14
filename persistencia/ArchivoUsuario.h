#pragma once
#include <string>
#include "../entidades/Usuario.h"
class ArchivoUsuario{
    private:
        char _nombreArchivo[30];
    public:
        //CONSTRUCTOR:
            ArchivoUsuario();
        //GETTERS:
                int getNuevoId();
                int getCantidadRegistros();
        //METODOS:
            bool guardar(Usuario reg);
            Usuario leer(int pos);
            bool modificar(Usuario reg, int pos);
            bool bajaLogica(int pos);
            bool altaLogica(int pos);

            int buscarPosicion(int id);
            int buscarUsuario(const char* usuario);
};


