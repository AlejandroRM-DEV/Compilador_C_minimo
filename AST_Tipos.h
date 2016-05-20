#ifndef AST_TIPOS_H_INCLUDED
#define AST_TIPOS_H_INCLUDED

#include <vector>
#include <iostream>
#include <sstream>
#include <deque>

#include "TablaSimbolos.h"
#include "ManejadorVariables.h"

#define TABULADOR "\t"

extern unsigned int contador;
extern unsigned int contadorDoWhile;
extern unsigned int contadorIf;
extern unsigned int contadorFor;
extern unsigned int contadorWhile;
extern TablaSimbolos* tablaSimbolos;
extern ManejadorVariables* manejadorVariables;
extern deque<string> iterativasActivas;
using namespace std;

class Nodo {
	public:
		string simbolo;
		TipoDato dato;

		Nodo() {}
		virtual ~Nodo() {}
		virtual TipoDato analizarTipo() = 0;
		virtual string toString() = 0;
		virtual string generarCodigo() = 0;
};

class Tipo: public Nodo {
	public:
		Tipo ( string simbolo );
		~Tipo();
		TipoDato analizarTipo();
		string toString() ;
		string generarCodigo();
};

class Expresion: public Nodo {
	protected:
	public:
		Expresion* izquierda;
		Expresion* derecha;

		Expresion();
		virtual ~Expresion();
		virtual TipoDato analizarTipo() = 0;
		virtual bool analizarTipoConstante() = 0;
		virtual int evaluar() = 0;
		string toString() = 0;
		string generarCodigo();
};

class Identificador: public Expresion {
	public:
		Identificador ( string simbolo );
		~Identificador();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Entero: public Expresion {
	public:
		Entero ( string simbolo );
		~Entero();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class OR: public Expresion {
	public:
		OR ( Expresion* izquierda, Expresion* derecha );
		~OR();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class AND: public Expresion {
	public:
		AND ( Expresion* izquierda, Expresion* derecha ) ;
		~AND();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Igual: public Expresion {
	public:
		Igual ( Expresion* izquierda, Expresion* derecha );
		~Igual();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Diferente: public Expresion {
	public:
		Diferente ( Expresion* izquierda, Expresion* derecha );
		~Diferente();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Menor: public Expresion {
	public:
		Menor ( Expresion* izquierda, Expresion* derecha );
		~Menor();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class MenorIgual: public Expresion {
	public:
		MenorIgual ( Expresion* izquierda, Expresion* derecha );
		~MenorIgual();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Mayor: public Expresion {
	public:
		Mayor ( Expresion* izquierda, Expresion* derecha );
		~Mayor();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class MayorIgual: public Expresion {
	public:
		MayorIgual ( Expresion* izquierda, Expresion* derecha );
		~MayorIgual();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Suma: public Expresion {
	public:
		Suma ( Expresion* izquierda, Expresion* derecha );
		~Suma();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Resta: public Expresion {
	public:
		Resta ( Expresion* izquierda, Expresion* derecha );
		~Resta();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Multiplicacion: public Expresion {
	public:
		Multiplicacion ( Expresion* izquierda, Expresion* derecha );
		~Multiplicacion();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Division: public Expresion {
	public:
		Division ( Expresion* izquierda, Expresion* derecha );
		~Division();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Modulo: public Expresion {
	public:
		Modulo ( Expresion* izquierda, Expresion* derecha );
		~Modulo();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Asignacion: public Expresion {
	public:
		Identificador* id;
		Expresion* expresion;

		Asignacion ( Identificador* id, Expresion* expresion );
		TipoDato analizarTipo();
		~Asignacion();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class PosfijoIncremento: public Expresion {
	public:
		Identificador* exp;

		PosfijoIncremento ( Identificador* exp );
		~PosfijoIncremento( );
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class PosfijoDecremento: public Expresion {
	public:
		Identificador* exp;

		PosfijoDecremento ( Identificador* exp );
		~PosfijoDecremento( );
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class UnarioIncremento: public Expresion {
	public:
		Identificador* exp;

		UnarioIncremento ( Identificador* exp ) ;
		~UnarioIncremento( );
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class UnarioDecremento: public Expresion {
	public:
		Identificador* exp;

		UnarioDecremento ( Identificador* exp ) ;
		~UnarioDecremento( );
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class UnarioNot: public Expresion {
	public:
		Expresion* exp;

		UnarioNot ( Expresion* exp ) ;
		~UnarioNot( );
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class UnarioNegativo: public Expresion {
	public:
		Expresion* exp;

		UnarioNegativo ( Expresion* exp ) ;
		~UnarioNegativo( );
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class UnarioPositivo: public Expresion {
	public:
		Expresion* exp;

		UnarioPositivo ( Expresion* exp );
		~UnarioPositivo( ) ;
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class Definicion: public Nodo {
	public:
		Tipo* tipo;

		Definicion ( Tipo* tipo );
		virtual ~Definicion();
		virtual TipoDato analizarTipo() = 0;
		virtual string toString() = 0;
		virtual string generarCodigo() = 0;
};

class Parametro: public Nodo {
	public:
		Tipo* tipo;
		Identificador* id;

		Parametro ( Tipo* tipo, Identificador* id );
		~Parametro();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
};

class DefinicionVariable: public Definicion {
	public:
		vector<Asignacion*> asignaciones;

		DefinicionVariable ( Tipo* tipo ) : Definicion ( tipo ) {}

		~DefinicionVariable();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
};

class Proposicion: public Nodo {
	public:
		Proposicion() {}
		virtual ~Proposicion() {}
		virtual string toString() = 0;
		virtual string generarCodigo() = 0;
};

class If: public Proposicion {
	public:
		Expresion* exp;
		Nodo* proIf;
		Nodo* proElse;
		string contextoIf, contextoElse;

		If();
		~If();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		void buscarVariables();
};

class Continue: public Proposicion {
	public:
		Continue();
		~Continue();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
};

class Break: public Proposicion {
	public:
		Break();
		~Break();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
};

class Return: public Proposicion {
	public:
		static bool permiteExpresion;
		Expresion* exp;

		Return();
		~Return();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
};

class ProposicionCompuesta: public Proposicion {
	public:
		vector<Nodo*> cuerpo;

		ProposicionCompuesta ( vector<Nodo*> cuerpo );
		~ProposicionCompuesta() ;
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
};

class DoWhile: public Proposicion {
	public:
		Expresion* exp;
		ProposicionCompuesta* proposicion;
		string contexto;

		DoWhile();
		~DoWhile();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		void buscarVariables();
};

class For: public Proposicion {
	public:
		Expresion* pre;
		Expresion* exp;
		Expresion* post;
		Nodo* proposicion;
		string contexto;

		For();
		~For();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		void buscarVariables();
};

class While: public Proposicion {
	public:
		Expresion* exp;
		Nodo* proposicion;
		string contexto;

		While();
		~While();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		void buscarVariables();
};

class DefinicionFuncion: public Definicion {
	public:
	    static string retornoActivo;
		Identificador* id;
		vector<Parametro*> parametros;
		ProposicionCompuesta* cuerpo;

		DefinicionFuncion ( Tipo* tipo, Identificador* id );
		~DefinicionFuncion();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		int roundUp ( int numToRound, int multiple );
};

class LlamadaFuncion: public Expresion {
	public:
		Identificador* id;
		vector<Expresion*> parametros;

		LlamadaFuncion ( Identificador* id );
		~LlamadaFuncion();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
		bool analizarTipoConstante();
		int evaluar();
};

class UnidadTraduccion: public Nodo {
	public:
		vector<Definicion*> definiciones;

		UnidadTraduccion();
		~UnidadTraduccion();
		TipoDato analizarTipo();
		string toString();
		string generarCodigo();
};

#endif // AST_TIPOS_H_INCLUDED
