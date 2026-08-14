#include <cstdio>
#include <cstring>
#include "ArchivoRol.h"

//CONSTRUCTOR:
    ArchivoRol::ArchivoRol(){
        strcpy(_nombreArchivo, "datos/roles.dat");
    }

//GETTERS:
    int ArchivoRol::getNuevoId(){
        return getCantidadRegistros() + 1;
    }

    int ArchivoRol::getCantidadRegistros(){
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return 0;
        }
        fseek(p, 0, SEEK_END);
        int tam = ftell(p);
        fclose(p);
        return tam / sizeof(Rol);
    }

//METODOS.
    bool ArchivoRol::guardar(Rol reg){
        FILE* p = fopen(_nombreArchivo, "ab");
        if(p == NULL){
            return false;
        }
        bool escribio = fwrite(&reg, sizeof(Rol), 1, p);
        fclose(p);
        return escribio;
    }

    Rol ArchivoRol::leer(int posicion){
        Rol reg;
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return reg;
        }
        fseek(p, posicion * sizeof(Rol), SEEK_SET);
        fread(&reg, sizeof(Rol), 1, p);
        fclose(p);
        return reg;
    }

    int ArchivoRol::buscarPosicion(int id){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Rol reg = leer(i);
            if(reg.getIdRol() == id && reg.getEstado() == true)
            {
                return i;
            }
        }
        return -1;
    }

    int ArchivoRol::buscarPorNombre(const char* nombre){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Rol reg = leer(i);
            if(strcmp(reg.getNombre(), nombre) == 0 && reg.getEstado() == true){
                return i;
            }
        }
        return -1;
    }

    bool ArchivoRol::modificar(Rol reg, int posicion){
        FILE* p = fopen(_nombreArchivo, "rb+");
        if(p == NULL){
            return false;
        }
        fseek(p, posicion * sizeof(Rol), SEEK_SET);
        bool escribio = fwrite(&reg, sizeof(Rol), 1, p);
        fclose(p);
        return escribio;
    }

    bool ArchivoRol::bajaLogica(int posicion){
        Rol reg = leer(posicion);
        reg.setEstado(false);
        return modificar(reg, posicion);
    }
