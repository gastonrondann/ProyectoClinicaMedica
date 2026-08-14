#include "ArchivoEspecialidad.h"
#include <stdio.h>
#include <cstring>

//CONSTRUCTOR:
    ArchivoEspecialidad::ArchivoEspecialidad(){
        strcpy(_nombreArchivo, "datos/Especialidad.dat");
    }

//GETTERS:
    int ArchivoEspecialidad::getNuevoId(){
        return getCantidadRegistros() + 1;
    }

    int ArchivoEspecialidad::getCantidadRegistros(){
        FILE *p = fopen(_nombreArchivo, "rb");
        if(p == nullptr){
            return 0;
        }
        fseek(p, 0, SEEK_END);
        int tamTotal = ftell(p) / sizeof(Especialidad);
        fclose(p);
        return tamTotal;
    }

//METODOS:
    bool ArchivoEspecialidad::guardar(Especialidad reg){
        FILE *p = fopen(_nombreArchivo, "ab");
        if(p == nullptr){
            return false;
        }
        int cant = fwrite(&reg, sizeof(Especialidad), 1, p);
        fclose(p);
        return cant;
    }

    Especialidad ArchivoEspecialidad::leer(int pos){
        Especialidad reg;
        FILE *p = fopen(_nombreArchivo, "rb");
        if(p == nullptr){
            return reg;
        }
        fseek(p, pos * sizeof(Especialidad), SEEK_SET);
        fread(&reg, sizeof(Especialidad), 1, p);
        fclose(p);
        return reg;
    }
    

    bool ArchivoEspecialidad::modificar(Especialidad reg, int pos){
        FILE *p = fopen(_nombreArchivo, "rb+");
        if(p == nullptr){
            return false;
        }
        fseek(p, pos * sizeof(Especialidad), SEEK_SET);
        bool escribio = fwrite(&reg, sizeof(Especialidad), 1, p);
        fclose(p);
        return escribio;
    }



bool ArchivoEspecialidad::bajaLogica(int posicion)
    {
        if(posicion < 0 || posicion >= getCantidadRegistros())
        {
            return false;
        }

        Especialidad reg = leer(posicion);
        reg.setEstado(false);
        return modificar(reg, posicion);
    }

    
bool ArchivoEspecialidad::altaLogica(int posicion)
    {
        if(posicion < 0 || posicion >= getCantidadRegistros())
        {
            return false;
        }
        Especialidad reg = leer(posicion);
        reg.setEstado(true);
        return modificar(reg, posicion);
    }


    

int ArchivoEspecialidad::buscarPosicion(int id){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Especialidad reg = leer(i);
            if(reg.getIdEspecialidad() == id && reg.getEstado() == true){
                return i;
            }
        }
        return -1;
    }



    int ArchivoEspecialidad::buscarPorNombre(const char* especialidad){
        Especialidad reg;
        int cant = getCantidadRegistros();
        for(int i = 0; i < cant; i++){
            reg = leer(i);
            if(strcmp(reg.getNombre(), especialidad) == 0){
                return i;
            }
        }
        return -1;
    }