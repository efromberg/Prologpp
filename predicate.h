#ifndef _PREDICATE_H_
#define _PREDICATE_H_
/* swipl - built-in predicates
https://www.swi-prolog.org/pldoc/doc_for?object=%28is%29%2f2
Predicate is/2
https://www.swi-prolog.org/pldoc/man?section=builtin
Chap. 4 Built-in Predicates
	4.27 Arithmetic
expr	integer
expr	op(expr1, expr2)
op		+ - * /
eval( op(e1,e2)) == eval(e1) op eval(e2)
eval(e1)		integer
eval(integer)	integer

Predicates:
is/2
=\=/2
=:=/2
</2
=</2
>/2
>=/2
!/0
fail/0
TBI:
var(X)
nonvar(X)
atom(X)
number(X)
atomic(X);



*/

#include "prolog.h"

/*  general form for derived class of Funct 
class derive : public Funct
{ derive() : Funct("symbol", arg1, arg2, ...) { };  CTOR
  void print();
  bool unify2(Funct* t);
  pFunc copy2();
  derive(derive* p);		Copy CTOR
 	Not Used: bool unify(pT); pTerm copy(); int eval(); 
}
*/

class is : public Funct
{public:
is() : Funct("is",
			pVar(new Var()),
			pNum(new Num("0"))) { };

void print();
bool unify2(Funct* t);
pFunc copy2(); //pTc copy2();
is(is* p);
/*	Not Used: bool unify(pT); pTerm copy(); int eval(); */
};	// class is
//-------------------------------------------------------
class notequal : public Funct	//   =\=
{public:
 notequal() : Funct( "=\\=",
				pNum(new Num("0")),
				pNum(new Num("0"))) { };
 void print();
 bool unify2(Funct* t);
 pFunc copy2();	
 notequal(notequal* p);
};
//-------------------------------------------------------
// class equal causes failure in 
//  pClause pceq = make_shared<Clause>(make_shared<equalx>(), nullptr);
class equalx : public Funct	//   =:=
{public:
 equalx() : Funct( "=:=",
				pNum(new Num("0")),
				pNum(new Num("0"))) { };
 void print();
 bool unify2(Funct* t);
 pFunc copy2();	
 equalx(equalx* p);
};
//----------------------------
class equal : public Funct	//   =:=
{public:
 equal() : Funct( "=:=",
				pNum(new Num("0")),
				pNum(new Num("0"))) { };
 void print();
 bool unify2(Funct* t);
 pFunc copy2();	
 equal(equal* p);
};

//-------------------------------------------------------
class lt : public Funct	
{public:
 lt() : Funct( "<", 
				pNum(new Num("0")),
				pNum(new Num("0"))) { };
 void print();
 bool unify2(Funct* t);
 pFunc copy2();
 lt(lt* p);
};
//-------------------------------------------------
class lte : public Funct	
{public:
 lte() : Funct( "=<", 
				pNum(new Num("0")),
				pNum(new Num("0"))) { };
 void print();
 bool unify2(Funct* t);
 pFunc copy2();
 lte(lte* p);
};
//------------------------------------------
class gt : public Funct
{public:
 gt() : Funct( ">", 
				pNum(new Num("0")),
				pNum(new Num("0"))) { };
 void print();
 bool unify2(Funct* t);
 pFunc copy2();
 gt(gt* p);
};
//------------------------------------------
class gte : public Funct
{public:
 gte() : Funct( ">=", 
				pNum(new Num("0")),
				pNum(new Num("0"))) { };
 void print();
 bool unify2(Funct* t);
 pFunc copy2();
 gte(gte* p);
};

//-------------------------------------------------------
class cut: public Funct
{public:
 cut() : Funct("!") { };
 void print();
 bool unify2(Funct* t);
 pFunc copy2();
 cut(cut* p);
};
//-------------------------------------------------------
class fail: public Funct
{public:
 fail() : Funct("fail") { };
 void print();
 bool unify2(Funct* t);
 pFunc copy2();
 fail(fail* p);
};
//---------------------------------------------------
class call: public Funct
{public:
 call() : Funct("call", pVar(new Var())) { };
 void print();
 bool unify2(Funct* t);
 pFunc copy2();
 call(call* p);
 };

// --------------------------------------------
class not_: public Funct
{public: 
 not_() : Funct("not", pVar(new Var())) {  };
 void print();
 bool unify2(Funct* t);
 pFunc copy2();
 not_(not_* p);
 };

//--- shared_ptr< >  ---------------------------------   


 using pIs = shared_ptr<is>;
 using pnEq = shared_ptr<notequal>;
 using pLt = shared_ptr<lt>;
 using pEqx = shared_ptr<equalx>;
 using pLte = shared_ptr<lte>;
 using pGt = shared_ptr<gt>;
 using pGte = shared_ptr<gte>;
 using pCut = shared_ptr<cut>;
 using pFail = shared_ptr<fail>;


pProg builtinPreds();
pProgV builtinPredsV();

//-------------------------------------------------------




#endif

