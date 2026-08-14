#pragma once

#include "../entidades/AgendaMedico.h"

class ArchivoAgendaMedico{
    private:
        char _nombreArchivo[30];

    public:
    //CONSTRUCTOR:
        ArchivoAgendaMedico();

    //GETTERS:
        int getNuevoId();
        int getCantidadRegistros();

    //METODOS:
        bool guardar(AgendaMedico reg);
        bool guardar(AgendaMedico reg, int pos);
        AgendaMedico leer(int pos);
        bool modificar(AgendaMedico reg,int pos);
        bool bajaLogica(int posicion);
        bool altaLogica(int pos);

        int buscarPosicion(int id);
        int buscarPorFechaYHora(int idMedico, Fecha f, Hora h);
};

