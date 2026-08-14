#pragma once

class Hora {
    private:
        int _hora;
        int _minuto;

    public:
        // CONSTRUCTOR:
        Hora(int hora = 0, int minuto = 0);

        // GETTERS Y SETTERS:
        int getHora();
        bool setHora(int hora);

        int getMinuto();
        bool setMinuto(int minuto);

        // METODOS
        void mostrar();
        bool agregar();
};
