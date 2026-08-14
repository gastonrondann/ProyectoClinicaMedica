#include "ManagerAgendaMedico.h"
#include "../entidades/Medico.h"
#include "../persistencia/ArchivoMedico.h"
#include <iostream>
#include "../funciones/validaciones.h"
#include <cstring>
#include "../persistencia/ArchivoMedico.h"

using namespace std;

//CONSTRUCTOR:
    ManagerAgendaMedico::ManagerAgendaMedico(){}


void ManagerAgendaMedico::agregar()
{
    system("cls");

    AgendaMedico reg;
    int idAgenda = _repoAgendaMedico.getNuevoId();
    char matricula[50];

    cout  << "---INGRESAR AGENDA MEDICA---"  << endl;

    if(!validarId(idAgenda))
    {
        cout << "ERROR: No se puede asignar el ID." << endl;
        return;
    }

    reg.setIdAgendaMedico(idAgenda);

    //BUSCAR MEDICO

    bool medicoValido = false;
    int posMedico;
    Medico med;

        do
    {
        cout << "Matricula del medico: ";
        cin.getline(matricula,50);

        posMedico = _repoMedico.buscarMatricula(matricula);

        if(posMedico == -1)
        {
            cout << "Error! El medico no existe." << endl;
        }
        else
        {
            med = _repoMedico.leer(posMedico);

            if(!med.getEstado())
            {
                cout << "Error! El medico esta dado de baja." << endl;
            }
            else
            {
                medicoValido = true;
            }
        }

    }while(!medicoValido);

    reg.setIdMedico(med.getIdMedico());

    Fecha fecha;


        cout << "Fecha de la agenda:" << endl;

    while(!fecha.agregar())
    {
        cout << "Fecha invalida." << endl;
    }

    reg.setFecha(fecha);

    Hora hora;

    cout << "Hora de la agenda:" << endl;

    while(!hora.agregar())
    {
        cout << "Hora invalida." << endl;
    }

    reg.setHora(hora);


        if(_repoAgendaMedico.buscarPorFechaYHora(med.getIdMedico(),fecha, hora) != -1)
    {
        cout << "Error! Ya existe una agenda para ese medico en esa fecha y hora." << endl;
        return;
    }

        reg.setDisponible(true);
    reg.setEstado(true);

    if(_repoAgendaMedico.guardar(reg))
    {
        cout << "Agenda medica guardada correctamente." << endl;
    }
    else
    {
        cout << "Error al guardar la agenda medica." << endl;
    }

    system("pause");
}



void ManagerAgendaMedico::modificar()
{
    system("cls");
    char auxMatricula[50];

    int opcion;

    Fecha fecha;
    Hora hora;

    cout << "----MODIFICACION DE AGENDA MEDICA----" << endl;
    cout <<"Ingrese matricula medica: " << endl;
    cin.getline(auxMatricula,50);

    int posMedico = _repoMedico.buscarMatricula(auxMatricula);
    if(posMedico == -1)
    {
        cout << "El medico no existe o esta dado de baja." << endl;
        return;
    }

    Medico med = _repoMedico.leer(posMedico);

    cout << "Ingrese la fecha de la agenda:" << endl;

    while(!fecha.agregar());

    cout << "Ingrese la hora de la agenda:" << endl;

    while(!hora.agregar());

    int posAgenda = _repoAgendaMedico.buscarPorFechaYHora( med.getIdMedico(),fecha,hora);

    if(posAgenda == -1)
    {
        cout << "No existe una agenda con esos datos." << endl;
        return;
    }

    AgendaMedico reg = _repoAgendaMedico.leer(posAgenda);

    reg.mostrar();

    cout << endl;
    cout << "¿Que desea modificar?" << endl;
    cout << "1 - Fecha" << endl;
    cout << "2 - Hora" << endl;
    cout << "3 - Disponibilidad" << endl;
    cout << "0 - Cancelar" << endl;

    cin >> opcion;
    cin.ignore();

    switch(opcion)
    {
    case 1:
{
    Fecha nuevaFecha;

    cout << "Ingrese la nueva fecha:" << endl;

    while(!nuevaFecha.agregar())
    {
        cout << "Fecha invalida." << endl;
    }

    int posNueva = _repoAgendaMedico.buscarPorFechaYHora( reg.getIdMedico(),nuevaFecha,reg.getHora());

if(posNueva != -1 && posNueva != posAgenda)
{
    cout << "Error! Ya existe una agenda para ese medico en esa fecha y hora." << endl;
    return;
}

reg.setFecha(nuevaFecha);

}
break;

case 2:
{
    Hora nuevaHora;

    cout << "Ingrese la nueva hora:" << endl;

    while(!nuevaHora.agregar())
    {
        cout << "Hora invalida." << endl;
    }

    int posNueva = _repoAgendaMedico.buscarPorFechaYHora(reg.getIdMedico(),reg.getFecha(),nuevaHora);

if(posNueva != -1 && posNueva != posAgenda)
{
    cout << "Error! Ya existe una agenda para ese medico en esa fecha y hora." << endl;
    return;
}

reg.setHora(nuevaHora);
}
break;

case 3:
{
    char op;

    do
    {
        cout << "Disponible (S/N): ";
        cin >> op;

        if(op != 'S' && op != 's' &&op != 'N' && op != 'n')
        {
            cout << "Opcion invalida." << endl;
        }

    } while(op != 'S' && op != 's' &&op != 'N' && op != 'n');

    if(op == 'S' || op == 's')
    {
        reg.setDisponible(true);
    }
    else
    {
        reg.setDisponible(false);
    }
}
break;

case 0:
            cout << "Operacion cancelada" << endl;
            return;
        default:
            cout << "Opcion invalida" << endl;
            return;
    }

bool exito = _repoAgendaMedico.modificar(reg, posAgenda);

if(exito)
{
    cout << "Agenda modificada con exito." << endl;
}
else
{
    cout << "No se pudo modificar la agenda." << endl;
}

system("pause");
}






    void ManagerAgendaMedico::bajaLogica()
{
    system("cls");

    char auxDni[15];
    Fecha fecha;
    Hora hora;

    cout << "---- BAJA LOGICA DE AGENDA MEDICA ----" << endl;

    cout << "Ingrese DNI del medico: ";
    cin.getline(auxDni, 15);

    int posMedico = _repoMedico.buscarPorDni(auxDni);

    if(posMedico == -1)
    {
        cout << "El medico no existe o esta dado de baja." << endl;
        system("pause");
        return;
    }

    Medico med = _repoMedico.leer(posMedico);

    cout << "Ingrese la fecha de la agenda:" << endl;
    while(!fecha.agregar());

    cout << "Ingrese la hora de la agenda:" << endl;
    while(!hora.agregar());

    int posAgenda = _repoAgendaMedico.buscarPorFechaYHora(med.getIdMedico(),fecha,hora);

    if(posAgenda == -1)
    {
        cout << "No existe una agenda con esos datos." << endl;
        system("pause");
        return;
    }

    AgendaMedico reg = _repoAgendaMedico.leer(posAgenda);

    if(reg.getEstado() == false)
    {
        cout << "La agenda ya se encuentra dada de baja." << endl;
        system("pause");
        return;
    }

    char opcion;

    cout << "Confirma la baja de la agenda? (S/N): ";
    cin >> opcion;

    if(opcion != 'S' && opcion != 's')
    {
        cout << "Operacion cancelada." << endl;
        system("pause");
        return;
    }

    bool exito = _repoAgendaMedico.bajaLogica(posAgenda);

    if(exito)
    {
        cout << "Agenda medica dada de baja con exito." << endl;
    }
    else
    {
        cout << "ERROR: No se pudo realizar la baja de la agenda." << endl;
    }

    system("pause");
}


void ManagerAgendaMedico::altaLogica()
{
    system("cls");
    char auxDni[15];
    Fecha fecha;
    Hora hora;

    cout << "----ALTA LOGICA DE AGENDA MEDICO----" << endl;

    cout << "Ingrese el DNI del medico"<< endl;
    cin.getline(auxDni,15);

    int posMedico = _repoMedico.buscarPorDni(auxDni);

    if(posMedico == -1)
    {
        cout << "El medico no existe o esta dado de baja." << endl;
        system("pause");
        return;
    }

    Medico med = _repoMedico.leer(posMedico);

    cout << "Ingrese la  fecha de la agenda:" << endl;
    while(!fecha.agregar());

    cout << "Ingrese la hora de la agenda:" << endl;
    while(!hora.agregar());

    int posAgenda = _repoAgendaMedico.buscarPorFechaYHora(med.getIdMedico(),fecha,hora);

    if(posAgenda == -1)
    {
        cout << "No existe una agenda con esos datos." << endl;
        system("pause");
        return;
    }

    AgendaMedico reg = _repoAgendaMedico.leer(posAgenda);

    if(reg.getEstado() == true)
    {
        cout << "La Agenda se encuentra dada de Alta." << endl;
        system("pause");
        return;
    }

    char opcion;
    cin.ignore();

    cout << "Confirma la alta de la agenda? (S/N):  ";
    cin >> opcion;

    if(opcion != 'S' && opcion != 's')
    {
        cout << "Operacion Cancelada." << endl;
        system("pause");
        return;
    }

    bool exito = _repoAgendaMedico.altaLogica(posAgenda);

    if(exito)
    {
        cout << "Agenda medica dada de alta con exito." << endl;
    }
    else
    {
        cout << "ERROR: No se pudo realizar la alta de la agenda." << endl;
    }

    system("pause");
}






//LISTADO:
    void ManagerAgendaMedico::listarActivos()
{
    int cantidad = _repoAgendaMedico.getCantidadRegistros();
    bool hayAgendasMedicas = false;

    cout << "--- LISTADO DE AGENDAS MEDICAS ACTIVAS ---" << endl;

    for(int i = 0; i < cantidad; i++)
    {
        AgendaMedico reg = _repoAgendaMedico.leer(i);

        if(reg.getEstado())
        {
            reg.mostrar();
            cout << "-----------------------------" << endl;
            hayAgendasMedicas = true;
        }
    }

    if(!hayAgendasMedicas)
    {
        cout << endl;
        cout << "No hay agendas medicas activas en el sistema." << endl;
    }
}

void ManagerAgendaMedico::listarInactivos()
{
    int cantidad = _repoAgendaMedico.getCantidadRegistros();
    bool hayAgendasMedicas = false;

    cout << "--- LISTADO DE AGENDAS MEDICAS INACTIVAS ---" << endl;

    for(int i = 0; i < cantidad; i++)
    {
        AgendaMedico reg = _repoAgendaMedico.leer(i);

        if(!reg.getEstado())
        {
            reg.mostrar();
            cout << "-------------------------------" << endl;
            hayAgendasMedicas = true;
        }
    }

    if(!hayAgendasMedicas)
    {
        cout << endl;
        cout << "No hay agendas medicas inactivas en el sistema." << endl;
    }
}

void ManagerAgendaMedico::listarTodos()
{
    int cantidad = _repoAgendaMedico.getCantidadRegistros();
    bool hayAgendasMedicas = false;

    cout << "--- LISTADO DE TODAS LAS AGENDAS MEDICAS ---" << endl;

    for(int i = 0; i < cantidad; i++)
    {
        AgendaMedico reg = _repoAgendaMedico.leer(i);

        reg.mostrar();
        cout << "---------------------------------------" << endl;
        hayAgendasMedicas = true;
    }

    if(!hayAgendasMedicas)
    {
        cout << endl;
        cout << "No hay agendas medicas registradas en el sistema." << endl;
    }
}



//CONSULTAS
    

    void ManagerAgendaMedico::consultarPorMedico()
{
    char auxDni[15];
    bool encontrado = false;

    cout << "Ingrese DNI del medico: ";
    cin.getline(auxDni, 15);

    int posMedico = _repoMedico.buscarPorDni(auxDni);

    if(posMedico == -1)
    {
        cout << "El medico no existe o esta dado de baja." << endl;
        return;
    }

    Medico med = _repoMedico.leer(posMedico);

    int cantidad = _repoAgendaMedico.getCantidadRegistros();

    for(int i = 0; i < cantidad; i++)
    {
        AgendaMedico agenda = _repoAgendaMedico.leer(i);

        if(agenda.getEstado() && agenda.getDisponible() &&agenda.getIdMedico() == med.getIdMedico())
        {
            agenda.mostrar();
            cout << "-----------------------------" << endl;
            encontrado = true;
        }
    }

    if(!encontrado)
    {
        cout << "No se encontraron horarios disponibles para ese medico." << endl;
    }
}



    void ManagerAgendaMedico::consultarPorFecha(){
        Fecha fechaBuscada;
        bool encontrado = false;
        cout << "Ingrese la fecha a consultar:" << endl;
        fechaBuscada.agregar();
        int cant = _repoAgendaMedico.getCantidadRegistros();
        for(int i = 0; i < cant; i++){
            AgendaMedico agenda = _repoAgendaMedico.leer(i);
            Fecha fechaAgenda = agenda.getFecha();
            if(agenda.getEstado() == true && agenda.getDisponible() == true && fechaAgenda.getDia() == fechaBuscada.getDia() && fechaAgenda.getMes() == fechaBuscada.getMes() && fechaAgenda.getAnio() == fechaBuscada.getAnio()){
                agenda.mostrar();
                cout << "-----------------------------" << endl;
                encontrado = true;
            }
        }
        if(!encontrado){
            cout << "No existen horarios disponibles para esa fecha." << endl;
        }
    }


    void ManagerAgendaMedico::consultarPorEspecialidad()
{
    char nombreEspecialidad[50];
    bool encontrado = false;

    cout << "Ingrese el nombre de la especialidad: ";
    cin.getline(nombreEspecialidad, 50);

    int posEspecialidad = _repoEspecialidad.buscarPorNombre(nombreEspecialidad);

    if(posEspecialidad == -1)
    {
        cout << "La especialidad no existe." << endl;
        return;
    }

    Especialidad esp = _repoEspecialidad.leer(posEspecialidad);

    int cantAgenda = _repoAgendaMedico.getCantidadRegistros();

    for(int i = 0; i < cantAgenda; i++)
    {
        AgendaMedico agenda = _repoAgendaMedico.leer(i);

        if(agenda.getEstado() && agenda.getDisponible())
        {
            int posMedico = _repoMedico.buscarPosicion(agenda.getIdMedico());

            if(posMedico >= 0)
            {
                Medico medico = _repoMedico.leer(posMedico);

                if(medico.getIdEspecialidad() == esp.getIdEspecialidad())
                {
                    medico.mostrar();
                    agenda.mostrar();
                    cout << "-----------------------------" << endl;
                    encontrado = true;
                }
            }
        }
    }

    if(!encontrado)
    {
        cout << "No hay medicos disponibles para esa especialidad." << endl;
    }
}
    
