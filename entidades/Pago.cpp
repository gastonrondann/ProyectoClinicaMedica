#include "Pago.h"
#include <iostream>
#include "../persistencia/ArchivoPago.h"
#include "../funciones/validaciones.h"

using namespace std;

//CONSTRUCTRES:
    Pago::Pago(int idPago, int idTurno, float monto, Fecha fecha, bool estado){
        if(idPago == 999 && idTurno == 999 && monto == 0.0f && fecha.getDia() == 0 && fecha.getMes() == 0 && fecha.getAnio() == 0 && estado == true){
            _idPago = idPago;
            _idTurno = idTurno;
            _monto = monto;
            _fecha = fecha;
        } else {
            setIdPago(idPago);
            setIdTurno(idTurno);
            setMonto(monto);
            setFecha(fecha);
        }
        setEstado(true);
    }

//GETTERS Y SETTERS.
    int Pago::getIdPago(){
        return _idPago;
    }
    void Pago::setIdPago(int idPago){
        _idPago = idPago;
    }

    int Pago::getIdTurno(){
        return _idTurno;
    }
    void Pago::setIdTurno(int idTurno){
        _idTurno = idTurno;
    }

    float Pago::getMonto(){
        return _monto;
    }
    void Pago::setMonto(float monto){
        _monto = monto;
    }

    Fecha Pago::getFecha(){
        return _fecha;
    }
    void Pago::setFecha(Fecha fecha){
        _fecha = fecha;
    }

    bool Pago::getEstado(){
        return _estado;
    }
    void Pago::setEstado(bool estado){
        _estado = estado;
    }

///METODOS.
    void Pago::mostrar(){
        if(!getEstado()){
            cout << "[Pago rechazado / cancelado]" << endl;
            return;
        }
        cout << "--------------------" << endl;
        cout << "---DATOS DEL PAGO---" << endl;
        cout << "--------------------" << endl;
        cout << "ID del pago: " << getIdPago() << endl;
        cout << "ID Turno asignado: " << getIdTurno() << endl;
        cout << "Monto del pago: " << getMonto() << endl;
        cout << "Fecha del pago: ";
        getFecha().mostrar();
        cout << endl;
    }
