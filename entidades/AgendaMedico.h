#pragma once
#include "auxiliares/Fecha.h"
#include "auxiliares/Hora.h"

class AgendaMedico{
  private:
      int _idAgendaMedico;
      int _idMedico;
      Fecha _fecha;
      Hora _hora;
      bool _disponible;
      bool _estado;

  public:
      // CONSTRUCTORES:
        AgendaMedico();
        AgendaMedico(int idAgendaMedico, int idMedico, Fecha fecha, Hora hora, bool disponible, bool estado);

      // GETTERS Y SETTERS:
        int getIdAgendaMedico();
        void setIdAgendaMedico(int idAgendaMedico);

        int getIdMedico();
        void setIdMedico(int idMedico);

        Fecha getFecha();
        void setFecha(Fecha fecha);

        Hora getHora();
        void setHora(Hora hora);

        bool getDisponible();
        void setDisponible(bool disponible);

        bool getEstado();
        void setEstado(bool estado);

      // METODOS:
        void mostrar();
};