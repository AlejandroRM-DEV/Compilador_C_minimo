#include "../AST_Tipos.h"

PosfijoDecremento::PosfijoDecremento( Identificador* exp ) {
    this->exp = exp;
}

PosfijoDecremento::~PosfijoDecremento( ) {
    delete exp;
}

TipoDato PosfijoDecremento::analizarTipo() {
    return exp->analizarTipo();
}

string PosfijoDecremento::toString() {
    stringstream ss;
    ss << "<POSFIJO_DECREMENTO>" << endl;

    if( exp != nullptr ) {
        ss << exp->toString( );
    }
    ss << "</POSFIJO_DECREMENTO>" << endl;
    return ss.str();
}

string PosfijoDecremento::generarCodigo(){
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

    //Entrega el valor
    ss << TABULADOR << "movl" << TABULADOR << "%r10d," << TABULADOR << "%eax" << endl;

    //Incrementa su valor y lo guarda en la variable correspondiente
    ss << TABULADOR << "subl" << TABULADOR << "$1," << TABULADOR << "%r10d" << endl;
    ss << TABULADOR << "movl" << TABULADOR << "%r10d," << TABULADOR;
    if(pos>=0){
        ss << "-" <<pos << "(%rbp)";
    }else{
        ss << simbolo << "(%rip)";
    }
    ss  << endl;

    return ss.str();
}

bool PosfijoDecremento::analizarTipoConstante() {
	return false;
}

int PosfijoDecremento::evaluar() {
	return 0;
}
