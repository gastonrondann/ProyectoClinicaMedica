#include <iostream>
#include "Menu.h"

using namespace std;

void Menu::ejecutarMenu(){
    int opcion;
    do{
        system("cls");
        mostrarOpciones();
        opcion = seleccionarOpciones();
        system("cls");
        ejecutarOpciones(opcion);
        if(opcion != 0){
            system("pause");
        }
    } while(opcion != 0);
}

void Menu::setCantidadItems(int cantidadItems){
    _cantidadItems = cantidadItems;
}
int Menu::getCantidadItems(){
    return _cantidadItems;
}

int Menu::seleccionarOpciones(){
    int opcion;
    do{
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();
        if(opcion < 0 || opcion > getCantidadItems()){
                cout << "Opcion incorrecta" << endl;
            }
    } while(opcion < 0 || opcion > getCantidadItems());
    return opcion;
}
