// protran.cc	translate .pl text into classes


#include "prolog.h"
#include "parse.h"
#include "protran.h"

int debug =0; 		// only this file

pGoal GOAL(vector<Token>& tok)		// body of CLAUSE
{Var::mTVar.clear();
 int indx=0;
 pFunc pterm = FUNCT(tok, indx);
 pGoal pgoal = pGoal(new Goal(pterm, nullptr));
 
 while(tok[indx].type == COMMA)
	{ ++indx;		// consume COMMA
	  pterm = FUNCT(tok,indx);
	  pGoal pg1 = pGoal(new Goal(pterm,nullptr));
	  pgoal = pgoal->append(pg1);
	}
 return pgoal;		// expect token EOC (". ")
}

pClause CLAUSE(vector<Token>& tok )
{
Var::mTVar.clear();
int indx=0;
pFunc phead = FUNCT(tok, indx);

if( tok[indx].type ==EOC) 
	{
	 return pClause(new Clause(phead,nullptr));	// "Fact"
	}

if( tok[indx].type == COLON)	// :-		"Rule"
{ ++indx;		// consume :-
  pGoal pbody;
  pFunc ptc1 = FUNCT(tok, indx);	// 
  pbody = pGoal(new Goal( ptc1, nullptr));
  while( tok[indx].type == COMMA)
 { ++indx;	// consume COMMA
  ptc1 = FUNCT(tok, indx);
  pGoal pg1 = pGoal(new Goal(ptc1,nullptr));
  pbody = pbody->append(pg1);
}	// while
 return pClause(new Clause(phead, pbody));
}	// if

 for(uint ind=0; ind<tok.size();++ind) cout<<tok[ind].symbol;
 cout<<endl;
 return nullptr;
}	// CLAUSE


pFunc FUNCT(vector<Token>& tok, int& indx)
{ 
enum SymType type=tok[indx].type;
if(! ( (type==AFUNC)||(type==CFUNC)||(type==OP)||(type==LB)) )
			cout<<"FUNCT() ERROR, type= "<< strSType(type) <<endl;	
 /*if(type==OP)
 	{cout<<"  indx= "<< indx << endl;
 	cout<<"OP= "<<tok[indx].symbol << endl;} */
 vector<pTerm> vpTerm;
 pFunc pret;

 if(tok[indx].symbol == "!") {		// temporary special handling
	string fsym = tok[indx].symbol;
	++indx;
	return pFunc(new Funct(fsym,vpTerm));
	}
 if(type ==AFUNC)
 	{
	string fsym = tok[indx].symbol; indx++;
	 pret = pFunc(new Funct(fsym,vpTerm));
	 return pret;
	}
 if( (type == CFUNC)||( type == OP))
{ 
	string fsym = tok[indx].symbol; indx++;
 vpTerm = ARGLIST(tok,indx);		// expect CFUNC, type=LP
 pret  = pFunc(new Funct(fsym, vpTerm));
 return pret;
}

 if( type == LB)	// start a list Funct
	{ pFunc elemprev;
	pret =  LIST(tok,indx, elemprev);
	return pret; }

 cout<<"ERROR protran.cc:FUNCT(), uninitialized pTerm \n";
 return pret=nullptr;
}	// FUNCT()

//----------------------------------------------------------
// called with type = LB from  FUNCT(), start a list
// called with type = COMMA from LIST

pFunc LIST(vector<Token>& tok, int& indx, pTerm elemprev)
{ SymType  type = tok[indx].type;
  bool ok= (type==LB)||(type==COMMA)||(type==SEP)||(type==RB);
  if(!ok) cout<<"ERROR LIST()-1, unexpected input token= "<<tok[indx].symbol 
	<<", "  << strSType(type)<<endl;

 pTerm elem, elem1;	// = nullptr
 pFunc pfret;
  if(type==LB)	// start of a new list, expect Term or nil
{	
	if(tok[indx+1].type == RB)
		{ indx+=2;		// consume [ ]
	  	 return pFunc(new Funct("[]"));
		}
// expect Term after LB,COMMA (at least one),  SEP is an error
  ++indx;
  elemprev = TERM(tok,indx);
	
  if( ! elemprev) cout<<"ERROR LIST()-2, expect valid elem after ["<<endl;
// have elem, expect following COMMA, SEP RB
  return LIST(tok,indx, elemprev);
}	// LB

 
  if(tok[indx].type == SEP)		
	{ ++indx;
	  pTerm tail = TERM(tok,indx); 
	  	// expect ]
	 if(tok[indx].type != RB){cout<< "ERROR LIST()-3, expect ], ";
			 prntok(tok[indx]); cout<<endl;}
	  ++indx;	// consume ]
 	 return pFunc(new Funct(".",elemprev, tail));
	}

   if(tok[indx].type == RB)
	{ ++indx;	// consume RB
	 pfret =  pFunc(new Funct(".",elemprev, pFunc(new Funct("[]" )) ));
	 return pfret;
	}

  if(tok[indx].type == COMMA)		// expect more Terms
	{++indx;
	 elem = TERM(tok,indx);
	 pfret = pFunc(new Funct(".",elemprev, LIST(tok,indx,elem)));
	 return pfret;
    }


  pFunc ret = nullptr;
  cout<<"ERROR LIST()-4 exit, tok= "; prntok(tok[indx]);cout<<endl;
  return ret;
}	// LIST
//-------------------------------------------------------------


vector<pTerm> ARGLIST(vector<Token>& tok, int& indx)
{ 
  vector<pTerm> vret;	// .size = 0
  if(tok[indx].type != LP) // expect LP at start
    { 
     ++indx;
	 return vret; }
  ++indx;	// consume LP
  pTerm pT1 = TERM(tok,indx);	// 1st term
  vret.push_back(pT1);
  while( tok[indx].type == COMMA)
   { 
   ++indx;		// consume ','
   pT1 = TERM(tok, indx);	
   vret.push_back(pT1); 
  }

 if(tok[indx].type != RP)
	{cout<<"ARGLIST ERROR expect RP, indx= "<<indx<<" "<< tok[indx].symbol <<
		", type= "<< strSType( tok[indx].type) << endl;
	}
	
 ++indx;	// consume RP
 return vret;
}	// ARGLIST()

vector<pTerm> ELEMS(vector<Token>& tok, int& indx)
{ vector<pTerm> vret;	// size=0 
	if(tok[indx].type == RB) {}
  return vret;
}	// ELEMS()

pTerm TERM(vector<Token>& tok, int& indx)
{ 
 if(! isTerm(tok[indx]) )
	{cout<<"TERM() ERROR not a term: "
		<<"'" <<tok[indx].symbol <<"'"
		<<", type= "<< tok[indx].type <<endl;
	 exit(1);
	 return pTerm(nullptr); }
 
 int type = tok[indx].type;
 if(type==NUM) return NUMBER(tok,indx);
 if(type==VAR) return VARIABLE(tok,indx);
 return FUNCT(tok,indx);
}



pNum NUMBER(vector<Token>& tok, int& indx)
{ string fsym = tok[indx].symbol; 
  pNum pTn1 = pNum(new Num(fsym));
  ++indx;
  return pTn1;
}

pVar VARIABLE(vector<Token>& tok, int& indx)
{pVar pvar;
 string symbol = tok[indx].symbol;
 if(! isVAR(tok[indx]))
	cout<<"ERROR VARIABLE() not a Variable: "<<tok[indx].symbol<<endl;
 map<string, pVar>::const_iterator it;
 it = Var::mTVar.find(symbol); // check for previous use in clause
 if( (it != Var::mTVar.end()) && (symbol != "_") )
		pvar = Var::mTVar[symbol];	//symbol found

 else { pvar = make_shared<Var>();
    	Var::mTVar[symbol] = pvar;
	  }
 ++indx;
 return pvar;
}

bool isTerm(Token tok)
{
 switch(tok.type)
{ case AFUNC: 
  case CFUNC:
  case OP:
  case VAR:
  case NUM:
  case LB:
	return true;
  default: return false;
}
}

bool isVAR(Token tok)
{ if( tok.type == VAR) return true;
  return false;
}




