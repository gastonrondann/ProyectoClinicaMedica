#include <iostream>
#include "ManagerUsuario.h"
#include <cstring>
#include <limits>
#include "../funciones/validaciones.h"
#include "../entidades/Paciente.h"
#include "../entidades/Medico.h"

using namespace std;

//CONSTRUCTOR:
    ManagerUsuario::ManagerUsuario(){}

//METODOS:
    void ManagerUsuario::registrarUsuario(){
        bool repetirTodo;
        do {
            system("cls");
            char nombreRol[50];
            int posRol;
            Rol rol;
            bool esValido;
            bool registroExitoso = false;
            cout << "---REGISTRAR NUEVO USUARIO---" << endl;
            do {
                esValido = false;
                cout << "Nombre del rol: ";
                cin.getline(nombreRol, 50);
                posRol = _repoRol.buscarPorNombre(nombreRol);
                if(posRol == -1){
                    cout << "\nEL ROL NO EXISTE EN EL SISTEMA" << endl;
                    cout << "\nLISTADO DE ROLES ACTIVOS:" << endl;
                    _managerRol.listar();
                    cout << endl;
                    if(!repetirIngreso()){
                        return;
                    }
                } else {
                    rol = _repoRol.leer(posRol);
                    esValido = true;
                }
            } while(!esValido);
            switch(rol.getIdRol()){
                case 1: // Paciente
                    registroExitoso = agregarUsuarioPaciente(rol.getIdRol());
                    break;
                case 2: // Medico
                    registroExitoso = agregarUsuarioMedico(rol.getIdRol());
                    break;
                case 3: // Administrador
                    registroExitoso = agregarUsuarioAdministrador(rol.getIdRol());
                    break;
                default:
                    cout << "\nERROR: No se puede registrar un usuario con el rol seleccionado...." << endl;
                    system("pause");
                    break;
            }
            if (registroExitoso) {
                repetirTodo = repetirRegistrar();
            } else {
                repetirTodo = false;
            }
        } while(repetirTodo);
    }

    bool ManagerUsuario::agregarUsuarioPaciente(int idRol){
        system("cls");
        cout << "---REGISTRO DE USUARIO PACIENTE---" << endl;
        Usuario regUsuario;
        Paciente regPaciente;
        bool esValido;
        char cadenaDeTexto[100];
        char d[10], m[10], a[10];
        do {
            esValido = false;
            int nuevoIdU = _repoUsuario.getNuevoId();
            if(!validarId(nuevoIdU)){
                cout << "\nERROR: No se pudo generar un ID de usuario valido..." << endl;
                if(!repetirIngreso()){
                    return false;
                }
            } else {
                regUsuario.setIdUsuario(nuevoIdU);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            int nuevoIdP = _repoPaciente.getNuevoId();
            if(!validarId(nuevoIdP)){
                cout << "\nERROR: No se pudo generar un ID de paciente valido..." << endl;
                if(!repetirIngreso()){
                    return false;
                }
            } else {
                regPaciente.setIdPaciente(nuevoIdP);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Nombre: ";
            cin.getline(cadenaDeTexto, 50);
            if(!validarNombre(cadenaDeTexto)){
                cout << "\nERROR: Nombre invalido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de nombre---" << endl;
            } else {
                regUsuario.setNombre(cadenaDeTexto);
                regPaciente.setNombre(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Apellido: ";
            cin.getline(cadenaDeTexto, 50);
            if(!validarApellido(cadenaDeTexto)){
                cout << "\nERROR: Apellido invalido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de apellido---" << endl;
            } else {
                regUsuario.setApellido(cadenaDeTexto);
                regPaciente.setApellido(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Telefono: ";
            cin.getline(cadenaDeTexto, 20);
            if(!validarTelefono(cadenaDeTexto)){
                cout << "\nERROR: Telefono invalido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de telefono---" << endl;
            } else {
                regPaciente.setTelefono(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "DNI: ";
            cin.getline(cadenaDeTexto, 15);
            int pos = _repoPaciente.buscarPorDni(cadenaDeTexto);
            if(pos >= 0){
                cout << "\nERROR: El DNI ingresado ya existe en el sistema..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de DNI---" << endl;
            } else if(!validarDni(cadenaDeTexto)){
                cout << "\nERROR: DNI invalido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
            } else {
                regPaciente.setDni(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Nombre de la obra Social: ";
            cin.getline(cadenaDeTexto, 50);
            int posOS = _repoObraSocial.buscarPorNombre(cadenaDeTexto);
            if(posOS == -1){
                cout << "\nERROR: La obra social no existe..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de obra social---" << endl;
            } else {
                ObraSocial os = _repoObraSocial.leer(posOS);
                regPaciente.setIdObraSocial(os.getIdObraSocial());
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Numero de afiliado: ";
            cin.getline(cadenaDeTexto, 30);
            if(!validarNroAfiliado(cadenaDeTexto)){
                cout << "\nERROR: Numero de afiliado invalido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de numero de afiliado---" << endl;
            } else {
                regPaciente.setNroAfiliado(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        regPaciente.setAntecedentes("Sin datos");
        do {
            esValido = false;
            cout << "Fecha de nacimiento del paciente" << endl;
            bool diaOk = false, mesOk = false, anioOk = false;
            do {
                cout << "Ingrese dia: ";
                cin.getline(d, 10);
                if(!validarDia(d)){
                    cout << "Error: Dia no numerico..." << endl;
                } else {
                    diaOk = true;
                }
            } while(!diaOk);
            do {
                cout << "Ingrese mes: ";
                cin.getline(m, 10);
                if (!validarMes(m)) {
                    cout << "Error: Mes no numerico..." << endl;
                } else {
                    mesOk = true;
                }
            } while(!mesOk);
            do {
                cout << "Ingrese anio: ";
                cin.getline(a, 10);
                if(!validarAnio(a)){
                    cout << "Error: Anio no numerico..." << endl;
                } else {
                    anioOk = true;
                }
            } while(!anioOk);
            int dia = atoi(d);
            int mes = atoi(m);
            int anio = atoi(a);
            if(!validarFecha(dia, mes, anio)){
                cout << "\nERROR: La fecha ingresada no existe o es incorrecta..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de fecha de naciemiento---" << endl;
            } else {
                Fecha fechaNac(dia, mes, anio);
                regPaciente.setFechaNacimiento(fechaNac);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Usuario: ";
            cin.getline(cadenaDeTexto, 50);
            int posU = _repoUsuario.buscarUsuario(cadenaDeTexto);
            if(posU >= 0){
                cout << "\nERROR: El nombre de usuario ya existe..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de nombre de usuario---" << endl;
            } else if(!validarNombreUsuario(cadenaDeTexto)){
                cout << "\nERROR: Nombre de usuario invalido (minimo 4 caracteres)..." << endl;
                if(!repetirIngreso()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de nombre de usuario---" << endl;
            } else {
                regUsuario.setUsuario(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Password: ";
            cin.getline(cadenaDeTexto, 50);
            if(!validarPassword(cadenaDeTexto)){
                cout << "\nERROR: Password invalida..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de constrasenia---" << endl;
            } else {
                regUsuario.setPassword(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        regUsuario.setIdRol(idRol);
        regUsuario.setEstado(true);
        regPaciente.setEstado(true);
        do {
            esValido = false;
            if(_repoPaciente.guardar(regPaciente) && _repoUsuario.guardar(regUsuario)){
                cout << "\nUsuario registrado correctamente!" << endl;
                esValido = true;
                return true;
            } else {
                cout << "\nERROR: No se pudieron guardar los registros en el disco..." << endl;
                if (!repetirIngreso()){
                    return false;
                }
            }
        } while(!esValido);
        return false;
    }

    bool ManagerUsuario::agregarUsuarioMedico(int idRol){
        system("cls");
        cout << "---REGISTRO DE USUARIO MEDICO---" << endl;
        Usuario regUsuario;
        Medico regMedico;
        bool esValido;
        char cadenaDeTexto[100];
        do {
            esValido = false;
            int nuevoIdU = _repoUsuario.getNuevoId();
            if(!validarId(nuevoIdU)){
                cout << "\nERROR: No se pudo generar un ID de usuario valido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
            } else {
                regUsuario.setIdUsuario(nuevoIdU);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            int nuevoIdM = _repoMedico.getNuevoId();
            if(!validarId(nuevoIdM)){
                cout << "\nERROR: No se pudo generar un ID de medico valido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
            } else {
                regMedico.setIdMedico(nuevoIdM);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Nombre: ";
            cin.getline(cadenaDeTexto, 50);
            if(!validarNombre(cadenaDeTexto)){
                cout << "\nERROR: Nombre invalido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de nombre---" << endl;
            } else {
                regUsuario.setNombre(cadenaDeTexto);
                regMedico.setNombre(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Apellido: ";
            cin.getline(cadenaDeTexto, 50);
            if(!validarApellido(cadenaDeTexto)){
                cout << "\nERROR: Apellido invalido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de apellido---" << endl;
            } else {
                regUsuario.setApellido(cadenaDeTexto);
                regMedico.setApellido(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Telefono: ";
            cin.getline(cadenaDeTexto, 20);
            if(!validarTelefono(cadenaDeTexto)){
                cout << "\nERROR: Telefono invalido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de telefono---" << endl;
            } else {
                regMedico.setTelefono(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "DNI: ";
            cin.getline(cadenaDeTexto, 15);
            int pos = _repoMedico.buscarPorDni(cadenaDeTexto);
            if(pos >= 0){
                cout << "\nERROR: El DNI ingresado ya existe en el sistema." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de DNI---" << endl;
            } else if(!validarDni(cadenaDeTexto)){
                cout << "\nERROR: DNI invalido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
            } else {
                regMedico.setDni(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Nombre de la especialidad: ";
            cin.getline(cadenaDeTexto, 50);
            int posEsp = _repoEspecialidad.buscarPorNombre(cadenaDeTexto);
            if(posEsp == -1){
                cout << "\nERROR: La especialidad no existe..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de especialidad---" << endl;
            } else {
                Especialidad esp = _repoEspecialidad.leer(posEsp);
                regMedico.setIdEspecialidad(esp.getIdEspecialidad());
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Matricula: ";
            cin.getline(cadenaDeTexto, 50);
            if(!validarMatricula(cadenaDeTexto)){
                cout << "\nERROR: Matricula invalida..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de matricula---" << endl;
            } else {
                regMedico.setMatricula(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Usuario: ";
            cin.getline(cadenaDeTexto, 50);
            int posU = _repoUsuario.buscarUsuario(cadenaDeTexto);
            if(posU >= 0){
                cout << "\nERROR: El nombre de usuario ya existe..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de nombre de usuario---" << endl;
            } else if(!validarNombreUsuario(cadenaDeTexto)){
                cout << "\nERROR: Nombre de usuario invalido (minimo 4 caracteres)..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de nombre de usuario---" << endl;
            } else {
                regUsuario.setUsuario(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Password: ";
            cin.getline(cadenaDeTexto, 50);
            if(!validarPassword(cadenaDeTexto)){
                cout << "\nERROR: Password invalida..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de contrasenia---" << endl;
            } else {
                regUsuario.setPassword(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        regUsuario.setIdRol(idRol);
        regUsuario.setEstado(true);
        regMedico.setEstado(true);
        do {
            esValido = false;
            if(_repoMedico.guardar(regMedico) && _repoUsuario.guardar(regUsuario)){
                cout << "\nUsuario registrado correctamente!" << endl;
                esValido = true;
                return true;
            } else {
                cout << "\nERROR: No se pudieron guardar los registros en el disco..." << endl;
                if (!repetirIngresoDeDato()){
                    return false;
                }
            }
        } while(!esValido);
        return false;
    }

    bool ManagerUsuario::agregarUsuarioAdministrador(int idRol){
        system("cls");
        cout << "---REGISTRO DE USUARIO ADMINISTRADOR---" << endl;
        Usuario regUsuario;
        bool esValido;
        char cadenaDeTexto[100];
        do {
            esValido = false;
            int nuevoIdU = _repoUsuario.getNuevoId();
            if(!validarId(nuevoIdU)){
                cout << "\nERROR: No se pudo generar un ID de usuario valido..." << endl;
                if(!repetirIngreso()){
                    return false;
                }
            } else {
                regUsuario.setIdUsuario(nuevoIdU);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Nombre: ";
            cin.getline(cadenaDeTexto, 50);
            if(!validarNombre(cadenaDeTexto)){
                cout << "\nERROR: Nombre invalido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de nombre---" << endl;
            } else {
                regUsuario.setNombre(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Apellido: ";
            cin.getline(cadenaDeTexto, 50);
            if(!validarApellido(cadenaDeTexto)){
                cout << "\nERROR: Apellido invalido..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de apellido---" << endl;
            } else {
                regUsuario.setApellido(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Usuario: ";
            cin.getline(cadenaDeTexto, 50);
            int posU = _repoUsuario.buscarUsuario(cadenaDeTexto);
            if(posU >= 0){
                cout << "\nERROR: El nombre de usuario ya existe..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de nombre de usuario---" << endl;
            } else if(!validarNombreUsuario(cadenaDeTexto)){
                cout << "\nERROR: Nombre de usuario invalido (minimo 4 caracteres)..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de nombre de usuario---" << endl;
            } else {
                regUsuario.setUsuario(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        do {
            esValido = false;
            cout << "Password: ";
            cin.getline(cadenaDeTexto, 50);
            if(!validarPassword(cadenaDeTexto)){
                cout << "\nERROR: Password invalida..." << endl;
                if(!repetirIngresoDeDato()){
                    return false;
                }
                cin.ignore();
                cout << "\n---Reintentando ingreso de contrasenia---" << endl;
            } else {
                regUsuario.setPassword(cadenaDeTexto);
                esValido = true;
            }
        } while(!esValido);
        regUsuario.setIdRol(idRol);
        regUsuario.setEstado(true);
        do {
            esValido = false;
            if(_repoUsuario.guardar(regUsuario)){
                cout << "\nUsuario registrado correctamente!" << endl;
                esValido = true;
                return true;
            } else {
                cout << "\nERROR: No se pudo guardar el registro en el disco..." << endl;
                if (!repetirIngreso()){
                    return false;
                }
            }
        } while(!esValido);
        return false;
    }

    void ManagerUsuario::agregar(){
        cin.ignore();
        system("cls");
        int idUsuario = _repoUsuario.getNuevoId();
        char nombre[50], usuario[50], password[50], nombreRol[50];
        int idRol;
        cout<< "--- REGISTRAR USUARIO ---" <<endl;
        if(!validarId(idUsuario)){
            cout<< "Error al generar el ID." <<endl;
            return;
        }
        bool nombreValido = false;
        do{
            cout<< "Nombre: ";
            cin.getline(nombre,50);
            if(!validarNombre(nombre)){
                cout<< "Nombre invalido." <<endl;
            } else {
                nombreValido = true;
            }
        } while(!nombreValido);
        bool usuarioValido = false;
        do{
            cout<< "Usuario: ";
            cin.getline(usuario,50);
            if(_repoUsuario.buscarUsuario(usuario) != -1){
                cout<< "Ese usuario ya existe." <<endl;
            } else if(!validarNombreUsuario(usuario)){
                cout<< "Nombre de usuario invalido. Debe contener un minimo de 4 caracteres" <<endl;
            } else {
                usuarioValido = true;
            }
        } while(!usuarioValido);
        bool passwordValida = false;
        do{
            cout<< "Password: ";
            cin.getline(password,50);
            if(!validarPassword(password)){
                cout<< "Password invalida." <<endl;
            } else {
                passwordValida = true;
            }
        } while(!passwordValida);
        bool rolValido = false;
        int posRol;
        Rol rol;
        do{
            cout<< "Nombre del rol: ";
            cin.getline(nombreRol,50);
            posRol = _repoRol.buscarPorNombre(nombreRol);
            if(posRol == -1){
                cout<< "El rol no existe en el sistema." <<endl;
                cout<< endl;
            cout<< "LISTADO DE ROLES ACTIVOS" <<endl;
            _managerRol.listar();
            cout<< endl;
        } else {
                rol = _repoRol.leer(posRol);
                idRol = rol.getIdRol();
                rolValido = true;
            }
        } while(!rolValido);
        Usuario reg(idUsuario, nombre, usuario, password, idRol, true);
        if(_repoUsuario.guardar(reg)){
            cout<< "Usuario agregado correctamente." <<endl;
        } else {
            cout<< "No se pudo guardar el usuario." <<endl;
        }
        system("pause");
    }

void ManagerUsuario::modificar(){

    system("cls");

    char usuario[50];
    char nuevoNombre[50];
    char nuevoUsuario[50];
    char nuevaPassword[50];
    char nombreRol[50];

    int opcion;

    cout<< "--- MODIFICACION DE USUARIO ---" <<endl;
    cout<< "Ingrese el nombre de usuario: ";
    cin.getline(usuario,50);

    int pos = _repoUsuario.buscarUsuario(usuario);

    if(pos == -1){
        cout<< "El usuario no existe o esta dado de baja." <<endl;
        return;
    }

    Usuario reg = _repoUsuario.leer(pos);

    reg.mostrar();

    cout<< endl;
    cout<< "Que desea modificar?" <<endl;
    cout<< "1 - Nombre" <<endl;
    cout<< "2 - Usuario" <<endl;
    cout<< "3 - Password" <<endl;
    cout<< "4 - Rol" <<endl;
    cout<< "0 - Cancelar" <<endl;
    cout<< "Opcion: ";
    cin>> opcion;
    cin.ignore();

    switch(opcion){

    case 1:
    {
        bool nombreValido = false;

        do{

            cout << "Nuevo nombre: ";
            cin.getline(nuevoNombre,50);

            if(!validarNombre(nuevoNombre)){
                cout<< "Nombre invalido." <<endl;
            }
            else{
                nombreValido = true;
            }

        }while(!nombreValido);

        reg.setNombre(nuevoNombre);
    }
    break;

    case 2:
    {
        bool usuarioValido = false;

        do{

            cout<< "Nuevo usuario: ";
            cin.getline(nuevoUsuario,50);

            if(strcmp(nuevoUsuario, reg.getUsuario()) == 0){
                cout << "Es el mismo usuario." << endl;
            }
            else{

                int posNueva = _repoUsuario.buscarUsuario(nuevoUsuario);

                if(posNueva >= 0 && posNueva != pos){
                    cout<< "Ese usuario ya existe." <<endl;
                }
                else if(!validarNombreUsuario(nuevoUsuario)){
                    cout<< "Nombre de usuario invalido." <<endl;
                }
                else{
                    usuarioValido = true;
                }

            }

        }while(!usuarioValido);

        reg.setUsuario(nuevoUsuario);
    }
    break;

    case 3:
    {
        bool passwordValida = false;

        do{

            cout<< "Nueva password: ";
            cin.getline(nuevaPassword,50);

            if(!validarPassword(nuevaPassword)){
                cout<< "Password invalida." <<endl;
            }
            else{
                passwordValida = true;
            }

        }while(!passwordValida);

        reg.setPassword(nuevaPassword);
    }
    break;

    case 4:
    {
        bool rolValido = false;

        Rol rol;

        cout<< "LISTADO DE ROLES ACTIVOS" <<endl;
        _managerRol.listar();

        do{

            cout<< "Nombre del rol: ";
            cin.getline(nombreRol,50);

            int posRol = _repoRol.buscarPorNombre(nombreRol);

            if(posRol == -1){
                cout<< "El rol no existe." <<endl;
            }
            else{
                rol = _repoRol.leer(posRol);
                reg.setIdRol(rol.getIdRol());
                rolValido = true;
            }

        }while(!rolValido);
    }
    break;

    case 0:
        cout<< "Operacion cancelada." <<endl;
        return;

    default:
        cout<< "Opcion invalida." <<endl;
        return;
    }

    if(_repoUsuario.modificar(reg,pos)){
        cout<< "Usuario modificado correctamente." <<endl;
    }
    else{
        cout<< "No se pudo modificar el usuario." <<endl;
    }

    system("pause");
}

void ManagerUsuario::bajaLogica(){

    system("cls");

    char usuario[50];

    cout<< "--- BAJA LOGICA DE USUARIO ---" <<endl;

    cout<< "Ingrese el nombre de usuario: ";
    cin.getline(usuario,50);

    int pos = _repoUsuario.buscarUsuario(usuario);

    if(pos == -1){
        cout<< "ERROR: El usuario no existe en el sistema." <<endl;
        system("pause");
        return;
    }

    Usuario reg = _repoUsuario.leer(pos);

    if(!reg.getEstado()){
        cout<< "ERROR: El usuario ya se encuentra dado de baja." <<endl;
        system("pause");
        return;
    }

    reg.mostrar();

    char opcion;

    cout<< endl;
    cout<< "Confirma la baja del usuario? (S/N): ";
    cin>> opcion;

    if(opcion != 'S' && opcion != 's'){
        cout<< "Operacion cancelada." <<endl;
        system("pause");
        return;
    }

    if(_repoUsuario.bajaLogica(pos)){
        cout<< "Usuario dado de baja correctamente." <<endl;
    }
    else{
        cout<< "ERROR: No se pudo dar de baja el usuario." <<endl;
    }

    system("pause");
}

    void ManagerUsuario::altaLogica(){

    system("cls");

    char usuario[50];

    cout<< "--- ALTA LOGICA DE USUARIO ---" <<endl;
    cout<< "Ingrese el nombre de usuario: ";
    cin.getline(usuario,50);

    int pos = _repoUsuario.buscarUsuario(usuario);

    if(pos == -1){
        cout<< "ERROR: El usuario no existe en el sistema." <<endl;
        system("pause");
        return;
    }

    Usuario reg = _repoUsuario.leer(pos);

    if(reg.getEstado()){
        cout<< "ERROR: El usuario ya se encuentra activo." <<endl;
        system("pause");
        return;
    }

    reg.mostrar();

    char opcion;

    cout<< endl;
    cout<< "Confirma el alta del usuario? (S/N): ";
    cin>> opcion;
    cin.ignore();

    if(opcion != 'S' && opcion != 's'){
        cout<< "Operacion cancelada." <<endl;
        system("pause");
        return;
    }

    if(_repoUsuario.altaLogica(pos)){
        cout<< "Usuario reactivado correctamente." <<endl;
    }
    else{
        cout<< "ERROR: No se pudo reactivar el usuario." <<endl;
    }

    system("pause");
}

    Usuario ManagerUsuario::login(int &idPaciente){
        Usuario u;
        u.setIdRol(-1);
        idPaciente = 0;
        cout << "--------------------" << endl;
        cout << "---INICIAR SESION---" << endl;
        cout << "--------------------" << endl;
        char usuario[50], password[50];
        cout << "Usuario: ";
        cin.getline(usuario, 50);
        cout << "Password: ";
        cin.getline(password, 50);
        int posU = _repoUsuario.buscarUsuario(usuario);
        if(posU >= 0){
            Usuario temp = _repoUsuario.leer(posU);
            if(strcmp(temp.getPassword(), password) == 0){
                u = temp;
                if(u.getIdRol() == 1){
                    int posP = _repoPaciente.buscarPosicion(u.getIdUsuario());
                    if(posP >= 0){
                        Paciente p = _repoPaciente.leer(posP);
                        idPaciente = p.getIdPaciente();
                        cout << "\nBienvenido " << p.getNombre() << "!" << endl;
                    }
                } else {
                    cout << "\nBienvenido al sistema!" << endl;
                }
                system("pause");
            }
        } else {
            cout << "\nUsuario o contrasenia incorrectos." << endl;
            system("pause");
        }
        return u;
    }

//LISTADO:
    void ManagerUsuario::listar(){

    int cantidad = _repoUsuario.getCantidadRegistros();
    bool hayUsuarios = false;

    cout << "--- LISTADO DE USUARIOS ---" << endl;

    for(int i = 0; i < cantidad; i++){
        Usuario reg = _repoUsuario.leer(i);
        reg.mostrar();
        hayUsuarios = true;
    }

    if(!hayUsuarios){
        cout << endl;
        cout << "No hay USUARIOS registrados en el sistema." << endl;
    }
}

void ManagerUsuario::listarActivos(){

    int cantidad = _repoUsuario.getCantidadRegistros();
    bool hayUsuarios = false;

    cout<< "--- LISTADO DE USUARIOS ACTIVOS ---" <<endl;

    for(int i = 0; i < cantidad; i++){
        Usuario reg = _repoUsuario.leer(i);
        if(reg.getEstado()){
            reg.mostrar();
            hayUsuarios = true;
        }
    }
    if(!hayUsuarios){
        cout<< endl;
        cout<< "No hay usuarios activos en el sistema." <<endl;

    }
}

void ManagerUsuario::listarInactivos(){

    int cantidad = _repoUsuario.getCantidadRegistros();
    bool hayUsuarios = false;

    cout<< "--- LISTADO DE USUARIOS INACTIVOS ---" <<endl;

    for(int i = 0; i < cantidad; i++){

        Usuario reg = _repoUsuario.leer(i);

        if(!reg.getEstado() == false){
            reg.mostrar();
            hayUsuarios = true;
        }
    }
    if(!hayUsuarios){
        cout<< endl;
        cout<< "No hay usuarios inactivos en el sistema." <<endl;
    }
}
