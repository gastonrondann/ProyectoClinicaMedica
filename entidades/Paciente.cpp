#include "Paciente.h"
#include <cstring>
#include <iostream>
using namespace std;

//CONSTRUCTORES:
Paciente::Paciente(){
    _idPaciente = 0;
    _idObraSocial = 0;
    strcpy(_nroAfiliado, "SIN DATOS");
    strcpy(_antecedentes, "SIN DATOS");
}

Paciente::Paciente(const char* dni, const char* nombre, const char* apellido, const char* telefono, bool estado, int idPaciente, int idObraSocial, const char* nroAfiliado, const char* antecedentes, Fecha fechaNacimiento)

: Persona(dni, nombre, apellido, telefono, estado)
{
    setIdPaciente(idPaciente);
    setIdObraSocial(idObraSocial);
    setNroAfiliado(nroAfiliado);
    setAntecedentes(antecedentes);
    setFechaNacimiento(fechaNacimiento);
}

//GETTERS Y SETTERS:
  int Paciente::getIdPaciente(){
    return _idPaciente;
  }
  void Paciente::setIdPaciente(int idPaciente){
    _idPaciente = idPaciente;
  }

  int Paciente::getIdObraSocial(){
    return _idObraSocial;
  }
  void Paciente::setIdObraSocial(int idObraSocial){
    _idObraSocial = idObraSocial;
  }

  const char* Paciente::getNroAfiliado(){
    return _nroAfiliado;
  }
  void Paciente::setNroAfiliado(const char* nroAfiliado){
    strcpy(_nroAfiliado, nroAfiliado);
  }

    const char* Paciente::getAntecedentes(){
    return _antecedentes;
  }
  void Paciente::setAntecedentes(const char* antecedentes){
    strcpy(_antecedentes, antecedentes);
  }

  Fecha Paciente::getFechaNacimiento(){
    return _fechaNacimiento;
  }
  void Paciente::setFechaNacimiento(Fecha fechaNacimiento){
    _fechaNacimiento = fechaNacimiento;
  }

//METODOS:
    void Paciente::mostrar(){

        cout << "------------------------" << endl;
        cout << "---DATOS DEL PACIENTE---" << endl;
        cout << "------------------------" << endl;
        cout << "ID del paciente: " << _idPaciente << endl;
        Persona::mostrar();
        cout << "ID de la obra social: " << _idObraSocial << endl;
        cout << "Numero de afiliado: " << _nroAfiliado << endl;
        cout << "Antecedentes: " << _antecedentes << endl;
        cout << "Fecha de nacimiento: ";
        _fechaNacimiento.mostrar();
        cout << endl;

          cout << "Estado: ";
    if(getEstado()){
        cout<< "Activo" <<endl;
    }
    else{
        cout<< "Inactivo" <<endl;
    }
        cout << endl;
    }
