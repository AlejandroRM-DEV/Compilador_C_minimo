#include "../AST_Tipos.h"

Definicion::Definicion( Tipo* tipo ) {
    this->tipo = tipo;
}

Definicion:: ~Definicion() {
    if( tipo != nullptr ) {
        delete tipo;
    };
}
