#include "Gestor.h"

Gestor::Gestor(){}
//Create, Read, Update, Delete
		
//Funciones para gestionar PRODUCTOS
void Gestor::agregarProducto() {
    Consola consola;
    string clave, existenciaStr, nombre, marca, precioStr;
    float precio = -1;
    int existencia = -1;

    cout << "------------AGREGAR PRODUCTO-------------" << endl;

    Producto nuevo;
    consola.limpiarBufferEntrada();

    // CLAVE
    do {
        cout << "Clave: ";
        getline(cin, clave);

        if (!consola.entradaValida(clave)) {
            cout << "Entrada invalida para clave. Solo letras, numeros o espacios.\n";
            clave.clear();
        } else if (buscarProducto(clave) != nullptr) {
            cout << "Ya existe un producto con esta clave.\n";
            clave.clear();
        }
    } while (clave.empty());
    nuevo.setClave(clave);

    // NOMBRE
    do {
        cout << "Nombre: ";
        getline(cin, nombre);
        if (!consola.entradaValida(nombre)) {
            cout << "Entrada invalida para nombre.\n";
            nombre.clear();
        }
    } while (nombre.empty());
    nuevo.setNombre(nombre);

    // MARCA
    do {
        cout << "Marca: ";
        getline(cin, marca);
        if (!consola.entradaValida(marca)) {
            cout << "Entrada invalida para marca.\n";
            marca.clear();
        }
    } while (marca.empty());
    nuevo.setMarca(marca);

    // EXISTENCIA (número entero positivo)
    do {
        cout << "Existencia: ";
        getline(cin, existenciaStr);
        existencia = consola.convertirCadenaANumero(existenciaStr);
        if (existencia < 0) {
            cout << "Existencia invalida. Solo se permiten numeros enteros positivos.\n";
        }
    } while (existencia < 0);
    nuevo.setExistencia(existencia);

    // PRECIO (número flotante positivo validado a mano)
    do {
        bool valido = true;
        bool hayPunto = false;
        precio = 0;
        precioStr = "";

        cout << "Precio: ";
        getline(cin, precioStr);

        if (precioStr.empty()) {
            valido = false;
        }

        // Validación manual
        for (int i = 0; i < precioStr.size(); i++) {
            char c = precioStr[i];
            if (c == '.') {
                if (hayPunto) {
                    valido = false;
                    break;
                }
                hayPunto = true;
            } else if (c < '0' || c > '9') {
                valido = false;
                break;
            }
        }

        // Conversión manual de string a float si válido
        if (valido) {
            int parteEntera = 0, parteDecimal = 0, decimales = 0;
            bool parteDecimalActiva = false;

            for (int i = 0; i < precioStr.size(); i++) {
                char c = precioStr[i];
                if (c == '.') {
                    parteDecimalActiva = true;
                    continue;
                }

                if (!parteDecimalActiva) {
                    parteEntera = parteEntera * 10 + (c - '0');
                } else {
                    parteDecimal = parteDecimal * 10 + (c - '0');
                    decimales++;
                }
            }

            precio = parteEntera + (parteDecimal / pow(10, decimales));
            if (precio < 0) valido = false;
        }

        if (!valido || precio < 0) {
            cout << "Precio invalido. Solo se permiten numeros positivos, usa punto decimal.\n";
            precio = -1;
        }

    } while (precio < 0);
    nuevo.setPrecio(precio);

    // Agregar producto
    productos.push_back(nuevo);
    cout << "Producto agregado correctamente.\n" << endl;
}



void Gestor::actualizarProducto(int clave){

}
void Gestor::borrarProducto(int clave){

}
void Gestor::mostrarProductos(){
	Consola consola;
	consola.limpiarConsola();
	int total = cantidadTotalProductos();
	cout << "\n----- LISTA DE PRODUCTOS -----\n";
	cout << "CLAVE |     NOMBRE     |     MARCA     | EXISTENCIA | PRECIO\n";
    cout << "------------------------------------------------------------\n";
    for(int i=0;i<total;i++){
    	Producto& p = productos[i];  // Referencia al producto actual
        cout << p.getClave() << " | "<< p.getNombre() << " | "<< p.getMarca() << " | "<< p.getExistencia() << " | $"<< p.getPrecio() << "\n";
	}
	cout << "------------------------------------------------------------\n";
}
		
//Funciones gestoras globales
//Buscar producto: verifica la existencia del producto <--- Polimorfismo
// Buscar por clave exacta o parcial
Producto* Gestor::buscarProducto(const string& clave) {
	Consola consola;
	for (int i = 0; i < productos.size(); i++) {
		if (consola.contieneSubcadena(productos[i].getClave(), clave)) {
			return &productos[i];  // Retorna dirección del producto encontrado
		}
	}
	return nullptr;  // No encontrado
}

// Buscar por nombre exacto o parcial
Producto* Gestor::buscarProductoPorNombre(const string& nombre) {
	Consola consola;
	for (int i = 0; i < productos.size(); i++) {
		if (consola.contieneSubcadena(productos[i].getNombre(), nombre)) {
			return &productos[i];  // Retorna dirección del producto encontrado
		}
	}
	return nullptr;  // No encontrado
}

// Buscar por clave Y nombre (coincidencia en ambos)
Producto* Gestor::buscarProducto(const string& clave, const string& nombre) {
	Consola consola;
	for (int i = 0; i < productos.size(); i++) {
		if (consola.contieneSubcadena(productos[i].getClave(), clave) &&
		    consola.contieneSubcadena(productos[i].getNombre(), nombre)) {
			return &productos[i];  // Retorna dirección del producto encontrado
		}
	}
	return nullptr;  // No encontrado
}
		
Venta* Gestor::buscarVentaPorNumeroNota(int numeroNota){
	return nullptr;
}
vector<Venta*> Gestor::buscarVentasPorFecha(int fecha){
	return {};
} //Buscar venta por fecha

//Funciones para gestionar VENTAS
void Gestor::registrarVenta(const Venta& venta){}

//Util
int Gestor::cantidadTotalProductos(){
	int totalProductos = 0;
	while (totalProductos < productos.size()) {
    	totalProductos++;
	}
	return totalProductos;
}

const vector<Producto>& Gestor::getProductos() const {
    return productos;
}

void Gestor::agregarProductoDesdeArchivo(const Producto& producto) {
    productos.push_back(producto);
}


