#pragma once
#include "Persona.h"

class Medico : public Persona{
    private:
        int _idMedico;
        int _idEspecialidad;
        char _matricula[50];

    public:
        // CONSTRUCTOR:
        Medico(); 

        Medico(const char* dni, const char* nombre, const char* apellido, const char* telefono, bool estado, int idMedico, const char* matricula, int idEspecialidad);

        // GETTERS Y SETTERS
            int getIdMedico();
            void setIdMedico(int idMedico); 

            const char* getMatricula();
            void setMatricula(const char* matricula); 

            int getIdEspecialidad();
            void setIdEspecialidad(int idEspecialidad); 

        //METODOS
            void mostrar();
};