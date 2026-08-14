#pragma once

class Persona{
    private:
        char _dni[15];
        char _nombre[50];
        char _apellido[50];
        char _telefono[20];
        bool _estado;

    public:
            Persona(); 
            Persona(const char* dni, const char* nombre, const char* apellido, const char* telefono, bool estado);

        //GETTERS Y SETTERS:
            const char* getDni();
            void setDni(const char* dni);

            const char* getNombre();
            void setNombre(const char* nombre);

            const char* getApellido();
            void setApellido(const char* apellido);

            const char* getTelefono();
            void setTelefono(const char* telefono);

            bool getEstado();
            void setEstado(bool estado);

        //METODOS:
            void mostrar();
};