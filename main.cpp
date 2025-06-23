#include <iostream>
#include "Sistema.h"
#include "Pantalla.h"
#include "Consola.h"
using namespace std;

int main(int argc, char** argv) {
	cout << "Iniciando main..." << endl;

	Pantalla pantalla;
	cout << "Pantalla cargada..." << endl;

	Consola consola;
	cout << "Consola cargada..." << endl;

	Sistema programaCargado;
	cout << "Sistema cargado..." << endl;
	
	pantalla.mensajeEnter();
	
	if(consola.esperarEnter()){
		consola.limpiarConsola();
		pantalla.mostrarPantallaPrincipal();
		if (consola.esperarEnter()) {
			consola.limpiarConsola();
			programaCargado.iniciarSistema();
		}
	}
	

	return 0;
}
