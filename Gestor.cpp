/*
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
*/
#include "Gestor.h"

Gestor::Gestor() {}

// Agregar producto
void Gestor::agregarProducto() {
    string clave, nombre, marca, existenciaStr;
    int existencia;
    float precio;

    cout << "------------ AGREGAR PRODUCTO ------------\n";

    Producto nuevo;

    cout << "Clave: ";
    getline(cin, clave);
    if (!consola.entradaValida(clave)) {
        cout << "Entrada invalida para clave.\n";
        return;
    }
    if (buscarProducto(clave) != nullptr) {
        cout << "Producto con esa clave ya existe.\n";
        return;
    }
    nuevo.setClave(clave);

    cout << "Nombre: ";
    getline(cin, nombre);
    if (!consola.entradaValida(nombre)) {
        cout << "Entrada invalida para nombre.\n";
        return;
    }
    nuevo.setNombre(nombre);

    cout << "Marca: ";
    getline(cin, marca);
    if (!consola.entradaValida(marca)) {
        cout << "Entrada invalida para marca.\n";
        return;
    }
    nuevo.setMarca(marca);

    cout << "Existencia: ";
    getline(cin, existenciaStr);
    existencia = consola.convertirCadenaANumero(existenciaStr);
    if (existencia < 0) {
        cout << "Existencia invalida.\n";
        return;
    }
    nuevo.setExistencia(existencia);

    cout << "Precio: ";
    cin >> precio;
    cin.ignore();
    if (precio < 0) {
        cout << "Precio invalido.\n";
        return;
    }
    nuevo.setPrecio(precio);

    productos.push_back(nuevo);
    cout << "Producto agregado correctamente.\n";
}

// Actualizar producto
void Gestor::actualizarProducto(string clave) {
    Producto* p = buscarProducto(clave);
    if (p == nullptr) {
        cout << "Producto no encontrado.\n";
        return;
    }

    string nombre, marca, existenciaStr;
    int existencia;
    float precio;

    cout << "Actualizar datos para producto con clave " << clave << ":\n";

    cout << "Nuevo nombre: ";
    getline(cin, nombre);
    if (!consola.entradaValida(nombre)) {
        cout << "Entrada invalida para nombre.\n";
        return;
    }
    p->setNombre(nombre);

    cout << "Nueva marca: ";
    getline(cin, marca);
    if (!consola.entradaValida(marca)) {
        cout << "Entrada invalida para marca.\n";
        return;
    }
    p->setMarca(marca);

    cout << "Nueva existencia: ";
    getline(cin, existenciaStr);
    existencia = consola.convertirCadenaANumero(existenciaStr);
    if (existencia < 0) {
        cout << "Existencia invalida.\n";
        return;
    }
    p->setExistencia(existencia);

    cout << "Nuevo precio: ";
    cin >> precio;
    cin.ignore();
    if (precio < 0) {
        cout << "Precio invalido.\n";
        return;
    }
    p->setPrecio(precio);

    cout << "Producto actualizado correctamente.\n";
}

// Borrar producto
void Gestor::borrarProducto(string clave) {
    int indice = -1;
    for (int i = 0; i < (int)productos.size(); i++) {
        if (productos[i].getClave() == clave) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        cout << "Producto no encontrado.\n";
        return;
    }
    for (int i = indice; i < (int)productos.size() - 1; i++) {
        productos[i] = productos[i + 1];
    }
    productos.pop_back();
    cout << "Producto eliminado correctamente.\n";
}

// Mostrar productos
void Gestor::mostrarProductos() {
    consola.limpiarConsola();
    cout << "\n----- LISTA DE PRODUCTOS -----\n";
    cout << "CLAVE | NOMBRE | MARCA | EXISTENCIA | PRECIO\n";
    cout << "----------------------------------------------\n";
    for (int i = 0; i < (int)productos.size(); i++) {
        Producto p = productos[i];
        cout << p.getClave() << " | " << p.getNombre() << " | " << p.getMarca() << " | "
            << p.getExistencia() << " | $" << p.getPrecio() << "\n";
    }
    cout << "----------------------------------------------\n";
}

// Buscar producto por clave
Producto* Gestor::buscarProducto(const string& clave) {
    string claveBusqueda = consola.limpiarEspacios(clave);
    claveBusqueda = consola.toLowerString(claveBusqueda);
    
    for (int i = 0; i < (int)productos.size(); i++) {
        string claveProducto = consola.limpiarEspacios(productos[i].getClave());
        claveProducto = consola.toLowerString(claveProducto);

        if (claveProducto == claveBusqueda) {
            return &productos[i];
        }
    }
    return nullptr;
}


// Buscar producto por nombre (exacto)
Producto* Gestor::buscarProductoPorNombre(const string& nombre) {
    string nombreBuscado = consola.toLowerString(nombre);
    
    for (int i = 0; i < (int)productos.size(); i++) {
        string nombreProducto = consola.toLowerString(productos[i].getNombre());

        if (consola.contieneSubcadena(nombreProducto, nombreBuscado)) {
            return &productos[i];
        }
    }
    return nullptr;
}



// Buscar venta por número de nota
Venta* Gestor::buscarVentaPorNumeroNota(int numeroNota) {
    for (int i = 0; i < (int)ventas.size(); i++) {
        if (ventas[i].getNumeroNota() == numeroNota) {
            return &ventas[i];
        }
    }
    return nullptr;
}

// Buscar ventas por fecha
vector<Venta*> Gestor::buscarVentasPorFecha(int fecha) {
    vector<Venta*> resultado;
    for (int i = 0; i < (int)ventas.size(); i++) {
        if (ventas[i].getFechaNota() == fecha) {
            resultado.push_back(&ventas[i]);
        }
    }
    return resultado;
}

vector<Producto*> Gestor::buscarProductosPorCoincidencia(const string& termino) {
    vector<Producto*> resultado;
    string terminoMinus = consola.limpiarEspacios(termino);
    terminoMinus = consola.toLowerString(terminoMinus);

    for (int i = 0; i < (int)productos.size(); i++) {
        string claveProducto = consola.limpiarEspacios(productos[i].getClave());
        string nombreProducto = consola.limpiarEspacios(productos[i].getNombre());
        claveProducto = consola.toLowerString(claveProducto);
        nombreProducto = consola.toLowerString(nombreProducto);

        if (consola.contieneSubcadena(claveProducto, terminoMinus) ||
            consola.contieneSubcadena(nombreProducto, terminoMinus)) {
            resultado.push_back(&productos[i]);
        }
    }
    return resultado;
}

// Registrar venta
void Gestor::registrarVenta(const Venta& venta) {
    ventas.push_back(venta);
    cout << "Venta registrada correctamente.\n";
}

// Cantidad total de productos
int Gestor::cantidadTotalProductos() {
    return (int)productos.size();
}

// Cantidad total de ventas
int Gestor::cantidadTotalVentas() {
    return (int)ventas.size();
}

void Gestor::limpiarProductos() {
    productos.clear();
}

//Kind of wraps papu
void Gestor::agregarProductoDirecto(const Producto& producto) { 
	productos.push_back(producto); 
}

const vector<Producto>& Gestor::obtenerProductos() const { 
	return productos; 
}

void Gestor::limpiarVentas() { 
	ventas.clear();
}

const vector<Venta>& Gestor::obtenerVentas() const {
    return ventas;
}

