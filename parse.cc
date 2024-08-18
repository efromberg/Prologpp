/* parse.cc		11/2/21
 from	parse2.cc with  
		prolog2.h, prolog2.cc

$ g++ -o parse parse.cc prolog.cc protran.cc predicate.cc
Using valgrind:
$ g++ -g -o parse parse.cc prolog.cc protran.cc predicate.cc
$ valgrind --leak-check=yes ./prolog ../Nqueens2.pl
  valgrind reports both Leaks and Errors.	11/3/21
 11/7/21 convert to unbound== instance=nullptr
	valgrind: no memory leaks, no errors
10/26/22: allow + * as AFUNC

11/10/22 use Program::solve(): l.69, l.101
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <cctype>
#include <sys/resource.h>
//#define _POSIX_SOURCE 200112L
#include <unistd.h>
using namespace std;

#include "prolog.h"
#include "protran.h"
#include "parse.h"
#include "predicate.h"



/*
//            0     1     2     3    4    5   6     7        8      9    10  11  12    13   14    15   16
enum SymType{NONE, VAR, AFUNC, CFUNC,NUM,OP, SPACE, PERIOD, COMMA, SEMI, LP, RP,COLON,QUERY,DASH, EOC,CUT };

*/

//=== MAIN =====================================================

int main( int argc, char* argv[])
{ 

string file;
if(argc>=2) file=argv[1];
cout<<"Input: "<< file <<endl<<endl;
pProg prog;
pProgV progv;
vector<pGoal> vgoals;
vector<pVarMap> vvar_map;

getProgram(file,prog,vgoals,vvar_map);
//getProgram(file,progv, vgoals, vvar_map);

cout<<"vgoals.size= "<< vgoals.size() << endl;

cout<<"Program: "<<endl; prog->print();
for(uint kg=0; kg<vgoals.size(); ++kg)
 { Goal::Timestart = time_now();
   cout<<"Goal: ";vgoals[kg]->print();cout<<endl;
   Goal::Nans = 0;
	Goal::Ntries = 0;
	Goal::Nunifs = 0;
	
   vgoals[kg]->solve(prog, 0, vvar_map[kg]);
   
   //prog->solve(vgoals[kg], 0, vvar_map[kg]);
   
   
	cout<< "Finished, Nans= "<<Goal::Nans
		<<", Ntries= "<<Goal::Ntries<<", Nunifs= "<<Goal::Nunifs;
	 Timept t2 = time_now();
	 cout<< ", Elapsed_time= "<< timediff( Goal::Timestart, t2)<<endl<<endl;
 }
 
 repl(prog);


}	// main()

void repl(pProg prog)
{ while(1) {
string query;
cout<<"?- ";
getline(cin, query);
if(query.size() <1) exit(0);
query="?- "+query;
cout<<"QUERY= "<< query << endl;
pClause pclause=nullptr;
pGoal pgoal=nullptr;
getClause(query,pclause,pgoal);
cout<<"Goal: "; pgoal->print(); cout<<endl;
  Goal::Nans = 0;
	Goal::Ntries = 0;
	Goal::Nunifs = 0;
	Goal::Timestart = time_now();
pVarMap var_map = pVarMap(new TermVarMapping(pgoal->mTVar));
pgoal->solve(prog,0, var_map);
//prog->solve(pgoal,0, var_map);
	cout<< "Finished, Nans= "<<Goal::Nans
		<<", Ntries= "<<Goal::Ntries<<", Nunifs= "<<Goal::Nunifs;
	cout<<endl;
 }
}	// repl()

//--------------------------------------------------
/* Reads Prolog database, converts to C++ pP struct, ready to execute
Procedure:
getClause(string -> pclause)
	getToken() string -> tokens by enum SymType{ }
	CLAUSE(toks)
	GOAL(toks)

*/
void getProgram(string& file, pProg& prog, vector<pGoal>& vgoals,
		vector<pVarMap>& vvar_map)
{ 
prog = nullptr;
vgoals.clear();
vvar_map.clear();
ifstream infile;
infile.open(file);
if(!infile.is_open())		// ERROR,file not opened
	{ cout<<"ERROR, not found, file= "<< file << endl;
	  exit(1); }

vector<string> dbase;


readDataBase(infile,dbase);		// 1 clause/line
// TBI: convert dbase to Tokens

pClause pclause;
pGoal pgoal;
prog = builtinPreds();		// start program
cout<<"getProgram(): after builtinPreds() " << endl;
// add builtin scripts here, to dbase
vector<pClause> rules;

for(uint kcl=0;kcl<dbase.size();++kcl)	// add clauses
 { pClause pclause=nullptr;
   pGoal pgoal=nullptr;
  			// string to clause
	getClause(dbase[kcl],pclause, pgoal);	// pclause or pgoal,not both
	 if(pgoal) vgoals.push_back(pgoal);
	 if(pclause) {

		if(prog) prog = prog->append(pProg(new Program(pclause,nullptr)));
		else prog = pProg(new Program(pclause,nullptr)); 
		 }
 }
vvar_map.clear();		// var_map for each goal
for(uint kg=0; kg<vgoals.size(); ++kg)
 { pVarMap var_map = pVarMap(new TermVarMapping(vgoals[kg]->mTVar));
   vvar_map.push_back(var_map);
 }	
}	// getProgram()

void getProgram(string& file, pProgV& progv, vector<pGoal>& vgoals,
		vector<pVarMap>& vvar_map)
{
pProg prog;  // temp, TBDeleted
prog = nullptr;
vgoals.clear();
vvar_map.clear();
ifstream infile;
infile.open(file);
if(!infile.is_open())		// ERROR,file not opened
	{ cout<<"ERROR, not found, file= "<< file << endl;
	  exit(1); }

vector<string> dbase;

readDataBase(infile,dbase);		// 1 clause/line

pClause pclause;
pGoal pgoal;
vector<pClause> rules;

prog = builtinPreds();		// start program
cout<<"getProgram(): after builtinPreds() " << endl;
// add builtin scripts here, to dbase

for(uint kcl=0;kcl<dbase.size();++kcl)	// add clauses
 { pClause pclause=nullptr;
   pGoal pgoal=nullptr;
  			// string to clause
	getClause(dbase[kcl],pclause, pgoal);	// pclause or pgoal,not both
	 if(pgoal) vgoals.push_back(pgoal);
	 if(pclause) {
		rules.push_back(pclause);
		if(prog) prog = prog->append(pProg(new Program(pclause,nullptr)));
		else prog = pProg(new Program(pclause,nullptr)); 
		 }
 }
vvar_map.clear();		// var_map for each goal
for(uint kg=0; kg<vgoals.size(); ++kg)
 { pVarMap var_map = pVarMap(new TermVarMapping(vgoals[kg]->mTVar));
   vvar_map.push_back(var_map);
 }	


}	// getProgram(... progv..)


//----------------------------------------------------------
//	str1 --> Clause or Query, not both
void getClause(string& str1, pClause& pcl, pGoal& pgl)
{ 					
vector<Token> toks;
uint indx=0;
while(indx < str1.size())
	{Token tk = getToken(str1,indx);
	 toks.push_back(tk);
	}
 pgl = nullptr;
 pcl = nullptr;
if( toks[0].type == QUERY)
{  toks.erase(toks.begin());	// remove ?-
   pgl = GOAL(toks);
   pgl->mTVar = Var::mTVar;	// for GOAL Clause only
}
else {pcl = CLAUSE(toks);
pcl->print(); cout<<endl; 
	}

}	// getClause()


//------------------------------------------------------
/* --- getToken()  Extract symbol from clause string
I	str input clause string, consumes leading whitespace
I/O	k	start at k, k at end is next char
O	type	type () of returned symbol
return 	returned symbol string
,(  .(   OP  
,  seperates Terms in arglist
tk.type= VAR, CFUNC,AFUNC,NUM,OP
getToken(): l.186 - l.343
*/

Token getToken(const string& str, uint& k)
{
string symb;
Token tk; tk.type=NONE;
if(k >= str.size()) return tk;	// symb;	// ERROR

// consume leading ws:
char c1;
c1 = getChar(str, k);
while((!isgraph(c1))&&(k<str.size())) {++k; c1=str[k];}

if( isupper(c1) || (c1=='_') )	// VAR
	{  while( isalnum(c1)|| (c1== '_'))
	  { symb.append(1,c1);
		c1 = getChar(str, ++k);
	 }
	 tk.type = VAR;
	 tk.symbol = symb;
	 return tk;	
    }
if(islower(c1)	)//  AFUNC, CFUNC
	{  while( isalnum(c1)|| c1== '_')
	  { symb.append(1,c1);
		c1 = getChar(str, ++k); }
	if(c1=='(') tk.type = CFUNC; //3;
	else tk.type = AFUNC;		// 2 expect c1= , )
	tk.symbol = symb;
	return tk;	//symb;
    }	
    
 char sqt = '\'';	// check for '(' etc for  single quote
 if(c1 == sqt)		
 { //cout<<"sqt= "<< sqt <<", k= "<< k << endl;
   int k2 = k+1;
   char c2 = getChar(str,k2); //cout<<"   c2= "<< c2 <<    endl;
   symb.clear();
   while( c2 != sqt) 	// 'symb'	// expect final sqt
   		{ symb.append(1,c2);
   		  c2 = getChar(str, ++k2);	}	// closes with sqt
   	k = k2+1;
   	tk.symbol = symb;
   	//cout<<"symb= "<< symb << ", c2= "<< c2 <<", k= "<<k << endl;
   	tk.type = AFUNC;
   	return tk;
 }

if(isdigit(c1))		// expect NUM, unsigned digits, not + -
{	while(isdigit(c1))
		{symb.append(1,c1); c1 = getChar(str, ++k); }
  tk.type = NUM;	// 4	expect c1=  ,  )
	tk.symbol = symb;
  return tk;	//symb;
 }

if( (c1=='+') || (c1=='-'))		//only  NUM or OP (or AFUNC)
{ 
  symb.assign(1,c1);
  int k2=k+1;	// look at next char
  char c2 = getChar(str,k2);
  while(isdigit(c2) ){symb.append(1,c2);  // NUM
					  c2 = getChar(str, ++k2);}
   if(symb.size() >= 2) {
		tk.type=NUM; k=k2; 
		tk.symbol = symb;		
		return tk; }
   if(c2 == '(' ) 			// OP, no digits 
	{ ++k;
	  tk.type = OP;
	  tk.symbol.assign(1,c1);
	  return tk;
	}
// 10/26/22 allow + as AFUNC character (use in expressions) 
	++k;	// next char
    tk.type = AFUNC;
	tk.symbol.assign(1,c1);
	return tk;
	
	cout<<"ERROR getToken (+-) c1= "<< c1 <<", c2= "<<c2 <<endl;
	tk.type = NONE;
    tk.symbol.assign(1,c1);
	tk.symbol.append(1,c2);
	return tk;
}	// if( + _ ..

if( (c1== '*')||(c1== '/'))		// (prefix) OP only
{ int c2, k2=k+1;			// look at next char
  c2 = getChar(str, k2);	// expect '('
  if(c2 == '(')
	{++k;
	 tk.type = OP;
	 tk.symbol.assign(1,c1);
	 return tk;
	}
	++k;	// allow AFUNC (10/16/22)
	tk.type = AFUNC;
	tk.symbol.assign(1,c1);
	return tk;
}	// if( * /

if( (c1==':') && (getChar(str,k+1)=='-'))
	{ symb = ":-";
	  tk.type =  COLON;
	  k = k+2;	// next char
	  tk.symbol = symb;
	  return tk;
	}
if( (c1=='?') && (getChar(str,k+1)=='-'))
	{ symb = "?-";
	  tk.type = QUERY;
      k = k+2;
	  tk.symbol = symb;
	  return tk;
	}
if( c1=='!')	// reserved symbol
	{ symb.append(1, c1);
	  tk.type = OP;
	  ++k;
	  tk.symbol = symb;
	  return tk;
	}
if( (c1==',')||(c1== ';'))
	{ int c2 = str[k+1];	// check next char
	 if( c2 == '(')		// OP:  ,  ;   AND OR prefix ops
		{ tk.symbol.assign(1,c1);
		  tk.type = OP;
		  ++k;
		  return tk;
		}
	 if( c1== ',')
		{ tk.symbol.assign(1,c1);
		  tk.type = COMMA; 
			++k;
			return tk;}	// separator in a clause
	if(c1== ';')
		{ tk.symbol.assign(1,c1);
		  tk.type = SEMI; 
			++k;
			return tk;}	// separator in a clause
	}	// if(c1==


if(isOpChar(c1))  // require '(' termination
{int k2=k;
 while(isOpChar(c1)) 
    {symb.append(1,c1); c1 = getChar(str,++k2); }
  if( c1 == '(' ) {tk.type = OP; k=k2; 
		tk.symbol = symb;		
		return tk;} // arity >= 1
  c1=getChar(str,k);  // restore initial state
}	//if(isOpChar


if( (c1=='.')&&(getChar(str,k+1)==' ')) // End of Clause
{ symb= ". ";
  tk.type = EOC;
  k = k+2;
	tk.symbol = symb;
  return tk;
}
	// LISTS:
if(c1=='[') {tk.type=LB; tk.symbol=c1; ++k; return tk;}
if(c1=='|') {tk.type=SEP; tk.symbol=c1; ++k; return tk;}
if(c1==']') {tk.type=RB; tk.symbol=c1; ++k; return tk;}
if(isPrologPunc(c1))	//
{ tk.type = getPuncType(c1);
  symb = c1;
  ++k;
	tk.symbol = symb;
  return tk;
}
symb = c1;
cout<<"getToken() ERROR c1= "<< (char)c1 <<",k= "<<k 
				<<",size= "<<str.size()<< endl;
++k;
tk.type = NONE; //
tk.symbol = symb;
return tk;	// ERROR, no Atom found
}	// getToken(), l.155


//------------------------------------------------------------------

// parse.h enum SymType{ }
string strSType(enum SymType styp)
{ string str;
switch(styp)
{
case NONE: return str="NONE";
case VAR:  return str="VAR";
case AFUNC: return str="ATOMF";
case CFUNC: return str="CFUNC";
case NUM: return str="NUM";
case OP:  return str="OP";
case SPACE: return str="SPACE";
case PERIOD: return str="PERIOD";
case COMMA: return str="COMMA";
case SEMI: return str="SEMI";
case LP: return str= "LP";
case RP: return str="RP";
case COLON: return str="COLON";
case QUERY: return str="QUERY";
case DASH: return str="DASH";
case EOC:  return str="EOC";
case CUT:  return str= "CUT";
case LB:   return str = "LB";
case RB:  return str = "RB";
case SEP: return str = "SEP";
default: return str="NONE";
}	// switch
}	// strSType()

				// checks k < str.size(), else getChar=0
int getChar(const string& str, uint k)
{ if(k < str.size()) return str[k];
  else return 0;
}	// getChar();


// prolog Punc:  ' ' , ; ( )	terminate symbols in clauses
bool isPrologPunc(char c)
{
 switch(c)
{case ' ': return true;
 case ',': return true;
 case ';': return true;
 case '(': return true;
 case ')': return true;
 case '.': return true;
 case ':': return true;	// needs '-'
 case '?': return true;	// needs '-'
 case '-': return true; // follows : ?
 default:
 return false;
}	// switch
}	// isPrologPunc()


char getPunc(const string& str, 
					int& indx, enum SymType& type)
{ 
  int k=indx;
  char rchar = 0; 	// return value
  type = NONE;
  char pchar = getChar(str, k);
  if(pchar == ' ') rchar = pchar;
  while(pchar == ' ') { pchar = getChar(str, ++k);} // absorb leading ws
  if( isPrologPunc(pchar))
	{indx = k;
	 type = getPuncType(pchar);
	 indx = k+1;
	// cout<<"getPunc() pchar= "<< pchar <<", type= "<<type <<", k= "<< k <<endl;
	 return pchar; // either , ; ( )
	}
  indx = k+1;
  type = getPuncType(rchar);
  return rchar;		// either 0,  ' '
}	// getPunc()

//enum SymType{NONE, VAR, AFUNC, CFUNC,NUM,OP, SPACE, PERIOD, COMMA, SEMI, LP, RP,COLON,QUERY,DASH,EOC };
SymType getPuncType(char cp)
{switch(cp)
 {case ' ': return SPACE;
  case '.': return PERIOD;
  case ',': return COMMA;
  case ';': return SEMI;
  case '(': return LP;
  case ')': return RP;
  case ':': return COLON;
  case '?': return QUERY;
  case '-': return DASH;
  // case= ". " is EOC
}
  return NONE;
}	// getPuncType()

//----------------------------------------------------------
/* read file of clauses for Program
I	infile	Input stream(opened file) each clause terminated with '. '
O	dbase	vector of clauses(text)
*/
void readDataBase(ifstream& infile, vector<string>& dbase)
{ string strline;
 while(infile)
  { getline(infile, strline, '\n');
    clean(strline);		// delete comment(%-EOL), leading ws
	if(strline.size()>0) dbase.push_back(strline);
  }
 combine2period(dbase);
// removews(dbase);

}

//--------------------------------------------------------
/* combine successive strings until '.'
I	kb	lines from input file
	replace each final "." with ". " (blank,not just white space)
O	kb	1 clause/string, ends with ". "
*/
void combine2period(vector<string>& kb)
{ uint kloop = 0;
 vector<string> kb2;
 if(kb.size() ==0) return;
// force final '.' to ". " (since EOL deleted)
for(kloop=0; kloop<kb.size(); ++kloop)  // each input line
{string &str = kb[kloop];
 uint indx = str.find_last_of('.');
 if( indx == str.size()-1 ) str.append(" ");  
 else if((0<=indx)&& (indx < str.size()-1)&&( !isgraph( str[indx+1]))) //any ws char
	 str.insert(indx+1, " "); 	//substitute ". " over ".ws"
}

// int str.find(c) <0 (= -1) if c not found
 uint kline =0;
 int indx;
 string str;	
 str = kb[0];	// initial

 while(kline < kb.size())
{
 indx = str.find(". ");			//anywhere in current str
 if((indx<0) &&(kline<kb.size()-1)) str+=kb[++kline];//not found, add next record
 else 
  {kb2.push_back(str);		// ". " found, write out
   if(kline<kb.size()-1) str= kb[++kline]; // get next str
   else {++kline;	//cout<<"KLINE= "<<kline;
		}    // end: kloop = kb.size()
  } 
}	// while(kline...

 kb = kb2;
}	// combine2period()
//---------------------------------------------------
void removews(vector<string>& kb)
{for( uint kv=0; kv<kb.size();++kv)
{ string outstr;
  string& instr = kb[kv];	// input clause string
  uint kin=0;
  outstr.clear();
  for(kin=0; kin<=instr.size()-2; ++kin)
	if( !isspace(instr[kin])  )outstr=outstr+instr[kin];
  outstr=outstr+instr[instr.size()-1];	//copy final space
  kb[kv]=outstr;
}
}	// removews()

//------------------------------------------

// List of chars allowed in OP, see syntax.txt
// TBI:  # (CLP)
bool isOpChar(char cp)
{switch(cp)
  { case '.':
	case ',':
	case ';':
	case '>':
	case '<':
	case ':':
//	case '?':
	case '*':
	case '=':
	case '@':
	case '\\':
	case '/':
	case '+':
	case '-':
	case '^':
 // special OPs
	case '!':
//	case '$':
	case '[':
	case '|':
	case ']':
	  return true;
	default:
	  return false;
  }
}
// remaining permitted chars after special cases
//	handled in getToken()
bool isOpchar2(char cp)
{ switch(cp) {
//	case ',':
//	case ';':
	case '>':
	case '<':
//	case ':':
//	case '?':
//	case '*':
	case '=':
	case '@':
	case '\\':
//	case '/':
//	case '+':
//	case '-':
	case '^':
 // special OPs
	case '!':
//	case '$':
	case '[':
	case '|':
	case ']':
	  return true;
	default:
	  return false;
  }
}	// 

// === UTILITY functions ======================================

void clean(string& str)		// remove leading ws, comment(% - EOL)
{if(str.size()==0) return;
uint kloop=0;
do { if(isgraph(str[kloop])) break;
	 ++kloop;
	} while(kloop<str.size());
// kloop ws chars here
str.assign(str, kloop, str.size()-kloop);
// remove comments:  % to EOL
int indx = str.find('%');
str.assign(str, 0, indx);
// remove trailing ws
indx = str.size()-1;
while((indx>=0) && (!isgraph(str[indx])))
	{  str.erase(indx, 1);
		--indx; }
}	// clean()

//--------------------------------------------------------

// Return unbalanced parens
int checkparens(vector<string>& tokens)
{ int parens = 0;
  string tok;
 for(uint k=0; k< tokens.size(); ++k)
 { tok = tokens[k];
  if(tok == "(") ++parens;
  if(tok == ")") --parens;
  }
 return parens;
}

void prntoks(vector<Token>& toks)
{ cout<<"TOKS: ";
  for(uint k=0; k<toks.size(); ++k)
	cout<<k<<":"<<toks[k].symbol <<" "<<strSType(toks[k].type)<<", ";
 cout<<endl;
}
void prntok(Token tok)
{ cout<<"TOK: "<< tok.symbol <<" "<<strSType(tok.type)<<" ";
}




