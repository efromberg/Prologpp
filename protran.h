#ifndef _PROTRAN_H_
#define _PROTRAN_H_

#include "parse.h"

pGoal GOAL(vector<Token>& tok);
pClause CLAUSE(vector<Token>& tok);
pFunc FUNCT(vector<Token>& tok, int& indx);
pFunc LIST(vector<Token>& tok, int& indx, pTerm elemprev);
vector<pTerm> ARGLIST(vector<Token>& tok, int& indx);
vector<pTerm> ELEMS(vector<Token>& tok, int& indx);

pTerm TERM(vector<Token>& tok, int& indx);
bool isTerm(Token tok);
pNum NUMBER(vector<Token>& tok, int& indx);
pVar VARIABLE(vector<Token>& tok, int& indx);
bool isVAR(Token tok);

#endif



