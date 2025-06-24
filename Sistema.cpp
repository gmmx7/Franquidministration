/*
#include "Sistema.h"
#include <fstream>
#include <iostream>
using namespace std;

Sistema::Sistema() {}

// Función principal
void Sistema::iniciarSistema() {
	
    cout << "Iniciando sistema..." << endl;

    // Persistencia
    if (existeArchivo(archivoProductos)) {
        cargarProductos();
    } else {
        crearArchivoProductos();
        cout << "\t--> No se encontro el archivo de productos. \n\t   Se creo uno nuevo con formato base." << endl;
    }

    if (existeArchivo(archivoVentas)) {
        cargarVentas();
    } else {
        crearArchivoVentas();
        cout << "\t--> No se encontro el archivo de ventas. \n\t   Se creo uno nuevo con formato base." << endl;
    }
	
	if(consola.esperarEnter()){
		consola.limpiarConsola();
		menuPrincipal();
	}
}

// ------------------- Persistencia ---------------------
bool Sistema::existeArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    return archivo.good();
}

void Sistema::crearArchivoProductos() {
    ofstream archivo(archivoProductos);
    archivo << "CLAVE |     NOMBRE     |     MARCA     | EXISTENCIA | PRECIO\n";
    archivo << "------------------------------------------------------------\n";
    archivo << "  <<<<<<LISTA VACIA, AGREGUE PRODUCTOS DESDE EL MENU>>>>>>  \n";
    archivo.close();
}

void Sistema::crearArchivoVentas() {
    ofstream archivo(archivoVentas);
    archivo << "# REGISTRO DE VENTAS\n";
    archivo << "NOTA | FECHA    | PRODUCTOS (clave-cantidad-subtotal) | TOTAL\n";
    archivo << "-------------------------------------------------------------\n";
    archivo << "  <<<<<<LISTA VACIA, AGREGUE PRODUCTOS DESDE EL MENU>>>>>>  \n";
	archivo.close();
}

void Sistema::cargarProductos() {
    ifstream archivo(archivoProductos);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de productos.\n";
        return;
    }

    string linea;
    // Saltar las primeras 2 líneas de encabezado
    getline(archivo, linea);
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        // Ignorar líneas vacías o que digan "LISTA VACIA"
        if (linea.find("VACIA") != string::npos || linea.empty()) {
            continue;
        }

        Producto nuevo;
        string clave = "", nombre = "", marca = "";
        int existencia = 0;
        float precio = 0.0;

        size_t pos = 0;
        size_t separador = 0;

        // Extraer Clave
        separador = linea.find("|", pos);
        if (separador != string::npos) {
            clave = consola.limpiarEspacios(linea.substr(pos, separador - pos));
            pos = separador + 1;
        }

        // Extraer Nombre
        separador = linea.find("|", pos);
        if (separador != string::npos) {
            nombre = consola.limpiarEspacios(linea.substr(pos, separador - pos));
            pos = separador + 1;
        }

        // Extraer Marca
        separador = linea.find("|", pos);
        if (separador != string::npos) {
            marca = consola.limpiarEspacios(linea.substr(pos, separador - pos));
            pos = separador + 1;
        }

        // Extraer Existencia 
        separador = linea.find("|", pos);
        string existenciaStr = "";
        if (separador != string::npos) {
            existenciaStr = consola.limpiarEspacios(linea.substr(pos, separador - pos));
            existencia = consola.convertirCadenaANumero(existenciaStr);
            pos = separador + 1;
        }

        // Extraer Precio
        string precioStr = consola.limpiarEspacios(linea.substr(pos));
        precio = consola.convertirCadenaAFloat(precioStr);

        // Validaciones mínimas
        if (clave.empty() || nombre.empty() || marca.empty() || existencia < 0 || precio < 0) {
            cout << "Producto mal formado en el archivo, ignorado: " << linea << endl;
            continue;
        }

        nuevo.setClave(clave);
        nuevo.setNombre(nombre);
        nuevo.setMarca(marca);
        nuevo.setExistencia(existencia);
        nuevo.setPrecio(precio);

        gestor.agregarProductoDesdeArchivo(nuevo);
    }

    archivo.close();
    cout << "Productos cargados correctamente desde archivo.\n";
}


void Sistema::guardarProductos() {
	ofstream archivo(archivoProductos);

	if (!archivo.is_open()) {
		cout << "Error al abrir el archivo de productos para guardar.\n";
		return;
	}

	archivo << "CLAVE |     NOMBRE     |     MARCA     | EXISTENCIA | PRECIO\n";
	archivo << "------------------------------------------------------------\n";

	vector<Producto> productos = gestor.getProductos(); // Usaremos este método, lo implementamos abajo

	if (productos.empty()) {
		archivo << "  <<<<<<LISTA VACIA, AGREGUE PRODUCTOS DESDE EL MENU>>>>>>  \n";
	} else {
		for (int i = 0; i < productos.size(); i++) {
			Producto p = productos[i];
			archivo << p.getClave() << " | " 
					<< p.getNombre() << " | "
					<< p.getMarca() << " | "
					<< p.getExistencia() << " | "
					<< p.getPrecio() << "\n";
		}
	}
	archivo.close();
}


void Sistema::cargarVentas() {
    cout << "Ventas cargadas correctamente desde archivo.\n";
}

void Sistema::guardarVentas() {
    cout << "[guardarVentas()] -> Aqui va la logica para guardar ventas en ventas.txt.\n";
}

// ------------------- Menús ---------------------
void Sistema::menuPrincipal() {
	short opc;
	do{
		pantalla.mostrarMenuPrincipal();
		cin >> opc;
		consola.limpiarConsola();
		switch(opc){
			case 1:{//Agregar producto
				Producto p;
				gestor.agregarProducto();
				break;
			}
			case 2:{//Realizar venta
				
				break;
			}
			case 3:{//Gestionar productos
				menuProductos();
				break;
			}
			case 4:{//Gestionar ventas
				
				break;
			}
			case 5:{//Cerrar programa
				cout << "Saliendo del programa..." << endl;
				break;
			}
			default:{
				cout << "Accion no valida, intenta de nuevo.\n" << endl;
				break;
			}
		}
	}while(opc != 5);
}

void Sistema::menuProductos() {
    short opc;
    do{
    	pantalla.mostrarMenuProductos();
    	cin >> opc;
    	
    	consola.limpiarConsola();
    	Producto p;
    	switch(opc){
    		case 1:{
				gestor.agregarProducto();
				guardarProductos();
				break;
			}
			case 2:{ //Borrar producto - relación por clave o nombre
				//gestor.borrarProducto();
				break;
			}
			case 3:{
				//gestor.actualizarProducto();
				break;
			}
			case 4:{
				gestor.mostrarProductos();
				break;
			}
			case 5:{
				//gestor.buscarProducto();
				break;
			}
			case 6:{ //Salir
				cout << "Saliendo del gestor...\n" << endl;
				break;
			}
			default:{
				cout << "Accion no valida, intenta de nuevo\n" << endl;
				break;
			}
		}
	}while(opc != 6);
}

void Sistema::menuVentas() {
    cout << "[menuVentas()] → Aqui ira el menu para gestionar ventas.\n";
}
*/
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

    // Saltar encabezados (2 líneas)
    getline(archivo, linea);
    getline(archivo, linea);

    gestor.limpiarProductos();

    while (getline(archivo, linea)) {
        if (linea == "<<<<<<LISTA VACIA, AGREGUE PRODUCTOS DESDE EL MENU>>>>>>") break;
        // Parsear línea en formato "clave | nombre | marca | existencia | precio"
        string clave, nombre, marca, existenciaStr, precioStr;

        int pos1 = 0, pos2 = 0;
        // clave
        pos2 = linea.find('|', pos1);
        clave = linea.substr(pos1, pos2 - pos1);
        clave = clave.substr(0, clave.find_last_not_of(" \t") + 1);
        clave = clave.substr(clave.find_first_not_of(" \t"));

        pos1 = pos2 + 1;
        // nombre
        pos2 = linea.find('|', pos1);
        nombre = linea.substr(pos1, pos2 - pos1);
        nombre = nombre.substr(0, nombre.find_last_not_of(" \t") + 1);
        nombre = nombre.substr(nombre.find_first_not_of(" \t"));

        pos1 = pos2 + 1;
        // marca
        pos2 = linea.find('|', pos1);
        marca = linea.substr(pos1, pos2 - pos1);
        marca = marca.substr(0, marca.find_last_not_of(" \t") + 1);
        marca = marca.substr(marca.find_first_not_of(" \t"));

        pos1 = pos2 + 1;
        // existencia
        pos2 = linea.find('|', pos1);
        existenciaStr = linea.substr(pos1, pos2 - pos1);
        existenciaStr = existenciaStr.substr(0, existenciaStr.find_last_not_of(" \t") + 1);
        existenciaStr = existenciaStr.substr(existenciaStr.find_first_not_of(" \t"));

        pos1 = pos2 + 1;
        // precio
        precioStr = linea.substr(pos1);
        precioStr = precioStr.substr(0, precioStr.find_last_not_of(" \t") + 1);
        precioStr = precioStr.substr(precioStr.find_first_not_of(" \t"));

        // Convertir existencia y precio
        int existencia = 0;
        float precio = 0.0;

        int i = 0;
        existencia = 0;
        while (i < (int)existenciaStr.size()) {
            if (existenciaStr[i] >= '0' && existenciaStr[i] <= '9') {
                existencia = existencia * 10 + (existenciaStr[i] - '0');
            }
            i++;
        }

        i = 0;
        precio = 0;
        int decimal_pos = precioStr.find('.');
        if (decimal_pos == -1) {
            // sin decimal
            int j = 0;
            while (j < (int)precioStr.size()) {
                if (precioStr[j] >= '0' && precioStr[j] <= '9') {
                    precio = precio * 10 + (precioStr[j] - '0');
                }
                j++;
            }
        }
        else {
            // con decimal
            int j = 0;
            while (j < decimal_pos) {
                if (precioStr[j] >= '0' && precioStr[j] <= '9') {
                    precio = precio * 10 + (precioStr[j] - '0');
                }
                j++;
            }
            float dec_part = 0;
            float div = 10;
            j = decimal_pos + 1;
            while (j < (int)precioStr.size()) {
                if (precioStr[j] >= '0' && precioStr[j] <= '9') {
                    dec_part += (precioStr[j] - '0') / div;
                    div *= 10;
                }
                j++;
            }
            precio += dec_part;
        }

        Producto p(clave, nombre, marca, existencia, precio);
        //productos.push_back(p);
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
        // Aquí debería parsear las ventas, pero para simplificar el ejemplo
        // se puede dejar vacío o agregar después si quieres.
    }
    archivo.close();
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
        for (int i = 0; i < (int)ventas.size(); i++) {
            Venta v = ventas[i];
            // Aquí puedes implementar la forma de escribir la venta en texto,
            // pero para el ejemplo lo dejo simple.
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
            cout << "Funcion para realizar venta aun no implementada.\n";
            consola.esperarEnter();
            consola.limpiarConsola();
            break;
        case 3:
            menuProductos();
            break;
        case 4:
            cout << "Funcion para gestionar ventas aun no implementada.\n";
            consola.esperarEnter();
            consola.limpiarConsola();
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
            string clave;
            cout << "Ingrese clave del producto a buscar: ";
            getline(cin, clave);
            Producto* p = gestor.buscarProducto(clave);
            if (p != nullptr) {
                cout << "Producto encontrado:\n";
                cout << "Clave: " << p->getClave() << "\n";
                cout << "Nombre: " << p->getNombre() << "\n";
                cout << "Marca: " << p->getMarca() << "\n";
                cout << "Existencia: " << p->getExistencia() << "\n";
                cout << "Precio: " << p->getPrecio() << "\n";
            }
            else {
                cout << "Producto no encontrado.\n";
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
    cout << "Gestion de ventas no implementada aun.\n";
}

