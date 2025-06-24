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
int Venta::getNumeroNota() const{
	return numeroNota;
}

int Venta::getFechaNota() const{
	return fechaNota;
}

const vector<Carrito>& Venta::getItems() const {
	return items;
}


float Venta::getTotal() const{
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
void Venta::agregarItem(const Carrito& item) {
    items.push_back(item);
}

void Venta::calcularTotal() {
    total = 0;
    for (int i = 0; i < items.size(); i++) {
        total += items[i].getSubTotal();
    }
}


