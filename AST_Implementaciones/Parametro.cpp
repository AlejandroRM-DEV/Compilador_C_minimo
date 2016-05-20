#include "../AST_Tipos.h"

Parametro::Parametro( Tipo* tipo, Identificador* id ) {
    this->tipo = tipo;
    this->id = id;
}

Parametro::~Parametro() {
    delete tipo;
    delete id;
}
TipoDato Parametro::analizarTipo() {
    return tipo->analizarTipo();
}
string Parametro::toString() {
    stringstream ss;

    ss << "<PARAMETRO>" << endl;

    ss << tipo->toString();
    ss << id->toString( );
    ss << "</PARAMETRO>" << endl;
    return ss.str();
}

string Parametro::generarCodigo(){
    stringstream ss;

    return ss.str();
}
