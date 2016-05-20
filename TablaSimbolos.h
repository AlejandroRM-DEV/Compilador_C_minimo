#ifndef TABLASIMBOLOS_H_INCLUDED
#define TABLASIMBOLOS_H_INCLUDED

#include <iostream>
#include <deque>
#include <vector>

using namespace std;

enum TipoDef {T_VARIABLE, T_FUNCION};
enum TipoDato {T_INT, T_VOID, T_VACIO, T_ERROR};

class EntradaTS {
private:
public:
    string simbolo;
    TipoDef tipo;
    string contexto;
    TipoDato dato;
    vector<TipoDato> parametros;
    bool esPrototipo;

    EntradaTS( string simbolo, TipoDef tipo, string contexto, TipoDato dato, vector<TipoDato>& parametros, bool esPrototipo ):
         EntradaTS( simbolo, tipo, contexto, dato, esPrototipo ) {
        this->parametros = parametros;
    }

    EntradaTS( string simbolo, TipoDef tipo, string contexto, TipoDato dato, bool esPrototipo ) {
        this->simbolo = simbolo;
        this->tipo = tipo;
        this->contexto = contexto;
        this->dato = dato;
        this->esPrototipo = esPrototipo;
    }
};

class TablaSimbolos {
private:
    vector<EntradaTS*> tabla;
    deque<string> contextos;
    unsigned long anonimos;

public:
    TablaSimbolos() ;
    bool agregarFuncion( string simbolo, TipoDato dato, vector<TipoDato>& parametros, bool esPrototipo  );
    bool agregarVariable( string simbolo, TipoDato dato, bool esPrototipo );
    string agregaContextoAnonimo();
    void agregaContexto( string contexto );
    void quitaContexto() ;
    TipoDato tipoSim( string simbolo );
    bool existe( string simbolo );
    TipoDato existe( string simbolo, vector<TipoDato>& parametros );
    void print() ;
    vector<EntradaTS*> totalVariables(string contexto);
    string contexto();
    bool existeMain();
};


#endif // TABLASIMBOLOS_H_INCLUDED
