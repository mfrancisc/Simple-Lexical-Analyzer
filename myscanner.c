#include <stdio.h>
#include "myscanner.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char *names[] = {NULL, "db_type", "db_name", "db_table_prefix", "db_port"};

int main(void) 
{

  int ntoken, vtoken;

  ntoken = yylex();
  while(ntoken) {

    printf("%d\n", ntoken);

    //error
    if(yylex() != COLON) {
      printf("Syntax error in line %d, Expected a ':' but found %s\n", yylineno, yytext);
      return 1;//exit
    }

    //value token
    vtoken = yylex();
    switch(ntoken) {
      case TYPE:
      case NAME:
      case TABEL_PREFIX:
        if(vtoken != IDENTIFIER) {
          printf("Syntax error in line %d, Expected a identifier but found %s\n", yylineno, yytext);
          return 1;//exit
        }
        printf("%s is set to %s\n", names[ntoken], yytext);
        break;
      case PORT:
        if(vtoken != INTEGER) {
          printf("Syntax error in line %d, Expected an integer but found %s\n", yylineno, yytext);
          return 1;//exit
        }
        printf("%s is set to %s\n", names[ntoken], yytext);
        break;
      default:
        printf("Syntax error in line %d\n", yylineno);
    }
    ntoken = yylex();
  }
  return 0;
}
