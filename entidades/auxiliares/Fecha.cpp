#include <iostream>
#include "Fecha.h"

using namespace std;

//CONSTRUCTOR:
    Fecha::Fecha(int dia, int mes, int anio){
            setDia(dia);
            setMes(mes);
            setAnio(anio);
        }

//GETTERS Y SETTERS:
    int Fecha::getDia(){
        return _dia;
    }
    void Fecha::setDia(int dia){
        _dia = dia;
    }

    int Fecha::getMes(){
        return _mes;
    }
    void Fecha::setMes(int mes){
        _mes = mes;
    }

    int Fecha::getAnio(){
        return _anio;
    }
    void Fecha::setAnio(int anio){
        _anio = anio;
    }

//METODOS:
    void Fecha::mostrar(){
        cout << _dia << "/"
            << _mes << "/"
            << _anio;
    }

//FUNCIONES:
    bool Fecha::esIgual(Fecha otra){
        return (_dia == otra.getDia() && _mes == otra.getMes() && _anio == otra.getAnio());
    }

    bool Fecha::fechaEsMayorOIgual(Fecha otra){
        if(_anio > otra.getAnio()){
            return true;
        }
        if(_anio == otra.getAnio()){
            if(_mes > otra.getMes()){
                return true;
            }
            if(_mes == otra.getMes()){
                return _dia >= otra.getDia();
            }
        }
        return false;
    }

    bool Fecha::fechaEsMenorOIgual(Fecha otra){
        if(_anio < otra.getAnio()){
            return true;
        }
        if(_anio == otra.getAnio()){
            if(_mes < otra.getMes()){
                return true;
            }
            if(_mes == otra.getMes()){
                return _dia <= otra.getDia();
            }
        }
        return false;
    }

    bool Fecha::agregar()
{
    int dia, mes, anio;

    cout << "Dia: ";
    cin >> dia;

    cout << "Mes: ";
    cin >> mes;

    cout << "Anio: ";
    cin >> anio;

    cin.ignore();

    if(dia < 1 || dia > 31) return false;
    if(mes < 1 || mes > 12) return false;
    if(anio < 1900) return false;

    _dia = dia;
    _mes = mes;
    _anio = anio;

    return true;
}
