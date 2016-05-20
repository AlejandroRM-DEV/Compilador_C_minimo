#include "ManejadorVariables.h"

void ManejadorVariables::agregar ( vector<EntradaTS*> vars ) {
	for ( EntradaTS* v : vars ) {
		variables.push_back ( v );
	}
}

int ManejadorVariables::buscar ( string simbolo ) {
	int pos;
	for ( string contexto : contextos ) {
            pos = 1;
		for ( EntradaTS* var : variables ) {
			if ( var->simbolo == simbolo && var->contexto == contexto ) {
				return pos * 4;
			}
			pos++;
		}
	}
	return -1;
}

void ManejadorVariables::vaciar() {
	variables.clear();
}

int ManejadorVariables::total() {
	return variables.size();
}

void ManejadorVariables::agregaContexto ( string contexto ) {
	contextos.push_front ( contexto );
}

void ManejadorVariables::quitaContexto() {
	contextos.pop_front();
}

string ManejadorVariables::contexto() {
	return contextos.front();
}
