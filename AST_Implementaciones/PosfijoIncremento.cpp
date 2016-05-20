#include "../AST_Tipos.h"

PosfijoIncremento::PosfijoIncremento ( Identificador* exp ) {
	this->exp = exp;
}

PosfijoIncremento::~PosfijoIncremento( ) {
	delete exp;
}

TipoDato PosfijoIncremento::analizarTipo() {
	return exp->analizarTipo();
}

string PosfijoIncremento::toString() {
	stringstream ss;
	ss << "<POSFIJO_INCREMENTO>" << endl;

	if ( exp != nullptr ) {
		ss << exp->toString( );
	}
	ss << "</POSFIJO_INCREMENTO>" << endl;
	return ss.str();
}

string PosfijoIncremento::generarCodigo() {
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
    ss << TABULADOR << "addl" << TABULADOR << "$1," << TABULADOR << "%r10d" << endl;
    ss << TABULADOR << "movl" << TABULADOR << "%r10d," << TABULADOR;
    if(pos>=0){
        ss << "-" <<pos << "(%rbp)";
    }else{
        ss << simbolo << "(%rip)";
    }
    ss  << endl;

	return ss.str();
}

bool PosfijoIncremento::analizarTipoConstante() {
	return false;
}

int PosfijoIncremento::evaluar() {
	return 0;
}
