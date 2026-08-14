#include <cstdio>
#include <cstring>
#include "ArchivoAgendaMedico.h"

//CONSTRUCTOR:
    ArchivoAgendaMedico::ArchivoAgendaMedico(){
        strcpy(_nombreArchivo, "datos/agenda_medico.dat");
    }

//GETTERS:
    int ArchivoAgendaMedico::getNuevoId(){
        int cantidad = getCantidadRegistros();
        if(cantidad == 0){
            return 1;
        }
        AgendaMedico ultimo = leer(cantidad - 1);
        return ultimo.getIdAgendaMedico() + 1;
    }

    int ArchivoAgendaMedico::getCantidadRegistros(){
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return 0;
        }
        fseek(p, 0, SEEK_END);
        int tam = ftell(p);
        fclose(p);
        return tam / sizeof(AgendaMedico);
    }

//METODOS:
    bool ArchivoAgendaMedico::guardar(AgendaMedico reg){
        FILE* p = fopen(_nombreArchivo, "ab");
        if(p == NULL){
            return false;
        }
        bool escribio = fwrite(&reg, sizeof(AgendaMedico), 1, p);
        fclose(p);
        return escribio;
    }

    bool ArchivoAgendaMedico::guardar(AgendaMedico reg, int pos){
        FILE* p = fopen(_nombreArchivo, "rb+"); 
        if(p == NULL){
            return false;
        }
        fseek(p, pos * sizeof(AgendaMedico), SEEK_SET);
        bool escribio = fwrite(&reg, sizeof(AgendaMedico), 1, p);
        fclose(p);
        return escribio;
    }

    AgendaMedico ArchivoAgendaMedico::leer(int posicion){
        AgendaMedico reg;
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return reg;
        }
        fseek(p, posicion * sizeof(AgendaMedico), SEEK_SET);
        fread(&reg, sizeof(AgendaMedico), 1, p);
        fclose(p);
        return reg;
    }


bool ArchivoAgendaMedico::modificar(AgendaMedico reg, int posicion){

        FILE* p = fopen(_nombreArchivo, "rb+");
        if(p == NULL){
            return false;
        }
        fseek(p, posicion * sizeof(AgendaMedico), SEEK_SET);
        bool escribio = fwrite(&reg, sizeof(AgendaMedico), 1, p);
        fclose(p);
        return escribio;
    }

//Baja Logica
bool ArchivoAgendaMedico::bajaLogica(int posicion){
        AgendaMedico reg = leer(posicion);
        reg.setEstado(false);
        return modificar(reg, posicion);
    }



//ALTA LOGICA

bool ArchivoAgendaMedico::altaLogica(int pos)
{
    {
        if(pos < 0 || pos >= getCantidadRegistros())
        {
            return false;
        }
        AgendaMedico reg = leer(pos);
        reg.setEstado(true);
        return modificar(reg, pos);
    }
}


    int ArchivoAgendaMedico::buscarPosicion(int id){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            AgendaMedico reg = leer(i);
            if(reg.getIdAgendaMedico() == id && reg.getEstado() == true){
                return i;
            }
        }
        return -1;
    }


int ArchivoAgendaMedico::buscarPorFechaYHora(int idMedico, Fecha f, Hora h){
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return -1;
        }
        AgendaMedico reg;
        int pos = 0;
        while(fread(&reg, sizeof(AgendaMedico), 1, p) == 1){

            if(reg.getIdMedico() == idMedico && reg.getEstado()){

                if(reg.getFecha().esIgual(f)){

                    if(reg.getHora().getHora() == h.getHora() && reg.getHora().getMinuto() == h.getMinuto()){
                        fclose(p);
                        return pos;
                    }
                }
            }
            pos++;
        }
        fclose(p);
        return -1;
    }
