#ifndef PRODUCTO_H
#define PRODUCTO_H

#include <string>
using namespace std;

class Producto{
	private:
		string clave;
		string nombre;
		string marca;
		int existencia;
		float precio;
	public:
		//Constructor
		Producto();
		Producto(string clave, string nombre, string marca, int existencia, float precio);
		
		//Definir Getters
		string getClave();
		string getNombre();
		string getMarca();
		int getExistencia();
		float getPrecio();
		
		//Definir Setters
		void setClave(string clave);
		void setNombre(string nombre);
		void setMarca(string marca);
		void setExistencia(int existencia);
		void setPrecio(float precio);
};
#endif