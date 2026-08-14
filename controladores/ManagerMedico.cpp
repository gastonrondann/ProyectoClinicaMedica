#include <iostream>
#include <cstring>
#include "ManagerMedico.h"
#include "../funciones/validaciones.h"
using namespace std;
//COMPLETO !!

//CONSTRUCTOR:
    ManagerMedico::ManagerMedico(){}

void ManagerMedico::agregar(){
    system("cls");
    int idMedico = _repoMedico.getNuevoId();
    char auxNombre[50], auxApellido[50], auxMatricula[50], auxDni[15], auxTelefono[20], auxEspecialidad[50];

    cout << "---INGRESAR DATOS DE MEDICO---" << endl;

    if(!validarId(idMedico)){
        cout << "ERROR: No se pudo asignar el ID automatico generado..." << endl;
        return;
    }

    //DNI DENTRO DE UN DO-WHILE
    bool dniValido = false;
    do{
        cout << "DNI: ";
        cin.getline(auxDni, 15);

        //SI EL DNI EXISTE....
        int pos = _repoMedico.buscarPorDni(auxDni);
        if(pos != -1){
            cout << "Error! DNI ya existe!" << endl;
        }
        //SI EL DNI NO EXISTE...SE LLAMA A VALIDAR DNI 
        else if(!validarDni(auxDni)){
            cout << "Error! El DNI ingresado es invalido..." << endl;
        }
        else{
            dniValido = true;
        }
    } while(!dniValido); //--> MIENTRAS EL DNI NO SEA VALIDO, VUELVE A PEDIR LOS DATOS ARRIBA



    //NOMBRE --> SOLO PASA POR VALIDAR NOMBRE
    // PORQUE  ? PORQUE PUEDE EXISTIR UN MISMO NOMBRE
    bool nombreValido = false;
    do{
        cout << "Nombre: ";
        cin.getline(auxNombre, 50);
        if(!validarNombre(auxNombre)){
            cout << "Error! El nombre es invalido..." << endl;
        } else 
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
        } else 
        {
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

    //MATRICULA --- > MISMA RESOLUCION QUE DNI
    bool matriculaValida = false;
    do{
        cout << "Matricula: ";
        cin.getline(auxMatricula, 50);

    
        int pos = _repoMedico.buscarMatricula(auxMatricula);
        if(pos != -1){
            cout << "Error! Matricula ya existe!" << endl;
        }


        else if(!validarMatricula(auxMatricula))
        {
            cout << "Error! La matricula es invalida..." << endl;
        } 

        else
        {
            matriculaValida = true;
        }
    } while(!matriculaValida);


    //ESPECIALIDAD
    bool especialidadValida = false;
    int posEspecialidad;
    int idEspecialidad;
    Especialidad esp;

    do{
        cout << "Nombre de la especialidad: ";
        cin.getline(auxEspecialidad, 50);

        posEspecialidad = _repoEspecialidad.buscarPorNombre(auxEspecialidad);

        if(posEspecialidad == -1)
        {
            cout << "Error! La especialidad no existe en el sistema" << endl;
            cout << "LISTADO DE ESPECIALIDADES ACTIVAS" << endl;
            _managerEspecialidad.listar(1); //listaria las especialidades activas
        }
        else
        {
            esp = _repoEspecialidad.leer(posEspecialidad);
            idEspecialidad =  esp.getIdEspecialidad();
            especialidadValida = true;
        }
    } while(!especialidadValida);


    //se crea un objeto medico con todos los datos cargados
    //no se corre riesgo de tener datos vacios
    //Al crearse se llama al 2 constructor, q ese mismo llama a los setter
    Medico reg(auxDni, auxNombre, auxApellido, auxTelefono, true, idMedico, auxMatricula, idEspecialidad);

    if(_repoMedico.guardar(reg)){
        cout << "MEDICO guardado correctamente!" << endl;
    } else {
        cout << "ERROR: No se pudo guardar el medico en el disco..." << endl;
    }
}




//METODO MODIFICAR
void ManagerMedico::modificar(){
    system("cls");
    char auxDni[15], nuevoDni[20], nuevoNombre[50], nuevoApellido[50], nuevaMatricula[50], nuevoTelefono[20];
    int opcion;
    cout << "---- MODIFICACION DE MEDICO ----" << endl;
    cout << "Ingrese DNI a buscar: " << endl;
    cin >> auxDni;

    int pos = _repoMedico.buscarPorDni(auxDni);
    if(pos == -1)
    {
        cout << "Medico no existe o esta dado de baja" << endl;
        return;
    }

    Medico reg = _repoMedico.leer(pos);
    listar(reg);

    cout << "Que desea modificar: " << endl;
    cout << "1 - DNI" << endl;
    cout << "2 - Nombre" << endl;
    cout << "3 - Apellido" << endl;
    cout << "4 - Matricula" << endl;
    cout << "5 - Telefono" << endl;
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
                cin >> nuevoDni;

                if(strcmp(nuevoDni, reg.getDni()) == 0){
                    cout << "Error! Mismo DNI" << endl;
                }
                else{
                    int posNueva = _repoMedico.buscarPorDni(nuevoDni);
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
            bool matriculaValida = false;
            do{
                cout << "Ingrese nueva matricula: " << endl;
                cin >> nuevaMatricula;

                if(strcmp(nuevaMatricula, reg.getMatricula()) == 0){
                    cout << "Error! Misma matricula" << endl;
                }
                else{
                    int posNueva = _repoMedico.buscarMatricula(nuevaMatricula);
                    if(posNueva >= 0 && posNueva != pos){
                        cout << "ERROR ! Ya existe la matricula" << endl;
                    }
                    else if(!validarMatricula(nuevaMatricula)){
                        cout << "Error! Tamanio o caracteres incorrectos" << endl;
                    }
                    else{
                        matriculaValida = true;
                    }
                }
            } while(!matriculaValida);

            reg.setMatricula(nuevaMatricula);
        }
        break;

        case 5:
        {
            bool telefonoValido = false;
            do{
                cout << "Ingrese nuevo telefono: " << endl;
                cin >> nuevoTelefono;

                if(strcmp(nuevoTelefono, reg.getTelefono()) == 0){
                    cout << "Error! Mismo telefono" << endl;
                }
                else if(!validarTelefono(nuevoTelefono)){
                    cout << "Error! Tamanio o caracteres incorrectos" << endl;
                }
                else{
                    telefonoValido = true;
                }
            } while(!telefonoValido);
            
            reg.setTelefono(nuevoTelefono);
        }
        break;

        case 0:
            cout << "Operacion cancelada" << endl;
            return;
        default:
            cout << "Opcion invalida" << endl;
            return;
    }

    bool exito = _repoMedico.modificar(reg, pos);
    
    if(exito)
    {
        cout << "Medico modificado con exito" << endl;
    }
    else
    {
        cout << "Medico no se pudo modificar" << endl;
    }
}




//BAJA LOGICA
void ManagerMedico::bajaLogica(){
    system("cls");
    char auxDni[20];
    cout << "---ELIMINAR MEDICO (BAJA LOGICA)---" << endl;

    cout << "Ingrese DNI del medico a eliminar: " << endl;
    cin >> auxDni;
    int pos = _repoMedico.buscarPorDni(auxDni);

    if(pos == -1){
        cout << "ERROR: El medico no existe en el sistema..." << endl;
        return;
    }

    Medico reg = _repoMedico.leer(pos);
    if(reg.getEstado() == false)
    {
        cout << "Error! el medico ya se encuentra inactivo" << endl;
        return;
    }


    bool exito = _repoMedico.bajaLogica(pos);
    if(exito){
        cout << "El medico ha sido dado de baja con exito!" << endl;
    } 
    else 
    {
        cout << "ERROR: No se pudo procesar la baja en el archivo de medicos..." << endl;
    }
}



void ManagerMedico::altaLogica(){

    system("cls");
    char auxDni[20];
    cout << "---ALTA MEDICO (ALTA LOGICA)---" << endl;

    cout << "Ingrese DNI del medico a dar de alta: " << endl;
    cin >> auxDni;
    int pos = _repoMedico.buscarPorDni(auxDni);

    if(pos == -1){
        cout << "ERROR: El medico no existe en el sistema..." << endl;
        return;
    }

    Medico reg = _repoMedico.leer(pos);
    if(reg.getEstado() == true)
    {
        cout << "Error! El medico ya se encuentra activo" << endl;
        return;
    }


    bool exito = _repoMedico.altaLogica(pos);
    if(exito){
        cout << "El medico ha sido de alta con exito!" << endl;
    } 
    else 
    {
        cout << "ERROR: No se pudo procesar la alta en el archivo de medicos..." << endl;
    }
}






//LISTADOS:
    void ManagerMedico::listar(int opcion){
        int cantidad = _repoMedico.getCantidadRegistros();
        bool hayMedicos = false;
        cout << "------------------------" << endl;
        cout << "---LISTADO DE MEDICOS---" << endl;
        cout << "------------------------" << endl;
        if(opcion == 1)
    {
        for(int i = 0; i < cantidad; i++){
            Medico reg = _repoMedico.leer(i);
            if(reg.getEstado() == true){
                reg.mostrar();
                hayMedicos = true;
            }
        }
    }
    else if(opcion == 2)
    {
        for(int i = 0; i < cantidad; i++){
            Medico reg = _repoMedico.leer(i);
            if(reg.getEstado() == false){
                reg.mostrar();
                hayMedicos = true;
            }
        }
    }
    else
    {
        for(int i = 0; i < cantidad; i++){
            Medico reg = _repoMedico.leer(i);
                reg.mostrar();
                hayMedicos = true;
        }
    }

        if(!hayMedicos){
            cout << endl;
            cout << "No hay medicos registrados en el sistema." << endl;
        }
    }




void ManagerMedico::listar(Medico reg)
{
    reg.mostrar();
}





    void ManagerMedico::listarPorApellido(){
        int cant = _repoMedico.getCantidadRegistros();
        if(cant <= 0){
            cout << "El archivo no tiene registros" << endl;
            return;
        }


        Medico *medPuntero = new Medico [cant];
        if(medPuntero==nullptr){
            return;
        }


        for(int i = 0; i < cant; i++){
            medPuntero[i] = _repoMedico.leer(i);
        }
        


        Medico aux;
        for(int i = 0; i < cant-1; i++){
            for(int x = i+1; x < cant; x++){
                if(strcmp(medPuntero[i].getApellido(), medPuntero[x].getApellido()) > 0){
                    aux = medPuntero[i];
                    medPuntero[i] = medPuntero[x];
                    medPuntero[x] = aux;
                }
            }
        }
    

        for(int i = 0; i < cant; i++){
                medPuntero[i].mostrar();
                cout << "---------------------------" << endl;
        }
        delete[] medPuntero;
    }



    void ManagerMedico::listarPorEspecialidad(){
        int cant = _repoMedico.getCantidadRegistros();
        if(cant <= 0){
            cout << "El archivo no tiene registros" << endl;
            return;
        }


        Medico *medPuntero = new Medico [cant];
        if(medPuntero==nullptr){
            return;
        }
        for(int i = 0; i < cant; i++){
            medPuntero[i] = _repoMedico.leer(i);
        }
        Medico aux;
        for(int i = 0; i < cant-1; i++){
            for(int x = i+1; x < cant; x++){
                if(medPuntero[i].getIdEspecialidad() > medPuntero[x].getIdEspecialidad()){
                    aux = medPuntero[i];
                    medPuntero[i] = medPuntero[x];
                    medPuntero[x] = aux;
                }
            }
        }
        
        for(int i = 0; i < cant; i++){
                medPuntero[i].mostrar();
                
                cout << "------------------------------------" << endl;
        }
        delete[]medPuntero;
    }


