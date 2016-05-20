#include "../AST_Tipos.h"

Resta::Resta ( Expresion* izquierda, Expresion* derecha ) {
	simbolo = "-";
	this->izquierda = izquierda;
	this->derecha = derecha;
}

Resta::~Resta() {}

TipoDato Resta::analizarTipo() {
	if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
		return izquierda->analizarTipo();
	} else {
		return T_ERROR;
	}
}

string Resta::toString() {
	stringstream ss;
	ss << "<RESTA>" << endl;
	if ( izquierda != nullptr ) {
		ss << izquierda->toString( );
	}
	if ( derecha != nullptr ) {
		ss << derecha->toString( );
	}
	ss << "</RESTA>" << endl;
	return ss.str();
}

string Resta::generarCodigo() {
	stringstream ss;
    ss << TABULADOR << "pushq" << TABULADOR << "%rbx" << endl;
	ss << izquierda->generarCodigo();
	ss << TABULADOR << "movl" << TABULADOR << "%eax," << TABULADOR << "%ebx" << endl;
	ss << derecha->generarCodigo();
	ss << TABULADOR << "subl" << TABULADOR << "%eax," << TABULADOR << "%ebx" << endl;
	ss << TABULADOR << "movl" << TABULADOR << "%ebx," << TABULADOR << "%eax" << endl;
	ss << TABULADOR << "popq" << TABULADOR << "%rbx" << endl;
	return ss.str();
}

bool Resta::analizarTipoConstante() {
	return ( izquierda->analizarTipoConstante() &&  derecha->analizarTipoConstante() );
}

int Resta::evaluar() {
	return izquierda->evaluar() - derecha->evaluar();
}
