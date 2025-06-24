#include "Pantalla.h"
#include <iostream>
using namespace std;

void Pantalla::mostrarPantallaPrincipal() {
	cout << " _______________________________________________________________________________________________________________\n";
	cout << "|\t________ _______ _______ _______ _______ _______     ___ ___ _______ ______  _______ _______ _______ \t|\n";
	cout << "|\t" << R"(|   _   |   _   |   _   |       |   _   |   _   \   |   Y   |   _   |   _  \|       |   _   |   _   |)" << "\t|\n";
	cout << "|\t|.  |___|.  1___|   1___|.|   | |.  |   |.  l   /   |.  |   |.  1___|.  |   |.|   | |.  1   |   1___|\t|\n";
	cout << "|\t|.  |   |.  __)_|____   `-|.  |-|.  |   |.  _   1   |.  |   |.  __)_|.  |   `-|.  |-|.  _   |____   |\t|\n";
	cout << "|\t|:  1   |:  1   |:  1   | |:  | |:  1   |:  |   |   |:  1   |:  1   |:  |   | |:  | |:  |   |:  1   |\t|\n";
	cout << "|\t" << R"(|::.. . |::.. . |::.. . | |::.| |::.. . |::.|:. |    \:.. ./|::.. . |::.|   | |::.| |::.|:. |::.. . |)" << "\t|\n";
	cout << "|	`-------`-------`-------' `---' `-------`--- ---'     `---' `-------`--- ---' `---' `--- ---`-------'\t|\n";
	cout << "|\t\t\t\t\t\t\t\t\t\tProyecto: Franquidministration\t|\n";
	cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
	cout << "|\t\t\t\t\tPresiona [ENTER] para continuar\t\t\t\t\t\t|\n";
	cout << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
	cout << "|_______________________________________________________________________________________________________________|\n";                                  
}

void Pantalla::mostrarMenuPrincipal() {
    cout << "----------SISTEMA DE VENTAS----------\n";
    cout << "\t1. Agregar producto\n";
    cout << "\t2. Realizar venta\n";
    cout << "\t3. Gestionar Productos\n";
    cout << "\t4. Gestionar ventas\n";
    cout << "\t5. Cerrar programa\n";
    cout << "Selecciona una opcion: ";
}

void Pantalla::mostrarMenuProductos(){
	cout << "--------GESTION DE PRODUCTOS---------\n";
	cout << "\t1. Agregar producto\n";
    cout << "\t2. Eliminar producto\n";
    cout << "\t3. Actualizar producto\n";
    cout << "\t4. Mostrar lista de productos\n";
    cout << "\t5. Buscar producto\n";
    cout << "\t6. Salir del gestor\n";
    cout << "Selecciona una opcion: ";
}

void Pantalla::mostrarMenuVentas() {
    cout << "-------- MENU DE VENTAS --------\n";
    cout << "\t1. Mostrar todas las ventas\n";
    cout << "\t2. Buscar por numero de nota\n";
    cout << "\t3. Buscar por fecha\n";
    cout << "\t4. Registrar nueva venta\n";
    cout << "\t5. Regresar al menu principal\n";
    cout << "Seleccione una opcion: ";
}

void Pantalla::mensajeEnter(){
	cout << "Presiona [ENTER] para continuar\n";
}