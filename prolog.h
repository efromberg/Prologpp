#ifndef _PROLOG_H_
#define _PROLOG_H_
 
/*     

Refs:
 ~/Programs/Prolog/LPN/ prolog_grammer.txt
 ~/Documents/Prolog/Mycroft/Notes.txt
 ~/Documents/Prolog/TheoremProver/Stickel/DescribeProlog..-Cohen.pdf
	outline of solve() and unify()

*/

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
using namespace std;


void indent(int n);

// --- USING shared_ptr  -----------------------------
class Term;
using pTerm = shared_ptr<Term>;

class Funct;		// AFUNC, CFUNC, OP
using pFunc = shared_ptr<Funct>;

class Num;
using pNum = shared_ptr<Num>;

class Var;
using pVar = shared_ptr<Var>;

class Goal;
using pGoal = shared_ptr<Goal>;

class Clause;
using pClause = shared_ptr<Clause>;

class Program;
using pProg = shared_ptr<Program>;

class ProgV;
using pProgV = shared_ptr<ProgV>;

class Trail;
using pTrail = shared_ptr<Trail>;

class TermVarMapping;
using pVarMap = shared_ptr<TermVarMapping>;

// --- TERM -------------------------------------------
class Term 
{public:
 virtual void print() = 0;
 virtual bool unify(pTerm) = 0;
 virtual bool unify2(Funct* ) = 0;
 virtual pTerm copy() = 0; 
 virtual long int eval() = 0;
 virtual ~Term() = default;	// C++ Primer p.622
};	// class Term

//--- FUNCT -------------------------------------
// add member function: shared_from_this()
class Funct : public Term, public enable_shared_from_this<Funct> 
{private:
 protected:
 string fsym;
 int arity;
 vector<pTerm> args;
public:
 Funct(string f): fsym(f), arity(0){args.clear();}
 Funct(string f, pTerm a1) 
	:fsym(f),arity(1) {args={a1}; }
 Funct(string f, pTerm a1, pTerm a2)
	:fsym(f),arity(2) {args={a1,a2}; }	
 Funct(string f, pTerm a1, pTerm a2, pTerm a3)
	:fsym(f),arity(3),args{a1,a2,a3}{} 
 Funct(string  f, vector<pTerm> vpTerm)
	:fsym(f),arity(vpTerm.size()),args(arity)
		{for(int k=0; k<arity;++k) args[k]=vpTerm[k]; }
 virtual void print();
 virtual bool unify(pTerm t);
 pTerm copy() {return copy2(); }	// used in Goal::solve()
 virtual long int eval();
			// 9/23/21 add virtual to copy2()
 virtual pFunc copy2() {	return pFunc(new Funct(this) ); }
 string getfsym(){ return fsym; }
 int getarity(){ return arity;}
 pTerm getargs(int ka){ return args[ka]; }
 ~Funct() = default;
//private:
protected:
 Funct(Funct* p);
private: 
 bool unify2(Funct* t);	// unify(C1,C2)
};	// Funct


class Num : public Funct		// arity=0
{
public:	
  long int val;
//  
  Num(string f): Funct(f) {val = stol(f); }
  Num(long int value): Funct(to_string(value)),val(value){ }
  bool unify(pTerm t) { return t->unify2(this);};
  pTerm copy() { return copy2(); };
 
pFunc copy2() { return pNum(new Num(this)); } 
  void print() {  Funct::print(); }
  virtual long int eval() { return val; }
private:
  Num(Num* t): Funct(t),val(t->val) { }
  bool unify2(Num* t) { return val == t->val; }
};

class Var;

// --- VAR ------------------------------------
// add member function:  shared_from_this()
class Var : public Term, public enable_shared_from_this<Var>
{private:
  pTerm instance;
  long varno;

public:
  static int timestamp;

  static map<string,pVar> mTVar;  // track usage in a clause

  Var() : instance(nullptr), varno(++timestamp)	{ }
  void print();
  virtual bool unify(pTerm t);		// in .cc
  pTerm copy();						// in .cc
  virtual long int eval();
  void reset(){ instance = nullptr;
		}
private:
  virtual  bool unify2(Funct* t);
		
};	// Var

// --- TRAIL ----------------------------------------
class Trail					// List of Variables
{private:
	pVar tcar;
	pTrail tcdr;
	static pTrail sofar;		// current Trail

	Trail(pVar h, pTrail t): tcar(h), tcdr(t){ }
public:
	static pTrail Note() { return sofar; }
	static void Push(pVar x);	// {sofar = pTr(new Trail(x,sofar));}
	static void Undo(pTrail whereto);
	void print();  // print Trail
	static void prnsofar(int level);
};

class Program;
class TermVarMapping; 
class Goal;

// --- CLAUSE ---------------------------------
class Clause		// head :- body
{public:
 pFunc head;
 pGoal body;
Clause(pFunc h, pGoal t):head(h), body(t){ }
 pClause copy(); 
 void print(); 
};	// Clause

typedef chrono::high_resolution_clock::time_point Timept;

// --- GOAL ----------------------------------------
class Goal
{public:
 pFunc ghead;
 pGoal gtail;
 
public:
 //static int nans;
 Goal(pFunc h, pGoal t):ghead(h),gtail(t) { }
 pGoal copy(); 
 pGoal append(pGoal l); 
 void print(); 
 void solve(pProg p, int level, pVarMap map);
 map<string,pVar> mTVar;		// only in ?- GOAL clause
 void goalanswer();
 
 static int Trace;	// Trace level: 0,1,2
 static int Nans, Maxans, Ntries,Nunifs;//Num.ans's, Maximum answers,then halt
 static Timept Timestart;
};	// Goal



// --- PROGRAM -------------------------------------
// 
class Program : public enable_shared_from_this<Program>
{public:
 pClause pcar;
 pProg pcdr;
 vector<pClause> vrule;
 
 Program(pClause h, pProg t): pcar(h),pcdr(t) { }
 Program(vector<pClause> rules):vrule(rules) { }
 
 pProg append(pProg pc){return pProg(new Program(pcar,	// 9/12/21
		pcdr==NULL? pc : pcdr->append(pc)) ); }
 void print(); 
 // replace Goal.solve()
 void solve(pGoal g, int level, pVarMap map);
 
};

class ProgV
{ public:
 vector<pClause> rules;
 ProgV(vector<pClause>  rulev):rules(rulev){ }
};

// --- TERMVARMAPPING -----------------------------
class TermVarMapping
{private:
	vector<pVar> varvar;
	vector<string> vartext;
//	int size;
public:
	int size;
	TermVarMapping(vector<pVar> vv, vector<string> vt)
		: varvar(vv),vartext(vt),size(vv.size()) {}
	TermVarMapping(map<string,pVar> mTVar);
	void showanswer();
};	// TermVarMapping


//  UTILITY  Elapsed time functions, from -MatrixArray/src/utility.cc, .h
// #include <chrono>   typedef put before Goal class
//typedef chrono::high_resolution_clock::time_point Timept;
Timept time_now();
double timediff(Timept start, Timept stop);		//secs,  Mat.cc

#endif

