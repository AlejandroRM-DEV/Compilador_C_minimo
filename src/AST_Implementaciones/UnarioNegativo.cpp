#include "../AST_Tipos.h"

UnarioNegativo::UnarioNegativo ( Expresion* exp ) {
	this->exp = exp;
}

UnarioNegativo::~UnarioNegativo( ) {
	delete exp;
}

TipoDato UnarioNegativo::analizarTipo() {
	return exp->analizarTipo();
}

string UnarioNegativo::toString() {
	stringstream ss;
	ss << "<UNARIO_NEGATIVO>" << endl;

	if ( exp != nullptr ) {
		ss << exp->toString( );
	}
	ss << "</UNARIO_NEGATIVO>" << endl;
	return ss.str();
}

string UnarioNegativo::generarCodigo() {
	stringstream ss;
	ss << exp->generarCodigo();
	ss << TABULADOR << "neg" << TABULADOR << "%eax" << endl;
	return ss.str();
}

bool UnarioNegativo::analizarTipoConstante() {
	return true;
}

int UnarioNegativo::evaluar() {
	return -exp->evaluar();
}
