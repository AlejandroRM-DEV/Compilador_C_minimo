#include "../AST_Tipos.h"

AND::AND ( Expresion* izquierda, Expresion* derecha ) {
	simbolo = "&&";
	this->izquierda = izquierda;
	this->derecha = derecha;
}

AND::~AND() {}

TipoDato AND::analizarTipo() {
	if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
		return izquierda->analizarTipo();
	} else {
		return T_ERROR;
	}
}

string AND::toString() {
	stringstream ss;
	ss << "<AND>" << endl;
	if ( izquierda != nullptr ) {
		ss << izquierda->toString( );
	}
	if ( derecha != nullptr ) {
		ss << derecha->toString( );
	}
	ss << "</AND>" << endl;
	return ss.str();
}

string AND::generarCodigo() {
	stringstream ss, fin;
	fin << "FIN_AND_" << ( ++contador );

    ss << TABULADOR << "pushq" << TABULADOR << "%rbx" << endl;

	ss << izquierda->generarCodigo();
	// Si lado izquierdo es falso, producios corto circuito
	ss << TABULADOR << "cmpl" << TABULADOR << "$1," << TABULADOR << "%eax" << endl;
	ss << TABULADOR << "jl" << TABULADOR << fin.str()  << endl;

	ss << derecha->generarCodigo();

	ss << fin.str() << ": " << endl;
	ss << TABULADOR << "popq" << TABULADOR << "%rbx" << endl;
	return ss.str();
}

bool AND::analizarTipoConstante() {
	return ( izquierda->analizarTipoConstante() &&  derecha->analizarTipoConstante() );
}

int AND::evaluar() {
	return izquierda->evaluar() && derecha->evaluar();
}
