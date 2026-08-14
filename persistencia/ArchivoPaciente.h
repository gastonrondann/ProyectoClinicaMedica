#pragma once

#include "../entidades/Paciente.h"

class ArchivoPaciente{
private:
    char _nombreArchivo[30];

public:
    //CONSTRUCTOR:
        ArchivoPaciente();
    //GETTERS:
        int getNuevoId();
        int getCantidadRegistros();

    //METODOS ABML
        bool guardar(Paciente reg);
        Paciente leer(int pos);
        bool modificar(Paciente reg, int pos);
        bool bajaLogica(int posicion);
        bool altaLogica(int posicion);

    //BUSCADORES
        int buscarPosicion(int idPaciente);
        int buscarPorDni(const char* dni);
        int buscarPorNroAfiliado(const char* nroAfiliado);
};
