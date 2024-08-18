#ifndef _PARSE2_H_
#define _PARSE2_H_
 
using namespace std;

//            0     1     2     3    4    5   6     7        8      9    10  11  12    13   14    15   16   17  18   19
enum SymType{NONE, VAR, AFUNC, CFUNC,NUM,OP, SPACE, PERIOD, COMMA, SEMI, LP, RP,COLON,QUERY,DASH, EOC,CUT, LB, RB, SEP };

using uint = unsigned int;

void getProgram(string& file, pProg& prog, vector<pGoal>& vgoals,
		vector<pVarMap>& vvar_map);
void getProgram(string& file, pProgV& progv, vector<pGoal>& vgoals,
		vector<pVarMap>& vvar_map);
		
void repl(pProg prog);	// Read,Eval,Process,Loop

string strSType(enum SymType);	// get name of SymType
struct Token { string symbol; SymType type; };

void getClause(string& str1, pClause& pcl, pGoal& pgl);

//Token getSymbol(const string& str, uint& indx);
Token getToken(const string& str, uint& indx);
int getChar(const string& str, uint k);	// checks k < str.size(), else getChar=0
bool isPrologPunc(char c);
char getPunc(const string& str, 
					int& indx, enum SymType& type);
SymType getPuncType(char cp);
void readDataBase(ifstream& infile, vector<string>& dbase);
void combine2period(vector<string>& kb);
bool isOpChar(char c);
bool isOpchar2(char cp);

// UTILITY functions
void clean(string& str);
void combine2period(vector<string>& kb);
void removews(vector<string>& kb);
int checkparens(vector<string>& tokens);

template<class T>
void prnvec(vector<T>& vec)
  {for(int k= 0;k< vec.size();++k) cout<< vec[k]<<endl;}

void prntoks(vector<Token>& toks);
void prntok(Token tok); 

#endif

