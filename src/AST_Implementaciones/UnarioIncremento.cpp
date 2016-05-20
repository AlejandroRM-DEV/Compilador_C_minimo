#include "../AST_Tipos.h"

UnarioIncremento::UnarioIncremento( Identificador* exp ) {
    this->exp = exp;
}

UnarioIncremento::~UnarioIncremento( ) {
    delete exp;
}

TipoDato UnarioIncremento::analizarTipo() {
    return exp->analizarTipo();
}

string UnarioIncremento::toString() {
    stringstream ss;
    ss << "<UNARIO_INCREMENTO>" << endl;

    if( exp != nullptr ) {
        ss << exp->toString( );
    }
    ss << "</UNARIO_INCREMENTO>" << endl;
    return ss.str();
}

string UnarioIncremento::generarCodigo(){
    stringstream ss;
    int pos = manejadorVariables->buscar(exp->simbolo);

    //Obtiene la variable
    ss << TABULADOR << "movl" << TABULADOR;
    if(pos>=0){
        ss << "-" <<pos << "(%rbp)";
    }else{
        ss << simbolo << "(%rip)";
    }
    ss << "," << TABULADOR << "%r10d" << endl;

    //Incrementa su valor y lo guarda en la variable correspondiente
    ss << TABULADOR << "addl" << TABULADOR << "$1," << TABULADOR << "%r10d" << endl;
    ss << TABULADOR << "movl" << TABULADOR << "%r10d," << TABULADOR;
    if(pos>=0){
        ss << "-" <<pos << "(%rbp)";
    }else{
        ss << simbolo << "(%rip)";
    }
    ss  << endl;

    //Entrega el valor
    ss << TABULADOR << "movl" << TABULADOR << "%r10d," << TABULADOR << "%eax" << endl;

    return ss.str();
}

bool UnarioIncremento::analizarTipoConstante() {
	return false;
}

int UnarioIncremento::evaluar() {
	return 0;
}
