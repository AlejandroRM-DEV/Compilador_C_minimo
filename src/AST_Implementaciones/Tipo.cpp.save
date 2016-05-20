#include "../AST_Tipos.h"

Tipo::Tipo( string simbolo ) {
    this->simbolo = simbolo;
}

Tipo::~Tipo() {}

TipoDato Tipo::analizarTipo() {
    if( simbolo == "int" ) {
        return T_INT;
    } else {
        return T_VOID;
    }
}

string Tipo::toString() {
    stringstream ss;
    ss << "<TIPO>" << simbolo << "</TIPO>" << endl;
    return ss.str();
}
