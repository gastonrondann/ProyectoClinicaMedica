#pragma once
#include "../entidades/ObraSocial.h"

class ArchivoObraSocial{
    private:
        char _nombreArchivo[30];
    public:
        //CONSTRUCTOR:
            ArchivoObraSocial();
        //GETTERS:
            int getNuevoId();
            int getCantidadRegistros();
        //METODOS
            bool guardar(ObraSocial reg);
            ObraSocial leer(int pos);
            bool modificar(ObraSocial reg, int pos);
            bool bajaLogica(int pos);
            bool altaLogica(int pos);
            
        //BUSCADORES:
            int buscarPosicion(int id);
            int buscarPorNombre(const char* obraSocial);
};
