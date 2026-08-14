#include <iostream>
#include "ManagerTurno.h"
#include "../entidades/auxiliares/Fecha.h"
#include "../entidades/auxiliares/Hora.h"
#include "../persistencia/ArchivoPaciente.h"
#include "../persistencia/ArchivoMedico.h"
#include "../persistencia/ArchivoPago.h"
#include "../persistencia/ArchivoObraSocial.h"
#include "../persistencia/ArchivoEspecialidad.h"
#include "../persistencia/ArchivoAgendaMedico.h"
#include <cstring>
#include <ctime>
#include "../funciones/validaciones.h"

using namespace std;

//CONSTRUCTOR.
    ManagerTurno::ManagerTurno(){}

//METODOS.
    void ManagerTurno::agregar(){ //NOTA: Este metodo no se usa
        bool repetirTodo;
        do {
            system("cls");
            Turno reg;
            bool esValido;
            cout << "---INGRESAR DATOS DE TURNO---" << endl;
            do {
                esValido = false;
                int nuevoId = _repoTurno.getNuevoId();
                if(!reg.setIdTurno(nuevoId)){
                    cout << "\nERROR: No se pudo asignar el ID automatico generado..." << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                } else {
                    esValido = true;
                }
            } while(!esValido);
            do {
                esValido = false;
                cout << "Ingrese DNI del Paciente: ";
                char auxDniPaciente[20];
                cin >> auxDniPaciente;
                cin.ignore();
                int posPac = _repoPaciente.buscarPorDni(auxDniPaciente);
                if(posPac == -1){
                    cout << "\nEL PACIENTE NO EXISTE EN EL SISTEMA" << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                } else {
                    Paciente pac = _repoPaciente.leer(posPac);
                    int idPacienteReal = pac.getIdPaciente(); 
                    if(!pac.getEstado()){
                        cout << "\nEL PACIENTE SE ENCUENTRA DADO DE BAJA EN EL SISTEMA" << endl;
                        if(!repetirIngreso()){
                            return;
                        }
                    }
                    else if(!reg.setIdPaciente(idPacienteReal)){
                        cout << "\nERROR: El ID de Paciente recuperado es invalido..." << endl;
                        if(!repetirIngreso()){
                            return;
                        }
                    } else {
                        cout << "Paciente seleccionado: " << pac.getNombre() << " (ID: " << idPacienteReal << ")" << endl;
                        esValido = true;
                    }
                }
            } while(!esValido);
            Fecha auxFecha;
            do {
                esValido = false;
                cout << "\n---Ingrese la fecha deseada para el turno---" << endl;
                if(!auxFecha.agregar()){
                    cout << "\nERROR: La fecha ingresada es invalida." << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                } else {
                    esValido = true;
                }
            } while(!esValido);
            int cantidadAgendasEncontradas = 0;
            int cantAgendas = _repoAgendaMedico.getCantidadRegistros();
            cout << "\n--- AGENDAS DISPONIBLES PARA LA FECHA: ";
            auxFecha.mostrar();
            cout << " ---" << endl;
            for (int i = 0; i < cantAgendas; i++) {
                AgendaMedico agenda = _repoAgendaMedico.leer(i);
                if (agenda.getEstado() && agenda.getDisponible() && agenda.getFecha().getDia() == auxFecha.getDia() && agenda.getFecha().getMes() && auxFecha.getMes() && agenda.getFecha().getAnio() == auxFecha.getAnio()){
                    cout << "ID Agenda: " << agenda.getIdAgendaMedico() << " | Hora: ";
                    agenda.getHora().mostrar();
                    cout << " | ID Medico: " << agenda.getIdMedico() << endl;
                    cantidadAgendasEncontradas++;
                }
            }
            if (cantidadAgendasEncontradas == 0) {
                cout << "\nNo hay agendas disponibles para la fecha seleccionada." << endl;
                system("pause");
                repetirTodo = repetirAgregar();
                continue;
            }
            AgendaMedico agendaSeleccionada;
            int posAgenda = -1;
            do {
                esValido = false;
                cout << "\nSeleccione el ID de la Agenda Medica deseada: ";
                int auxIdAgenda;
                cin >> auxIdAgenda;
                cin.ignore();

                posAgenda = _repoAgendaMedico.buscarPosicion(auxIdAgenda);
                if (posAgenda == -1) {
                    cout << "\nEL ID DE AGENDA NO EXISTE" << endl;
                    if (!repetirIngreso()) return;
                } else {
                    agendaSeleccionada = _repoAgendaMedico.leer(posAgenda);
                    if (!agendaSeleccionada.getDisponible() || 
                        !(agendaSeleccionada.getFecha().getDia() == auxFecha.getDia() &&
                        agendaSeleccionada.getFecha().getMes() == auxFecha.getMes() &&
                        agendaSeleccionada.getFecha().getAnio() == auxFecha.getAnio())) {
                        cout << "\nLa agenda seleccionada no esta disponible o no corresponde a la fecha elegida." << endl;
                        if (!repetirIngreso()) return;
                    } else {
                        reg.setIdAgendaMedico(auxIdAgenda);
                        reg.setFecha(agendaSeleccionada.getFecha());
                        reg.setHora(agendaSeleccionada.getHora());
                        esValido = true;
                    }
                }
            } while (!esValido);
            reg.setEstado(true);
            do {
                esValido = false;
                if(_repoTurno.guardar(reg)){
                    agendaSeleccionada.setDisponible(false);
                    if(_repoAgendaMedico.guardar(agendaSeleccionada, posAgenda)){
                        cout << "\nTURNO guardado y Agenda reservada correctamente!" << endl;
                    } else {
                        cout << "\nTURNO guardado, pero error al actualizar la disponibilidad de la Agenda..." << endl;
                    }
                    esValido = true;
                } else {
                    cout << "\nERROR: No se pudo guardar el turno en el disco..." << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                }
            } while(!esValido);
            repetirTodo = repetirAgregar();
        } while(repetirTodo);
    }

    bool ManagerTurno::cargarDatosComunesTurno(Turno& reg){
        bool esValido;
        Fecha auxFecha;
        do {
            esValido = false;
            int d, m, a;
            cout << "\n--- Ingrese la fecha deseada para el turno ---" << endl;
            cout << "Dia: "; cin >> d;
            cout << "Mes: "; cin >> m;
            cout << "Anio: "; cin >> a;
            cin.ignore();
            if(!validarFecha(d, m, a)){
                cout << "\nERROR: La fecha ingresada es invalida." << endl;
                if (!repetirIngreso()) {
                    return false;
                }
            } else {
                auxFecha.setDia(d);
                auxFecha.setMes(m);
                auxFecha.setAnio(a);
                esValido = true;
            }
        } while(!esValido);
        int cantidadAgendasEncontradas = 0;
        int cantAgendas = _repoAgendaMedico.getCantidadRegistros();
        cout << "\n--- AGENDAS DISPONIBLES PARA LA FECHA: ";
        auxFecha.mostrar(); 
        cout << " ---" << endl;
        for(int i = 0; i < cantAgendas; i++){
            AgendaMedico agenda = _repoAgendaMedico.leer(i);
            if(agenda.getEstado() && agenda.getDisponible() && agenda.getFecha().getDia() == auxFecha.getDia() && agenda.getFecha().getMes() == auxFecha.getMes() && agenda.getFecha().getAnio() == auxFecha.getAnio()){
                cout << "ID Agenda: " << agenda.getIdAgendaMedico() << " | Hora: ";
                agenda.getHora().mostrar();
                cout << " | ID Medico: " << agenda.getIdMedico() << endl;
                cantidadAgendasEncontradas++;
            }
        }
        if(cantidadAgendasEncontradas == 0){
            cout << "\nNo hay agendas disponibles para la fecha seleccionada." << endl;
            system("pause");
            return false; 
        }
        do {
            esValido = false;
            cout << "\nIngrese ID de Agenda Medico deseada del listado: ";
            int auxIdAgenda;
            cin >> auxIdAgenda;
            cin.ignore();
            int posAgenda = _repoAgendaMedico.buscarPosicion(auxIdAgenda);
            if(posAgenda == -1){
                cout << "\nLA AGENDA MEDICA NO EXISTE EN EL SISTEMA" << endl;
                if (!repetirIngreso()) {
                    return false;
                }
            } else {
                AgendaMedico agenda = _repoAgendaMedico.leer(posAgenda);
                bool coincideFecha = (agenda.getFecha().getDia() == auxFecha.getDia() && agenda.getFecha().getMes() == auxFecha.getMes() && agenda.getFecha().getAnio() == auxFecha.getAnio());
                if(!agenda.getEstado()){
                    cout << "\nLA AGENDA SELECCIONADA NO ESTA ACTIVA EN EL SISTEMA" << endl;
                    if(!repetirIngreso()){
                        return false;
                    }
                } else if(!agenda.getDisponible()){
                    cout << "\nLA AGENDA SELECCIONADA YA NO ESTA DISPONIBLE (YA FUE RESERVADA)" << endl;
                    if(!repetirIngreso()){
                        return false;
                    }
                } else if(!coincideFecha){
                    cout << "\nERROR: La agenda seleccionada no corresponde a la fecha que ingresaste originalmente." << endl;
                    if(!repetirIngreso()){
                        return false;
                    }
                } else {
                    reg.setIdAgendaMedico(auxIdAgenda);
                    reg.setFecha(agenda.getFecha());
                    reg.setHora(agenda.getHora());
                    esValido = true;
                }
            }
        } while(!esValido);
        return true;
    }

    void ManagerTurno::solicitarTurno(int idPaciente){
        system("cls");
        Turno reg;
        cout << "---SOLICITAR TURNO---" << endl;
        reg.setIdTurno(_repoTurno.getNuevoId());
        reg.setIdPaciente(idPaciente);
        if(cargarDatosComunesTurno(reg)){
            reg.setEstado(true);
            if(_repoTurno.guardar(reg)){
                if (_managerPago.agregarPagoDeTurno(reg.getIdTurno(), reg.getFecha())){
                    int idAgenda = reg.getIdAgendaMedico();
                    int posAgenda = _repoAgendaMedico.buscarPosicion(idAgenda);
                    if(posAgenda != -1){
                        AgendaMedico agenda = _repoAgendaMedico.leer(posAgenda);
                        agenda.setDisponible(false);
                        if(_repoAgendaMedico.guardar(agenda, posAgenda)){
                            cout << "\nSu turno ha sido solicitado y abonado con exito!" << endl;
                        } else {
                            cout << "\nTurno solicitado y abonado, pero hubo un error al actualizar la disponibilidad de la agenda." << endl;
                        }
                    } else {
                        cout << "\nSu turno ha sido solicitado y abonado con exito! (No se encontro la agenda para actualizar disponibilidad)." << endl;
                    }
                } else {
                    int posTurno = _repoTurno.buscarPosicion(reg.getIdTurno());
                    if (posTurno != -1) {
                        _repoTurno.bajaLogica(posTurno); 
                    }
                    cout << "\nOperacion cancelada. No se registro el turno al no concretarse el pago." << endl;
                }
            } else {
                cout << "\nERROR: No se pudo guardar el turno en el disco..." << endl;
            }
        }
        system("pause");
    }

    void ManagerTurno::asignarTurno(){
        bool repetirTodo;
        do {
            system("cls");
            Turno reg;
            bool esValido;
            cout << "---ASIGNAR TURNO---" << endl;
            reg.setIdTurno(_repoTurno.getNuevoId());
            do {
                esValido = false;
                char auxDni[12];
                cout << "Ingrese DNI del Paciente: ";
                cin.getline(auxDni, 12);
                int posPac = _repoPaciente.buscarPorDni(auxDni);
                if(posPac == -1){
                    cout << "\nEL PACIENTE NO EXISTE EN EL SISTEMA" << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                } else {
                    Paciente pac = _repoPaciente.leer(posPac);
                    if (!pac.getEstado()) {
                        cout << "\nERROR: El paciente se encuentra inactivo en el sistema." << endl;
                        if(!repetirIngreso()){
                            return;
                        }
                    } else {
                        reg.setIdPaciente(pac.getIdPaciente());
                        cout << "Paciente seleccionado: " << pac.getNombre() << endl;
                        esValido = true;
                    }
                }
            } while (!esValido);
            if (cargarDatosComunesTurno(reg)) {
                reg.setEstado(true);
                if (_repoTurno.guardar(reg)) {
                    if (_managerPago.agregarPagoDeTurno(reg.getIdTurno(), reg.getFecha())) {
                        cout << "\nTurno asignado, guardado y abonado correctamente!" << endl;
                    } else {
                        int posTurno = _repoTurno.buscarPosicion(reg.getIdTurno());
                        if (posTurno != -1) {
                            _repoTurno.bajaLogica(posTurno);
                        }
                        cout << "\nAsignacion cancelada. Se removio el turno al no registrarse el pago." << endl;
                    }
                } else {
                    cout << "\nERROR: No se pudo guardar el turno en el disco..." << endl;
                }
            } else {
                cout << "\nOperacion cancelada por el usuario." << endl;
                return;
            }
            repetirTodo = repetirAgregar();
        } while (repetirTodo);
    }

    void ManagerTurno::modificar(){
        bool repetirTodo;
        do {
            system("cls");
            bool esValido;
            repetirTodo = false;
            cout << "--- MODIFICAR DATOS DE TURNO ---" << endl;
            cout << "Ingrese ID del turno a modificar: ";
            int idTurno;
            cin >> idTurno;
            cin.ignore();
            int pos = _repoTurno.buscarPosicion(idTurno);
            if(pos == -1){
                cout << "\nNO EXISTE EL TURNO EN EL SISTEMA" << endl;
                if(!repetirIngreso()){
                    return;
                }
                repetirTodo = true;
            } else {
                system("cls");
                Turno reg = _repoTurno.leer(pos);
                cout << "\n--- DATOS ACTUALES DEL TURNO ---" << endl;
                cout << "ID Paciente: " << reg.getIdPaciente() << endl;
                cout << "ID Agenda Medico: " << reg.getIdAgendaMedico() << endl;
                cout << "Fecha: "; reg.getFecha().mostrar(); cout << endl;
                cout << "Hora: "; reg.getHora().mostrar(); cout << endl;
                cout << "Estado actual: " << (reg.getEstado() ? "Activo" : "Dado de baja") << endl;
                cout << "-----------------------------------" << endl;
                cout << "\nQue dato desea modificar?" << endl;
                cout << "1. Paciente asociado" << endl;
                cout << "2. Agenda de Medico asociada" << endl;
                cout << "3. Fecha del turno" << endl;
                cout << "4. Hora del turno" << endl;
                if (reg.getEstado()) {
                    cout << "5. Dar de BAJA (Baja Logica)" << endl;
                } else {
                    cout << "5. Dar de ALTA (Alta Logica)" << endl;
                }
                cout << "0. Cancelar operacion" << endl;
                cout << "Seleccione una opcion: ";
                int opcion;
                cin >> opcion;
                cin.ignore();
                int idPacienteTemporal = reg.getIdPaciente();
                int idAgendaMedicoTemporal = reg.getIdAgendaMedico();
                Fecha fechaTemporal = reg.getFecha();
                Hora horaTemporal = reg.getHora();
                bool estadoTemporal = reg.getEstado();
                switch(opcion){
                    case 1: {
                        if(!reg.getEstado()){
                            cout << "\nERROR: No se pueden modificar los datos de un turno dado de baja." << endl;
                            if(!repetirIngreso()){
                                return;
                            }
                            repetirTodo = true;
                            break;
                        }
                        do {
                            esValido = false;
                            cout << "\nID Paciente actual: " << reg.getIdPaciente() << endl;
                            cout << "Ingrese nuevo ID Paciente: ";
                            int auxIdPaciente;
                            cin >> auxIdPaciente;
                            cin.ignore();
                            int posPac = _repoPaciente.buscarPosicion(auxIdPaciente);
                            if(posPac == -1){
                                cout << "\nEL PACIENTE NO EXISTE EN EL SISTEMA" << endl;
                                if(!repetirIngreso()){
                                    return;
                                }
                            } else {
                                // Se valida externamente la lógica del idPaciente si existiera, o se asigna directo tras verificar existencia.
                                idPacienteTemporal = auxIdPaciente;
                                esValido = true;
                            }
                        } while(!esValido);
                        break;
                    }
                    case 2: {
                        if(!reg.getEstado()){
                            cout << "\nERROR: No se pueden modificar los datos de un turno dado de baja." << endl;
                            if(!repetirIngreso()){
                                return;
                            }
                            repetirTodo = true;
                            break;
                        }
                        do {
                            esValido = false;
                            cout << "\nID Agenda Medico actual: " << reg.getIdAgendaMedico() << endl;
                            cout << "Ingrese nuevo ID Agenda Medico: ";
                            int auxIdMedico;
                            cin >> auxIdMedico;
                            cin.ignore();
                            int posMed = _repoMedico.buscarPosicion(auxIdMedico);
                            if(posMed == -1){
                                cout << "\nEL MEDICO NO EXISTE EN EL SISTEMA" << endl;
                                if(!repetirIngreso()){
                                    return;
                                }
                            } else {
                                idAgendaMedicoTemporal = auxIdMedico;
                                esValido = true;
                            }
                        } while(!esValido);
                        break;
                    }
                    case 3: {
                        if(!reg.getEstado()){
                            cout << "\nERROR: No se pueden modificar los datos de un turno dado de baja." << endl;
                            if(!repetirIngreso()){
                                return;
                            }
                            repetirTodo = true;
                            break;
                        }
                        do {
                            esValido = false;
                            int d, m, a;
                            cout << "\nFecha actual: "; reg.getFecha().mostrar(); cout << endl;
                            cout << "--- Ingrese nueva fecha ---" << endl;
                            cout << "Dia: "; cin >> d;
                            cout << "Mes: "; cin >> m;
                            cout << "Anio: "; cin >> a;
                            cin.ignore();

                            // Lógica estilo Especialidad: validación perimetral previa
                            if(!validarFecha(d, m, a)){
                                cout << "\nERROR: La fecha ingresada es invalida." << endl;
                                if(!repetirIngreso()){
                                    return;
                                }
                            } else {
                                Fecha auxFecha(d, m, a);
                                fechaTemporal = auxFecha;
                                esValido = true;
                            }
                        } while(!esValido);
                        break;
                    }
                    case 4: {
                        if(!reg.getEstado()){
                            cout << "\nERROR: No se pueden modificar los datos de un turno dado de baja." << endl;
                            if(!repetirIngreso()){
                                return;
                            }
                            repetirTodo = true;
                            break;
                        }
                        do {
                            esValido = false;
                            cout << "\nHora actual: "; reg.getHora().mostrar(); cout << endl;
                            cout << "--- Ingrese nueva hora ---" << endl;
                            int h, min;
                            cout << "Hora (0-23): "; cin >> h;
                            cout << "Minuto (0-59): "; cin >> min;
                            cin.ignore();

                            if(!validarHora(h, min)){
                                cout << "\nERROR: La hora ingresada es invalida." << endl;
                                if(!repetirIngreso()){
                                    return;
                                }
                            } else {
                                Hora auxHora(h, min);
                                horaTemporal = auxHora;
                                esValido = true;
                            }
                        } while(!esValido);
                        break;
                    }
                    case 5: {
                        if (reg.getEstado()) {
                            estadoTemporal = false;
                            cout << "\nEstado cambiado a: BAJA (Se aplica al guardar)" << endl;
                        } else {
                            estadoTemporal = true;
                            cout << "\nEstado cambiado a: ACTIVO (Se aplica al guardar)" << endl;
                        }
                        break;
                    }
                    case 0: {
                        cout << "\nOperacion cancelada por el usuario." << endl;
                        return;
                    }
                    default: {
                        cout << "\nOpcion incorrecta." << endl;
                        if(!repetirIngreso()){
                            return;
                        }
                        repetirTodo = true;
                        break;
                    }
                }
                if(!repetirTodo) {
                    reg.setIdPaciente(idPacienteTemporal);
                    reg.setIdAgendaMedico(idAgendaMedicoTemporal);
                    reg.setFecha(fechaTemporal);
                    reg.setHora(horaTemporal);
                    reg.setEstado(estadoTemporal);
                    do {
                        esValido = false;
                        if(_repoTurno.modificar(reg, pos)){
                            cout << "\nTURNO MODIFICADO CORRECTAMENTE" << endl;
                            esValido = true;
                        } else {
                            cout << "\nERROR AL GUARDAR LAS MODIFICACIONES" << endl;
                            if(!repetirIngreso()){
                                return;
                            }
                        }
                    } while(!esValido);
                    repetirTodo = repetirAgregar();
                }
            }
        } while(repetirTodo);
}

//LISTADOS:
    void ManagerTurno::listados(){
        bool repetirMenu;
        do {
            system("cls");
            repetirMenu = false;
            cout << "---MENU DE LISTADOS DE TURNOS---" << endl;
            cout << "1. Listar todos los turnos" << endl;
            cout << "2. Listar turnos activos" << endl;
            cout << "3. Listar turnos inactivos" << endl;
            cout << "4. Listar turnos por Fecha" << endl;
            cout << "5. Listar turnos por Hora" << endl;
            cout << "0. Volver al menu principal" << endl;
            cout << "Seleccione una opcion: ";
            int opcion;
            cin >> opcion;
            cin.ignore();
            switch(opcion){
                case 1: {
                    system("cls");
                    listar();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 2: {
                    system("cls");
                    listarActivos();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 3: {
                    system("cls");
                    listarInactivos();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 4: {
                    system("cls");
                    listarPorFecha();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 5: {
                    system("cls");
                    listarPorHora();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 0: {
                    break;
                }
                default: {
                    cout << "\nOpcion incorrecta. Intente nuevamente." << endl;
                    system("pause");
                    repetirMenu = true;
                    break;
                }
            }
        } while(repetirMenu);
    }

    void ManagerTurno::listar(){
        int cantidad = _repoTurno.getCantidadRegistros();
        bool hayTurnos = false;
        cout << "---LISTADO DE TURNOS ACTIVOS---" << endl;
        for(int i = 0; i < cantidad; i++){
            Turno reg = _repoTurno.leer(i);
            reg.mostrar();
            hayTurnos = true;
        }
        if(!hayTurnos){
            cout << endl;
            cout << "No hay TURNOS registrados en el sistema." << endl;
        }
    }

    void ManagerTurno::listarActivos(){
        int cantidad = _repoTurno.getCantidadRegistros();
        bool hayTurnos = false;
        cout << "---LISTADO DE TURNOS ACTIVOS---" << endl;
        for(int i = 0; i < cantidad; i++){
            Turno reg = _repoTurno.leer(i);
            if(reg.getEstado() == true){
                reg.mostrar();
                hayTurnos = true;
            }
        }
        if(!hayTurnos){
            cout << endl;
            cout << "No hay TURNOS activos registrados en el sistema." << endl;
        }
    }

    void ManagerTurno::listarInactivos(){
        int cantidad = _repoTurno.getCantidadRegistros();
        bool hayTurnos = false;
        cout << "---LISTADO DE TURNOS ACTIVOS---" << endl;
        for(int i = 0; i < cantidad; i++){
            Turno reg = _repoTurno.leer(i);
            if(reg.getEstado() == false){
                reg.mostrar();
                hayTurnos = true;
            }
        }
        if(!hayTurnos){
            cout << endl;
            cout << "No hay TURNOS inactivos registrados en el sistema." << endl;
        }
    }

    void ManagerTurno::listarPorFecha(){
        bool repetirTodo;
        do {
            system("cls");
            repetirTodo = false;
            bool esValido = false;
            int d, m, a;
            cout << "---LISTAR TURNOS POR FECHA---" << endl;
            do {
                cout << "Dia: "; cin >> d;
                cout << "Mes: "; cin >> m;
                cout << "Anio: "; cin >> a;
                cin.ignore();

                if(!validarFecha(d, m, a)){
                    cout << "\nERROR: La fecha ingresada es invalida." << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                } else {
                    esValido = true;
                }
            } while(!esValido);
            Fecha fechaBusqueda(d, m, a);
            int cantidad = _repoTurno.getCantidadRegistros();
            bool encontroAlguno = false;
            cout << "\n---LISTADO DE TURNOS PARA LA FECHA SELECCIONADA---" << endl;
            for(int i = 0; i < cantidad; i++){
                Turno reg = _repoTurno.leer(i);
                if(reg.getEstado() == true && reg.getFecha().getDia() == fechaBusqueda.getDia() && reg.getFecha().getMes() == fechaBusqueda.getMes() && reg.getFecha().getAnio() == fechaBusqueda.getAnio()){
                    reg.mostrar();
                    cout << "-----------------------------------" << endl;
                    encontroAlguno = true;
                }
            }
            if(!encontroAlguno){
                cout << "No se encontraron turnos programados para esa fecha." << endl;
            }
            repetirTodo = repetirIngreso();
        } while(repetirTodo);
    }

    void ManagerTurno::listarPorHora(){
        bool repetirTodo;
        do {
            system("cls");
            repetirTodo = false;
            bool esValido = false;
            int h, min;
            cout << "---LISTAR TURNOS POR HORA---" << endl;
            do {
                cout << "Hora (0-23): "; cin >> h;
                cout << "Minuto (0-59): "; cin >> min;
                cin.ignore();
                if(!validarHora(h, min)){
                    cout << "\nERROR: La hora ingresada es invalida." << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                } else {
                    esValido = true;
                }
            } while(!esValido);
            Hora horaBusqueda(h, min);
            int cantidad = _repoTurno.getCantidadRegistros();
            bool encontroAlguno = false;
            cout << "\n---LISTADO DE TURNOS PARA LA HORA SELECCIONADA---" << endl;
            for(int i = 0; i < cantidad; i++){
                Turno reg = _repoTurno.leer(i);
                if(reg.getEstado() == true &&
                    reg.getHora().getHora() == horaBusqueda.getHora() &&
                    reg.getHora().getMinuto() == horaBusqueda.getMinuto()){
                    reg.mostrar();
                    cout << "-----------------------------------" << endl;
                    encontroAlguno = true;
                }
            }
            if(!encontroAlguno){
                cout << "No se encontraron turnos programados para esa hora." << endl;
            }
            repetirTodo = repetirIngreso();
        } while(repetirTodo);
    }

    void ManagerTurno::listarMisTurnos(int idPaciente){
        system("cls");
        cout << "---MIS TURNOS AGENDADOS---" << endl;
        int cantidadRegistros = _repoTurno.getCantidadRegistros();
        if(cantidadRegistros == 0){
            cout << "No tienes turnos agendados o el archivo no existe." << endl;
            return;
        }
        Turno reg;
        int cantidadTurnosPaciente = 0;
        for (int i = 0; i < cantidadRegistros; i++){
            reg = _repoTurno.leer(i);
            if(reg.getIdPaciente() == idPaciente && reg.getEstado() == true){
                reg.mostrarMiTurno();
                cantidadTurnosPaciente++;
            }
        }
        if (cantidadTurnosPaciente == 0){
            cout << "No se encontraron turnos activos para tu usuario." << endl;
        } else {
            cout << "Total de turnos encontrados: " << cantidadTurnosPaciente << endl;
        }
        cout << endl;
    }

//CONSULTAS:
    void ManagerTurno::consultas(){
        bool repetirMenu;
        do {
            system("cls");
            repetirMenu = false;
            cout << "--- MENU DE CONSULTAS DE TURNOS ---" << endl;
            cout << "1. Consultar turno por Fecha" << endl;
            cout << "2. Consultar turno por Paciente" << endl;
            cout << "3. Consultar turno por Medico" << endl;
            cout << "0. Volver al menu principal" << endl;
            cout << "Seleccione una opcion: ";
            int opcion;
            cin >> opcion;
            cin.ignore();
            switch(opcion){
                case 1: {
                    system("cls");
                    consultarTurnoPorFecha();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 2: {
                    system("cls");
                    consultarTurnoPorPaciante();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 3: {
                    system("cls");
                    consultarTurnoPorMedico();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 0: {
                    break;
                }
                default: {
                    cout << "\nOpcion incorrecta. Intente nuevamente." << endl;
                    system("pause");
                    repetirMenu = true;
                    break;
                }
            }
        } while(repetirMenu);
    }

    void ManagerTurno::consultarTurnoPorFecha(){
        bool esValido = false;
        int d, m, a;
        cout << "---CONSULTAR TURNOS POR FECHA---" << endl;
        do {
            cout << "Dia: "; cin >> d;
            cout << "Mes: "; cin >> m;
            cout << "Anio: "; cin >> a;
            cin.ignore();

            if(!validarFecha(d, m, a)){
                cout << "\nERROR: La fecha ingresada es invalida." << endl;
                if(!repetirIngreso()){
                    return;
                }
            } else {
                esValido = true;
            }
        } while(!esValido);
        Fecha fechaBusqueda(d, m, a);
        int cantidad = _repoTurno.getCantidadRegistros();
        bool encontroAlguno = false;
        cout << "\n---LISTADO DE TURNOS PARA LA FECHA SELECCIONADA---" << endl;
        for(int i = 0; i < cantidad; i++){
            Turno reg = _repoTurno.leer(i);
            Fecha fechaTurno = reg.getFecha();
            if(reg.getEstado() == true && fechaTurno.esIgual(fechaBusqueda))
            {
                reg.mostrar();
                cout << "-----------------------------------" << endl;
                encontroAlguno = true;
            }
        }
        if(!encontroAlguno){
            cout << "No se encontraron turnos programados para esta fecha." << endl;
        }
    }

    void ManagerTurno::consultarTurnoPorPaciante(){
        char dniBusqueda[15];
        cout << "---CONSULTAR TURNOS POR PACIENTE---" << endl;
        cout << "Ingrese el DNI del paciente: ";
        cin >> dniBusqueda;
        cin.ignore();
        ArchivoPaciente repoPaciente;
        int posPaciente = repoPaciente.buscarPorDni(dniBusqueda);
        if(posPaciente == -1){
            cout << "\nERROR: El DNI ingresado no corresponde a un paciente registrado." << endl;
            return;
        }
        Paciente pac = repoPaciente.leer(posPaciente);
        int idPacienteBusqueda = pac.getIdPaciente();
        int cantidad = _repoTurno.getCantidadRegistros();
        bool encontroAlguno = false;
        cout << "\n---LISTADO DE TURNOS PARA EL PACIENTE SELECCIONADO---" << endl;
        for(int i = 0; i < cantidad; i++){
            Turno reg = _repoTurno.leer(i);
            if(reg.getEstado() == true && reg.getIdPaciente() == idPacienteBusqueda){
                reg.mostrar();
                cout << "-----------------------------------" << endl;
                encontroAlguno = true;
            }
        }
        if(!encontroAlguno){
            cout << "No se encontraron turnos programados para este paciente." << endl;
        }
    }

    void ManagerTurno::consultarTurnoPorMedico(){
        char nombreBusqueda[50];
        char apellidoBusqueda[50];
        cout << "---CONSULTAR TURNOS POR MEDICO---" << endl;
        cout << "Ingrese el nombre del medico: ";
        cin >> nombreBusqueda;
        cin.ignore();
        cout << "Ingrese el apellido del medico: ";
        cin >> apellidoBusqueda;
        cin.ignore();
        ArchivoMedico repoMedico;
        int cantidadMedicos = repoMedico.getCantidadRegistros();
        int idMedicoBusqueda = -1;
        bool encontradoMedico = false;
        for(int i = 0; i < cantidadMedicos; i++){
            Medico med = repoMedico.leer(i);
            if(med.getEstado() == true && strcmp(med.getNombre(), nombreBusqueda) == 0 && strcmp(med.getApellido(), apellidoBusqueda) == 0){
                idMedicoBusqueda = med.getIdMedico();
                encontradoMedico = true;
                break;
            }
        }
        if(!encontradoMedico){
            cout << "\nERROR: No se encontro ningun medico activo con ese nombre y apellido." << endl;
            return;
        }
        int cantidad = _repoTurno.getCantidadRegistros();
        bool encontroAlguno = false;
        cout << "\n---LISTADO DE TURNOS PARA EL MEDICO SELECCIONADO---" << endl;
        for(int i = 0; i < cantidad; i++){
            Turno reg = _repoTurno.leer(i);
            if(reg.getEstado() == true && reg.getIdAgendaMedico() == idMedicoBusqueda){
                reg.mostrar();
                cout << "-----------------------------------" << endl;
                encontroAlguno = true;
            }
        }
        if(!encontroAlguno){
            cout << "No se encontraron turnos programados para este medico." << endl;
        }
    }

//REPORTE N2

bool ManagerTurno::esAnioBisiesto(int anio){
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

void ManagerTurno::reportePromedioPacientesPorDia(){

    int anioDesde, anioHasta;

    cout << "--- PROMEDIO DE PACIENTES ATENDIDOS POR DIA ---" << endl;

    cout << "Ingrese desde que anio desea calcular el promedio de pacientes atendidos por dia: ";
    cin >> anioDesde;

    cout << "Ingrese hasta que anio calcular el promedio de pacientes atendidos por dia: ";
    cin >> anioHasta;

    if(anioDesde > anioHasta){
        cout << "ERROR: El rango de anios es invalido." << endl;
        return;
    }

    ArchivoTurno archivoTurno;

    int cantidadRegistros = archivoTurno.getCantidadRegistros();
    int cantidadTurnos = 0;

    for(int i = 0; i < cantidadRegistros; i++){

        Turno reg = archivoTurno.leer(i);

        int anioTurno = reg.getFecha().getAnio();

        if(reg.getEstado() &&
           anioTurno >= anioDesde &&
           anioTurno <= anioHasta){

            cantidadTurnos++;
        }
    }

    int totalDias = 0;

    for(int anio = anioDesde; anio <= anioHasta; anio++){

        if(esAnioBisiesto(anio)){
            totalDias += 366;
        }
        else{
            totalDias += 365;
        }
    }

    cout << endl;
    cout << "Periodo analizado: " << anioDesde << " - " << anioHasta << endl;
    cout << "Turnos considerados: " << cantidadTurnos << endl;

    if(totalDias > 0){

        float promedio = (float)cantidadTurnos / totalDias;

        cout << "Promedio de pacientes atendidos por dia: ";
        cout << promedio << endl;

    }
    else{

        cout << "No fue posible calcular el promedio." << endl;

    }
}
