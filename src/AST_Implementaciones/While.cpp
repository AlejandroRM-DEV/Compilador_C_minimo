#include "../AST_Tipos.h"

While::While() {
	exp = nullptr;
	proposicion = nullptr;
}

While::~While() {
	delete exp;
	delete proposicion;
}

TipoDato While::analizarTipo() {
	if ( exp->analizarTipo() == T_ERROR ) {
		return T_ERROR;
	}
	contexto =  tablaSimbolos->agregaContextoAnonimo();
	if ( proposicion->analizarTipo() == T_ERROR ) {
		return T_ERROR;
	}
	tablaSimbolos->quitaContexto();
	return T_VACIO;
}

string While::toString() {
	stringstream ss;
	ss << "<WHILE>" << endl;
	ss << "<EXPRESION>" << endl;
	ss << exp->toString();
	ss << "</EXPRESION>" << endl;
	ss << proposicion->toString( );
	ss << "</WHILE>" << endl;
	return ss.str();
}

string While::generarCodigo() {
	stringstream ss, sel, fin;
	sel << "WHILE_" << ( ++contadorWhile );
	fin << "FIN_WHILE_" << ( contadorWhile );

    iterativasActivas.push_front(sel.str());

	ss << sel.str() << ": " << endl;
	ss << exp->generarCodigo();
	ss << TABULADOR << "cmpl" << TABULADOR << "$1," << TABULADOR << "%eax" << endl;
	ss << TABULADOR << "jl" << TABULADOR << fin.str()  << endl;
	manejadorVariables->agregaContexto ( contexto );
	ss << proposicion->generarCodigo();
	manejadorVariables->quitaContexto();
	ss << TABULADOR << "jmp" << TABULADOR << sel.str() << endl;
	ss << fin.str() << ": " << endl;

	iterativasActivas.pop_front();

	return ss.str();
}


void While::buscarVariables() {
	manejadorVariables->agregaContexto ( contexto );
	manejadorVariables->agregar ( tablaSimbolos->totalVariables ( contexto ) );

	if ( ProposicionCompuesta* cuerpo = dynamic_cast<ProposicionCompuesta*> ( proposicion ) ) {
		for ( Nodo* nodo : cuerpo->cuerpo ) {
			if ( DoWhile* dv = dynamic_cast<DoWhile*> ( nodo ) ) {
				dv->buscarVariables();
			} else if ( For* dv = dynamic_cast<For*> ( nodo ) ) {
				dv->buscarVariables();
			} else if ( If* dv = dynamic_cast<If*> ( nodo ) ) {
				dv->buscarVariables();
			} else if ( While* dv = dynamic_cast<While*> ( nodo ) ) {
				dv->buscarVariables();
			}
		}
	}
	manejadorVariables->quitaContexto();
}
