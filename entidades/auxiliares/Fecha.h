#pragma once
class Fecha{
    private:
        int _dia;
        int _mes;
        int _anio;

    public:
        //CONSTRUCTOR:
            Fecha(int dia = 0, int mes = 0, int anio = 0);

        //GETTERS Y SETTERS:
            int getDia();
            void setDia(int dia);

            int getMes();
            void setMes(int mes);

            int getAnio();
            void setAnio(int anio);


        //METODOS
            void mostrar();
            bool esIgual(Fecha otra);
            bool fechaEsMayorOIgual(Fecha otra);
            bool fechaEsMenorOIgual(Fecha otra);
            bool agregar();
};



