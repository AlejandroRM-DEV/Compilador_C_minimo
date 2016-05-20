#include "../AST_Tipos.h"

Identificador::Identificador ( string simbolo ) {
	this->simbolo = simbolo;
}

Identificador::~Identificador() {}

TipoDato Identificador::analizarTipo() {
	return tablaSimbolos->tipoSim ( simbolo );
}

string Identificador::toString() {
	stringstream ss;
	ss << "<ID>" << simbolo << "</ID>" << endl;
	return ss.str();
}

string Identificador::generarCodigo() {
	stringstream ss;
    int pos = manejadorVariables->buscar(simbolo);
    ss << TABULADOR << "movl" << TABULADOR;
    if(pos>=0){
        ss << "-" <<pos << "(%rbp)";
    }else{
        ss << simbolo << "(%rip)";
    }
    ss << "," << TABULADOR << "%eax" << endl;
	return ss.str();
}

bool Identificador::analizarTipoConstante() {
	return false;
}

int Identificador::evaluar() {
	return 0;
}
