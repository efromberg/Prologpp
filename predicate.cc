


#include "predicate.h"

//--- IS ------------------------------------------------
bool is::unify2(Funct* t)
{
 if(! ((fsym==t->getfsym()) && (arity==t->getarity()) )  )
		{ 	return false;}
 int val = t->getargs(1)->eval();
 pNum pn = make_shared<Num>(val);
 return t->getargs(0)->unify(pn);
}	// unify2()
void is::print() {Funct::print();}

pFunc is::copy2()  { return make_shared<is>(this); }

is::is(is* p): Funct(p){ }


//--- =\= -----------------------------------------
// arithmetic inequality:  =\=
bool notequal::unify2(Funct* t) {
 if(! ((fsym==t->getfsym())	
	&& arity==t->getarity())) 
			return false;  
 int val1 = t->getargs(0)->eval();
 int val2 = t->getargs(1)->eval();
 if( val1 != val2) return true;
 return false;
}
void notequal::print(){ Funct::print(); }
pFunc notequal::copy2() 
	{	return make_shared<notequal>(this); }
notequal::notequal(notequal* p):Funct(p){ }

//--- =:= -----------------------------------------
// arithmetic equality:  =:=
bool equalx::unify2(Funct* t) {
 if(! ((fsym==t->getfsym())	
	&& arity==t->getarity())) 
			return false;  
 int val1 = t->getargs(0)->eval();
 int val2 = t->getargs(1)->eval();
 if( val1 == val2) return true;
 return false;
}
void equalx::print(){ Funct::print(); }
pFunc equalx::copy2() 
	{	return make_shared<equalx>(this); }
equalx::equalx(equalx* p):Funct(p){ }

//--- =:= -----------------------------------------
// arithmetic equality:  =:=
bool equal::unify2(Funct* t) {
 if(! ((fsym==t->getfsym())	
	&& arity==t->getarity())) 
			return false;  
 int val1 = t->getargs(0)->eval();
 int val2 = t->getargs(1)->eval();
 if( val1 == val2) return true;
 return false;
}
void equal::print(){ Funct::print(); }
pFunc equal::copy2() 
	{	return make_shared<equal>(this); }
equal::equal(equal* p):Funct(p){ }

//---------------------------------------------------
// less than:
bool lt::unify2(Funct* t) {
 if(! ( (fsym==t->getfsym())		
		&& (arity==t->getarity()) ) )
			return false;  
 int val1 = t->getargs(0)->eval();
 int val2 = t->getargs(1)->eval();
 if( val1 < val2) return true;
 return false; 
}
void lt::print(){Funct::print(); }
pFunc lt::copy2() {return make_shared<lt>(this); }
lt::lt(lt* p):Funct(p){ }
//--------------------------------------------------------
// less than equal:
bool lte::unify2(Funct* t) {
 if(! ( (fsym==t->getfsym())		
		&& (arity==t->getarity()) ) )
			return false;  
 int val1 = t->getargs(0)->eval();
 int val2 = t->getargs(1)->eval();
 if( val1 <= val2) return true;
 return false; 
}
void lte::print(){Funct::print(); }
pFunc lte::copy2() {return make_shared<lte>(this); }
lte::lte(lte* p):Funct(p){ }
//--------------------------------------------------------
// greater than:
bool gt::unify2(Funct* t) {
 if(! ( (fsym==t->getfsym())		
		&& (arity==t->getarity()) ) )
			return false;  
 int val1 = t->getargs(0)->eval();
 int val2 = t->getargs(1)->eval();
 
 if( val1 > val2) return true;
 return false; 
}
void gt::print(){Funct::print(); }
pFunc gt::copy2() {return make_shared<gt>(this); }
gt::gt(gt* p):Funct(p){ }
//--------------------------------------------------------
// greater than equal:
bool gte::unify2(Funct* t) {
 if(! ( (fsym==t->getfsym())		
		&& (arity==t->getarity()) ) )
			return false;  
 int val1 = t->getargs(0)->eval();
 int val2 = t->getargs(1)->eval();
 if( val1 >= val2) return true;
 return false; 
}
void gte::print(){Funct::print(); }
pFunc gte::copy2() {return make_shared<gte>(this); }
gte::gte(gte* p):Funct(p){ }

//--- cut ------------------------------------
void cut::print() {Funct::print(); }
bool cut::unify2(Funct* t) { 
  if(! ( (fsym==t->getfsym()) && (arity==t->getarity()) ) )
			return false;  
	return true; }
pFunc cut::copy2() { return make_shared<cut>(this); }
cut::cut(cut* p):Funct(p) { }

//--- call -----------------------------------
void call::print(){Funct::print(); }
pFunc call::copy2(){return make_shared<call>(this); }
call :: call(call* p):Funct(p){ }
bool call::unify2(Funct* t)		// need prog p for goal
{ 
 // t->solve(pProg p, int level, pVarMap tmap);

 return true;	// avoid Warning
}




//--- not ---------------------------------
void not_::print(){Funct::print(); }
pFunc not_::copy2() { return make_shared<not_>(this); }
not_::not_(not_* p):Funct(p){ }

bool not_::unify2(Funct* t) {
 if(! ( (fsym==t->getfsym())		
		&& (arity==t->getarity()) ) )
		//	return false;  
		return true; 
 return true;	// avoid warning
		}




//================================================
pProg builtinPreds()
{pProg prog;

pClause pcis = make_shared<Clause>( make_shared<is>(),nullptr);
pClause pcneq = make_shared<Clause>(make_shared<notequal>(), nullptr);
pClause pceqx = make_shared<Clause>(make_shared<equalx>(), nullptr);
		// make_shared<equal>()  fails
//pClause pceq = make_shared<Clause>(make_shared<equal>(), nullptr);
pClause pclt = make_shared<Clause>(make_shared<lt>(), nullptr);
pClause pclte = make_shared<Clause>(make_shared<lte>(), nullptr);
pClause pcgt = make_shared<Clause>(make_shared<gt>(), nullptr);
pClause pcgte = make_shared<Clause>(make_shared<gte>(), nullptr);

pClause pccut = make_shared<Clause>(make_shared<cut>(), nullptr);



prog = make_shared<Program>(pcis, nullptr);
prog = prog->append(make_shared<Program>(pcneq,nullptr));
prog = prog->append(make_shared<Program>(pceqx,nullptr));
//prog = prog->append(make_shared<Program>(pceq,nullptr));
prog = prog->append(make_shared<Program>(pclt,nullptr));
prog = prog->append(make_shared<Program>(pclte,nullptr));
prog = prog->append(make_shared<Program>(pcgt,nullptr));
prog = prog->append(make_shared<Program>(pcgte,nullptr));

prog = prog->append(make_shared<Program>(pccut,nullptr));

cout<<"builtinPreds() prog= "; prog->print(); cout<<endl;
return prog;
} 

pProgV builtinPredsV()
{vector<pClause> rules;
rules.push_back(make_shared<Clause>( make_shared<is>(),nullptr) );
rules.push_back(make_shared<Clause>(make_shared<notequal>(), nullptr));
rules.push_back( make_shared<Clause>(make_shared<equalx>(), nullptr));
		// make_shared<equal>()  fails
//pClause pceq = make_shared<Clause>(make_shared<equal>(), nullptr);
rules.push_back( make_shared<Clause>(make_shared<lt>(), nullptr));
rules.push_back( make_shared<Clause>(make_shared<lte>(), nullptr));
rules.push_back( make_shared<Clause>(make_shared<gt>(), nullptr));
rules.push_back( make_shared<Clause>(make_shared<gte>(), nullptr));

rules.push_back( make_shared<Clause>(make_shared<cut>(), nullptr));
rules.push_back( make_shared<Clause>(make_shared<call>(), nullptr));

return make_shared<ProgV>(rules);
}
//-------------------------
string script_not()			// not used, ! not correct
{ string str=
  "not(X) :- X,!,fail.  not(X). " ;
  return str;
}
string script_append()
{ string str =
 	"append([],L,L). append( [X|L1], L2, [X|L3]) :- append(L1,L2, L3). ";
  return str;
}


void readInitScripts()		// predefined predicate scripts
{


}




