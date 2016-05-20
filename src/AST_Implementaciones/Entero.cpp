#include "../AST_Tipos.h"

Entero::Entero ( string simbolo ) {
	this->simbolo = simbolo;
}

Entero::~Entero() {}

TipoDato Entero::analizarTipo() {
	return T_INT;
}

string Entero::toString() {
	stringstream ss;
	ss << "<ENTERO>" << simbolo << "</ENTERO>" << endl;
	return ss.str();
}

string Entero::generarCodigo() {
	stringstream ss;
	ss << TABULADOR << "movl " << TABULADOR << "$" << simbolo << "," << TABULADOR << "%eax" << endl;
	return ss.str();
}

bool Entero::analizarTipoConstante() {
	return true;
}

int Entero::evaluar() {
	istringstream iss ( simbolo );
	int valor;
	iss >> valor;
	return valor;
}
