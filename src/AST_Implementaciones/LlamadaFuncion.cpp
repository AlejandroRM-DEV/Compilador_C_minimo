#include "../AST_Tipos.h"

LlamadaFuncion::LlamadaFuncion ( Identificador* id ) {
	this->id = id;
}
LlamadaFuncion::~LlamadaFuncion() {
	delete id;
	for ( Expresion* p : parametros ) {
		delete p;
	}
}

TipoDato LlamadaFuncion::analizarTipo() {
	vector<TipoDato> tiposParametros;
	for ( Expresion* p : parametros ) {
		tiposParametros.push_back ( p->analizarTipo() );
	}

	return tablaSimbolos->existe ( id->simbolo, tiposParametros );
}

string LlamadaFuncion::toString() {
	stringstream ss;

	ss << "<LLAMADA_FUNCION>" << endl;
	ss << id->toString( );
	for ( Expresion* p : parametros ) {
		ss << p->toString();
	}
	ss << "</LLAMADA_FUNCION>" << endl;

	return ss.str();
}

string LlamadaFuncion::generarCodigo() {
    vector<string> regsParam = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d"};
	vector<string> temp = {"%r10", "%r11", "%r12", "%r13", "%r14", "%r15"};
	deque <string> usados;
	stringstream ss;

    auto itTemp = temp.begin();
    for (auto it = parametros.rbegin(); it != parametros.rend(); ++it){
        ss << TABULADOR << "pushq" << TABULADOR << (*itTemp) << endl;
        ss <<(*it)->generarCodigo();
        ss << TABULADOR << "movl" << TABULADOR << "%eax," << TABULADOR << (*itTemp) << "d" << endl;
        usados.push_front(*itTemp);
        itTemp++;
    }

    auto itParam = regsParam.begin();
    for(string str: usados){
        ss << TABULADOR << "movl" << TABULADOR << str<< "d"  << "," << TABULADOR << (*itParam) << endl;
        itParam++;
    }

    ss << TABULADOR << "call" << TABULADOR << id->simbolo << endl;
    while(!usados.empty()){
        ss << TABULADOR << "popq" << TABULADOR << usados.front() << endl;
        usados.pop_front();
    }

	return ss.str();
}

bool LlamadaFuncion::analizarTipoConstante() {
	return false;
}

int LlamadaFuncion::evaluar() {
	return 0;
}
