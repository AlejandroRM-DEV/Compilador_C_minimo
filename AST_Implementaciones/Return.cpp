#include "../AST_Tipos.h"

bool Return::permiteExpresion = true;

Return::Return() {
	simbolo = "return";
	exp = nullptr;
}

Return::~Return() {
	if ( exp != nullptr ) {
		delete exp;
	}
}

TipoDato Return::analizarTipo() {
	if ( exp != nullptr ) {
		if ( permiteExpresion ) {
			return exp->analizarTipo();
		} else {
			return T_ERROR;
		}
	}
	return T_VACIO;
}

string Return::toString() {
	stringstream ss;
	ss << "<RETURN>" << endl;
	if ( exp != nullptr ) {
		ss << exp->toString( );
	}
	ss << " < / RETURN > " << endl;
	return ss.str();
}

string Return::generarCodigo() {
	stringstream ss;
	if ( exp != nullptr ) {
		ss << exp->generarCodigo( );
	}
	ss << TABULADOR << "jmp" << TABULADOR << DefinicionFuncion::retornoActivo << endl;
	return ss.str();
}
