/* main file for U1Comp
 *
 * history:
 */

#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "pretty.h"
#include "tree.h"
#include "symbol.h"
#include "weed.h"
#include "type.h"
#include "resource.h"
#include "emit.h"
#include "code.h"
#include "memory.h"
#include "assembler.h"

void yyparse();

struct SCRIPTCOLLECTION *thescriptcollection;


int main(int argc, char **argv)
{
 
  /* debugging */
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);
  
  if(argc < 3){
    printf("Usage: u1comp <infile> <outfile>\n");
    exit(1);
  } 
  else {
    if(freopen(argv[1],"r",stdin) != NULL){
      printf("// Parsing...\n");
      lineno=1;
      yyparse(); /* Build AST */
    }
    else {
      printf("Couldn't open file %s\n",argv[1]);
      exit(1);
    }
  }
  errorCheck();

  printf("// Weeding...\n");
  weedSCRIPTCOLLECTION(thescriptcollection);
  errorCheck();

  printf("// Symbolchecking...\n");
  symSCRIPTCOLLECTION(thescriptcollection);
  errorCheck();

  printf("// Typechecking...\n");
  typeSCRIPTCOLLECTION(thescriptcollection);
  errorCheck();

  /*
  printf("// Prettyprinting...\n");
  prettySCRIPTCOLLECTION(thescriptcollection);
  errorCheck();
  */
  printf("// Resource calculations...\n");
  resSCRIPTCOLLECTION(thescriptcollection);
  errorCheck();

  printf("// Coding...\n");
  codeSCRIPTCOLLECTION(thescriptcollection);
  errorCheck();

  printf("// Emitting (asm)...\n");
  emitSCRIPTCOLLECTION(thescriptcollection);
  errorCheck();
  
  printf("// Assembling...\n");
  AssembleFile(argv[2]);
  
    
 
 return 0;
}
