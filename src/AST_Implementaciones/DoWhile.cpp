#include "../AST_Tipos.h"

DoWhile::DoWhile() {
	exp = nullptr;
	proposicion = nullptr;
}

DoWhile::~DoWhile() {
	delete exp;
	delete proposicion;
}

TipoDato DoWhile::analizarTipo() {
	contexto = tablaSimbolos->agregaContextoAnonimo();
	if ( proposicion->analizarTipo() == T_ERROR ) {
		return T_ERROR;
	}
	if ( exp->analizarTipo() == T_ERROR ) {
		return T_ERROR;
	}
	tablaSimbolos->quitaContexto();
	return T_VACIO;
}

string DoWhile::toString() {
	stringstream ss;
	ss << "<DO_WHILE>" << endl;
	ss << proposicion->toString();
	ss << "<EXPRESION>" << endl;
	ss << exp->toString( );
	ss << "</EXPRESION>" << endl;
	ss << "</DO_WHILE>" << endl;
	return ss.str();
}

string DoWhile::generarCodigo() {
	stringstream ss, sel, fin;
	sel << "DO_WHILE_" << ( ++contadorDoWhile );
	fin << "FIN_DO_WHILE_" << ( contadorDoWhile );

    iterativasActivas.push_front(sel.str());

	ss << sel.str() << ": " << endl;
	manejadorVariables->agregaContexto ( contexto );
	ss << proposicion->generarCodigo();
	manejadorVariables->quitaContexto();

	ss << exp->generarCodigo();
	ss << TABULADOR << "cmpl" << TABULADOR << "$1," << TABULADOR << "%eax" << endl;
	ss << TABULADOR << "jl" << TABULADOR << fin.str()  << endl;
	ss << TABULADOR << "jmp" << TABULADOR << sel.str() << endl;
	ss << fin.str() << ": " << endl;

	iterativasActivas.pop_front();

	return ss.str();
}

void DoWhile::buscarVariables() {
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
