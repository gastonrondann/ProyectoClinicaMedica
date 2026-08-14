#pragma once

class Especialidad{
    private:
        int _idEspecialidad;
        char _nombre[50];
        bool _estado;

    public:
        //CONSTRUCTORES:
            Especialidad();
            Especialidad(int idEspecialidad, const char* nombre, bool estado);

        //GETTERS Y SETTERS:
            int getIdEspecialidad();
            void setIdEspecialidad(int idEspecialidad);

            const char* getNombre();
            void setNombre(const char* nombre);

            bool getEstado();
            void setEstado(bool estado);

        //METODOS:
            void mostrar();
};