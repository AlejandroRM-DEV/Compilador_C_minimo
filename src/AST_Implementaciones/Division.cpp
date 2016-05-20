#include "../AST_Tipos.h"

Division::Division ( Expresion* izquierda, Expresion* derecha ) {
	simbolo = "/";
	this->izquierda = izquierda;
	this->derecha = derecha;
}

Division::~Division() {}

TipoDato Division::analizarTipo() {
	if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
		return izquierda->analizarTipo();
	} else {
		return T_ERROR;
	}
}

string Division::toString() {
	stringstream ss;
	ss << "<DIVISION>" << endl;
	if ( izquierda != nullptr ) {
		ss << izquierda->toString( );
	}
	if ( derecha != nullptr ) {
		ss << derecha->toString( );
	}
	ss << "</DIVISION>" << endl;
	return ss.str();
}

string Division::generarCodigo() {
	stringstream ss;
	ss << TABULADOR << "pushq" << TABULADOR << "%rbx" << endl;
	ss << izquierda->generarCodigo();
	ss << TABULADOR << "movl" << TABULADOR << "%eax," << TABULADOR << "%ebx" << endl;
	ss << derecha->generarCodigo();
	ss << TABULADOR << "xchgl" << TABULADOR << " %eax," << TABULADOR << " %ebx" << endl;
	ss << TABULADOR << "xor" << TABULADOR << "%rdx," << TABULADOR << "%rdx" << endl;
	ss << TABULADOR << "idiv" << TABULADOR << "%ebx" << endl;
	ss << TABULADOR << "popq" << TABULADOR << "%rbx" << endl;
	return ss.str();
}

bool Division::analizarTipoConstante() {
	return ( izquierda->analizarTipoConstante() &&  derecha->analizarTipoConstante() );
}

int Division::evaluar() {
	return izquierda->evaluar() / derecha->evaluar();
}
