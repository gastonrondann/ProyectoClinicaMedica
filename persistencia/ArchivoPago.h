#pragma once

#include "../entidades/Pago.h"

class ArchivoPago{
    private:
        char _nombreArchivo[30];
        
    public:
        //CONSTRUCTOR:
            ArchivoPago();

        //GETTERS:
            int getNuevoId();
            int getCantidadRegistros();

        //METODOS:
            bool guardar(Pago reg);
            Pago leer(int pos);
            int buscarPosicion(int id);
            bool modificar(Pago reg, int pos);
            bool bajaLogica(int pos);
};
