#include "../AST_Tipos.h"

Menor::Menor ( Expresion* izquierda, Expresion* derecha ) {
	simbolo = "<";
	this->izquierda = izquierda;
	this->derecha = derecha;
}

Menor::~Menor() {}

TipoDato Menor::analizarTipo() {
	if ( izquierda->analizarTipo() == derecha->analizarTipo() ) {
		return izquierda->analizarTipo();
	} else {
		return T_ERROR;
	}
}

string Menor::toString() {
	stringstream ss;
	ss << "<MENOR>" << endl;
	if ( izquierda != nullptr ) {
		ss << izquierda->toString( );
	}
	if ( derecha != nullptr ) {
		ss << derecha->toString( );
	}
	ss << "</MENOR>" << endl;
	return ss.str();
}

string Menor::generarCodigo() {
	stringstream ss, falso, fin;
	falso << "FALSO_" << ( ++contador );
	fin << "FIN_" << ( contador );

	ss << TABULADOR << "pushq" << TABULADOR << "%rbx" << endl;
	ss << izquierda->generarCodigo();
	ss << TABULADOR << "movl" << TABULADOR << "%eax," << TABULADOR << "%ebx" << endl;
	ss << derecha->generarCodigo();

	ss << TABULADOR << "cmpl" << TABULADOR << "%eax," << TABULADOR << "%ebx" << endl; // ebx < eax
	ss << TABULADOR << "jge" << TABULADOR << falso.str() << endl;

	ss << TABULADOR << "movl" << TABULADOR << "$1," << TABULADOR << "%eax" << endl;
	ss << TABULADOR << "jmp" << TABULADOR << fin.str() << endl;

	ss << falso.str() << ": " << endl;
	ss << TABULADOR << "movl" << TABULADOR << "$0," << TABULADOR << "%eax" << endl;

	ss << fin.str() << ": " << endl;
	ss << TABULADOR << "popq" << TABULADOR << "%rbx" << endl;
	return ss.str();
}

bool Menor::analizarTipoConstante() {
	return ( izquierda->analizarTipoConstante() &&  derecha->analizarTipoConstante() );
}

int Menor::evaluar() {
	return izquierda->evaluar() < derecha->evaluar();
}
