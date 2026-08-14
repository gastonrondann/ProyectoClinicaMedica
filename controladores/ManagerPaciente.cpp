#include "ManagerPaciente.h"
#include <iostream>
#include <cstring>
#include <limits>
#include <cstdlib>
#include "../funciones/validaciones.h"

using namespace std;

//CONSTRUCTOR:
    ManagerPaciente::ManagerPaciente(){}


void ManagerPaciente::agregar(){
    system("cls");
    int idPaciente = _repoPaciente.getNuevoId();
    char auxNombre[50], auxApellido[50], auxDni[15], auxTelefono[20], auxObraSocial[50], auxNroAfiliado[30], auxAntecedentes[300], auxDia[10],auxMes[10], auxAnio[10];

    cout << "---INGRESAR DATOS DEL PACIENTE---" << endl;
    if(!validarId(idPaciente)){
        cout << "ERROR: No se pudo asignar el ID automatico generado..." << endl;
        return;
    }

    //DNI
    bool dniValido = false;
    do{
        cout << "DNI: ";
        cin.getline(auxDni, 15);
        int pos = _repoPaciente.buscarPorDni(auxDni);

        if(pos != -1){
            cout << "Error! DNI ya existe!" << endl;
        }
        else if(!validarDni(auxDni)){
            cout << "Error! El DNI ingresado es invalido...El DNI debe contener entre 7 y 9 numeros" << endl;
        } else
        {
            dniValido = true;
        }
    } while(!dniValido);


    //NOMBRE
    bool nombreValido = false;
    do{
        cout << "Nombre: ";
        cin.getline(auxNombre, 50);
        if(!validarNombre(auxNombre)){
            cout << "Error! El nombre es invalido..." << endl;
        }
        {
            nombreValido = true;
        }
    } while(!nombreValido);

    //APELLIDO
    bool apellidoValido = false;
    do{
        cout << "Apellido: ";
        cin.getline(auxApellido, 50);
        if(!validarApellido(auxApellido)){
            cout << "Error! El apellido es invalido..." << endl;
        }
        else {
            apellidoValido = true;
        }
    } while(!apellidoValido);

    //TELEFONO
    bool telefonoValido = false;
    do{
        cout << "Telefono: ";
        cin.getline(auxTelefono, 20);
        if(!validarTelefono(auxTelefono)){
            cout << "Error! El telefono es invalido..." << endl;
        } else
        {
            telefonoValido = true;
        }
    } while(!telefonoValido);

    //OBRA SOCIAL
    bool obraSocialValida = false;
    int posObraSocial;
    int idObraSocial;
    do{
        cout << "Nombre de la Obra Social: ";
        cin.getline(auxObraSocial, 50);
        posObraSocial = _repoObraSocial.buscarPorNombre(auxObraSocial);
        if(posObraSocial == -1){
            cout << "Error! La obra social no existe en el sistema." << endl;
        }
        else {
            ObraSocial os = _repoObraSocial.leer(posObraSocial);
            idObraSocial = os.getIdObraSocial();
            obraSocialValida = true;
        }
    } while(!obraSocialValida);

    //NRO AFILIADO
    bool afiliadoValido = false;
    do{
        cout << "Numero de afiliado: ";
        cin.getline(auxNroAfiliado, 30);
        if(!validarNroAfiliado(auxNroAfiliado)){
            cout << "Error! El numero de afiliado es invalido." << endl;
        }
        else {
            afiliadoValido = true;
        }
    } while(!afiliadoValido);

    //ANTECEDENTES
    bool antecedentesValidos = false;
    do{
        cout << "Antecedentes: ";
        cin.getline(auxAntecedentes, 300);
        if(!validarAntecedentes(auxAntecedentes)){
            cout << "Error! Los antecedentes son invalidos." << endl;
        } else {
            antecedentesValidos = true;
        }
    } while(!antecedentesValidos);

//FECHA NACIMIENTO
int diaNacimiento, mesNacimiento, anioNacimiento;
bool fechaValida = false;
do{
    cout << "Fecha de nacimiento del paciente" << endl;
    bool diaValido = false;
    do{
        cout << "Ingrese dia: " << endl;
        cin.getline(auxDia, 10);
        if(!validarDia(auxDia)){
            cout << "Error! El dia debe ser un numero." << endl;
        }
        else {
            diaValido = true;
        }
    } while(!diaValido);
    bool mesValido = false;
    do{
        cout << "Ingrese mes: " << endl;
        cin.getline(auxMes, 10);
        if(!validarMes(auxMes)){
            cout << "Error! El mes debe ser un numero." << endl;
        }
        else {
            mesValido = true;
        }
    } while(!mesValido);
    bool anioValido = false;
    do{
        cout << "Ingrese anio: " << endl;
        cin.getline(auxAnio, 10);
        if(!validarAnio(auxAnio)){
            cout << "Error! El anio debe ser un numero." << endl;
        }
        else {
            anioValido = true;
        }
    } while(!anioValido);

    diaNacimiento = atoi(auxDia);
    mesNacimiento = atoi(auxMes);
    anioNacimiento = atoi(auxAnio);
    if(!validarFecha(diaNacimiento, mesNacimiento, anioNacimiento)){
        cout << "Error! Fecha incorrecta (dia/mes/anio no forman una fecha valida)" << endl;
    }
    else {
        fechaValida = true;
    }
} while(!fechaValida);


    //se crea un objeto Paciente con los datos validos
    Paciente reg(auxDni, auxNombre, auxApellido, auxTelefono, true, idPaciente, idObraSocial, auxNroAfiliado, auxAntecedentes, Fecha(diaNacimiento, mesNacimiento, anioNacimiento));
    if(_repoPaciente.guardar(reg)){
        cout << "PACIENTE guardado correctamente!" << endl;
    } else {
        cout << "ERROR: No se pudo guardar el paciente en el disco..." << endl;
    }
}

//MODIFICAR
void ManagerPaciente::modificar()
{
    system("cls");
    char dniBuscar[15], nuevoNombre[50], nuevoApellido[50], nuevoDni[15], nuevoTelefono[20], nuevaObraSocial[50], nuevoNroAfiliado[30], nuevosAntecedentes[300];

    int opcion;
    cout << "----MODIFICACION DE PACIENTE----" << endl;
    cout << "Ingrese DNI paciente a buscar" << endl;
    cin.getline(dniBuscar, 15);

    int pos =  _repoPaciente.buscarPorDni(dniBuscar);
    if(pos == -1)
    {
        cout <<  "Paciente no existe o esta dado de baja" << endl;
        return;
    }

    Paciente reg  = _repoPaciente.leer(pos);
    reg.mostrar();

    cout << "Que desea modificar: " << endl;
    cout << "1 - DNI" << endl;
    cout << "2 - Nombre" << endl;
    cout << "3 - Apellido" << endl;
    cout << "4 - Telefono" << endl;
    cout << "5 - Obra Social" << endl;
    cout << "6 - Numero Afiliado" << endl;
    cout << "7 - Antecedentes" << endl;
    cout << "0 - Cancelar operacion" << endl;
    cin >> opcion;
    cin.ignore();
    switch(opcion)
    {
        case 1:
        {
            bool dniValido = false;
            do{
                cout << "Ingrese nuevo DNI: " << endl;
                cin.getline(nuevoDni,15);

                if(strcmp(nuevoDni, reg.getDni()) == 0){
                    cout << "Error! Mismo DNI" << endl;
                }
                else{
                    int posNueva = _repoPaciente.buscarPorDni(nuevoDni);
                    if(posNueva >= 0 && posNueva != pos){
                        cout << "Error! Ya existe DNI" << endl;
                    }
                    else if(!validarDni(nuevoDni)){
                        cout << "Error! Tamanio o caracteres incorrectos" << endl;
                    }
                    else{
                        dniValido = true;
                    }
                }
            } while(!dniValido);

            reg.setDni(nuevoDni);
        }
        break;
        case 2:
        {
        bool nombreValido = false;
            do{
                cout << "Ingrese nuevo nombre: " << endl;
                cin.getline(nuevoNombre, 50);
                if(!validarNombre(nuevoNombre)){
                    cout << "Error! Tamanio o caracteres incorrectos" << endl;
                } else {
                    nombreValido = true;
                }
            } while(!nombreValido);

            reg.setNombre(nuevoNombre);
        }
        break;

        case 3:
        {
            bool apellidoValido = false;
            do{
                cout << "Ingrese nuevo apellido: " << endl;
                cin.getline(nuevoApellido, 50);
                if(!validarApellido(nuevoApellido)){
                    cout << "Error! Tamanio o caracteres incorrectos" << endl;
                } else {
                    apellidoValido = true;
                }
            } while(!apellidoValido);

            reg.setApellido(nuevoApellido);
        }
        break;



        case 4:
{
    bool telefonoValido = false;

    do
    {
        cout << "Ingrese nuevo telefono: ";
        cin.getline(nuevoTelefono, 20);

        if(strcmp(nuevoTelefono, reg.getTelefono()) == 0)
        {
            cout << "Error! Es el mismo telefono." << endl;
        }
        else if(!validarTelefono(nuevoTelefono))
        {
            cout << "Error! El telefono es invalido." << endl;
        }
        else
        {
            telefonoValido = true;
        }

    }while(!telefonoValido);

    reg.setTelefono(nuevoTelefono);
}
break;


case 5:
{
    bool obraSocialValida = false;
    int posObraSocial;
    ObraSocial os;
    do
    {
        cout << "Ingrese nueva Obra Social: ";
        cin.getline(nuevaObraSocial, 50);

        posObraSocial = _repoObraSocial.buscarPorNombre(nuevaObraSocial);

        if(posObraSocial == -1)
        {
            cout << "Error! La obra social no existe en el sistema." << endl;
        }
        else
        {
            os = _repoObraSocial.leer(posObraSocial);

            if(os.getIdObraSocial() == reg.getIdObraSocial())
            {
                cout << "Error! El paciente ya posee esa obra social." << endl;
            }
            else
            {
                obraSocialValida = true;
            }
        }

    }while(!obraSocialValida);

    reg.setIdObraSocial(os.getIdObraSocial());
}
break;

    case 6:
{
    bool afiliadoValido = false;

    do
    {
        cout << "Ingrese nuevo numero de afiliado: ";
        cin.getline(nuevoNroAfiliado, 30);

        if(strcmp(nuevoNroAfiliado, reg.getNroAfiliado()) == 0)
        {
            cout << "Error! Es el mismo numero de afiliado." << endl;
        }
        else if(!validarNroAfiliado(nuevoNroAfiliado))
        {
            cout << "Error! El numero de afiliado es invalido." << endl;
        }
        else
        {
            afiliadoValido = true;
        }

    }while(!afiliadoValido);

    reg.setNroAfiliado(nuevoNroAfiliado);
}
break;

case 7:
{
    bool antecedentesValidos = false;

    do
    {
        cout << "Ingrese nuevos antecedentes: ";
        cin.getline(nuevosAntecedentes,300);

        if(strcmp(nuevosAntecedentes, reg.getAntecedentes()) == 0)
        {
            cout<<"Error! Son los mismos antecedentes."<<endl;
        }
        else if(!validarAntecedentes(nuevosAntecedentes))
        {
            cout<<"Error! Antecedentes invalidos."<<endl;
        }
        else
        {
            antecedentesValidos=true;
        }

    }while(!antecedentesValidos);

    reg.setAntecedentes(nuevosAntecedentes);
}
break;


case 0:
            cout << "Operacion cancelada" << endl;
            return;
        default:
            cout << "Opcion invalida" << endl;
            return;
    }

    bool exito = _repoPaciente.modificar(reg, pos);

    if(exito)
    {
        cout << "Paciente modificado con exito" << endl;
    }
    else
    {
        cout << "Paciente no se pudo modificar" << endl;
    }
    system("pause");
}



//BAJA LOGICA
void ManagerPaciente::bajaLogica()
{
    system("cls");
    char auxDni[20];
    cout << "---ELIMINAR  PACIENTE (BAJA LOGICA)---" << endl;

    cout << "Ingrese DNI del paciente a modificar: " << endl;
    cin.getline(auxDni,20);
    int pos = _repoPaciente.buscarPorDni(auxDni);

    if(pos == -1){
        cout << "ERROR: El paciente  no existe en el sistema..." << endl;
        return;
    }

    Paciente reg = _repoPaciente.leer(pos);
    if(reg.getEstado() == false)
    {
        cout << "Error! el Paciente  ya se encuentra inactivo" << endl;
        return;
    }

    bool exito  = _repoPaciente.bajaLogica(pos);
    if(exito){
        cout <<  "El Paciente ha sido dado de baja con exito!" << endl;

    }
    else{
        cout <<  " ERROR: No se pudo procesar la baja logica en el archivo de pacientes " << endl;
    }
    system("pause");
}

//ALTA LOGICA
void ManagerPaciente::altaLogica()
{
    system("cls");
    char auxDni[20];
    cout  << "---ALTA PACIENTE (ALTA LOGICA)---" << endl;

    cout << "Ingrese DNI  del  paciente a dar de alta:  " << endl;
    cin.getline(auxDni,20);
    int pos = _repoPaciente.buscarPorDni(auxDni);

    if(pos == -1){
        cout << "ERROR: El  paciente no existe en el sistema..." << endl;
        return;
    }

    Paciente reg = _repoPaciente.leer(pos);
    if(reg.getEstado() == true)
    {
        cout << "Error! El paciente ya se encuentra activo" << endl;
        return;
    }


    bool exito = _repoPaciente.altaLogica(pos);
    if(exito){
        cout << "El paciente ha sido de alta con exito!" << endl;
    }
    else
    {
        cout << "ERROR: No se pudo procesar la alta en el archivo de pacientes..." << endl;
    }
    system("pause");

}


//LISTADOS:
void ManagerPaciente::listarActivos()
{
    int cantidad = _repoPaciente.getCantidadRegistros();

    bool hayPacientes = false;
    for(int i=0; i<cantidad; i++)
    {
        Paciente reg = _repoPaciente.leer(i);
        if(reg.getEstado() == true)
        {
            reg.mostrar();
            hayPacientes = true;
        }
    }

    if(!hayPacientes)
        {
            cout << "No hay pacientes activos registrados" << endl;
        }
}


void ManagerPaciente::listarInactivos()
{
    int cantidad = _repoPaciente.getCantidadRegistros();

    bool hayPacientes = false;
    for(int i=0; i<cantidad; i++)
    {
        Paciente reg = _repoPaciente.leer(i);
        if(reg.getEstado() == false)
        {
            reg.mostrar();
            hayPacientes = true;
        }
    }

    if(!hayPacientes)
        {
            cout << "No hay pacientes inactivos registrados" << endl;
        }
}



void ManagerPaciente::listarTodos(){
        int cantidad = _repoPaciente.getCantidadRegistros();
        bool hayPacientes = false;

        for(int i = 0; i < cantidad; i++){
            Paciente reg = _repoPaciente.leer(i);
                reg.mostrar();
                hayPacientes = true;
        }

        if(!hayPacientes){
            cout << endl;
            cout << "No hay pacientes registrados en el sistema." << endl;
        }
        system("pause");
    }




    void ManagerPaciente::listarPorApellido(){
        int cantidad = _repoPaciente.getCantidadRegistros();
        Paciente vec[1000];
        int j = 0;
        for(int i = 0; i < cantidad; i++){
            Paciente reg = _repoPaciente.leer(i);
            if(reg.getEstado()){
                vec[j] = reg;
                j++;
            }
        }
        for(int i = 0; i < j-1; i++){
            for(int k = i+1; k < j; k++){
                if(strcmp(vec[i].getApellido(), vec[k].getApellido()) > 0){
                    Paciente aux;
                    aux = vec[i];
                    vec[i] = vec[k];
                    vec[k] = aux;
                }
            }
        }
        cout << "PACIENTES ORDENADOS POR APELLIDO" << endl;
        for(int i = 0; i < j; i++){
            vec[i].mostrar();
            cout << endl;
        }
    }



    void ManagerPaciente::listarPorObraSocial(){
        int cantidad = _repoPaciente.getCantidadRegistros();
        Paciente vec[1000];
        int j = 0;
        for(int i = 0; i < cantidad; i++){
            Paciente reg = _repoPaciente.leer(i);
            if(reg.getEstado()){
                vec[j] = reg;
                j++;
            }
        }
        for(int i = 0; i < j - 1; i++){
            for(int k = i + 1; k < j; k++){
                if(vec[i].getIdObraSocial() > vec[k].getIdObraSocial()){
                    Paciente aux;
                    aux = vec[i];
                    vec[i] = vec[k];
                    vec[k] = aux;
                }
            }
        }
        cout << "PACIENTES ORDENADOS POR OBRA SOCIAL" << endl;
        for(int i = 0; i < j; i++){
            vec[i].mostrar();
            cout << endl;
        }
    }

    void ManagerPaciente::listarPorEdad(){
        int cantidad = _repoPaciente.getCantidadRegistros();
        Paciente vec[1000];
        int j = 0;
        for(int i = 0; i < cantidad; i++){
            Paciente reg = _repoPaciente.leer(i);
            if(reg.getEstado()){
                vec[j] = reg;
                j++;
            }
        }
        for(int i = 0; i < j - 1; i++){
            for(int k = i + 1; k < j; k++){
                Fecha fecha1 = vec[i].getFechaNacimiento();
                Fecha fecha2 = vec[k].getFechaNacimiento();
                if(fecha1.getAnio() > fecha2.getAnio() || (fecha1.getAnio() == fecha2.getAnio() && fecha1.getMes() > fecha2.getMes()) || (fecha1.getAnio() == fecha2.getAnio() && fecha1.getMes() == fecha2.getMes() && fecha1.getDia() > fecha2.getDia())){
                    Paciente aux;
                    aux = vec[i];
                    vec[i] = vec[k];
                    vec[k] = aux;
                }
            }
        }
        cout << "PACIENTES ORDENADOS POR EDAD" << endl;
        for(int i = 0; i < j; i++){
            vec[i].mostrar();
            cout << endl;
        }
    }



//CONSULTAS:
    void ManagerPaciente::consultarPacientePorDni(){
        char dni[20];
        cout << "Ingrese DNI del paciente a consultar: ";
        cin.getline(dni, 20);
        int pos = _repoPaciente.buscarPorDni(dni);
        if(pos == -1){
            cout << "Error! paciente no encontrado" << endl;
            return;
        }
        Paciente reg = _repoPaciente.leer(pos);
        reg.mostrar();
    }

    void ManagerPaciente::consultarPacientePorAfiliado(){
        char afiliado[30];
        cout << "Ingrese numero de afiliado del paciente a consultar: ";
        cin.getline(afiliado, 30);
        int pos = _repoPaciente.buscarPorNroAfiliado(afiliado);
        if(pos == -1){
            cout << "PACIENTE NO ENCONTRADO" << endl;
            return;
        }
        Paciente reg = _repoPaciente.leer(pos);
        reg.mostrar();
    }






































