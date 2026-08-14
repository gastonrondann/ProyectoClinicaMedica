#pragma once

class Menu{
    private:
        int _cantidadItems;

    public:
        void ejecutarMenu();

    protected:
        void setCantidadItems(int cantidad);
        int getCantidadItems();
        virtual void mostrarOpciones() = 0;
        int seleccionarOpciones();
        virtual void ejecutarOpciones(int opcion) = 0;
};
