#include "../AST_Tipos.h"

UnarioPositivo::UnarioPositivo( Expresion* exp ) {
    this->exp = exp;
}

UnarioPositivo::~UnarioPositivo( ) {
    delete exp;
}

TipoDato UnarioPositivo::analizarTipo() {
    return exp->analizarTipo();
}

string UnarioPositivo::toString() {
    stringstream ss;
    ss << "<UNARIO_POSITIVO>" << endl;

    if( exp != nullptr ) {
        ss << exp->toString( );
    }
    ss << "</UNARIO_POSITIVO>" << endl;
    return ss.str();
}

string UnarioPositivo::generarCodigo(){
    stringstream ss;
    ss << exp->generarCodigo();
    return ss.str();
}

bool UnarioPositivo::analizarTipoConstante() {
	return true;
}

int UnarioPositivo::evaluar() {
	return exp->evaluar();
}
