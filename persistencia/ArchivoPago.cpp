#include <cstdio>
#include <cstring>
#include "ArchivoPago.h"
#include "../controladores/ManagerPago.h"

//CONSTRUCTOR:
    ArchivoPago::ArchivoPago(){
        strcpy(_nombreArchivo, "datos/pagos.dat");
    }

//GETTERS:
    int ArchivoPago::getNuevoId(){
        int cantidad = getCantidadRegistros();
        if(cantidad == 0){
            return 1;
        }
        Pago ultimo = leer(cantidad - 1);
        return ultimo.getIdTurno() + 1;
    }

    int ArchivoPago::getCantidadRegistros(){
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return 0;
        }
        fseek(p, 0, SEEK_END);
        int tam = ftell(p);
        fclose(p);
        return tam / sizeof(Pago);
    }

//METODOS:
    bool ArchivoPago::guardar(Pago reg){
        FILE* p = fopen(_nombreArchivo, "ab");
        if(p == NULL){
            return false;
        }
        bool escribio = fwrite(&reg, sizeof(Pago), 1, p);
        fclose(p);
        return escribio;
    }

    Pago ArchivoPago::leer(int posicion){
        Pago reg;
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return reg;
        }
        fseek(p, posicion * sizeof(Pago), SEEK_SET);
        fread(&reg, sizeof(Pago), 1, p);
        fclose(p);
        return reg;
    }

    int ArchivoPago::buscarPosicion(int id){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Pago reg = leer(i);
            if(reg.getIdPago() == id && reg.getEstado() == true){
                return i;
            }
        }
        return -1;
    }

    bool ArchivoPago::modificar(Pago reg, int posicion){
        FILE* p = fopen(_nombreArchivo, "rb+");
        if(p == NULL){
            return false;
        }
        fseek(p, posicion * sizeof(Pago), SEEK_SET);
        bool escribio = fwrite(&reg, sizeof(Pago), 1, p);
        fclose(p);
        return escribio;
    }

    bool ArchivoPago::bajaLogica(int posicion){
        Pago reg = leer(posicion);
        reg.setEstado(false);
        return modificar(reg, posicion);
    }