#include "Consola.h"
#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;

void Consola::ocultarCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Consola::mostrarCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void Consola::limpiarConsola() {
    system("cls");  // Más compatible con Windows que ANSI (\033[H\033[J)
}

bool Consola::esperarEnter() {
    ocultarCursor();
    while (_getch() != 13) {
        // Esperando ENTER
    }
    mostrarCursor();
    return true;
}

//Entrada a consola
bool Consola::esNumero(char caracter){
	return caracter >= '0' && caracter <= '9';
}

bool Consola::esLetra(char caracter){
	return (caracter >= 'A' && caracter <= 'Z') || (caracter >= 'a' && caracter <= 'z');
}

bool Consola::esValidoCaracter(char caracter){
	return esNumero(caracter) || esLetra(caracter) || caracter == ' ' || caracter == '\n';
}

// Devuelve true si la cadena es válida (sin símbolos raros)
bool Consola::entradaValida(const string& entrada){
	for (int i = 0; i < entrada.size(); i++){
		if (!esValidoCaracter(entrada[i])){
			return false;
		}
	}
	return true;
}

int Consola::convertirCadenaANumero(const string& entrada){
	int resultado = 0;
	for (int i = 0; i < entrada.size(); i++){
		if (esNumero(entrada[i])){
			resultado = resultado * 10 + (entrada[i] - '0');
		}else if (entrada[i] != ' '){
			return -1; // Error si contiene letras o caracteres inválidos
		}
	}
	return resultado;
}

char Consola::toLowerChar(char c){
	if (c >= 'A' && c <= 'Z') return c + 32;
	return c;
}

string Consola::toLowerString(const string& texto){
	string resultado = texto;
	for (int i = 0; i < resultado.size(); i++){
		resultado[i] = toLowerChar(resultado[i]);
	}
	return resultado;
}

bool Consola::contieneSubcadena(const string& texto, const string& subcadena) {
	int n = texto.size();
	int m = subcadena.size();

	if (m == 0 || m > n){
		return false;
	}
	for (int i = 0; i <= n - m; i++) {
		bool coincide = true;
		for (int j = 0; j < m; j++) {
			if (toLowerChar(texto[i + j]) != toLowerChar(subcadena[j])) {
				coincide = false;
				break;
			}
		}
		if (coincide){
			return true;
		}
	}
	return false;
}

void Consola::limpiarBufferEntrada() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Vaciar buffer
    }
}

string Consola::limpiarEspacios(const string& texto) {
    string resultado = texto;
    while (!resultado.empty() && resultado.front() == ' ') resultado.erase(0, 1);
    while (!resultado.empty() && resultado.back() == ' ') resultado.pop_back();
    return resultado;
}

float Consola::convertirCadenaAFloat(const string& entrada) {
    int parteEntera = 0, parteDecimal = 0, decimales = 0;
    bool parteDecimalActiva = false;
    bool valido = true;

    for (char c : entrada) {
        if (c == '.') {
            if (parteDecimalActiva) return -1; // Dos puntos decimales → inválido
            parteDecimalActiva = true;
            continue;
        }
        if (c < '0' || c > '9') return -1;
        if (!parteDecimalActiva) {
            parteEntera = parteEntera * 10 + (c - '0');
        } else {
            parteDecimal = parteDecimal * 10 + (c - '0');
            decimales++;
        }
    }

    float resultado = parteEntera + (parteDecimal / pow(10, decimales));
    return resultado;
}


