#pragma once

class Rol{
    private:
        int _idRol;
        char _nombre[20];
        bool _estado;
        
    public:
        //CONSTRUCTORES.
            Rol(int idRol = 999, const char* nombreRol = "SIN DATOS", bool estado = true);

        //GETTERS Y SETTERS.
            int getIdRol();
            bool setIdRol(int idRol);

            const char* getNombre();
            bool setNombre(const char* nombreRol);

            bool getEstado();
            bool setEstado(bool estado);

        //METODOS:
            void mostrar();
};
