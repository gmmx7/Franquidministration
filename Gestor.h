/*
#ifndef GESTOR_H
#define GESTOR_H

#include <vector>
#include <iostream>
#include <string>
#include "Producto.h"
#include "Venta.h"
#include "Consola.h"

using namespace std;

class Gestor{
	private:
		vector<Producto> productos;
		vector<Venta> ventas;
	public:
		Gestor();
		//Create, Read, Update, Delete
		
		//Funciones para gestionar PRODUCTOS
		void agregarProducto();
		void actualizarProducto(int clave);
		void borrarProducto(int clave);
		void mostrarProductos();
		int cantidadTotalProductos();
		const vector<Producto>& getProductos() const;
		void agregarProductoDesdeArchivo(const Producto& producto);
		
		//Funciones gestoras globales
		//Buscar producto: verifica la existencia del producto <--- Polimorfismo
		
		Producto* buscarProducto(const string& clave);
		Producto* buscarProductoPorNombre(const string& nombre);
		Producto* buscarProducto(const string& clave, const string& nombre);

		Venta* buscarVentaPorNumeroNota(int numeroNota); //único
		vector<Venta*> buscarVentasPorFecha(int fecha); //Buscar venta por fecha

		//Funciones para gestionar VENTAS
		void registrarVenta(const Venta& venta);
		

};
#endif
*/
#ifndef GESTOR_H
#define GESTOR_H

#include <vector>
#include <string>
#include <iostream>
#include "Producto.h"
#include "Venta.h"
#include "Consola.h"
using namespace std;

class Gestor {
private:
    vector<Producto> productos;
    vector<Venta> ventas;
    Consola consola;
public:
    Gestor();

    void agregarProducto();
    void actualizarProducto(string clave);
    void borrarProducto(string clave);
    void mostrarProductos();
    void agregarProductoDirecto(const Producto& producto);
    const vector<Producto>& obtenerProductos() const;

    Producto* buscarProducto(const string& clave);
    Producto* buscarProductoPorNombre(const string& nombre);
	vector<Producto*> buscarProductosPorCoincidencia(const string& termino);
	
    Venta* buscarVentaPorNumeroNota(int numeroNota);
    vector<Venta*> buscarVentasPorFecha(int fecha);
	const vector<Venta>& obtenerVentas() const;

    void registrarVenta(const Venta& venta);

    int cantidadTotalProductos();
    int cantidadTotalVentas();
    
    void limpiarProductos();
    void limpiarVentas();
};

#endif