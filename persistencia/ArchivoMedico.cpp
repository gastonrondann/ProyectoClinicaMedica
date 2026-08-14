#include <cstdio>
#include <cstring>
#include "ArchivoMedico.h"
#include "../controladores/ManagerMedico.h"

//CONSTRUCTOR:
    ArchivoMedico::ArchivoMedico(){
        strcpy(_nombreArchivo, "datos/medicos.dat");
    }

//GETTERS:
    int ArchivoMedico::getNuevoId(){
        int cantidadRegistros = getCantidadRegistros();
        if(cantidadRegistros == 0){
            return 1; //SI NO HAY REGISTROS, TE DA UN ID 1 (EL PRIMERO)
        }

        return cantidadRegistros + 1;
    }

    int ArchivoMedico::getCantidadRegistros(){
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return 0;
        }
        fseek(p, 0, SEEK_END);
        int tam = ftell(p);
        fclose(p);
        return tam / sizeof(Medico);
    }




//METODOS ABML
    bool ArchivoMedico::guardar(Medico reg){
        FILE* p = fopen(_nombreArchivo, "ab");
        if(p == NULL){
            return false;
        }
        bool escribio = fwrite(&reg, sizeof(Medico), 1, p);
        fclose(p);
        return escribio;
    }

    Medico ArchivoMedico::leer(int posicion){
        Medico reg;
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return reg;
        }
        fseek(p, posicion * sizeof(Medico), SEEK_SET);
        fread(&reg, sizeof(Medico), 1, p);
        fclose(p);
        return reg;
    }

    bool ArchivoMedico::modificar(Medico reg, int posicion){

        FILE* p = fopen(_nombreArchivo, "rb+");
        if(p == NULL){
            return false;
        }
        fseek(p, posicion * sizeof(Medico), SEEK_SET);
        bool escribio = fwrite(&reg, sizeof(Medico), 1, p);
        fclose(p);
        return escribio;
    }



    bool ArchivoMedico::bajaLogica(int posicion)
    {
        if(posicion < 0 || posicion >= getCantidadRegistros())
        {
            return false;
        }
        Medico reg = leer(posicion);
        reg.setEstado(false);
        return modificar(reg, posicion);
    }


    bool ArchivoMedico::altaLogica(int posicion)
    {
        if(posicion < 0 || posicion >= getCantidadRegistros())
        {
            return false;
        }
        Medico reg = leer(posicion);
        reg.setEstado(true);
        return modificar(reg, posicion);
    }



//TODOS LOS "BUSCAR" TINEN COINSISTENCIA
//TODOS LOS BUSCAR NO DISCRIMINAN SI ESTA ACTIVO O INACTIVO
//ESO LO DECIDIMOS EN EL MANAGER SI QUEREMOS DISCRIMINAR

    int ArchivoMedico::buscarPosicion(int id){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Medico med = leer(i);
            if(med.getIdMedico() == id){
                return i;
            }
        }
        return -1;
    }


    int ArchivoMedico::buscarPorDni(const char* dni){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Medico reg = leer(i);
            if(strcmp(dni, reg.getDni()) == 0){
                return i;
            }
        }
        return -1;
    }

    int ArchivoMedico::buscarMatricula(const char* matricula){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Medico med = leer(i);
            if(strcmp(med.getMatricula(), matricula) == 0){
                return i;
            }
        }
        return -1;
    }


    int ArchivoMedico::buscarPorNombreYApellido(const char* nombre, const char* apellido){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Medico reg = leer(i);
            if(strcmp(reg.getNombre(), nombre) == 0 && strcmp(reg.getApellido(), apellido) == 0){
                return i;
            }
        }
        return -1;
    }
