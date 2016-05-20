#include "TablaSimbolos.h"

#include <sstream>
#include <iomanip>

TablaSimbolos::TablaSimbolos() {
	anonimos = 0;
}

bool TablaSimbolos::agregarFuncion ( string simbolo, TipoDato dato, vector<TipoDato>& parametros,
                                     bool esPrototipo ) {
	if ( !existe ( simbolo ) ) {
		tabla.push_back ( new EntradaTS ( simbolo, T_FUNCION, contextos.front(), dato, parametros,
		                                  esPrototipo ) );
		return true;
	} else {
		for ( EntradaTS* e : tabla ) {
			if ( ( e->simbolo == simbolo ) && ( e->tipo == TipoDef::T_FUNCION ) && ( e->esPrototipo ) ) {
				if ( e->parametros == parametros ) {
					e->esPrototipo = false;
					return true;
				} else {
					cout << "La definicion " << simbolo << " no concuerda con parametros del prototipo" << endl;
					return false;
				}
			}
		}
		cout << "Multiple declaracion de " << simbolo << endl;
		return false;
	}
}

bool TablaSimbolos::agregarVariable ( string simbolo, TipoDato dato, bool esPrototipo ) {
	if ( existe ( simbolo ) ) {
		for ( EntradaTS* e : tabla ) {
			if ( e->contexto == contextos.front() && e->simbolo == simbolo ) {
				if ( e->esPrototipo ) {
					e->esPrototipo = false;
					return true;
				} else {
					cout << "Multiple declaracion de " << simbolo << endl;
					return false;
				}
			}
		}
	}
	tabla.push_back ( new EntradaTS ( simbolo, T_VARIABLE, contextos.front(), dato, esPrototipo ) );
	return true;
}

string TablaSimbolos::agregaContextoAnonimo() {
	stringstream ss;
	ss << "" << ( anonimos++ ) << "_ANON";
	contextos.push_front ( ss.str() );
	return ss.str();
}

void TablaSimbolos::agregaContexto ( string contexto ) {
	contextos.push_front ( contexto );
}

void TablaSimbolos::quitaContexto() {
	contextos.pop_front();
}

string TablaSimbolos::contexto() {
	return contextos.front();
}

TipoDato TablaSimbolos::tipoSim ( string simbolo ) {
	for ( string contexto : contextos ) {
		for ( EntradaTS* e : tabla ) {
			if ( e->contexto == contexto && e->simbolo == simbolo ) {
				return e->dato;
			}
		}
	}
	cout << simbolo << " no declarado en el contexto " << contextos.front() << endl;
	return T_ERROR;
}

bool TablaSimbolos::existe ( string simbolo ) {
	for ( string contexto : contextos ) {
		for ( EntradaTS* e : tabla ) {
			if ( e->contexto == contexto && e->simbolo == simbolo ) {
				return true;
			}
		}
	}
	return false;
}

TipoDato TablaSimbolos::existe ( string simbolo, vector<TipoDato>& parametros ) {
	for ( string contexto : contextos ) {
		for ( EntradaTS* e : tabla ) {
			if ( e->contexto == contexto && e->simbolo == simbolo && e->parametros == parametros ) {
				return e->dato;
			}
		}
	}
	cout << "La llamada a la funcion: " << simbolo << " no concuerda con los parametros" << endl;
	return T_ERROR;
}

void TablaSimbolos::print() {
	stringstream ss;
	string tipoDef[] = {"Variable", "Funcion"};
	string tipoDato[] = {"int", "void"};

	ss << setw ( 40 ) << "Tabla de simbolos" << std::left << endl;
	ss << setw ( 20 )  << "SIMBOLO" << setw ( 10 ) << "TIPO" << setw ( 20 ) << "CONTEXTO" << setw ( 10 )
	   << "T_DATO" << setw ( 10 ) << "PROTOTIPO" << "PARAMETROS" << endl;

	for ( EntradaTS* e : tabla ) {
		ss << setw ( 20 )  << e->simbolo << setw ( 10 ) << tipoDef[e->tipo] << setw ( 20 )
		   << e->contexto << setw ( 10 ) << tipoDato[e->dato] << setw ( 10 ) << e->esPrototipo;
		for ( TipoDato td : e->parametros ) {
			ss << tipoDato[td] << " - ";
		}
		ss << endl;
	}

	cout << ss.str() << endl;
}

vector<EntradaTS*> TablaSimbolos::totalVariables ( string contexto ) {
	vector<EntradaTS*> lista;
	for ( EntradaTS* e : tabla ) {
		if ( e->tipo == T_VARIABLE && e->contexto == contexto ) {
			lista.push_back ( e );
		}
	}
	return lista;
}

bool TablaSimbolos::existeMain() {
	for ( EntradaTS* e : tabla ) {
		if ( e->simbolo == "main" && e->tipo == T_FUNCION && e->contexto == "0_PROGRAMA" ) {
			return true;
		}
	}
	return false;
}
