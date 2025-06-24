/*
#ifndef SISTEMA_H
#define SISTEMA_H

#include "Consola.h"
#include "Pantalla.h"
#include "Gestor.h"
#include <string>
using namespace std;

class Sistema{
	private:
		Pantalla pantalla;
		Consola consola;
		Gestor gestor;
		string archivoProductos = "datos/productos.txt";
	    string archivoVentas = "datos/ventas.txt";
	    // Persistencia
	    void cargarProductos();
	    void guardarProductos();
	    void crearArchivoProductos();
	
	    void cargarVentas();
	    void guardarVentas();
	    void crearArchivoVentas();
		
		//Flujo
	    void menuPrincipal();
	    void menuProductos();
	    void menuVentas();
			
	    // Utilidades internas
	    bool existeArchivo(const string& nombreArchivo);
	public:
		Sistema();
		void iniciarSistema();
};

#endif
*/
#ifndef SISTEMA_H
#define SISTEMA_H

#include "Consola.h"
#include "Pantalla.h"
#include "Gestor.h"
#include <string>
using namespace std;

class Sistema {
private:
    Pantalla pantalla;
    Consola consola;
    Gestor gestor;

    string archivoProductos = "datos/productos.txt";
	string archivoVentas = "datos/ventas.txt";

    void cargarProductos();
    void guardarProductos();
    void crearArchivoProductos();

	void realizarVenta();
    void cargarVentas();
    void guardarVentas();
    void mostrarDetalleVenta(const Venta& v);
    void crearArchivoVentas();

    void menuPrincipal();
    void menuProductos();
    void menuVentas();

    bool existeArchivo(const string& nombreArchivo);

public:
    Sistema();
    void iniciarSistema();
};

#endif
