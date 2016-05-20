#include <iostream>
#include <fstream>

#include "Lexico.h"
#include "Sintactico.h"

using namespace std;

int main() {
	queue<ParToken> tokens;
	Sintactico* sintactico;
	Lexico* lexico;
	string nombre;

	cout << "Nombre archivo: ";
	getline( cin, nombre );
	lexico = new Lexico ( nombre );
	tokens = lexico->dameListaTokens();
	if ( !lexico->hayError() ) {
		cout << "Analisis Lexico: Aceptado" << endl;

		sintactico = new Sintactico ( tokens );
		Nodo*  nodo = sintactico->analiza();

		if ( !sintactico->hayError() ) {
			cout << "Analisis Sintactico: Aceptado" << endl;

			if ( nodo->analizarTipo( ) != T_ERROR ) {
				cout << "Analisis Semantico: Aceptado" << endl;

				ofstream salida ( "salida.asm" );
				tablaSimbolos->print();
				salida << nodo->generarCodigo( );
				//cout << nodo->generarCodigo();
				salida.close();
			} else {
				cout << "Analisis Semantico: Rechazado" << endl;
			}
		} else {
			cout << "Analisis Sintactico: Rechazado" << endl;
		}

		delete sintactico;
		delete nodo;
	} else {
		cout << "Analisis Lexico: Rechazado" << endl;
	}

	delete lexico;
	return 0;
}
