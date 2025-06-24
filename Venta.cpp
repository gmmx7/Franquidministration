#include "Venta.h"

//Constructores
Venta::Venta(int numeroNota, int fechaNota){
	this->numeroNota = numeroNota;
	this->fechaNota = fechaNota;
	this->total = 0.0;
}

Venta::Venta(){
	numeroNota = 0;
	fechaNota = 0;
	total = 0.0;
}

//Getters
int Venta::getNumeroNota(){
	return numeroNota;
}

int Venta::getFechaNota(){
	return fechaNota;
}

vector<Carrito>& Venta::getItems(){
	return this->items;
}

float Venta::getTotal(){
	return total;
}

//Setters
void Venta::setNumeroNota(int numeroNota){
	this->numeroNota = numeroNota;
}

void Venta::setFechaNota(int fechaNota){
	this->fechaNota = fechaNota;
}

void Venta::setTotal(float total){
	this->total = total;
}

//Funciones propias de la clase venta
void Venta::agregarItem(const Carrito& item){}
void Venta::calcularTotal(){}