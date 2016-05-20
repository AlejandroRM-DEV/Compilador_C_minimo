#include "../AST_Tipos.h"

Modulo::Modulo( Expresion* izquierda, Expresion* derecha ) {
    simbolo = "%";
    this->izquierda = izquierda;
    this->derecha = derecha;
}

Modulo::~Modulo() {}

TipoDato Modulo::analizarTipo() {
    if( izquierda->analizarTipo() == derecha->analizarTipo() ) {
        return izquierda->analizarTipo();
    } else {
        return T_ERROR;
    }
}

string Modulo::toString() {
    stringstream ss;
    ss << "<MODULO>" << endl;
    if( izquierda != nullptr ) {
        ss << izquierda->toString( );
    }
    if( derecha != nullptr ) {
        ss << derecha->toString( );
    }
    ss << "</MODULO>" << endl;
    return ss.str();
}

string Modulo::generarCodigo(){
    stringstream ss;
    ss << TABULADOR << "pushq" << TABULADOR << "%rbx" << endl;
	ss << izquierda->generarCodigo();
	ss << TABULADOR << "movl" << TABULADOR << "%eax," << TABULADOR << "%ebx" << endl;
	ss << derecha->generarCodigo();
	ss << TABULADOR << "xchgl" << TABULADOR << " %eax," << TABULADOR << " %ebx" << endl;
	ss << TABULADOR << "xor" << TABULADOR << "%rdx," << TABULADOR << "%rdx" << endl;
    ss << TABULADOR << "idiv" << TABULADOR << "%ebx" << endl;
    ss << TABULADOR << "movl" << TABULADOR << "%edx,"<<TABULADOR << "%eax"<<endl;
	ss << TABULADOR << "popq" << TABULADOR << "%rbx" << endl;
    return ss.str();
}

bool Modulo::analizarTipoConstante() {
	return ( izquierda->analizarTipoConstante() &&  derecha->analizarTipoConstante() );
}

int Modulo::evaluar() {
	return izquierda->evaluar() % derecha->evaluar();
}
