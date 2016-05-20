#include "../AST_Tipos.h"

ProposicionCompuesta::ProposicionCompuesta( vector<Nodo*> cuerpo ) {
    this->cuerpo = cuerpo;
}

ProposicionCompuesta::~ProposicionCompuesta() {
    for( Nodo* nodo : cuerpo ) {
        delete nodo;
    }
}

TipoDato ProposicionCompuesta::analizarTipo() {
    for( Nodo* n : cuerpo ) {
        if( n->analizarTipo( ) == T_ERROR ) {
            return T_ERROR;
        }
    }
    return T_VACIO;
}

string ProposicionCompuesta::toString() {
    stringstream ss;

    ss << "<PROPOSICION_COMPUESTA>" << endl;
    for( Nodo* n : cuerpo ) {
        ss << n->toString();
    }
    ss << "</PROPOSICION_COMPUESTA>" << endl;
    return ss.str();
}

string ProposicionCompuesta::generarCodigo(){
    stringstream ss;
    for( Nodo* nodo : cuerpo ) {
        ss << nodo->generarCodigo();
    }
    return ss.str();
}
