#include "../AST_Tipos.h"

DefinicionVariable::~DefinicionVariable() {
	for ( Asignacion* a : asignaciones ) {
		delete a;
	}
}

TipoDato DefinicionVariable::analizarTipo() {
	for ( Asignacion* a : asignaciones ) {
		if ( !tablaSimbolos->agregarVariable ( a->id->simbolo, tipo->analizarTipo(), false ) ) {
			return T_ERROR;
		}
		if ( a->expresion != nullptr ) {
			if ( a->analizarTipo( ) == T_ERROR ) {
				return T_ERROR;
			}
			if ( tablaSimbolos->contexto() == "0_PROGRAMA" && !a->analizarTipoConstante() ) {
				cout << "Variables globales solo con constantes" << endl;
				return T_ERROR;
			}
		}
	}
	return T_VACIO;
}
string DefinicionVariable::toString() {
	stringstream ss;

	ss << "<DEFINICION_VARIABLE>" << endl;
	ss << tipo->toString();
	for ( Asignacion* a : asignaciones ) {
		ss << "<ELEMENTO>"  << endl << a->id->toString() << "</ELEMENTO>" << endl;
		if ( a->expresion != nullptr )
		{ ss << a->toString(); }
	}
	ss << "</DEFINICION_VARIABLE>" << endl;


	return ss.str();
}

string DefinicionVariable::generarCodigo() {
	stringstream ss;
	for ( Asignacion* a : asignaciones ) {
		ss << a->generarCodigo();
	}
	return ss.str();
}
