#include "Sintactico.h"

void Sintactico::comprueba ( string simbolo ) {
	if ( tokens.front().first == simbolo ) {
		tokens.pop();
	} else {
		marcarError ( "Se esperaba un: " + simbolo );
	}
}

void Sintactico::comprueba ( Token tipo ) {
	if ( tokens.front().second == tipo ) {
		tokens.pop();
	} else {
		marcarError ( "Se esperaba un: " + etiquetas[tipo] );
	}
}

void Sintactico::marcarError ( string mensaje ) {
	cout << "ERROR: " << tokens.front().first << endl;
	cout << "NOTA:  "  << mensaje << endl;
	error = true;
}

Sintactico::Sintactico ( queue<ParToken> tokens ) {
	error = false;
	this->tokens = tokens;
}

Sintactico::~Sintactico() {}

bool Sintactico::hayError() {
	return error;
}

Nodo* Sintactico::analiza() {
	Nodo* nodo = unidad_traduccion();
	comprueba ( FIN_ENTRADA );
	return nodo;
}

UnidadTraduccion* Sintactico::unidad_traduccion() {
	UnidadTraduccion* ut = new UnidadTraduccion();

	ut->definiciones.push_back ( definicion() );
	unidad_traduccion_prima ( ut );

	return ut;
}

void Sintactico::unidad_traduccion_prima ( UnidadTraduccion* ut ) {
	if ( !error ) {
		if ( tokens.front().second != FIN_ENTRADA ) {
			ut->definiciones.push_back ( definicion() );
			unidad_traduccion_prima ( ut );
		}
	}
}

Definicion* Sintactico::definicion() {
	if ( !error ) {
		Tipo* tipo = especificador_tipo();

		Identificador* id = new Identificador ( tokens.front().first );
		comprueba ( IDENTIFICADOR );

		return definicion_prima ( tipo, id );
	}
	return nullptr;
}

Definicion* Sintactico::definicion_prima ( Tipo* tipo, Identificador* id ) {
	if ( !error ) {
		if ( tokens.front().second == PARENTESIS_IZQ ) {
			tokens.pop();
			DefinicionFuncion* def = new DefinicionFuncion ( tipo, id );
			if ( tokens.front().second == PARENTESIS_DER ) {
				tokens.pop();
				cuerpo_funcion ( def );
			} else {
				lista_param ( def );
				comprueba ( PARENTESIS_DER );
				cuerpo_funcion ( def );
			}
			return def;
		} else {
			DefinicionVariable* def = new DefinicionVariable ( tipo );
			def->asignaciones.push_back ( new Asignacion ( id, declarador_init_prima() ) );
			lista_vars ( def );
			return def;
		}
	}
	return nullptr;
}

void Sintactico::cuerpo_funcion ( DefinicionFuncion* def ) {
	if ( !error ) {
		if ( tokens.front().second == DELIMITADOR ) {
			tokens.pop();
		} else {
			def->cuerpo = proposicion_compuesta();
		}
	}
}

void Sintactico::lista_vars ( DefinicionVariable* dv ) {
	if ( !error ) {
		switch ( tokens.front().second ) {
		case DELIMITADOR:
			tokens.pop();
			break;
		case COMA:
			tokens.pop();
			dv->asignaciones.push_back ( declarador_init() );
			lista_vars ( dv );
			break;
		default:
			marcarError ( "Se esperaba un \";\" o una \",\"" );
		}
	}
}

void Sintactico::lista_de_declaraciones ( vector<Nodo*>& vec ) {
	Tipo* tipo = nullptr;
	DefinicionVariable* def = nullptr;
	if ( !error ) {
		switch ( reservados.find ( tokens.front().first )->second ) {
		case INT:
			tipo = especificador_tipo();
			def = new DefinicionVariable ( tipo );

			def->asignaciones.push_back ( declarador_init() );
			lista_vars ( def );

			vec.push_back ( def );
			lista_de_declaraciones ( vec );

			break;
		case VOID:
			marcarError ( "La variable no puede ser de tipo \"void\", se esperaba un tipo \"int\"" );
			break;
		default:
			break;
		}
	}
}

Asignacion* Sintactico::declarador_init() {
	if ( !error ) {
		Identificador* id = new Identificador ( tokens.front().first );
		comprueba ( IDENTIFICADOR );

		return new Asignacion ( id, declarador_init_prima() );
	}
	return nullptr;
}

Expresion* Sintactico::declarador_init_prima() {
	Expresion* exp = nullptr;

	if ( !error ) {
		if ( tokens.front().second == OP_ASIGNACION ) {
			tokens.pop();
			exp = expresion_de_asignacion();
		}
	}
	return exp;
}

void Sintactico::lista_param ( DefinicionFuncion* def ) {
	if ( !error ) {
		Tipo* tipo = especificador_tipo();
		Identificador* id = new Identificador ( tokens.front().first );
		comprueba ( IDENTIFICADOR );
		def->parametros.push_back ( new Parametro ( tipo, id ) );
		lista_param_prima ( def );
	}
}

void Sintactico::lista_param_prima ( DefinicionFuncion* def ) {
	if ( !error ) {
		if ( tokens.front().second == COMA ) {
			tokens.pop();
			Tipo* tipo = especificador_tipo();
			Identificador* id = new Identificador ( tokens.front().first );
			comprueba ( IDENTIFICADOR );
			def->parametros.push_back ( new Parametro ( tipo, id ) );
			lista_param_prima ( def );
		}
	}
}

Tipo* Sintactico::especificador_tipo() {
	Tipo* exp = nullptr;
	if ( !error ) {
		switch ( reservados.find ( tokens.front().first )->second ) {
		case INT:
		case VOID:
			exp = new Tipo ( tokens.front().first );
			tokens.pop();
			break;
		default:
			marcarError ( "Se esperaba el especificador int o void" );
			break;
		}
	}
	return exp;
}

Expresion* Sintactico::expresion() {
	Expresion* exp = nullptr;
	if ( !error ) {
		exp = expresion_de_asignacion();
		expresion_prima ( exp );
	}
	return exp;
}

/**
*   ¿Realmente se utiliza, donde y como solucionar?
*/
void Sintactico::expresion_prima ( Expresion* &exp ) {
	if ( !error ) {
		if ( tokens.front().second == COMA ) {
			tokens.pop();
			exp = expresion_de_asignacion();
			expresion_prima ( exp );
		}
	}
}

Expresion* Sintactico::expresion_de_asignacion() {
	Expresion* exp = nullptr;
	if ( !error ) {
		exp = expresion_unaria();
		switch ( tokens.front().second ) {
		case OP_ASIGNACION:
			tokens.pop();
			if ( Identificador* dv = dynamic_cast<Identificador*> ( exp ) ) {
				exp = new Asignacion ( dv, expresion_de_asignacion() );
			} else {
				marcarError ( "Se requiere una variable como operando izquierdo de una asignacion" );
			}
			break;
		case OP_MULTIPLICATIVO:
			expresion_multiplicativa_prima ( exp );
		case OP_ADITIVO :
			expresion_aditiva_prima ( exp );
		case OP_RELACIONAL:
			expresion_relacional_prima ( exp );
		case OP_IGUALDAD:
			expresion_de_igualdad_prima ( exp );
		case LOGICO_AND:
			expresion_logica_AND_prima ( exp );
		case LOGICO_OR:
			expresion_logica_OR_prima ( exp );
			break;
		default:
			break;
		}
	}
	return exp;
}

Expresion* Sintactico::expresion_logica_OR() {
	Expresion* exp = nullptr;
	if ( !error ) {
		exp = expresion_logica_AND();
		expresion_logica_OR_prima ( exp );
	}
	return exp;
}

void Sintactico::expresion_logica_OR_prima ( Expresion* &exp ) {
	if ( !error ) {
		if ( tokens.front().second == LOGICO_OR ) {
			tokens.pop();
			exp = new OR ( exp, expresion_logica_AND() );
			expresion_logica_OR_prima ( exp );
		}
	}
}

Expresion* Sintactico::expresion_logica_AND() {
	Expresion* exp = nullptr;
	if ( !error ) {
		exp = expresion_de_igualdad();
		expresion_logica_AND_prima ( exp );
	}
	return exp;
}

void Sintactico::expresion_logica_AND_prima ( Expresion* &exp ) {
	if ( !error ) {
		if ( tokens.front().second == LOGICO_AND ) {
			tokens.pop();
			exp = new AND ( exp, expresion_de_igualdad() );
			expresion_logica_AND_prima ( exp );
		}
	}
}

Expresion* Sintactico::expresion_de_igualdad() {
	Expresion* exp = nullptr;
	if ( !error ) {
		exp = expresion_relacional();
		expresion_de_igualdad_prima ( exp );
	}
	return exp;
}

void Sintactico::expresion_de_igualdad_prima ( Expresion* &exp ) {
	if ( !error ) {
		if ( tokens.front().second == OP_IGUALDAD ) {
			if ( tokens.front().first == "==" ) {
				tokens.pop();
				exp = new Igual ( exp, expresion_relacional() );
			} else {
				tokens.pop();
				exp = new Diferente ( exp, expresion_relacional() );
			}
			expresion_de_igualdad_prima ( exp );
		}
	}
}

Expresion* Sintactico::expresion_relacional() {
	Expresion* exp = nullptr;
	if ( !error ) {
		exp = expresion_aditiva();
		expresion_relacional_prima ( exp );
	}
	return exp;
}

void Sintactico::expresion_relacional_prima ( Expresion* &exp ) {
	if ( !error ) {
		if ( tokens.front().second == OP_RELACIONAL ) {
			if ( tokens.front().first == "<" ) {
				tokens.pop();
				exp = new Menor ( exp, expresion_aditiva() );
			} else if ( tokens.front().first == "<=" ) {
				tokens.pop();
				exp = new MenorIgual ( exp, expresion_aditiva() );
			} else if ( tokens.front().first == ">" ) {
				tokens.pop();
				exp = new Mayor ( exp, expresion_aditiva() );
			} else {
				tokens.pop();
				exp = new MayorIgual ( exp, expresion_aditiva() );
			}
			expresion_relacional_prima ( exp );
		}
	}
}

Expresion* Sintactico::expresion_aditiva() {
	Expresion* exp = nullptr;
	if ( !error ) {
		exp = expresion_multiplicativa();
		expresion_aditiva_prima ( exp );
	}
	return exp;
}

void Sintactico::expresion_aditiva_prima ( Expresion* &exp ) {
	if ( !error ) {
		if ( tokens.front().second == OP_ADITIVO ) {
			if ( tokens.front().first == "+" ) {
				tokens.pop();
				exp = new Suma ( exp, expresion_multiplicativa() );
			} else {
				tokens.pop();
				exp = new Resta ( exp, expresion_multiplicativa() );
			}
			expresion_aditiva_prima ( exp );
		}
	}
}

Expresion* Sintactico::expresion_multiplicativa() {
	Expresion* exp = nullptr;
	if ( !error ) {
		exp = expresion_unaria();
		expresion_multiplicativa_prima ( exp );
	}
	return exp;
}

void Sintactico::expresion_multiplicativa_prima ( Expresion* &exp ) {
	if ( !error ) {
		if ( tokens.front().second == OP_MULTIPLICATIVO ) {
			if ( tokens.front().first == "*" ) {
				tokens.pop();
				exp = new Multiplicacion ( exp, expresion_unaria() );
			} else if ( tokens.front().first == "/" ) {
				tokens.pop();
				exp = new Division ( exp, expresion_unaria() );
			} else {
				tokens.pop();
				exp = new Modulo ( exp, expresion_unaria() );
			}
			expresion_multiplicativa_prima ( exp );
		}
	}
}

Expresion* Sintactico::expresion_unaria() {
	Expresion* exp = nullptr;
	if ( !error ) {
		switch ( tokens.front().second ) {
		case OP_INCREMENTO:
			tokens.pop();
			exp = expresion_unaria() ;
			if ( Identificador* dv = dynamic_cast<Identificador*> ( exp ) ) {
				exp = new UnarioIncremento ( dv );
			} else {
				marcarError ( "Se requiere una variable como operando" );
			}
			break;
		case OP_DECREMENTO:
			tokens.pop();
			exp = expresion_unaria() ;
			if ( Identificador* dv = dynamic_cast<Identificador*> ( exp ) ) {
				exp = new UnarioDecremento ( dv );
			} else {
				marcarError ( "Se requiere una variable como operando" );
			}
			break;
		case OP_ADITIVO:
			if ( tokens.front().first == "+" ) {
				tokens.pop();
				exp = new UnarioPositivo ( expresion_unaria() );
			} else {
				tokens.pop();
				exp = new UnarioNegativo ( expresion_unaria() );
			}
			break;
		case LOGICO_NOT:
			tokens.pop();
			exp = new UnarioNot ( expresion_unaria() );
			break;
		default:
			exp = expresion_posfija();
		}
	}
	return exp;
}

Expresion* Sintactico::expresion_posfija() {
	Expresion* exp = nullptr;
	if ( !error ) {
		exp = expresion_primaria();
		expresion_posfija_prima ( exp );
	}
	return exp;
}

void Sintactico::expresion_posfija_prima ( Expresion* &exp ) {
	if ( !error ) {
		switch ( tokens.front().second ) {
		case OP_INCREMENTO:
			tokens.pop();
			if ( Identificador* dv = dynamic_cast<Identificador*> ( exp ) ) {
				exp = new PosfijoIncremento ( dv );
			} else {
				marcarError ( "Se requiere una variable como operando" );
			}
			expresion_posfija_prima ( exp );
			break;
		case OP_DECREMENTO:
			tokens.pop();
			if ( Identificador* dv = dynamic_cast<Identificador*> ( exp ) ) {
				exp = new PosfijoDecremento ( dv );
			} else {
				marcarError ( "Se requiere una variable como operando" );
			}
			expresion_posfija_prima ( exp );
			break;
		case PARENTESIS_IZQ: {
				tokens.pop();
				LlamadaFuncion* llamada = new LlamadaFuncion ( ( Identificador* ) exp );
				if ( tokens.front().second != PARENTESIS_DER ) {
					lista_expresiones_argumento ( llamada );
				}
				comprueba ( PARENTESIS_DER );
				exp = llamada;
				expresion_posfija_prima ( exp );
			}
		default:
			break;
		}
	}
}

void Sintactico::lista_expresiones_argumento ( LlamadaFuncion* llamada ) {
	if ( error ) { return; }

	llamada->parametros.push_back ( expresion_de_asignacion() );
	lista_expresiones_argumento_prima ( llamada );
}

void Sintactico::lista_expresiones_argumento_prima ( LlamadaFuncion* llamada ) {
	if ( error ) { return; }

	if ( tokens.front().second == COMA ) {
		tokens.pop();
		llamada->parametros.push_back ( expresion_de_asignacion() );
		lista_expresiones_argumento_prima ( llamada );
	}
}

Expresion* Sintactico::expresion_primaria() {
	Expresion* exp = nullptr;
	if ( !error ) {
		switch ( tokens.front().second ) {
		case IDENTIFICADOR:
			exp = new Identificador ( tokens.front().first );
			tokens.pop();
			break;
		case ENTERO:
			exp = new Entero ( tokens.front().first );
			tokens.pop();
			break;
		case PARENTESIS_IZQ:
			tokens.pop();
			exp = expresion();
			comprueba ( PARENTESIS_DER );
			break;
		default:
			marcarError ( "Se esperaba un Identificador, Numero o Parentesis de apertura" );
		}
	}
	return exp;
}

If* Sintactico::proposicion_de_seleccion() {
	If* proposicionIf = nullptr;
	if ( !error ) {
		if ( tokens.front().first == "if" ) {
			proposicionIf = new If();
			tokens.pop();
			comprueba ( PARENTESIS_IZQ );
			proposicionIf->exp = expresion();
			comprueba ( PARENTESIS_DER );
			proposicionIf->proIf = proposicion();
			proposicionIf->proElse = proposicion_de_seleccion_else();
		}
	}
	return proposicionIf;
}

Nodo* Sintactico::proposicion_de_seleccion_else() {
	if ( !error ) {
		if ( tokens.front().first == "else" ) {
			tokens.pop();
			return proposicion();
		}
	}
	return nullptr;
}

Nodo* Sintactico::proposicion() {
	Nodo* p = nullptr;
	if ( !error ) {
		if ( p == nullptr ) { p = proposicion_compuesta(); }
		if ( p == nullptr ) { p = proposicion_de_seleccion(); }
		if ( p == nullptr ) { p = proposicion_de_iteracion(); }
		if ( p == nullptr ) { p = proposicion_de_salto(); }
		/**
		    Las siguiente condiciones provocarian un falso error:

		    (*) '}' Se verifica que exista en proposicion_compuesta() por lista_de_proposiciones()
		    (*) P. Reservada: las unicas palabras reservadas admitidas por las proposiciones ya
		            se contemplaron en las funciones anteriores, si hay una P.R. debe validarla quien
		            llamo a proposicion()
		**/
		if ( tokens.front().second != LLAVE_DER && tokens.front().second != RESERVADO ) {
			if ( p == nullptr ) { p = proposicion_expresion(); }
		}
	}
	return p;
}

ProposicionCompuesta* Sintactico::proposicion_compuesta() {
	ProposicionCompuesta* pc = nullptr;
	vector<Nodo*> vec;
	if ( !error ) {
		if ( tokens.front().second == LLAVE_IZQ ) {
			tokens.pop();
			lista_de_declaraciones ( vec );
			lista_de_proposiciones ( vec );
			pc = new ProposicionCompuesta ( vec );
		}
	}
	return pc;
}

void Sintactico::lista_de_proposiciones ( vector<Nodo*>& vec ) {
	if ( !error ) {
		if ( tokens.front().second == LLAVE_DER ) {
			tokens.pop();
		} else {
			Nodo* p = proposicion();
			if ( p != nullptr ) {
				vec.push_back ( p );
			}
			lista_de_declaraciones ( vec );
			lista_de_proposiciones ( vec );
		}
	}
}

Expresion* Sintactico::proposicion_expresion() {
	Expresion* exp = nullptr;

	if ( !error ) {
		if ( tokens.front().second == DELIMITADOR ) {
			tokens.pop();
		} else {
			exp = expresion();
			comprueba ( DELIMITADOR );
		}
	}
	return exp;
}

Proposicion* Sintactico::proposicion_de_iteracion() {
	if ( error ) { return nullptr; }

	switch ( reservados.find ( tokens.front().first )->second ) {
	case WHILE: {
			tokens.pop();
			While* p = new While();
			comprueba ( PARENTESIS_IZQ );
			p->exp = expresion();
			comprueba ( PARENTESIS_DER );
			p->proposicion = proposicion();
			return p;
		}
	case DO: {
			tokens.pop();
			DoWhile* p = new DoWhile();
			p->proposicion = proposicion_compuesta();
			if ( tokens.front().first == "while" ) {
				tokens.pop();
				comprueba ( PARENTESIS_IZQ );
				p->exp = expresion();
				comprueba ( PARENTESIS_DER );
				comprueba ( DELIMITADOR );
			} else {
				marcarError ( "Se esperaba un \"while\" al termino de un \"do\"" );
				p = nullptr;
			}
			return p;
		}
	case FOR: {
			tokens.pop();
			For* p = new For();
			comprueba ( PARENTESIS_IZQ );
			p->pre = proposicion_expresion();
			p->exp = proposicion_expresion();
			if ( tokens.front().second == PARENTESIS_DER ) {
				tokens.pop();
				p->proposicion = proposicion();
			} else {
				p->post = expresion();
				if ( tokens.front().second == PARENTESIS_DER ) {
					tokens.pop();
					p->proposicion = proposicion();
				} else {
					marcarError ( "Se esperaba un parentesis de cierre" );
				}
			}
			return p;
		}
	default:
		return nullptr;
	}

}

Proposicion*  Sintactico::proposicion_de_salto() {
	if ( error ) { return nullptr; }

	switch ( reservados.find ( tokens.front().first )->second ) {
	case CONTINUE: {
			Continue* p = new Continue();
			tokens.pop();
			comprueba ( DELIMITADOR );
			return p;
		}
	case BREAK: {
			Break* p = new Break();
			tokens.pop();
			comprueba ( DELIMITADOR );
			return p;
		}
	case RETURN: {
			tokens.pop();
			Return* p = new Return();
			if ( tokens.front().second == DELIMITADOR ) {
				tokens.pop();
			} else {
				p->exp = expresion();
				comprueba ( DELIMITADOR );
			}
			return p;
		}
	default:
		return nullptr;
	}
}
