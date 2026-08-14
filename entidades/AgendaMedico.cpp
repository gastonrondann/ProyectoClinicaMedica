#include <iostream>
#include "AgendaMedico.h"
#include "../funciones/validaciones.h"
using namespace std;

//CONSTRUCTOR:
AgendaMedico::AgendaMedico(){
    _idAgendaMedico = 0;
    _idMedico = 0;
    _disponible = true;
    _estado = true;
}

AgendaMedico::AgendaMedico(int idAgendaMedico, int idMedico, Fecha fecha, Hora hora, bool disponible, bool estado){
    setIdAgendaMedico(idAgendaMedico);
    setIdMedico(idMedico);
    setFecha(fecha);
    setHora(hora);
    setDisponible(disponible);
    setEstado(estado);
}


// GETTERS Y SETTERS:
    int AgendaMedico::getIdAgendaMedico(){
        return _idAgendaMedico;
    }
    void AgendaMedico::setIdAgendaMedico(int idAgendaMedico){
        _idAgendaMedico = idAgendaMedico;
    }

    int AgendaMedico::getIdMedico(){
        return _idMedico;
    }
    void AgendaMedico::setIdMedico(int idMedico){
        _idMedico = idMedico;
    }

    Fecha AgendaMedico::getFecha(){
        return _fecha;
    }
    void AgendaMedico::setFecha(Fecha fecha){
        _fecha = fecha;
    }

    Hora AgendaMedico::getHora(){
        return _hora;
    }
    void AgendaMedico::setHora(Hora hora){
        _hora = hora;
    }

    bool AgendaMedico::getDisponible(){
        return _disponible;
    }
    void AgendaMedico::setDisponible(bool disponible){
        _disponible = disponible;
    }

    bool AgendaMedico::getEstado(){
        return _estado;
    }
    void AgendaMedico::setEstado(bool estado){
        _estado = estado;
    }

// METODOS:
    void AgendaMedico::mostrar(){
        cout << "ID Agenda: " << _idAgendaMedico << endl;
        cout << "ID Medico: " << _idMedico << endl;
        cout << "Fecha ";
        _fecha.mostrar();
        cout << endl;
        cout << "Hora ";
        _hora.mostrar();
        cout << endl;
        cout << "Disponible: " << (_disponible ? "SI" : "NO") << endl;
        cout << "Estado: " << (_estado ? "ACTIVO" : "INACTIVO") << endl;
    }
    