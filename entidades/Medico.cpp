#include <iostream>
#include <cstring>
#include "Medico.h"
#include "../funciones/validaciones.h"
#include "../persistencia/ArchivoEspecialidad.h"

using namespace std;

//CONSTRUCTOR:
Medico::Medico()
{
    _idMedico = 0;
    strcpy(_matricula, "SIN DATOS");
    _idEspecialidad = 0;
}

Medico::Medico(const char* dni, const char* nombre, const char* apellido, const char* telefono, bool estado, int idMedico, const char* matricula, int idEspecialidad)
    
: Persona(dni, nombre, apellido, telefono, estado)
    {
        setIdMedico(idMedico);
        setMatricula(matricula);
        setIdEspecialidad(idEspecialidad);
    }



//GETTERS Y SETTERS:
int Medico::getIdMedico(){
        return _idMedico;
    }
    void Medico::setIdMedico(int idMedico){
        _idMedico = idMedico;
    }

    const char* Medico::getMatricula(){
        return _matricula;
    }
    void Medico::setMatricula(const char* matricula){
        strcpy(_matricula, matricula);
    }

    int Medico::getIdEspecialidad(){
        return _idEspecialidad;
    }

    void Medico::setIdEspecialidad(int idEspecialidad){
        _idEspecialidad = idEspecialidad;
    }

    
//METODOS:
    void Medico::mostrar(){
       
        cout << "----------------------" << endl;
        cout << "---DATOS DEL MEDICO---" << endl;
        cout << "----------------------" << endl;
        cout << "ID Medico: " << getIdMedico() << endl;
        cout << "Matricula: " << getMatricula() << endl;
        Persona::mostrar();
        ArchivoEspecialidad archivoEspecialidades;
        int pos = archivoEspecialidades.buscarPosicion(_idEspecialidad);
        Especialidad esp = archivoEspecialidades.leer(pos);
        cout << "Especialidad: " << esp.getNombre() << endl;
        cout << endl;

          cout << "Estado: ";
    if(getEstado()){
        cout<< "Activo" <<endl;
    }
    else{
        cout<< "Inactivo" <<endl;
    }
        cout<< endl;
    }