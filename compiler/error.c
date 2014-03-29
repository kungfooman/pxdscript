/* wig error.c
 *
 * history:
 * 17.10.2000 created, defined yyerror()
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "error.h"

extern char *yytext;

int lineno = 0;

int errors = 0;

void yyerror(const char *format, ...)
{
  va_list argList;
  
  va_start(argList, format);
  vfprintf(stderr, format, argList);
  va_end(argList);
  
  fprintf(stderr, "\n");
  fprintf(stderr, "*** syntax error before %s at line %i\n", yytext, lineno);
  fprintf(stderr, "*** compilation terminated\n");
  
  exit(1);
}

void reportError(int lineno, const char *format, ...)
{
  va_list argList;

  fprintf(stderr, "*** Error: ");
  
  va_start(argList, format);
  vfprintf(stderr, format, argList);
  va_end(argList);
  
  fprintf(stderr, " at line %i\n", lineno);

  errors++;
}

void reportWarning(int lineno, const char *format, ...)
{
  va_list argList;

  fprintf(stderr, "*** Warning: ");
  
  va_start(argList, format);
  vfprintf(stderr, format, argList);
  va_end(argList);
  
  fprintf(stderr, " at line %i\n", lineno);
}

void errorCheck()
{
  if (errors!=0) {
  fprintf(stderr, "*** %i error(s) encountered, compilation terminated\n",errors);
     exit(1);
  }
}
