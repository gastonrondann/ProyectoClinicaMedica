#pragma once
#include "../entidades/Medico.h"
class ArchivoMedico{
    private:
        char _nombreArchivo[30];

    public:
        //CONSTRUCTOR:
            ArchivoMedico();

        //GETTERS:
            int getNuevoId();
            int getCantidadRegistros();

        //METODOS: ABML
            bool guardar(Medico reg);
            Medico leer(int pos);
            bool modificar(Medico reg, int posicion);
            bool bajaLogica(int posicion);
            bool altaLogica(int posicion);

            
            //BUSCADORES
            int buscarPosicion(int id);
            int buscarPorDni(const char* dni);
            int buscarMatricula(const char* matricula);
            int buscarPorNombreYApellido( const char* nombre, const char* apellido);
};
