#ifndef VENTA_H
#define VENTA_H

#include <string>
#include <vector>

#include "Carrito.h"
using namespace std;

class Venta{
	private:
		int numeroNota;
		int fechaNota;
		vector<Carrito> items;
		float total;
	public:
		//Constructores
		Venta();
		Venta(int numeroNota, int fechaNot);
		
		//Getters
		int getNumeroNota() const;
		int getFechaNota() const;
		const vector<Carrito>& getItems() const; // referencia para poder modificar y leer los productos
		float getTotal() const;
		
		//Setters
		void setNumeroNota(int numeroNota);
		void setFechaNota(int fechaNota);
		void setTotal(float total);
		
		// Funciones venta
    	void agregarItem(const Carrito& item);
    	void calcularTotal();
};

#endif