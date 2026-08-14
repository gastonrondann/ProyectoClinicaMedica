#pragma once

bool esPositivo(int num);
bool esNegativo(int num);

bool validarId(int id);
bool validarDni(const char* dni);
bool validarNombre(const char* nombre);
bool validarApellido(const char* apellido);
bool validarTelefono(const char* telefono);
bool validarMatricula(const char* matricula);
bool validarNroAfiliado(const char* nroAfiliado);
bool validarAntecedentes(const char* antecedentes);
bool validarNombreUsuario(const char* nombreUsuario);
bool validarPassword(const char* password);
bool validarNombreObraSocial(const char* nombre);
bool validarMonto(const char* monto);
bool validarFecha(int dia, int mes, int anio);
bool validarDia(const char* dia);
bool validarMes(const char* mes);
bool validarAnio(const char* anio);
bool validarHoraCampo(const char* hora);
bool validarMinuto(const char* minuto);
bool validarHora(int hora, int minuto);
bool compararTexto(const char* texto1, const char* texto2);

bool repetirIngreso();
bool repetirAgregar();
bool repetirConsultaMenu(const char* nombreConsulta);
bool repetirIngresoDeDato();
bool repetirRegistrar();
