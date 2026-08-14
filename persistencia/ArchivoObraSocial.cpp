#include <cstdio>
#include <cstring>
#include "ArchivoObraSocial.h"
#include "../funciones/validaciones.h"
//CONSTRUCTOR:
    ArchivoObraSocial::ArchivoObraSocial(){
        strcpy(_nombreArchivo, "datos/ObrasSociales.dat");
    }

//GETTERS:
    int ArchivoObraSocial::getNuevoId(){
        int cantidadRegistros = getCantidadRegistros();
        if(cantidadRegistros == 0){
            return 1;
        }
        return cantidadRegistros + 1;
    }

    int ArchivoObraSocial::getCantidadRegistros(){
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return 0;
        }
        fseek(p, 0, SEEK_END);
        int tam = ftell(p);
        fclose(p);
        return tam / sizeof(ObraSocial);
    }

//METODOS:
    bool ArchivoObraSocial::guardar(ObraSocial reg){
        FILE* p = fopen(_nombreArchivo, "ab");
        if(p == NULL){
            return false;
        }
        bool escribio = fwrite(&reg, sizeof(ObraSocial), 1, p);
        fclose(p);
        return escribio;
    }

    ObraSocial ArchivoObraSocial::leer(int pos){
        ObraSocial reg;
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return reg;
        }
        fseek(p, pos * sizeof(ObraSocial), SEEK_SET);
        fread(&reg, sizeof(ObraSocial), 1, p);
        fclose(p);
        return reg;
    }

    bool ArchivoObraSocial::modificar(ObraSocial reg, int pos){
        FILE* p = fopen(_nombreArchivo, "rb+");
        if(p == NULL){
            return false;
        }
        fseek(p, pos * sizeof(ObraSocial), SEEK_SET);
        bool escribio = fwrite(&reg, sizeof(ObraSocial), 1, p);
        fclose(p);
        return escribio;
    }


     bool ArchivoObraSocial::bajaLogica(int pos)
    {
        if(pos < 0 || pos >= getCantidadRegistros())
        {
            return false;
        }
        ObraSocial reg = leer(pos);
        reg.setEstado(false);
        return modificar(reg, pos);
    }

    bool ArchivoObraSocial::altaLogica(int pos)
    {
        if(pos < 0 || pos >= getCantidadRegistros())
        {
            return false;
        }
        ObraSocial reg = leer(pos);
        reg.setEstado(true);
        return modificar(reg, pos);
    }





    int ArchivoObraSocial::buscarPosicion(int id){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            ObraSocial reg = leer(i);
            if(reg.getIdObraSocial() == id){
                return i;
            }
        }
        return -1;
    }



int ArchivoObraSocial::buscarPorNombre(const char* obraSocial){

    ObraSocial reg;
    int cant = getCantidadRegistros();

    for(int i = 0; i < cant; i++){

        reg = leer(i);

        if(compararTexto(reg.getNombre(), obraSocial)){
            return i;
        }
    }

    return -1;
}
