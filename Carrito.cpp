#include "Carrito.h"

Carrito::Carrito(int claveProducto, int cantidadProducto, float subTotal){
	this->claveProducto = claveProducto;
	this->cantidadProducto = cantidadProducto;
	this->subTotal = subTotal;
}

Carrito::Carrito(){
	claveProducto = 0;
	cantidadProducto = 0;
	subTotal = 0.0;
}

//Getters
int Carrito::getClaveProducto(){
	return claveProducto;
}
int Carrito::getCantidadProducto(){
	return cantidadProducto;
}
float Carrito::getSubTotal(){
	return subTotal;
}
		
//Setters
void Carrito::setClaveProducto(int claveProducto){
	this->claveProducto = claveProducto;
}
void Carrito::setCantidadProducto(int cantidadProducto){
	this->cantidadProducto = cantidadProducto;
}
void Carrito::setSubTotal(float subTotal){
	this->subTotal = subTotal;
}