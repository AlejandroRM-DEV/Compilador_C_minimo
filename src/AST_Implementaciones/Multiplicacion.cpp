#include "../AST_Tipos.h"

Multiplicacion::Multiplicacion ( Expresion* izquierda, Expresion* derecha ) {
	simbolo = "*";
	this->izquierda = izquierda;
	this->derecha = derecha;
}

Multiplicacion::~Multiplicacion() {}

TipoDato Multiplicacion::analizarTipo() {
	if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
		return izquierda->analizarTipo();
	} else {
		return T_ERROR;
	}
}

string Multiplicacion::toString() {
	stringstream ss;
	ss << "<MULTIPLICACION>" << endl;
	if ( izquierda != nullptr ) {
		ss << izquierda->toString( );
	}
	if ( derecha != nullptr ) {
		ss << derecha->toString( );
	}
	ss << "</MULTIPLICACION>" << endl;
	return ss.str();
}

string Multiplicacion::generarCodigo() {
	stringstream ss;
    ss << TABULADOR << "pushq" << TABULADOR << "%rbx" << endl;
	ss << izquierda->generarCodigo();
	ss << TABULADOR << "movl" << TABULADOR << "%eax," << TABULADOR << "%ebx" << endl;
	ss << derecha->generarCodigo();
	ss << TABULADOR << "xchgl" << TABULADOR << " %eax," << TABULADOR << " %ebx" << endl;
    ss << TABULADOR << "imul" << TABULADOR << "%ebx" << endl;
	ss << TABULADOR << "popq" << TABULADOR << "%rbx" << endl;
	return ss.str();
}

bool Multiplicacion::analizarTipoConstante() {
	return ( izquierda->analizarTipoConstante() &&  derecha->analizarTipoConstante() );
}

int Multiplicacion::evaluar() {
	return izquierda->evaluar() * derecha->evaluar();
}
