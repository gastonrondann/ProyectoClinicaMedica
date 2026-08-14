#pragma once
#include "../persistencia/ArchivoUsuario.h"
#include "../persistencia/ArchivoRol.h"
#include "../persistencia/ArchivoPaciente.h"
#include "../persistencia/ArchivoObraSocial.h"
#include "../persistencia/ArchivoMedico.h"
#include "../persistencia/ArchivoEspecialidad.h"
#include "../entidades/Usuario.h"
#include "ManagerRol.h"

class ManagerUsuario{
    private:
        ArchivoUsuario _repoUsuario;
        ArchivoRol _repoRol;
        ManagerRol _managerRol;
        ArchivoPaciente _repoPaciente;
        ArchivoObraSocial _repoObraSocial;
        ArchivoMedico _repoMedico;
        ArchivoEspecialidad _repoEspecialidad;

    public:
        //CONSTRUCTOR:
            ManagerUsuario();
        //METODOS:
            void registrarUsuario();
            bool agregarUsuarioPaciente(int idRol);
            bool agregarUsuarioMedico(int idRol);
            bool agregarUsuarioAdministrador(int idRol);
            void agregar();   
            void modificar();  
            void bajaLogica();
            void altaLogica();
        //LOGIN
            Usuario login(int &idPacienteLogueado);
        //LISTADOS:
            void listar();
            void listarActivos();
            void listarInactivos();
};