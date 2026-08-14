#include <iostream>
#include "ManagerPago.h"
#include "../entidades/auxiliares/Fecha.h"
#include "../persistencia/ArchivoObraSocial.h"
#include "../persistencia/ArchivoTurno.h"
#include "../persistencia/ArchivoPaciente.h"
#include "../persistencia/ArchivoEspecialidad.h"
#include "../persistencia/ArchivoMedico.h"
#include <cstring>
#include "../funciones/validaciones.h"

using namespace std;

//CONSTRUCTOR.
    ManagerPago::ManagerPago(){}

//METODOS.
    void ManagerPago::agregar(){
        bool repetirTodo;
        do {
            system("cls");
            Pago reg;
            bool esValido;
            cout << "---INGRESAR DATOS DE PAGO---" << endl;
            int idPago = _repoPago.getNuevoId();
            reg.setIdPago(idPago);
            do {
                esValido = false;
                cout << "ID del turno: ";
                int auxIdTurno;
                cin >> auxIdTurno;
                cin.ignore();
                int posTurno = _repoTurno.buscarPosicion(auxIdTurno);
                if(posTurno == -1){
                    cout << "\nERROR: El turno ingresado no existe en el sistema o esta dado de baja..." << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                } else {
                    reg.setIdTurno(auxIdTurno); 
                    esValido = true;
                }
            } while(!esValido);
            do {
                esValido = false;
                cout << "Monto: $";
                float auxMonto;
                cin >> auxMonto;
                cin.ignore();
                if(auxMonto <= 0.0f){ 
                    cout << "\nERROR: El monto ingresado es invalido (debe ser mayor a 0)..." << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                } else {
                    reg.setMonto(auxMonto);
                    esValido = true;
                }
            } while(!esValido);
            do {
                esValido = false;
                int d, m, a;
                cout << "\n---Ingrese fecha del pago---" << endl;
                cout << "Dia: "; cin >> d;
                cout << "Mes: "; cin >> m;
                cout << "Anio: "; cin >> a;
                cin.ignore();
                if(!validarFecha(d, m, a)){
                    cout << "\nERROR: La fecha ingresada es invalida..." << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                } else {
                    Fecha fechaTemporal(d, m, a);
                    reg.setFecha(fechaTemporal);
                    esValido = true;
                }
            } while(!esValido);
            reg.setEstado(true);
            if(_repoPago.guardar(reg)){
                cout << "\nPAGO guardado correctamente!" << endl;
            } else {
                cout << "\nERROR: No se pudo guardar el pago en el disco..." << endl;
            }
            repetirTodo = repetirAgregar();
        } while(repetirTodo);
    }

    bool ManagerPago::agregarPagoDeTurno(int idTurno, Fecha fechaTurno) {
        Pago pagoReg;
        bool esValido = false;
        float montoAux;
        cout << "\n--- REGISTRAR PAGO DE TURNO ---" << endl;
        int nuevoIdPago = _repoPago.getNuevoId();
        pagoReg.setIdPago(nuevoIdPago); 
        pagoReg.setIdTurno(idTurno);              
        pagoReg.setFecha(fechaTurno);              
        pagoReg.setEstado(true); 
        do {
            cout << "Ingrese el monto a abonar para el turno: $";
            cin >> montoAux;
            cin.ignore();
            if (montoAux <= 0.0f) {
                cout << "\nERROR: El monto ingresado es invalido (debe ser mayor a 0)." << endl;
                if (!repetirIngreso()) {
                    return false;
                }
            } else {
                pagoReg.setMonto(montoAux);
                esValido = true;
            }
        } while (!esValido);
        if (_repoPago.guardar(pagoReg)) {
            cout << "¡Pago de $" << montoAux << " registrado con exito!" << endl;
            return true;
        } else {
            cout << "\nERROR: No se pudo registrar el pago en el archivo de datos..." << endl;
            return false;
        }
    }

    void ManagerPago::modificar(){
        bool repetirTodo;
        do {
            system("cls");
            bool esValido;
            repetirTodo = false;
            cout << "--- MODIFICAR DATOS DE PAGO ---" << endl;
            cout << "Ingrese ID del pago a modificar: ";
            int idPago;
            cin >> idPago;
            cin.ignore();
            int pos = _repoPago.buscarPosicion(idPago);
            if(pos == -1){
                cout << "\nNO EXISTE EL PAGO EN EL SISTEMA" << endl;
                if(!repetirIngreso()){
                    return;
                }
                repetirTodo = true;
            } else {
                system("cls");
                Pago reg = _repoPago.leer(pos);
                cout << "\n--- DATOS ACTUALES DEL PAGO ---" << endl;
                cout << "ID Turno asociado: " << reg.getIdTurno() << endl;
                cout << "Monto: $" << reg.getMonto() << endl;
                cout << "Fecha: "; reg.getFecha().mostrar(); cout << endl;
                cout << "Estado actual: " << (reg.getEstado() ? "Activo" : "Dado de baja") << endl;
                cout << "-----------------------------------" << endl;
                cout << "\nQue dato desea modificar?" << endl;
                cout << "1. Turno asociado" << endl;
                cout << "2. Monto del pago" << endl;
                cout << "3. Fecha del pago" << endl;
                if (reg.getEstado()) {
                    cout << "4. Dar de BAJA (Baja Logica)" << endl;
                } else {
                    cout << "4. Dar de ALTA (Alta Logica)" << endl;
                }
                cout << "0. Cancelar operacion" << endl;
                cout << "Seleccione una opcion: ";
                int opcion;
                cin >> opcion;
                cin.ignore();
                int idTurnoTemporal = reg.getIdTurno();
                float montoTemporal = reg.getMonto();
                Fecha fechaTemporal = reg.getFecha();
                bool estadoTemporal = reg.getEstado();
                switch(opcion){
                    case 1: {
                        if(!reg.getEstado()){
                            cout << "\nERROR: No se pueden modificar los datos de un pago dado de baja." << endl;
                            if(!repetirIngreso()){
                                return;
                            }
                            repetirTodo = true;
                            break;
                        }
                        do {
                            esValido = false;
                            cout << "\nID Turno actual: " << reg.getIdTurno() << endl;
                            cout << "Ingrese nuevo ID Turno: ";
                            int auxIdTurno;
                            cin >> auxIdTurno;
                            cin.ignore();
                            int posTurno = _repoTurno.buscarPosicion(auxIdTurno);
                            if(posTurno == -1){
                                cout << "\nEL NUEVO TURNO NO EXISTE EN EL SISTEMA" << endl;
                                if(!repetirIngreso()){
                                    return;
                                }
                            } else {
                                // Primero validamos la lógica, si está ok, guardamos en la temporal
                                idTurnoTemporal = auxIdTurno;
                                esValido = true;
                            }
                        } while(!esValido);
                        break;
                    }
                    case 2: {
                        if(!reg.getEstado()){
                            cout << "\nERROR: No se pueden modificar los datos de un pago dado de baja." << endl;
                            if(!repetirIngreso()){
                                return;
                            }
                            repetirTodo = true;
                            break;
                        }
                        do {
                            esValido = false;
                            cout << "\nMonto actual: $" << reg.getMonto() << endl;
                            cout << "Ingrese nuevo Monto: ";
                            float auxMonto;
                            cin >> auxMonto;
                            cin.ignore();
                            
                            // Validación externa de la lógica del negocio
                            if(auxMonto <= 0){
                                cout << "\nERROR: El monto ingresado es invalido..." << endl;
                                if(!repetirIngreso()){
                                    return;
                                }
                            } else {
                                montoTemporal = auxMonto;
                                esValido = true;
                            }
                        } while(!esValido);
                        break;
                    }
                    case 3: {
                        if(!reg.getEstado()){
                            cout << "\nERROR: No se pueden modificar los datos de un pago dado de baja." << endl;
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
                            
                            // Lógica defensiva como Especialidad: validar primero por fuera
                            if(!validarFecha(d, m, a)){
                                cout << "\nERROR: La fecha ingresada es invalida." << endl;
                                if(!repetirIngreso()){
                                    return;
                                }
                            } else {
                                // Si es válida, construimos el objeto y asignamos a la temporal
                                Fecha auxFecha(d, m, a);
                                fechaTemporal = auxFecha;
                                esValido = true;
                            }
                        } while(!esValido);
                        break;
                    }
                    case 4: {
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
                    reg.setIdTurno(idTurnoTemporal);
                    reg.setMonto(montoTemporal);
                    reg.setFecha(fechaTemporal);
                    reg.setEstado(estadoTemporal);
                    do {
                        esValido = false;
                        if(_repoPago.modificar(reg, pos)){
                            cout << "\nPAGO MODIFICADO CORRECTAMENTE" << endl;
                            esValido = true;
                        } 
                        else {
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

//LISTADO:
    void ManagerPago::listados(){
        bool repetirMenu;
        do {
            system("cls");
            repetirMenu = false;
            cout << "--------------------------------" << endl;
            cout << "---MENU DE LISTADOS DE PAGOS---" << endl;
            cout << "--------------------------------" << endl;
            cout << "1. Listar todos los pagos" << endl;
            cout << "2. Listar pagos activos" << endl;
            cout << "3. Listar pagos inactivos" << endl;
            cout << "--------------------------------" << endl;
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

    void ManagerPago::listar(){
        int cantidad = _repoPago.getCantidadRegistros();
        bool hayPagos = false;
        cout << "---LISTADO DE PAGOS---" << endl;
        for(int i = 0; i < cantidad; i++){
            Pago reg = _repoPago.leer(i);
                reg.mostrar();
                hayPagos = true;
        }
        if(!hayPagos){
            cout << endl;
            cout << "No hay PAGOS registrados en el sistema." << endl;
        }
    }

    void ManagerPago::listarActivos(){
        int cantidad = _repoPago.getCantidadRegistros();
        bool hayPagos = false;
        cout << "---LISTADO DE PAGOS ACTIVOS---" << endl;
        for(int i = 0; i < cantidad; i++){
            Pago reg = _repoPago.leer(i);
            if(reg.getEstado() == true){
                reg.mostrar();
                hayPagos = true;
            }
        }
        if(!hayPagos){
            cout << endl;
            cout << "No hay PAGOS activos registrados en el sistema." << endl;
        }
    }

    void ManagerPago::listarInactivos(){
        int cantidad = _repoPago.getCantidadRegistros();
        bool hayPagos = false;
        cout << "---LISTADO DE PAGOS INACTIVOS---" << endl;
        for(int i = 0; i < cantidad; i++){
            Pago reg = _repoPago.leer(i);
            if(reg.getEstado() == false){
                reg.mostrar();
                hayPagos = true;
            }
        }
        if(!hayPagos){
            cout << endl;
            cout << "No hay PAGOS inactivos registrados en el sistema." << endl;
        }
    }

//CONSULTAS:
    void ManagerPago::consultas(){
        bool repetirMenu;
        do {
            system("cls");
            repetirMenu = false;
            cout << "--- MENU DE CONSULTAS DE PAGOS ---" << endl;
            cout << "1. Consultar pago por rango de fechas" << endl;
            cout << "2. Consultar pago por Obra Social" << endl;
            cout << "3. Consultar pago por Especialidad" << endl;
            cout << "0. Volver al menu principal" << endl;
            cout << "Seleccione una opcion: ";
            int opcion;
            cin >> opcion;
            cin.ignore();
            switch(opcion){
                case 1: {
                    system("cls");
                    consultarPagoPorRangoDeFechas();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 2: {
                    system("cls");
                    consultarPagoPorObraSocial();
                    system("pause");
                    repetirMenu = true;
                    break;
                }
                case 3: {
                    system("cls");
                    consultarPagoPorEspecialidad();
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

    void ManagerPago::consultarPagoPorRangoDeFechas(){
    bool repetirConsulta;
    do {
        system("cls");
        repetirConsulta = false;
        bool esValido;
        int d, m, a;
        cout << "---CONSULTAR PAGOS POR RANGO DE FECHAS---" << endl;
        do {
            esValido = false;
            cout << "\nIngrese la FECHA INICIAL:" << endl;
            cout << "Dia: "; cin >> d;
            cout << "Mes: "; cin >> m;
            cout << "Anio: "; cin >> a;
            cin.ignore();
            if (!validarFecha(d, m, a)) {
                cout << "\nERROR: La fecha inicial ingresada es invalida." << endl;
                if (!repetirIngreso()){
                    return;
                }
            } else {
                esValido = true;
            }
        } while (!esValido);
        Fecha fechaDesde(d, m, a);
        do {
            esValido = false;
            cout << "\nIngrese la FECHA FINAL:" << endl;
            cout << "Dia: "; cin >> d;
            cout << "Mes: "; cin >> m;
            cout << "Anioe: "; cin >> a;
            cin.ignore();
            if (!validarFecha(d, m, a)) {
                cout << "\nERROR: La fecha final ingresada es invalida." << endl;
                if (!repetirIngreso()){
                    return;
                }
            } else {
                esValido = true;
            }
        } while (!esValido);
        Fecha fechaHasta(d, m, a);

        int cantidad = _repoPago.getCantidadRegistros();
        bool encontroAlguno = false;
        float totalRecaudado = 0.0;

        cout << "\n---LISTADO DE PAGOS EN EL RANGO SELECCIONADO---" << endl;
        for(int i = 0; i < cantidad; i++){
            Pago reg = _repoPago.leer(i);
            Fecha fPago = reg.getFecha();
            if(reg.getEstado() == true && fPago.fechaEsMayorOIgual(fechaDesde) && fPago.fechaEsMenorOIgual(fechaHasta)){
                reg.mostrar();
                cout << "-----------------------------------" << endl;
                totalRecaudado += reg.getMonto();
                encontroAlguno = true;
            }
        }
        if(!encontroAlguno){
            cout << "No se encontraron pagos registrados en ese rango de fechas." << endl;
        } else {
            cout << "TOTAL RECAUDADO EN EL RANGO: $" << totalRecaudado << endl;
        }
        repetirConsulta = repetirConsultaMenu("rango de fechas");
    } while(repetirConsulta);
}

    void ManagerPago::consultarPagoPorObraSocial(){
        bool repetirConsulta;
        do {
            system("cls");
            repetirConsulta = false;
            char nombreOSBusqueda[50];
            cout << "---CONSULTAR PAGOS POR OBRA SOCIAL---" << endl;
            cout << "Ingrese el nombre de la Obra Social: ";
            cin.getline(nombreOSBusqueda, 50);
            ArchivoObraSocial _repoObraSocal;
            int cantOS = _repoObraSocial.getCantidadRegistros();
            int idOSBusqueda = -1;

            for(int i = 0; i < cantOS; i++){
                ObraSocial os = _repoObraSocal.leer(i);
                if(os.getEstado() == true && strcmp(os.getNombre(), nombreOSBusqueda) == 0){
                    idOSBusqueda = os.getIdObraSocial();
                    break;
                }
            }
            if(idOSBusqueda == -1){
                cout << "\nERROR: No se encontro la Obra Social ingresada o esta inactiva." << endl;
            } 
            else {
                int cantidadPagos = _repoPago.getCantidadRegistros();
                ArchivoTurno _repoTurno;
                ArchivoPaciente _repoPaciente;
                bool encontroAlguno = false;
                cout << "\n---LISTADO DE PAGOS PARA LA OBRA SOCIAL SELECCIONADA---" << endl;
                for(int i = 0; i < cantidadPagos; i++){
                    Pago regPago = _repoPago.leer(i);
                    if(regPago.getEstado() == true){
                        int posTurno = _repoTurno.buscarPosicion(regPago.getIdTurno());
                        if(posTurno != -1){
                            Turno regTurno = _repoTurno.leer(posTurno);
                            int posPac = _repoPaciente.buscarPosicion(regTurno.getIdPaciente());
                            if(posPac != -1){
                                Paciente regPac = _repoPaciente.leer(posPac);
                                if(regPac.getIdObraSocial() == idOSBusqueda){
                                    regPago.mostrar();
                                    cout << "-----------------------------------" << endl;
                                    encontroAlguno = true;
                                }
                            }
                        }
                    }
                }
                if(!encontroAlguno){
                    cout << "No se registraron pagos de pacientes con esa Obra Social." << endl;
                }
            }
            repetirConsulta = repetirConsultaMenu("Obra Social");
        } while(repetirConsulta);
    }

    void ManagerPago::consultarPagoPorEspecialidad(){
        bool repetirConsulta;
        do {
            system("cls");
            repetirConsulta = false;
            char nombreEspecialidadBusqueda[50];
            cout << "---CONSULTAR PAGOS POR ESPECIALIDAD---" << endl;
            cout << "Ingrese el nombre de la Especialidad: ";
            cin.getline(nombreEspecialidadBusqueda, 50);
            ArchivoEspecialidad _repoEspecialidad;
            int cantEsp = _repoEspecialidad.getCantidadRegistros();
            int idEspecialidadBusqueda = -1;
            for(int i = 0; i < cantEsp; i++){
                Especialidad esp = _repoEspecialidad.leer(i);
                if(esp.getEstado() == true && strcmp(esp.getNombre(), nombreEspecialidadBusqueda) == 0){
                    idEspecialidadBusqueda = esp.getIdEspecialidad();
                    break;
                }
            }
            if(idEspecialidadBusqueda == -1){
                cout << "\nERROR: No se encontro la Especialidad ingresada o esta inactiva." << endl;
            } else {
                int cantidadPagos = _repoPago.getCantidadRegistros();
                ArchivoTurno _repoTurno;
                ArchivoMedico _repoMedico;
                bool encontroAlguno = false;
                cout << "\n---LISTADO DE PAGOS PARA LA ESPECIALIDAD SELECCIONADA---" << endl;
                for(int i = 0; i < cantidadPagos; i++){
                    Pago regPago = _repoPago.leer(i);
                    if(regPago.getEstado() == true){
                        int posTurno = _repoTurno.buscarPosicion(regPago.getIdTurno());
                        if(posTurno != -1){
                            Turno regTurno = _repoTurno.leer(posTurno);
                            int posMed = _repoMedico.buscarPosicion(regTurno.getIdAgendaMedico());
                            if(posMed != -1){
                                Medico regMed = _repoMedico.leer(posMed);
                                if(regMed.getIdEspecialidad() == idEspecialidadBusqueda){
                                    regPago.mostrar();
                                    cout << "-----------------------------------" << endl;
                                    encontroAlguno = true;
                                }
                            }
                        }
                    }
                }
                if(!encontroAlguno){
                    cout << "No se registraron pagos para turnos de esa Especialidad." << endl;
                }
            }
            repetirConsulta = repetirConsultaMenu("Especialidad");
        } while(repetirConsulta);
    }

//REPORTE N1

void ManagerPago::reporteEspecialidadMayorRecaudacion()
{
    int anioDesde, anioHasta;
    int cantPagos = _repoPago.getCantidadRegistros();
    int cantTurnos = _repoTurno.getCantidadRegistros();
    int cantAgendaMedico = _repoAgendaMedico.getCantidadRegistros();
    int cantMedico = _repoMedico.getCantidadRegistros();
    int cantEspecialidad = _repoEspecialidad.getCantidadRegistros();

    cout << "Ingrese anio desde: " << endl;
    cin >> anioDesde;
    cout << "Ingrese anio hasta: " << endl;
    cin >> anioHasta;

    float *recaudacion = new float[cantEspecialidad];
    for(int i=0; i<cantEspecialidad; i++)
    {
        recaudacion[i] = 0;
    }


    for(int i=0; i<cantPagos; i++)
    {
        Pago p = _repoPago.leer(i);
        if(p.getFecha().getAnio() >= anioDesde && p.getFecha().getAnio() <= anioHasta)
        {
            for(int x=0; x<cantTurnos; x++)
            {
                Turno t = _repoTurno.leer(x);
                if(p.getIdTurno() == t.getIdTurno())
                {
                    for(int j=0; j<cantAgendaMedico; j++)
                    {
                        AgendaMedico am = _repoAgendaMedico.leer(j);
                        if(t.getIdAgendaMedico() == am.getIdAgendaMedico())
                        {
                            for(int k=0; k<cantMedico; k++)
                            {
                                Medico med = _repoMedico.leer(k);
                                if(am.getIdMedico() == med.getIdMedico())
                                {
                                    for(int z=0; z<cantEspecialidad; z++)
                                    {
                                        Especialidad esp = _repoEspecialidad.leer(z);
                                        if(med.getIdEspecialidad() == esp.getIdEspecialidad())
                                        {
                                            recaudacion[z]+=p.getMonto();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    float mayor = 0;
    int posMayor = 0;

    for(int i = 0; i < cantEspecialidad; i++)
    {
        if(recaudacion[i] > mayor)
        {
            mayor = recaudacion[i];
            posMayor = i;
        }
    }
    Especialidad espMayor = _repoEspecialidad.leer(posMayor);
    
    cout << "-- ESPECIALIDAD CON MAYOR RECAUDACION --" << endl;
    cout << "Especialidad: " << espMayor.getNombre() << endl;
    cout << "Recaudacion total: $" << mayor << endl;
    cout << "Periodo: " << anioDesde << " - " << anioHasta << endl;
    
    delete[] recaudacion;
}