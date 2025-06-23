#include "Producto.h"

Producto::Producto(string clave, string nombre, string marca, int existencia, float precio){
	this->clave = clave;
	this->nombre = nombre;
	this->marca = marca;
	this->existencia = existencia;
	this->precio = precio;
}

Producto::Producto(){
	clave = "";
	nombre = "";
	marca = "";
	existencia = 0;
	precio = 0;
}

//Definir Getters
string Producto::getClave(){
	return clave;
}

string Producto::getNombre(){
	return nombre;
}

string Producto::getMarca(){
	return marca;
}

int Producto::getExistencia(){
	return existencia;
}

float Producto::getPrecio(){
	return precio;
}
		
//Definir Setters
void Producto::setClave(string clave){
	this->clave = clave;
}

void Producto::setNombre(string nombre){
	this->nombre = nombre;
}

void Producto::setMarca(string marca){
	this->marca = marca;
}

void Producto::setExistencia(int existencia){
	this->existencia = existencia;
}

void Producto::setPrecio(float precio){
	this->precio = precio;
}