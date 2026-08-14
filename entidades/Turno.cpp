#include "Turno.h"
#include <iostream>
#include "../persistencia/ArchivoPaciente.h"
#include "../funciones/validaciones.h"

using namespace std;

// CONSTRUCTOR
Turno::Turno(int idTurno, int idPaciente, int idAgendaMedico, Fecha fecha, Hora hora, bool estado)
{
    if(idTurno == 999 && idPaciente == 999 && idAgendaMedico == 999 &&
        fecha.getDia() == 0 && fecha.getMes() == 0 && fecha.getAnio() == 0 &&
        hora.getHora() == 0 && hora.getMinuto() == 0 && estado == true)
    {
        _idTurno = idTurno;
        _idPaciente = idPaciente;
        _idAgendaMedico = idAgendaMedico;
        _fecha = fecha;
        _hora = hora;
    }
    else
    {
        setIdTurno(idTurno);
        setIdPaciente(idPaciente);
        setIdAgendaMedico(idAgendaMedico);
        setFecha(fecha);
        setHora(hora);
    }

    setEstado(estado);
}

// GETTERS Y SETTERS

int Turno::getIdTurno()
{
    return _idTurno;
}

bool Turno::setIdTurno(int idTurno)
{
    if(!validarId(idTurno))
        return false;

    _idTurno = idTurno;
    return true;
}

int Turno::getIdPaciente()
{
    return _idPaciente;
}

bool Turno::setIdPaciente(int idPaciente)
{
    if(!validarId(idPaciente))
        return false;

    _idPaciente = idPaciente;
    return true;
}

int Turno::getIdAgendaMedico()
{
    return _idAgendaMedico;
}

bool Turno::setIdAgendaMedico(int idAgendaMedico)
{
    if(!validarId(idAgendaMedico))
        return false;

    _idAgendaMedico = idAgendaMedico;
    return true;
}

Fecha Turno::getFecha()
{
    return _fecha;
}

bool Turno::setFecha(Fecha fecha)
{
    _fecha = fecha;
    return true;
}

Hora Turno::getHora()
{
    return _hora;
}

bool Turno::setHora(Hora hora)
{
    _hora = hora;
    return true;
}

bool Turno::getEstado()
{
    return _estado;
}

bool Turno::setEstado(bool estado)
{
    _estado = estado;
    return true;
}

// METODOS

void Turno::mostrar(){
    if(!getEstado()){
        cout << "[Turno inactivo / cancelado]" << endl;
        return;
    }
    ArchivoPaciente repoPaciente;
    int pos = repoPaciente.buscarPosicion(_idPaciente);
    cout << "\n---DATOS DEL TURNO---" << endl;
    if(pos != -1){
        Paciente pac = repoPaciente.leer(pos);
        cout << "DNI del paciente: " << pac.getDni() << endl;
    } else {
        cout << "ID del paciente: " << _idPaciente << " (No encontrado)" << endl;
    }
    cout << "ID Agenda Medico: " << getIdAgendaMedico() << endl;
    cout << "Fecha: ";
    _fecha.mostrar();
    cout << endl;
    cout << "Hora: ";
    _hora.mostrar();
    cout << endl;
}

void Turno::mostrarMiTurno(){
    cout << "\n---TURNO NUMERO " << getIdTurno() << "---" << endl;
    if(!getEstado()){
        cout << "[Turno inactivo / cancelado]" << endl;
        return;
    }
    cout << "Fecha: ";
    _fecha.mostrar();
    cout << endl;
    
    cout << "Hora: ";
    _hora.mostrar();
    cout << endl;
}
