#include "../AST_Tipos.h"

Mayor::Mayor( Expresion* izquierda, Expresion* derecha ) {
    simbolo = ">";
    this->izquierda = izquierda;
    this->derecha = derecha;
}

Mayor::~Mayor() {}

TipoDato Mayor::analizarTipo() {
    if( izquierda->analizarTipo() == derecha->analizarTipo() ) {
        return izquierda->analizarTipo();
    } else {
        return T_ERROR;
    }
}

string Mayor::toString() {
    stringstream ss;
    ss << "<MAYOR>" << endl;
    if( izquierda != nullptr ) {
        ss << izquierda->toString( );
    }
    if( derecha != nullptr ) {
        ss << derecha->toString( );
    }
    ss << "</MAYOR>" << endl;
    return ss.str();
}
