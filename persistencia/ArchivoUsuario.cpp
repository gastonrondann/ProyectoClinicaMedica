#include <cstdio>
#include <cstring>
#include "ArchivoUsuario.h"
#include <iostream>
using namespace std;
//CONSTRUCTOR:
    ArchivoUsuario::ArchivoUsuario(){
        strcpy(_nombreArchivo, "datos/usuarios.dat");
    }

//GETTERS:
    int ArchivoUsuario::getNuevoId(){
        int cantidad = getCantidadRegistros();
        if(cantidad == 0){
            return 1;
        }
        return cantidad + 1;
    }

    int ArchivoUsuario::getCantidadRegistros(){
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return 0;
        }
        fseek(p, 0, SEEK_END);
        int tam = ftell(p);
        fclose(p);
        return tam / sizeof(Usuario);
    }

//METODOS:
    bool ArchivoUsuario::guardar(Usuario reg){
        FILE* p = fopen(_nombreArchivo, "ab");
        if(p == NULL){
            return false;
        }
        bool escribio = fwrite(&reg, sizeof(Usuario), 1, p);
        fclose(p);
        return escribio;
    }

    Usuario ArchivoUsuario::leer(int pos){
        Usuario reg;
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return reg;
        }
        fseek(p, pos * sizeof(Usuario), SEEK_SET);
        fread(&reg, sizeof(Usuario), 1, p);
        fclose(p);
        return reg;
    }

    bool ArchivoUsuario::modificar(Usuario reg, int pos){
        FILE* p = fopen(_nombreArchivo, "rb+");
        if(p == NULL){
            return false;
        }
        fseek(p, pos * sizeof(Usuario), SEEK_SET);
        bool escribio = fwrite(&reg, sizeof(Usuario), 1, p);
        fclose(p);
        return escribio;
    }

    bool ArchivoUsuario::bajaLogica(int pos){
        Usuario reg = leer(pos);
        reg.setEstado(false);
        return modificar(reg, pos);
    }

    bool ArchivoUsuario::altaLogica(int pos)
{
    if(pos < 0 || pos >= getCantidadRegistros()){
        return false;
    }

    Usuario reg = leer(pos);
    reg.setEstado(true);

    return modificar(reg, pos);
}




    int ArchivoUsuario::buscarUsuario(const char* usuario){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Usuario reg = leer(i);
            if(strcmp(reg.getUsuario(), usuario) == 0){
                return i;
            }
        }
        return -1;
    }

    int ArchivoUsuario::buscarPosicion(int id){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Usuario reg = leer(i);
            if(reg.getIdUsuario() == id && reg.getEstado() == true){
                return i;
            }
        }
        return -1;
    }
