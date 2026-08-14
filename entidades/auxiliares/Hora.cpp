#include <iostream>
#include "Hora.h"

using namespace std;

// CONSTRUCTOR:
    Hora::Hora(int hora, int minuto){
        if(hora == 0 &&
            minuto == 0){
            _hora = hora;
            _minuto = minuto;
        }
        else {
            setHora(hora);
            setMinuto(minuto);
        }
    }

// GETTERS Y SETTERS:
    int Hora::getHora() {
        return _hora;
    }

    bool Hora::setHora(int hora) {
            _hora = hora;
            return true;
    }

    int Hora::getMinuto() {
        return _minuto;
    }

    bool Hora::setMinuto(int minuto) {
            _minuto = minuto;
            return  true;
    }

// METODOS:
    void Hora::mostrar() {
        if (_hora < 10) cout << "0";
        cout << _hora << ":";
        if (_minuto < 10) cout << "0";
        cout << _minuto;
    }


    
    bool Hora::agregar()
{
    int hora, minuto;

    cout << "Hora: ";
    cin >> hora;

    cout << "Minuto: ";
    cin >> minuto;

    cin.ignore();

    return setHora(hora) && setMinuto(minuto);
}

