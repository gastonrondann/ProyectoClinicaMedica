#pragma once

#include "Persona.h"
#include "auxiliares/Fecha.h"

class Paciente : public Persona{
    private:
        int _idPaciente;
        int _idObraSocial;
        char _nroAfiliado[30];
        char _antecedentes[300];
        Fecha _fechaNacimiento;

    public:
        //CONSTRUCTOR:
            Paciente();
            Paciente(const char* dni, const char* nombre, const char* apellido, const char* telefono, bool estado, int idPaciente, int idObraSocial, const char* nroAfiliado, const char* antecedentes, Fecha fechaNacimiento);

        //GETTERS Y SETTERS:
            int getIdPaciente();
            void setIdPaciente(int idPaciente);

            int getIdObraSocial();
            void setIdObraSocial(int idObraSocial);

            const char* getNroAfiliado();
            void setNroAfiliado(const char* nroAfiliado);

            const char* getAntecedentes();
            void setAntecedentes(const char* antecedentes);

            Fecha getFechaNacimiento();
            void setFechaNacimiento(Fecha fechaNacimiento);
        //METODOS:
            void mostrar();
};
