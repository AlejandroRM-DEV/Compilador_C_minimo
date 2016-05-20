#include "../AST_Tipos.h"

For::For() {
    pre = nullptr;
    exp = nullptr;
    post = nullptr;
    proposicion = nullptr;
}

For::~For() {
    if( pre != nullptr ) delete pre;
    if( exp != nullptr )  delete exp;
    if( post != nullptr ) delete post;
    delete proposicion;
}

TipoDato For::analizarTipo() {
    if( pre != nullptr && pre->analizarTipo() == T_ERROR ) {
        return T_ERROR;
    }
    if( exp != nullptr && exp->analizarTipo() == T_ERROR ) {
        return T_ERROR;
    }
    if( post != nullptr && post->analizarTipo() == T_ERROR ) {
        return T_ERROR;
    }
    contexto = tablaSimbolos->agregaContextoAnonimo();
    if( proposicion->analizarTipo() == T_ERROR ) {
        return T_ERROR;
    }
    tablaSimbolos->quitaContexto();
    return T_VACIO;
}

string For::toString() {
    stringstream ss;
    ss << "<FOR>" << endl;
    if( pre != nullptr ) ss << pre->toString();
    if( exp != nullptr ) ss << exp->toString();
    if( post != nullptr ) ss << post->toString();
    ss << proposicion->toString( );
    ss << "</FOR>" << endl;
    return ss.str();
}

string For::generarCodigo(){
   stringstream ss, sel, fin;
	sel << "FOR_" << ( ++contadorFor );
	fin << "FIN_FOR_" << ( contadorFor );

    iterativasActivas.push_front(sel.str());

    if( pre != nullptr ){ //for ( XXXXX ; ; )
            ss << pre->generarCodigo();
	}

	ss << sel.str() << ": " << endl;

	if( exp != nullptr ){ //for ( ; XXXXX ; )
        ss << exp->generarCodigo();
        ss << TABULADOR << "cmpl" << TABULADOR << "$1," << TABULADOR << "%eax" << endl;
        ss << TABULADOR << "jl" << TABULADOR << fin.str()  << endl;
	}

	manejadorVariables->agregaContexto ( contexto );
	ss << proposicion->generarCodigo();
	manejadorVariables->quitaContexto();

    if( post != nullptr ){ //for ( ; ; XXXXX )
        ss << post->generarCodigo();
    }

	ss << TABULADOR << "jmp" << TABULADOR << sel.str() << endl;
	ss << fin.str() << ": " << endl;

	iterativasActivas.pop_front();

	return ss.str();
}


void For::buscarVariables() {
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

