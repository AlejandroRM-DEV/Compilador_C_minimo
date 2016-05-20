#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

#include <iostream>
#include <map>

using namespace std;

typedef pair<string, int> ParToken;

enum ID_Palabara_Reservada {
    AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, DOUBLE, ELSE, ENUM, EXTERN, FLOAT, FOR,
    GOTO, IF, INLINE, INT, LONG, REGISTER, RETURN, SHORT, SIGNED, SIZEOF, STATIC, STRUCT, SWITCH,
    TYPEDEF, UNION, UNSIGNED, VOID, VOLATILE, WHILE
};

const map<string, ID_Palabara_Reservada> reservados = {
    {"auto", AUTO },
    {"break", BREAK },
    {"case", CASE },
    {"char", CHAR },
    {"const", CONST },
    {"continue", CONTINUE },
    {"default", DEFAULT},
    {"do", DO },
    {"double", DOUBLE },
    {"else", ELSE },
    {"enum", ENUM },
    {"extern", EXTERN },
    {"float", FLOAT },
    {"for", FOR },
    {"goto", GOTO},
    {"if", IF },
    {"inline", INLINE },
    {"int", INT },
    {"long", LONG  },
    {"register", REGISTER },
    {"return", RETURN },
    {"short", SHORT},
    {"signed", SIGNED  },
    {"sizeof", SIZEOF },
    {"static", STATIC },
    {"struct", STRUCT },
    {"switch", SWITCH },
    {"typedef", TYPEDEF},
    {"union", UNION },
    {"unsigned", UNSIGNED },
    {"void", VOID },
    {"volatile", VOLATILE },
    {"while", WHILE}
};

enum Token {
    IDENTIFICADOR, RESERVADO, ENTERO, OP_ADITIVO, OP_INCREMENTO, OP_DECREMENTO, OP_MULTIPLICATIVO,
    LOGICO_AND, LOGICO_OR, LOGICO_NOT, OP_ASIGNACION, OP_IGUALDAD, OP_RELACIONAL, COMA, DELIMITADOR,
    COMENTARIO, PARENTESIS_IZQ, PARENTESIS_DER, LLAVE_IZQ, LLAVE_DER, FIN_ENTRADA, ERROR,
    NUMERO_TOKENS
};

const string etiquetas[NUMERO_TOKENS] = {
    [IDENTIFICADOR] = "Identificador",
    [RESERVADO] = "Reservado",
    [ENTERO] = "Entero",
    [OP_ADITIVO] = "OP Aditivo",
    [OP_INCREMENTO] = "OP Incremento",
    [OP_DECREMENTO] = "OP Decremento",
    [OP_MULTIPLICATIVO] = "OP Multiplicativo",
    [LOGICO_AND] = "Logico AND",
    [LOGICO_OR] = "Logico OR",
    [LOGICO_NOT] = "Logico NOT",
    [OP_ASIGNACION] = "OP Asignacion",
    [OP_IGUALDAD] = "OP Igualdad",
    [OP_RELACIONAL] = "OP Relacional",
    [COMA] = "Coma",
    [DELIMITADOR] = "Delimitador",
    [COMENTARIO] = "Comentario",
    [PARENTESIS_IZQ] = "Parentesis izq.",
    [PARENTESIS_DER] = "Parentesis der.",
    [LLAVE_IZQ] = "Llave izq.",
    [LLAVE_DER] = "Llave der.",
    [FIN_ENTRADA] = "Fin de entrada",
    [ERROR] = "Error"
};

#endif // CONSTANTES_H_INCLUDED
