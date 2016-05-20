#ifndef SINTACTICO_H_INCLUDED
#define SINTACTICO_H_INCLUDED

#include <queue>
#include "Constantes.h"
#include "AST_Tipos.h"

class Sintactico {
private:
    bool error;
    queue<ParToken> tokens;
    void comprueba( string simbolo );
    void comprueba( Token tipo );
    void marcarError( string mensaje );

public:
    Sintactico( queue<ParToken> tokens );
    ~Sintactico();
    bool hayError();
    Nodo* analiza();
    UnidadTraduccion* unidad_traduccion();
    void unidad_traduccion_prima( UnidadTraduccion* ut );
    Definicion* definicion();
    Definicion* definicion_prima( Tipo* tipo, Identificador* id );
    void cuerpo_funcion( DefinicionFuncion* def );
    void lista_vars( DefinicionVariable* dv );
    void lista_de_declaraciones( vector<Nodo*>& vec );
    Asignacion* declarador_init();
    Expresion* declarador_init_prima();
    void lista_param( DefinicionFuncion* def );
    void lista_param_prima( DefinicionFuncion* def );
    Tipo* especificador_tipo();
    Expresion* expresion();
    void expresion_prima( Expresion*& exp );
    Expresion* expresion_de_asignacion();
    Expresion* expresion_logica_OR();
    void expresion_logica_OR_prima( Expresion*& exp );
    Expresion* expresion_logica_AND();
    void expresion_logica_AND_prima( Expresion*& exp );
    Expresion* expresion_de_igualdad();
    void expresion_de_igualdad_prima( Expresion*& exp );
    Expresion* expresion_relacional();
    void expresion_relacional_prima( Expresion*& exp );
    Expresion* expresion_aditiva();
    void expresion_aditiva_prima( Expresion*& exp );
    Expresion* expresion_multiplicativa();
    void expresion_multiplicativa_prima( Expresion*& exp );
    Expresion* expresion_unaria();
    Expresion* expresion_posfija();
    void expresion_posfija_prima( Expresion*& exp );
    Expresion* expresion_primaria();
    If* proposicion_de_seleccion();
    Nodo* proposicion_de_seleccion_else();
    Nodo* proposicion();
    ProposicionCompuesta* proposicion_compuesta();
    void lista_de_proposiciones( vector<Nodo*>& vec );
    Expresion*  proposicion_expresion();
    Proposicion*  proposicion_de_iteracion();
    Proposicion*  proposicion_de_salto();
    void lista_expresiones_argumento(LlamadaFuncion* llamada);
    void lista_expresiones_argumento_prima(LlamadaFuncion* llamada);
};

#endif // SINTACTICO_H_INCLUDED
