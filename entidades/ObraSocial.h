#pragma once
class ObraSocial{
    private:
        int _idObraSocial;
        char _nombreObraSocial[50];
        bool _estado;

    public:
        //CONSTRUCTOR:
    ObraSocial();
    ObraSocial( int idObraSocial, const char* nombreObraSocial, bool estado);
    //GETTERS Y SETTERS:
    
    void setIdObraSocial(int idObraSocial);
    int getIdObraSocial();

    void setNombre(const char* nombreObraSocial);
    const char* getNombre();

    void setEstado(bool estado);
    bool getEstado();

        //METODOS:
            void mostrar();
};
