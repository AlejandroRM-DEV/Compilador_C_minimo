#include "Lexico.h"

Lexico::Lexico(string nombre) {
    archivo.open( nombre );
    if ( archivo.is_open() ) {
        error = false;
        simbolo = "";
        idTabla = 0;
        tipo = -1;
    } else {
        error = true;
    }
}

Lexico::~Lexico() {
    archivo.close();
}

void Lexico::sigSimbolo() {
    int columna;
    char temp;

    do {
        temp = transicion( archivo.peek() );
        while ( temp == E0 || temp == E1 ) {
            archivo.get( caracter );
            temp = transicion( archivo.peek() );
        }

        estado = Q0;
        simbolo = "";
        error = false;

        while( true ) {
            columna = transicion( archivo.peek() );
            if( salidas[estado][columna] == SI ) {
                break;
            }
            estado = matriz[estado][columna];

            archivo.get( caracter );
            simbolo += caracter;

            if( estado == K ) {
                error = true;
                break;
            }
        }
    } while ( estado == Q22 ); // Ignora comentarios
    fijaTipo( estado );
}

int Lexico::transicion( char c ) {
    if( c == ' ' || c == '\t' || c == '\v' || c == '\f' ) {
        return E0;
    } else if( c == '\r' || c == '\n' ) {
        return E1;
    } else if( ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ) ||  c == '_' ) {
        return E2;
    } else if( c >= '0' && c <= '9' ) {
        return E3;
    } else if( c == '+' ) {
        return E4;
    } else if( c == '-' ) {
        return E5;
    } else if( c == '/'  ) {
        return E6;
    } else if( c == '*' ) {
        return E7;
    } else if( c == '%' ) {
        return E8;
    } else if( c == '&' ) {
        return E9;
    } else if( c == '|' ) {
        return E10;
    } else if( c == '!' ) {
        return E11;
    } else if( c == '=' ) {
        return E12;
    } else if( c == '<' || c == '>' ) {
        return E13;
    } else if( c == ',' ) {
        return E14;
    } else if( c == ';' ) {
        return E15;
    } else if( c == '(' ) {
        return E16;
    } else if( c == ')' ) {
        return E17;
    } else if( c == '{' ) {
        return E18;
    } else if( c == '}' ) {
        return E19;
    } else if( c == EOF ) {
        return E20;
    } else { // RESTO DE ASCII
        return E21;
    }
}


void Lexico::fijaTipo( int estado ) {
    switch( estado ) {
    case Q1:
        if( reservados.find( simbolo ) != reservados.end() ) {
            tipo = RESERVADO;
        } else {
            tipo = IDENTIFICADOR;
        }
        break;
    case Q2:
        tipo = ENTERO;
        break;
    case Q3:
    case Q4:
        tipo = OP_ADITIVO;
        break;
    case Q5:
        tipo = OP_INCREMENTO;
        break;
    case Q6:
        tipo = OP_DECREMENTO;
        break;
    case Q7:
    case Q8:
        tipo = OP_MULTIPLICATIVO;
        break;
    case Q10:
        tipo = LOGICO_AND;
        break;
    case Q12:
        tipo = LOGICO_OR;
        break;
    case Q13:
        tipo = LOGICO_NOT;
        break;
    case Q14:
        tipo = OP_ASIGNACION;
        break;
    case Q15:
        tipo = OP_IGUALDAD;
        break;
    case Q16:
    case Q17:
        tipo = OP_RELACIONAL;
        break;
    case Q18:
        tipo = COMA;
        break;
    case Q19:
        tipo = DELIMITADOR;
        break;
    case Q22:
        tipo = COMENTARIO;
        break;
    case Q24:
        tipo = PARENTESIS_IZQ;
        break;
    case Q25:
        tipo = PARENTESIS_DER;
        break;
    case Q26:
        tipo = LLAVE_IZQ;
        break;
    case Q27:
        tipo = LLAVE_DER;
        break;
    case Q28:
        tipo = FIN_ENTRADA;
        break;
    default:
        tipo = ERROR;
        break;
    }
}

bool Lexico::hayError() {
    return error;
}

bool Lexico::fin() {
    return ( tipo == FIN_ENTRADA ) || hayError();
}

string Lexico::dameSimbolo() {
    return simbolo;
}

int Lexico::dameTipo() {
    return tipo;
}

queue<ParToken> Lexico::dameListaTokens() {
    while( !fin() ) {
        sigSimbolo();
        listaTokens.push ( make_pair(simbolo, tipo) );
    }
    return listaTokens;
}

string Lexico::toString() {
    stringstream ss;

    ss << "[ " << etiquetas[tipo] << " ] [ " << simbolo << " ]";
    return ss.str();
}
