#include "validaciones.h"
#include <iostream>
#include <cstring>

using namespace std;

bool esPositivo(int num){
    if(num > 0){
        return true;
    }
    return false;
}

bool esNegativo(int num){
    if(num < 0){
        return true;
    }
    return false;
}


bool validarId(int id){
    if(id <= 0){
        return false;
    }
    return true;
}

bool validarDni(const char* dni){

    int largo = strlen(dni);

    if(largo < 7 || largo > 8){
        return false;
    }

    for(int i = 0; i < largo; i++){
        if(dni[i] < '0' || dni[i] > '9'){
            return false;
        }
    }
    return true;
}

bool validarNombre(const char* nombre){

    int largo = strlen(nombre);

    if(largo < 2 || largo > 49){
        return false;
    }

    bool tieneLetra = false;

    for(int i = 0; i < largo; i++){
        if(nombre[i] == ' '){
            continue;
        }
        if((nombre[i] >= 'A' && nombre[i] <= 'Z') ||
           (nombre[i] >= 'a' && nombre[i] <= 'z')){
            tieneLetra = true;
        }
        else{
            return false;
        }
    }

    return tieneLetra;
}

bool validarApellido(const char* apellido){

    int largo = strlen(apellido);

    if(largo < 2 || largo > 49){
        return false;
    }

    bool tieneLetra = false;

    for(int i = 0; i < largo; i++){

        if(apellido[i] == ' '){
            continue;
        }
        if((apellido[i] >= 'A' && apellido[i] <= 'Z') ||
           (apellido[i] >= 'a' && apellido[i] <= 'z')){
            tieneLetra = true;
        }
        else{
            return false;
        }
    }

    return tieneLetra;
}

bool validarTelefono(const char* telefono){

    int largo = strlen(telefono);

    if(largo < 8 || largo > 15){
        return false;
    }
    for(int i = 0; i < largo; i++){
        if(telefono[i] < '0' || telefono[i] > '9'){
            return false;
        }
    }
    return true;
}

bool validarMatricula(const char* matricula){
    int largo = strlen(matricula);
    if(largo == 0 || largo > 49){
        return false;
    }
    for(int i = 0; i < largo; i++){
        if((matricula[i] < 'A' || (matricula[i] > 'Z' && matricula[i] < 'a') || matricula[i] > 'z')
           && (matricula[i] < '0' || matricula[i] > '9')){
            return false;
        }
    }
    return true;
}


bool validarNroAfiliado(const char* nroAfiliado){

    int largo = strlen(nroAfiliado);

    if(largo < 5 || largo > 20){
        return false;
    }
    bool tieneNumero = false;

    for(int i = 0; i < largo; i++){
        if(nroAfiliado[i] >= '0' && nroAfiliado[i] <= '9'){
            tieneNumero = true;
        }
        else if((nroAfiliado[i] >= 'A' && nroAfiliado[i] <= 'Z') ||
                (nroAfiliado[i] >= 'a' && nroAfiliado[i] <= 'z')){
            // letra válida
        }
        else{
            return false;
        }
    }
    return tieneNumero;
}

bool validarAntecedentes(const char* antecedentes){
    int largo = strlen(antecedentes);
    if(largo == 0 || largo > 299){
        return false;
    }
    for(int i = 0; i < largo; i++){

        char c = antecedentes[i];

        if((c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') ||
           c == ' ' ||
           c == '.' ||
           c == ',' ||
           c == '-' ||
           c == '/' ||
           c == ':' ||
           c == '(' ||
           c == ')' ||
           c == '+'){
            // carácter válido
        }else{
            return false;
        }
    }
    return true;
}

bool validarMonto(const char* monto) {
    bool esValido = true;
    bool tienePunto = false;

    if (monto[0] == '\0') {
        esValido = false;
    }
    else {
        for (int i = 0; monto[i] != '\0'; i++) {
            if (monto[i] >= '0' && monto[i] <= '9') {
                // caracter valido, no hace nada
            }
            else if (monto[i] == '.' && !tienePunto) {
                tienePunto = true;
            }
            else {
                esValido = false;
            }
        }
    }

    return esValido;
}

bool validarFecha(int dia, int mes, int anio){
    if(anio < 1900 || anio > 2100){
        return false;
    }
    if(mes < 1 || mes > 12){
        return false;
    }
    if(dia < 1){
        return false;
    }

    if((mes==4 || mes==6 || mes==9 || mes==11) && dia > 30){
        return false;
    }
    if(mes==2 && anio%4!=0 && dia > 28){
        return false;
    }
    if(mes==2 && anio%4==0 && dia > 29){
        return false;
    }
    if(mes!=2 && mes!=4 && mes!=6 && mes!=9 && mes!=11 && dia > 31){
        return false;
    }

    return true;
}

bool repetirIngreso(){
    int opcion;
    cout << "\n1. Reintentar\n0. Volver atras" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    cin.ignore();
    if(opcion == 1){
        return true;
    } else {
        return false;
    }
}

bool repetirAgregar(){
    int opcion;
    cout << "\n1. Repetir\n0. Volver atras" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    cin.ignore();
    if(opcion == 1){
        return true;
    } else {
        return false;
    }
}

bool repetirIngresoDeDato(){
    int opcion;
    cout << "\n1. Rintentar ingreso\n0. Volver atras" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    if(opcion == 1){
        return true;
    } else {
        return false;
    }
}

bool repetirRegistrar(){
    int opcion;
    cout << "\n1. Registar otro usuario\n0. Volver atras" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    cin.ignore();
    if(opcion == 1){
        return true;
    } else {
        return false;
    }
}

bool repetirConsultaMenu(const char* nombreConsulta){
    int opcion;
    cout << "\nDesea realizar otra consulta por " << nombreConsulta << "?" << endl;
    cout << "1. Si" << endl;
    cout << "0. Volver al menu de consultas" << endl;
    cout << "Seleccione una opcion: ";
    cin >> opcion;
    cin.ignore();
    if (opcion == 1) {
        return true;
    } else {
        return false;
    }
}

bool validarNombreUsuario(const char* nombreUsuario){

    int largo = strlen(nombreUsuario);

    if(largo < 4 || largo > 29){
        return false;
    }

    bool tieneLetra = false;

    for(int i = 0; i < largo; i++){

        if((nombreUsuario[i] >= 'a' && nombreUsuario[i] <= 'z') ||
           (nombreUsuario[i] >= 'A' && nombreUsuario[i] <= 'Z')){

            tieneLetra = true;
        }
        else if((nombreUsuario[i] >= '0' && nombreUsuario[i] <= '9') ||
                nombreUsuario[i] == '_'){

            // carácter válido
        }
        else{
            return false;
        }
    }

    return tieneLetra;
}

bool validarPassword(const char* password){
    int largo = strlen(password);

    if(largo < 6 || largo > 29){
        return false;
    }

    for(int i = 0; i < largo; i++){
        if(password[i] == ' '){
            return false;
        }
    }

    return true;
}


bool validarNombreObraSocial(const char* nombre){

    int largo = strlen(nombre);

    if(largo < 2 || largo > 49){
        return false;
    }

    for(int i = 0; i < largo; i++){

        if(nombre[i] == ' '){
            continue;
        }
        if((nombre[i] >= 'A' && nombre[i] <= 'Z') ||
           (nombre[i] >= 'a' && nombre[i] <= 'z')){
            continue;
        }
        return false;
    }
    return true;
}



bool validarDia(const char* dia)
{
    if(dia[0] == '\0')
    {
        return false;
    }

    int i = 0;
    while(dia[i] != '\0')
    {
        if(dia[i] < '0' || dia[i] > '9')
        {
            return false;
        }
        i++;
    }

    return true;
}


bool validarMes(const char* mes)
{
    if(mes[0] == '\0')
    {
        return false;
    }

    int i = 0;
    while(mes[i] != '\0')
    {
        if(mes[i] < '0' || mes[i] > '9')
        {
            return false;
        }
        i++;
    }

    return true;
}


bool validarAnio(const char* anio)
{
    if(anio[0] == '\0')
    {
        return false;
    }

    int i = 0;
    while(anio[i] != '\0')
    {
        if(anio[i] < '0' || anio[i] > '9')
        {
            return false;
        }
        i++;
    }

    return true;
}


bool validarHoraCampo(const char* hora)
{
    if(hora[0] == '\0')
    {
        return false;
    }

    int i = 0;
    while(hora[i] != '\0')
    {
        if(hora[i] < '0' || hora[i] > '9')
        {
            return false;
        }
        i++;
    }

    return true;
}


bool validarMinuto(const char* minuto)
{
    if(minuto[0] == '\0')
    {
        return false;
    }

    int i = 0;
    while(minuto[i] != '\0')
    {
        if(minuto[i] < '0' || minuto[i] > '9')
        {
            return false;
        }
        i++;
    }

    return true;
}


bool validarHora(int hora, int minuto)
{
    if(hora < 0 || hora > 23)
    {
        return false;
    }

    if(minuto < 0 || minuto > 59)
    {
        return false;
    }

    return true;
}






bool compararTexto(const char* texto1, const char* texto2){  //Valida textos y compara sin importar mayuscula o minuscula
    int i = 0;

    while(texto1[i] != '\0' && texto2[i] != '\0'){

        char c1 = texto1[i];
        char c2 = texto2[i];

        if(c1 >= 'A' && c1 <= 'Z'){
            c1 = c1 + ('a' - 'A');
        }

        if(c2 >= 'A' && c2 <= 'Z'){
            c2 = c2 + ('a' - 'A');
        }

        if(c1 != c2){
            return false;
        }

        i++;
    }

    return texto1[i] == '\0' && texto2[i] == '\0';
}
