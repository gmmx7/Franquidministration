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
	void mostrarVentas();
    void registrarVenta(const Venta& venta);

    int cantidadTotalProductos();
    int cantidadTotalVentas();
    
    void limpiarProductos();
    void limpiarVentas();
};

#endif