#include "../AST_Tipos.h"

MayorIgual::MayorIgual ( Expresion* izquierda, Expresion* derecha ) {
	simbolo = ">=";
	this->izquierda = izquierda;
	this->derecha = derecha;
}

MayorIgual::~MayorIgual() {}

TipoDato MayorIgual::analizarTipo() {
	if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
		return izquierda->analizarTipo();
	} else {
		return T_ERROR;
	}
}

string MayorIgual::toString() {
	stringstream ss;
	ss << "<MAYOR_IGUAL>" << endl;
	if ( izquierda != nullptr ) {
		ss << izquierda->toString( );
	}
	if ( derecha != nullptr ) {
		ss << derecha->toString( );
	}
	ss << "</MAYOR_IGUAL>" << endl;
	return ss.str();
}

string MayorIgual::generarCodigo() {
	stringstream ss, falso, fin;
	falso << "FALSO_" << ( ++contador );
	fin << "FIN_" << ( contador );

	ss << TABULADOR << "pushq" << TABULADOR << "%rbx" << endl;
	ss << izquierda->generarCodigo();
	ss << TABULADOR << "movl" << TABULADOR << "%eax," << TABULADOR << "%ebx" << endl;
	ss << derecha->generarCodigo();

	ss << TABULADOR << "cmpl" << TABULADOR << "%eax," << TABULADOR << "%ebx" << endl; // ebx >= eax
	ss << TABULADOR << "jl" << TABULADOR << falso.str() << endl;

	ss << TABULADOR << "movl" << TABULADOR << "$1," << TABULADOR << "%eax" << endl;
	ss << TABULADOR << "jmp" << TABULADOR << fin.str() << endl;

	ss << falso.str() << ": " << endl;
	ss << TABULADOR << "movl" << TABULADOR << "$0," << TABULADOR << "%eax" << endl;

	ss << fin.str() << ": " << endl;
	ss << TABULADOR << "popq" << TABULADOR << "%rbx" << endl;
	return ss.str();
}

bool MayorIgual::analizarTipoConstante() {
	return ( izquierda->analizarTipoConstante() &&  derecha->analizarTipoConstante() );
}

int MayorIgual::evaluar() {
	return izquierda->evaluar() >= derecha->evaluar();
}
