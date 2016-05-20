#include "../AST_Tipos.h"

string DefinicionFuncion::retornoActivo = "";

DefinicionFuncion::DefinicionFuncion ( Tipo* tipo, Identificador* id ) : Definicion ( tipo ) {
	this->id = id;
	cuerpo = nullptr;
}
DefinicionFuncion::~DefinicionFuncion() {
	delete id;
	for ( Parametro* p : parametros ) {
		delete p;
	}
	if ( cuerpo != nullptr ) {
		delete cuerpo;
	}
}

TipoDato DefinicionFuncion::analizarTipo() {
	vector<TipoDato> tiposParametros;

	for ( Parametro* p : parametros ) {
		tiposParametros.push_back ( p->analizarTipo() );
	}

	if(!tablaSimbolos->agregarFuncion ( id->simbolo, tipo->analizarTipo(), tiposParametros, cuerpo == nullptr )){
        return T_ERROR;
	}
	tablaSimbolos->agregaContexto ( id->simbolo );

	if ( tipo->analizarTipo() == T_INT ) {
		Return::permiteExpresion = true;
	} else {
		Return::permiteExpresion = false;
	}

	for ( Parametro* p : parametros ) {
		tablaSimbolos->agregarVariable ( p->id->simbolo, p->tipo->analizarTipo(), cuerpo == nullptr );
	}

	if ( cuerpo != nullptr ) {
		if ( cuerpo->analizarTipo( ) == T_ERROR ) {
			return T_ERROR;
		}
	}

	tablaSimbolos->quitaContexto();
	return T_VACIO;
}

string DefinicionFuncion::toString() {
	stringstream ss;

	ss << "<DEFINICION_FUNCION>" << endl;
	ss << tipo->toString();
	ss << id->toString();
	for ( Parametro* p : parametros ) {
		ss << p->toString();
	}
	if ( cuerpo != nullptr ) {
		ss << cuerpo->toString( );
	}
	ss << "</DEFINICION_FUNCION>" << endl;

	return ss.str();
}

int DefinicionFuncion::roundUp ( int numToRound, int multiple ) {
	return ( ( numToRound + multiple - 1 ) / multiple ) * multiple;
}

string DefinicionFuncion::generarCodigo() {
	string regsParam[] = {"%edi", "%esi", "%edx", "%ecx", "%r8d", "%r9d"};
	int totalVars;
	int pilaDecremento = -4;
	int pilaIncremento = 16;
	stringstream ss;

    DefinicionFuncion::retornoActivo = "retorno_" + id->simbolo;
	manejadorVariables->vaciar();
	manejadorVariables->agregaContexto ( id->simbolo );
	manejadorVariables->agregar ( tablaSimbolos->totalVariables (id->simbolo ) );

    for ( Nodo* nodo : cuerpo->cuerpo ) {
		if ( DoWhile* dv = dynamic_cast<DoWhile*> ( nodo ) ) {
			dv->buscarVariables();
		} else if ( For* dv = dynamic_cast<For*> ( nodo ) ) {
			dv->buscarVariables();
		} else if ( If* dv = dynamic_cast<If*> ( nodo ) ) {
			dv->buscarVariables();
		} else if ( While* dv = dynamic_cast<While*> ( nodo ) ) {
			dv->buscarVariables();
		}
	}

	totalVars = manejadorVariables->total();

	ss << id->simbolo << ":" << endl;
	ss << TABULADOR << "pushq" << TABULADOR << "%rbp" << endl;
	ss << TABULADOR << "movq" << TABULADOR << "%rsp," << TABULADOR << "%rbp" << endl;
	ss << TABULADOR << "subq" << TABULADOR << "$" << roundUp ( totalVars * 4,
	        16 ) << "," << TABULADOR << "%rsp" << endl;
	for ( unsigned int i = 0; i < parametros.size(); i++ ) {
		switch ( i ) {
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			ss << TABULADOR << "movl" << TABULADOR << regsParam[i] << "," << TABULADOR << pilaDecremento <<
			   "(%rbp)" << endl;
			pilaDecremento -= 4;
			break;
		default:
			ss << TABULADOR << "movl" << TABULADOR << pilaIncremento << "(%rbp)," << TABULADOR << "%eax" <<
			   endl;
			ss << TABULADOR << "movl" << TABULADOR << "%eax," << TABULADOR  << pilaDecremento << "(%rbp)" <<
			   endl;
			pilaDecremento -= 4;
			pilaIncremento += 4;
			break;
		}
	}

	if ( cuerpo != nullptr ) {
		ss << cuerpo->generarCodigo();
	}

	ss << DefinicionFuncion::retornoActivo << ":" << endl;
	ss << TABULADOR << "movq" << TABULADOR << "%rbp," << TABULADOR << "%rsp" << endl;
	ss << TABULADOR << "popq" << TABULADOR << "%rbp" << endl;
	ss << TABULADOR << "ret" << endl;
	ss << endl;

	manejadorVariables->quitaContexto();

	return ss.str();
}
