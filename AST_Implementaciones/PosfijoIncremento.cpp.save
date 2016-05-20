#include "../AST_Tipos.h"

PosfijoIncremento::PosfijoIncremento ( Expresion* exp ) {
	this->exp = exp;
}

PosfijoIncremento::~PosfijoIncremento( ) {
	delete exp;
}

TipoDato PosfijoIncremento::analizarTipo() {
	return exp->analizarTipo();
}

string PosfijoIncremento::toString() {
	stringstream ss;
	ss << "<POSFIJO_INCREMENTO>" << endl;

	if ( exp != nullptr ) {
		ss << exp->toString( );
	}
	ss << "</POSFIJO_INCREMENTO>" << endl;
	return ss.str();
}

string PosfijoIncremento::generarCodigo() {
	stringstream ss;

	return ss.str();
}

bool PosfijoIncremento::analizarTipoConstante() {
	return false;
}

int PosfijoIncremento::evaluar() {
	return 0;
}
