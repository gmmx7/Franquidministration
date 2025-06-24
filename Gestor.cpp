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

//Kind of wraps papuuuuuuuuuu
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

