#ifndef CARRITO_H
#define CARRITO_H
#include <string>
using namespace std;
class Carrito{
	private:
		int claveProducto;
		int cantidadProducto;
		float subTotal;
	public:
		Carrito();
		Carrito(int claveProducto, int cantidadProducto, float subTotal);
		//Getters
		int getClaveProducto() const;
		int getCantidadProducto() const;
		float getSubTotal() const;
		
		//Setters
		void setClaveProducto(int claveProducto);
		void setCantidadProducto(int cantidadProducto);
		void setSubTotal(float subTotal);
};
#endif