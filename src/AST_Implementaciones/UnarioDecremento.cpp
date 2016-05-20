#include "../AST_Tipos.h"

UnarioDecremento::UnarioDecremento( Identificador* exp ) {
    this->exp = exp;
}

UnarioDecremento::~UnarioDecremento( ) {
    delete exp;
}

TipoDato UnarioDecremento::analizarTipo() {
    return exp->analizarTipo();
}

string UnarioDecremento::toString() {
    stringstream ss;
    ss << "<UNARIO_DECREMENTO>" << endl;

    if( exp != nullptr ) {
        ss << exp->toString( );
    }
    ss << "</UNARIO_DECREMENTO>" << endl;
    return ss.str();
}

string UnarioDecremento::generarCodigo(){
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
    ss << TABULADOR << "subl" << TABULADOR << "$1," << TABULADOR << "%r10d" << endl;
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

bool UnarioDecremento::analizarTipoConstante() {
	return false;
}

int UnarioDecremento::evaluar() {
	return 0;
}
