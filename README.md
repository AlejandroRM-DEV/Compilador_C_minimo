# Compilador C mínimo
Proyecto para la materia Seminario de Solución de Problemas de Traductores de Lenguajes II del ciclo CUCEI-UdeG 2016A.

## Gramática soportada
* Ciclos
  - Do...While
  - For
  - While
* Selectivas
  - If
* Funciones (máximo 6 parámetros)
  - Prototipos
  - Llamadas a función
  - Tipos
    - int
    - void
* Variables globales
  - Tipo int
* Expresiones aritméticas
  - Suma 
  - Resta
  - Multiplicación
  - División
  - Modulo
* Expresiones relacionales
  - Mayor
  - Mayor igual
  - Menor
  - Menor igual
  - Igual
  - Diferente
* Expresiones lógicas
  - AND
  - OR
* Operadores unarios
  - Decremento
  - Incremento
  - Negativo
  - Not
  - Positivo
* Operadores posfijos
  - Decremento
  - Incremento

## Fases
* Análisis léxico: 
En esta etapa se realiza la separación del código fuente en tokens, si existen algún toquen invalido para la gramática soportada el proceso de compilación se detiene y si es posible se determina el error.
* Análisis sintáctico: 
Se revisa que el código fuente sea sintácticamente correcto y durante la misma revisión se va creando el árbol sintáctico, si existe algún error el proceso de compilación se detiene y si es posible se determina el error. 
* Análisis semántico: 
Se utiliza el árbol sintáctico para revisar que es semánticamente correcto, por ejemplo, las variables estén declaradas y su alcance sea válido, los parámetros de llamadas a funciones sean los correctos, las expresiones sean válidas: no utilizar void (variable o función) en una operación aritmética, etcétera.
* Generación de código: 
Se genera el código ensamblador con la sintaxis de AT&T.
