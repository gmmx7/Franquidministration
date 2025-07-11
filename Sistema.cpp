#include "Sistema.h"
#include <fstream>
#include <iostream>
using namespace std;

Sistema::Sistema() {}

void Sistema::iniciarSistema() {
    cout << "Iniciando sistema...\n";

    if (existeArchivo(archivoProductos)) {
        cargarProductos();
    }
    else {
        crearArchivoProductos();
        cout << "\t--> No se encontro archivo productos. Se creo nuevo.\n";
    }

    if (existeArchivo(archivoVentas)) {
        cargarVentas();
    }
    else {
        crearArchivoVentas();
        cout << "\t--> No se encontro archivo ventas. Se creo nuevo.\n";
    }

    if (consola.esperarEnter()) {
        consola.limpiarConsola();
        menuPrincipal();
    }
}

bool Sistema::existeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    return archivo.good();
}

void Sistema::crearArchivoProductos() {
    ofstream archivo(archivoProductos);
    archivo << "CLAVE |     NOMBRE     |     MARCA     | EXISTENCIA | PRECIO\n";
    archivo << "------------------------------------------------------------\n";
    archivo << "<<<<<<LISTA VACIA, AGREGUE PRODUCTOS DESDE EL MENU>>>>>>\n";
    archivo.close();
}

void Sistema::crearArchivoVentas() {
    ofstream archivo(archivoVentas);
    archivo << "# REGISTRO DE VENTAS\n";
    archivo << "NOTA | FECHA | PRODUCTOS (clave-cantidad-subtotal) | TOTAL\n";
    archivo << "---------------------------------------------------------\n";
    archivo << "<<<<<<LISTA VACIA, AGREGUE PRODUCTOS DESDE EL MENU>>>>>>\n";
    archivo.close();
}


void Sistema::cargarProductos() {
    ifstream archivo(archivoProductos);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir archivo productos.\n";
        return;
    }

    string linea;
    // Saltar encabezados (2 líneas) jhfkahf
    getline(archivo, linea);
    getline(archivo, linea);

    gestor.limpiarProductos();

    while (getline(archivo, linea)) {
        if (linea == "<<<<<<LISTA VACIA, AGREGUE PRODUCTOS DESDE EL MENU>>>>>>") break;

        string clave, nombre, marca, existenciaStr, precioStr;

        int pos1 = 0;
        int pos2 = linea.find('|', pos1);
        if (pos2 == -1) continue;
        clave = consola.limpiarEspacios(linea.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        pos2 = linea.find('|', pos1);
        if (pos2 == -1) continue;
        nombre = consola.limpiarEspacios(linea.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        pos2 = linea.find('|', pos1);
        if (pos2 == -1) continue;
        marca = consola.limpiarEspacios(linea.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        pos2 = linea.find('|', pos1);
        if (pos2 == -1) continue;
        existenciaStr = consola.limpiarEspacios(linea.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        precioStr = consola.limpiarEspacios(linea.substr(pos1));

        // Conversiooooon
        int existencia = consola.convertirCadenaANumero(existenciaStr);
        float precio = consola.convertirCadenaAFloat(precioStr);

        if (existencia == -1 || precio < 0) {
            cout << "Error al convertir datos. Producto omitido.\n";
            continue;
        }

        Producto p(clave, nombre, marca, existencia, precio);
        gestor.agregarProductoDirecto(p);
    }

    archivo.close();
}

void Sistema::guardarProductos() {
    ofstream archivo(archivoProductos);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir archivo productos para guardar.\n";
        return;
    }

    archivo << "CLAVE |     NOMBRE     |     MARCA     | EXISTENCIA | PRECIO\n";
    archivo << "------------------------------------------------------------\n";
    
	const vector<Producto>& productos = gestor.obtenerProductos();
    if (productos.size() == 0) {
        archivo << "<<<<<<LISTA VACIA, AGREGUE PRODUCTOS DESDE EL MENU>>>>>>\n";
    }
    else {
        for (int i = 0; i < (int)productos.size(); i++) {
            Producto p = productos[i];
            archivo << p.getClave() << " | " << p.getNombre() << " | " << p.getMarca() << " | " << p.getExistencia() << " | " << p.getPrecio() << "\n";
        }
    }
    archivo.close();
}

/*
void Sistema::cargarVentas() {
    ifstream archivo(archivoVentas);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir archivo ventas.\n";
        return;
    }

    string linea;
    // Saltar encabezados (3 líneas)
    getline(archivo, linea);
    getline(archivo, linea);
    getline(archivo, linea);

    gestor.limpiarVentas();

    while (getline(archivo, linea)) {
        if (linea == "<<<<<<LISTA VACIA, AGREGUE PRODUCTOS DESDE EL MENU>>>>>>") break;
        // Aquí debería parsear las ventas
    }
    archivo.close();
}
*/
void Sistema::cargarVentas() {
    ifstream archivo(archivoVentas);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir archivo ventas.\n";
        return;
    }

    string linea;
    // Saltar encabezados (3 líneas)
    getline(archivo, linea);
    getline(archivo, linea);
    getline(archivo, linea);

    gestor.limpiarVentas();

    while (getline(archivo, linea)) {
        if (linea.empty() || linea == "<<<<<<LISTA VACIA, AGREGUE PRODUCTOS DESDE EL MENU>>>>>>") break;

        // Ejemplo de línea:
        // 1 | 20250624 | 101-2-30.0, 102-1-25.0 | 55.0

        int pos1 = 0;
        int pos2 = linea.find('|');
        if (pos2 == -1) continue;
        string notaStr = consola.limpiarEspacios(linea.substr(pos1, pos2 - pos1));
        int nota = consola.convertirCadenaANumero(notaStr);

        pos1 = pos2 + 1;
        pos2 = linea.find('|', pos1);
        if (pos2 == -1) continue;
        string fechaStr = consola.limpiarEspacios(linea.substr(pos1, pos2 - pos1));
        int fecha = consola.convertirCadenaANumero(fechaStr);

        pos1 = pos2 + 1;
        pos2 = linea.find('|', pos1);
        if (pos2 == -1) continue;
        string productosStr = consola.limpiarEspacios(linea.substr(pos1, pos2 - pos1));

        pos1 = pos2 + 1;
        string totalStr = consola.limpiarEspacios(linea.substr(pos1));
        float total = consola.convertirCadenaAFloat(totalStr);

        // Crear venta
        Venta venta;
        venta.setNumeroNota(nota);
        venta.setFechaNota(fecha);

        // Separar productos
        vector<string> productos = consola.separarPorComas(productosStr);
        for (int i = 0; i < (int)productos.size(); i++) {
            string item = consola.limpiarEspacios(productos[i]);

            int p1 = item.find('-');
            int p2 = item.find('-', p1 + 1);
            if (p1 == -1 || p2 == -1) continue;

            string claveStr = item.substr(0, p1);
            string cantidadStr = item.substr(p1 + 1, p2 - p1 - 1);
            string subTotalStr = item.substr(p2 + 1);

            Carrito c;
            c.setClaveProducto(consola.convertirCadenaANumero(claveStr));
            c.setCantidadProducto(consola.convertirCadenaANumero(cantidadStr));
            c.setSubTotal(consola.convertirCadenaAFloat(subTotalStr));

            venta.agregarItem(c);
        }

        // Agregar al sistema
        venta.calcularTotal(); // opcional
        gestor.registrarVenta(venta);
    }

    archivo.close();
}


void Sistema::realizarVenta() {
    consola.limpiarConsola();
    cout << "---------- NUEVA VENTA ----------\n";
    
    Venta venta;
    int numeroNota = gestor.cantidadTotalVentas() + 1;
    venta.setNumeroNota(numeroNota);

    string fechaStr;
    cout << "Fecha de la venta (formato AAAAMMDD): ";
    getline(cin, fechaStr);
	int fecha = consola.convertirCadenaANumero(fechaStr);
	if (fechaStr.length() != 8 || fecha < 0) {
	    cout << "Formato de fecha invalido. Debe ser AAAAMMDD.\n";
	    return;
	}
	
	int anio = fecha / 10000;
	int mes = (fecha / 100) % 100;
	int dia = fecha % 100;
	
	bool fechaValida = true;
	if (anio < 2000 || anio > 2100) fechaValida = false;
	if (mes < 1 || mes > 12) fechaValida = false;
	if (dia < 1) fechaValida = false;
	
	int diasPorMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	// Verificamos si es año bisiesto
	if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) diasPorMes[1] = 29;
	
	if (mes >= 1 && mes <= 12 && dia > diasPorMes[mes - 1]) fechaValida = false;
	
	if (!fechaValida) {
	    cout << "Fecha invalida. Asegurate de que sea real y valida.\n";
	    return;
	}
	
	venta.setFechaNota(fecha);


    while (true) {
        string clave;
        cout << "\nIngrese clave del producto (o X para terminar): ";
        getline(cin, clave);
        if (clave == "X" || clave == "x"){
        	break;
		}

        Producto* producto = gestor.buscarProducto(clave);
        if (producto == nullptr) {
            cout << "Producto no encontrado.\n";
            continue;
        }

        cout << "Producto encontrado: " << producto->getNombre() << ", Precio: $" << producto->getPrecio() << ", Existencia: " << producto->getExistencia() << "\n";
        string cantidadStr;
        cout << "Cantidad a vender: ";
        getline(cin, cantidadStr);
        int cantidad = consola.convertirCadenaANumero(cantidadStr);

        if (cantidad <= 0 || cantidad > producto->getExistencia()) {
            cout << "Cantidad invalida o insuficiente.\n";
            continue;
        }

        float subTotal = cantidad * producto->getPrecio();
        Carrito item;
        item.setClaveProducto(consola.convertirCadenaANumero(producto->getClave()));
        item.setCantidadProducto(cantidad);
        item.setSubTotal(subTotal);

        venta.agregarItem(item);

        // Restar existencia al producto
        producto->setExistencia(producto->getExistencia() - cantidad);

        cout << "Item agregado. Subtotal: $" << subTotal << "\n";
    }

    venta.calcularTotal();
    cout << "\nTOTAL DE LA VENTA: $" << venta.getTotal() << "\n";

    gestor.registrarVenta(venta);
}


void Sistema::guardarVentas() {
    ofstream archivo(archivoVentas);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir archivo ventas para guardar.\n";
        return;
    }

    archivo << "# REGISTRO DE VENTAS\n";
    archivo << "NOTA | FECHA | PRODUCTOS (clave-cantidad-subtotal) | TOTAL\n";
    archivo << "---------------------------------------------------------\n";
	const vector<Venta>& ventas = gestor.obtenerVentas();

    if (ventas.size() == 0) {
        archivo << "<<<<<<LISTA VACIA, AGREGUE PRODUCTOS DESDE EL MENU>>>>>>\n";
    }
    else {
		for (int i = 0; i < ventas.size(); i++) {
		    Venta v = ventas[i];
		    archivo << v.getNumeroNota() << " | " << v.getFechaNota() << " | ";
		
		    const vector<Carrito>& items = v.getItems();
		    for (int j = 0; j < items.size(); j++) {
		        archivo << items[j].getClaveProducto() << "-" << items[j].getCantidadProducto() << "-" << items[j].getSubTotal();
		        if (j < items.size() - 1) archivo << ", ";
		    }
		    archivo << " | " << v.getTotal() << "\n";
		}
    }
    archivo.close();
}

void Sistema::menuPrincipal() {
    short opc;
    do {
        pantalla.mostrarMenuPrincipal();
        cin >> opc;
        cin.ignore();
        consola.limpiarConsola();
        switch (opc) {
        case 1:
            gestor.agregarProducto();
            guardarProductos();
            consola.esperarEnter();
            consola.limpiarConsola();
            break;
        case 2:
            realizarVenta(); 
		    guardarVentas(); 
		    guardarProductos(); 
		    consola.esperarEnter();
		    consola.limpiarConsola();
		    break;
        case 3:
            menuProductos();
            break;
        case 4:
            menuVentas();
            break;
        case 5:
            guardarProductos();
            guardarVentas();
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion invalida, intente de nuevo.\n";
            consola.esperarEnter();
            consola.limpiarConsola();
            break;
        }
    } while (opc != 5);
}

void Sistema::menuProductos() {
    short opc;
    do {
        pantalla.mostrarMenuProductos();
        cin >> opc;
        cin.ignore();
        consola.limpiarConsola();
        switch (opc) {
        case 1:
            gestor.agregarProducto();
            guardarProductos();
            consola.esperarEnter();
            consola.limpiarConsola();
            break;
        case 2: {
            string clave;
            cout << "Ingrese clave del producto a eliminar: ";
            getline(cin, clave);
            gestor.borrarProducto(clave);
            guardarProductos();
            consola.esperarEnter();
            consola.limpiarConsola();
            break;
        }
        case 3: {
            string clave;
            cout << "Ingrese clave del producto a actualizar: ";
            getline(cin, clave);
            gestor.actualizarProducto(clave);
            guardarProductos();
            consola.esperarEnter();
            consola.limpiarConsola();
            break;
        }
        case 4:
            gestor.mostrarProductos();
            consola.esperarEnter();
            consola.limpiarConsola();
            break;
		case 5: {
		    string termino;
		    cout << "Ingrese termino de busqueda (clave o nombre, parcial): ";
		    getline(cin, termino);
		    vector<Producto*> resultados = gestor.buscarProductosPorCoincidencia(termino);
		    if (resultados.empty()) {
		        cout << "No se encontraron productos que coincidan.\n";
		    } else {
		        cout << "Productos encontrados:\n";
		        for (Producto* p : resultados) {
		            cout << "- Clave: " << p->getClave() << ", Nombre: " << p->getNombre()
		                 << ", Marca: " << p->getMarca() << ", Existencia: " << p->getExistencia()
		                 << ", Precio: $" << p->getPrecio() << "\n";
		        }
		    }
		    consola.esperarEnter();
		    consola.limpiarConsola();
		    break;
		}
        case 6:
            cout << "Saliendo del gestor de productos...\n";
            break;
        default:
            cout << "Opcion invalida, intente de nuevo.\n";
            consola.esperarEnter();
            consola.limpiarConsola();
            break;
        }
    } while (opc != 6);
}

void Sistema::menuVentas() {
    short opc;
    do {
        pantalla.mostrarMenuVentas();  
        cin >> opc;
        cin.ignore();
        consola.limpiarConsola();

        switch (opc) {
            case 1: { // Mostrar todas las ventas
                const vector<Venta>& ventas = gestor.obtenerVentas();
                if (ventas.empty()) {
                    cout << "No hay ventas registradas.\n";
                } else {
                    for (int i = 0; i < (int)ventas.size(); i++) {
                        Venta v = ventas[i];
                        cout << "Nota: " << v.getNumeroNota() 
                             << " | Fecha: " << v.getFechaNota()
                             << " | Total: $" << v.getTotal() << "\n";
                    }
                }
                consola.esperarEnter();
                break;
            }
            case 2: { // Buscar por número de not
			    string notaStr;
			    cout << "Ingrese numero de nota a buscar: ";
			    getline(cin, notaStr);
			    int nota = consola.convertirCadenaANumero(notaStr);
			    if (nota < 0) {
			        cout << "Numero invalido.\n";
			    } else {
			        Venta* v = gestor.buscarVentaPorNumeroNota(nota);
			        if (v != nullptr) {
			            mostrarDetalleVenta(*v);
			        } else {
			            cout << "Venta no encontrada.\n";
			        }
			    }
			    consola.esperarEnter();
			    break;
            }
            case 3: { // Buscar por fecha
			    string fechaStr;
			    cout << "Ingrese fecha a buscar: ";
			    getline(cin, fechaStr);
			    int fecha = consola.convertirCadenaANumero(fechaStr);
			    if (fecha < 0) {
			        cout << "Fecha invalida.\n";
			    } else {
			        vector<Venta*> resultados = gestor.buscarVentasPorFecha(fecha);
			        if (resultados.empty()) {
			            cout << "No se encontraron ventas para esa fecha.\n";
			        } else {
			            for (Venta* v : resultados) {
			                mostrarDetalleVenta(*v); 
			            }
			        }
			    }
			    consola.esperarEnter();
			    break;
			}
            case 4: {
                cout << "Registro de venta.\n";
                realizarVenta(); 
		    	guardarVentas(); 
		    	guardarProductos(); 
		    	consola.esperarEnter();
		    	consola.limpiarConsola();
                break;
            }
            case 5:
                cout << "Saliendo de gestion de ventas...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
                consola.esperarEnter();
                break;
        }
        consola.limpiarConsola();
    } while (opc != 5);
}

void Gestor::mostrarVentas() {
    if (ventas.size() == 0) {
        cout << "No hay ventas registradas.\n";
        return;
    }
    for (int i = 0; i < (int)ventas.size(); i++) {
        Venta v = ventas[i];
        cout << "Nota: " << v.getNumeroNota() << ", Fecha: " << v.getFechaNota() << ", Total: $" << v.getTotal() << "\n";
    }
}

void Sistema::mostrarDetalleVenta(const Venta& v) {
    cout << "Número Nota: " << v.getNumeroNota() << "\n";
    cout << "Fecha: " << v.getFechaNota() << "\n";
    cout << "Total: $" << v.getTotal() << "\n";
    cout << "Productos:\n";

    const vector<Carrito>& items = v.getItems(); // Ya es const seguro
    if (items.size() == 0) {
        cout << "\t-- Sin productos --\n";
    } else {
        for (int i = 0; i < (int)items.size(); i++) {
            const Carrito& c = items[i];
            cout << "\tClave Producto: " << c.getClaveProducto()
                 << ", Cantidad: " << c.getCantidadProducto()
                 << ", Subtotal: $" << c.getSubTotal() << "\n";
        }
    }
}

