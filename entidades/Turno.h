#pragma once

#include "../entidades/auxiliares/Hora.h"
#include "../entidades/auxiliares/Fecha.h"

class Turno{
    private:
        int _idTurno;
        int _idPaciente;
        int _idAgendaMedico;
        Fecha _fecha;
        Hora _hora;
        bool _estado;

    public:
        //CONSTRUCTORES.
            Turno(int idTurno = 999, int idPaciente = 999, int idAgendaMedico = 999, Fecha fecha = Fecha(), Hora hora = Hora(), bool estado = true);

        //GETTERS Y SETTERS.
            int getIdTurno();
            bool setIdTurno(int idTurno);

            int getIdPaciente();
            bool setIdPaciente(int idPaciente);

            int getIdAgendaMedico();
            bool setIdAgendaMedico(int idAgendaMedico);

            Fecha getFecha();
            bool setFecha(Fecha fecha);

            Hora getHora();
            bool setHora(Hora hora);

            bool getEstado();
            bool setEstado(bool estado);

        //METODOS.
            void mostrar();
            void mostrarMiTurno();
};

