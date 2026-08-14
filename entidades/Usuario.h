#pragma once

class Usuario{
    private:
        int _idUsuario;
        char _nombre[50];
        char _apellido[50];
        char _usuario[50];
        char _password[50];
        int _idRol;
        bool _estado;

    public:
        //CONSTRUCTOR:
            Usuario();
            Usuario(int idUsuario, const char* nombre, const char* usuario, const char* password, int idRol, bool estado);

        //GETTERS Y SETTERS:
            int getIdUsuario();
            void setIdUsuario(int idUsusario);

            const char* getNombre();
            void setNombre(const char* nombre);

            const char* getApellido();
            void setApellido(const char* apellido);

            const char* getUsuario();
            void setUsuario(const char* usuario);

            const char* getPassword();
            void setPassword(const char* password);

            int getIdRol();
            void setIdRol(int idRol);

            bool getEstado();
            void setEstado (bool estado);

        //METODOS:
            void mostrar();
};