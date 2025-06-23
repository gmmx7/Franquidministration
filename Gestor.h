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