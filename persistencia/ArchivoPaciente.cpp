#include <cstdio>
#include <cstring>
#include "ArchivoPaciente.h"

//CONSTRUCTOR:
    ArchivoPaciente::ArchivoPaciente(){
        strcpy(_nombreArchivo, "datos/pacientes.dat");
    }

//GETTERS:
    int ArchivoPaciente::getNuevoId(){
        int cantidad = getCantidadRegistros();
        if(cantidad == 0){
            return 1;
        }
        
        return cantidad + 1;
    }

    int ArchivoPaciente::getCantidadRegistros(){
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return 0;
        }
        fseek(p, 0, SEEK_END);
        int tam = ftell(p);
        fclose(p);
        return tam / sizeof(Paciente);
    }

//METODOS:
    bool ArchivoPaciente::guardar(Paciente reg){
        FILE* p = fopen(_nombreArchivo, "ab");
        if(p == NULL){
            return false;
        }
        bool escribio = fwrite(&reg, sizeof(Paciente), 1, p);
        fclose(p);
        return escribio;
    }

    Paciente ArchivoPaciente::leer(int posicion){
        Paciente reg;
        FILE* p = fopen(_nombreArchivo, "rb");
        if(p == NULL){
            return reg;
        }
        fseek(p, posicion * sizeof(Paciente), SEEK_SET);
        fread(&reg, sizeof(Paciente), 1, p);
        fclose(p);
        return reg;
    }





    bool ArchivoPaciente::modificar(Paciente reg, int posicion){
        FILE* p = fopen(_nombreArchivo, "rb+");
        if(p == NULL){
            return false;
        }
        fseek(p, posicion * sizeof(Paciente), SEEK_SET);
        bool escribio = fwrite(&reg, sizeof(Paciente), 1, p);
        fclose(p);
        return escribio;
    }



    bool ArchivoPaciente::bajaLogica(int posicion){
        Paciente reg = leer(posicion);
        reg.setEstado(false);
        return modificar(reg, posicion);
    }



bool ArchivoPaciente::altaLogica(int posicion)
{
    if(posicion < 0 || posicion >= getCantidadRegistros())
    {
        return false;
    }

    Paciente reg = leer(posicion);

    reg.setEstado(true);

    return modificar(reg, posicion);
}






    int ArchivoPaciente::buscarPosicion(int id){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Paciente reg = leer(i);
            if(reg.getIdPaciente() == id){
                return i;
            }
        }
        return -1;
    }


    int ArchivoPaciente::buscarPorDni(const char* dni){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Paciente reg = leer(i);
            if(strcmp(reg.getDni(), dni) == 0){
                return i;
            }
        }
        return -1;
    }

    int ArchivoPaciente::buscarPorNroAfiliado(const char* nroAfiliado){
        int cantidad = getCantidadRegistros();
        for(int i = 0; i < cantidad; i++){
            Paciente reg = leer(i);
            if(strcmp(reg.getNroAfiliado(), nroAfiliado) == 0){
                return i;
            }
        }
        return -1;
    }