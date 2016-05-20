#include "../AST_Tipos.h"

Suma::Suma ( Expresion* izquierda, Expresion* derecha ) {
	simbolo = "+";
	this->izquierda = izquierda;
	this->derecha = derecha;
}

Suma::~Suma() {}

TipoDato Suma::analizarTipo() {
	if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
		return izquierda->analizarTipo();
	} else {
		return T_ERROR;
	}
}

string Suma::toString() {
	stringstream ss;
	ss << "<SUMA>" << endl;
	if ( izquierda != nullptr ) {
		ss << izquierda->toString( );
	}
	if ( derecha != nullptr ) {
		ss << derecha->toString( );
	}
	ss << "</SUMA>" << endl;
	return ss.str();
}

string Suma::generarCodigo() {
	stringstream ss;
	ss << TABULADOR << "pushq" << TABULADOR << "%rbx" << endl;
	ss << izquierda->generarCodigo();
	ss << TABULADOR << "movl" << TABULADOR << "%eax," << TABULADOR << "%ebx" << endl;
	ss << derecha->generarCodigo();
	ss << TABULADOR << "addl" << TABULADOR << "%eax," << TABULADOR << "%ebx" << endl;
	ss << TABULADOR << "movl" << TABULADOR << "%ebx," << TABULADOR << "%eax" << endl;
	ss << TABULADOR << "popq" << TABULADOR << "%rbx" << endl;
	return ss.str();
}

bool Suma::analizarTipoConstante() {
	return ( izquierda->analizarTipoConstante() &&  derecha->analizarTipoConstante() );
}

int Suma::evaluar() {
	return izquierda->evaluar() + derecha->evaluar();
}
