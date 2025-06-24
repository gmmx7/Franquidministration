#ifndef CONSOLA_H
#define CONSOLA_H
#include <string>
#include <math.h>
#include <vector>
using namespace std;

class Consola {
public:
    static void ocultarCursor();
    static void mostrarCursor();
    static void limpiarConsola();
    static bool esperarEnter();
    bool esNumero(char caracter);
	bool esLetra(char caracter);
	bool esValidoCaracter(char caracter);
	bool entradaValida(const string& entrada);
	int convertirCadenaANumero(const string& entrada);
	char toLowerChar(char c);
	string toLowerString(const string& texto);
	bool contieneSubcadena(const string& texto, const string& subcadena);
	void limpiarBufferEntrada();
	string limpiarEspacios(const string& texto);
	float convertirCadenaAFloat(const string& entrada);
	vector<string> separarPorComas(string linea);

};

#endif
