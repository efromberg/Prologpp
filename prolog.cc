

#include "prolog.h"

// initialize static variables:
 int Var::timestamp = 0;
 pTrail Trail::sofar = nullptr;
map<string, pVar> Var::mTVar;


int Goal::Trace = 0;
int Goal::Nans = 0;
int Goal::Maxans = 10000;
int Goal::Ntries = 0;
int Goal::Nunifs = 0;
Timept Goal::Timestart = time_now();


void indent(int n)
{ for (int i = 0; i<n; i++) cout << "    "; }

// --- FUNCT -------------------------------------
 void Funct::print()
 { cout<<fsym;	//	fsym->print();
   if (arity>0)
	{ cout<<"(";
	  for(int i=0; i<arity; )
		{
		 args[i]->print();
		 if(++i < arity) cout<<",";
		}
	   cout<<")";
	 } 
}
Funct::Funct(Funct* p)
	:fsym(p->fsym),arity(p->arity),args(arity)
		{for(int i=0; i<arity;i++)args[i]=p->args[i]->copy(); }

 bool Funct::unify(pTerm t)
	{  return t->unify2(this); }

 bool Funct::unify2(Funct* t)	// unify(C1,C2)
	{  if(! (( fsym==t->fsym)	
			&& (arity==t->arity) ))
		{  return false;}
      for(int i=0; i<arity;i++)	// exec. if arity==0
		if(!args[i]->unify( t->args[i] ) )
		  { return false;} 
	  return true;
	}

long int Funct::eval()	// expect:  + _ * / only, arity=2
{ if( arity != 2)
	{ cout<< "Funct::eval() ERROR arity !=2,arity= "
			<< arity << endl;  return 0; }
  char ca = getfsym()[0];
  switch(ca){
	case '+': return args[0]->eval()+args[1]->eval();
	case '-': return args[0]->eval()-args[1]->eval();
	case '*': return args[0]->eval()*args[1]->eval();
	case '/': return args[0]->eval()/args[1]->eval();

	default: {cout<<"Funct::eval() ERROR operator= "
			<< (char)ca <<endl;}
}	// switch
	return 0;	// ERROR
}	// eval

// --- VAR --------------------------------------

void Var::print() {		// print chain of values, 10/10/21
		if(Goal::Trace > 0){
		  cout<<"_"<<varno;
			if(instance)
				{ cout<<":"; instance->print();}}
		else {	if(instance) instance->print();
				else cout<<"_"<<varno; };
		 };


bool Var::unify(pTerm t)
	{ 
    if(instance) return instance->unify(t);		//bound
	Trail::Push(shared_from_this() );			// unbound
	if( t.get() == this)   return true;		// same term
	instance= t; return true;}	

pTerm Var::copy()		// used in Goal::solve()
	{ 	if(!instance)	// unbound
	  		{ Trail::Push(this->shared_from_this());	
		  	  instance=make_shared<Var>();
			}
	    return instance;
	}
bool Var::unify2(Funct* t)
     { 	auto pfunc = t->shared_from_this(); 
		return this->unify(pfunc); 
		 }	
long int Var::eval(){
	if(instance) return instance->eval();
	cout<<"TermVar::eval() ERROR unbound Variable"<<endl;
		print(); cout<<endl;
		return 0;
}
// --- TRAIL ------------------------------------
void Trail::Undo(pTrail whereto)
		{ for(; sofar && sofar!= whereto; sofar=sofar->tcdr)
			{ sofar->tcar->reset();  }		// Variable unbound
		}
	// called by unify, copy
void Trail::Push(pVar x) {sofar = pTrail(new Trail(x,sofar));}

void Trail::print()
		{ 
			if(tcar) { tcar->print(); cout<<", ";
					   if(tcdr) tcdr->print();}
			else cout<<"tcar is null \n" <<endl;
			}
void Trail::prnsofar(int level)
		{indent(level); cout<< "Sofar: ";
		 if(Trail::sofar)
			if(Trail::sofar->tcar) 
				{Trail::sofar->tcar->print(); cout<<", ";
				 if(Trail::sofar->tcdr)
						Trail::sofar->tcdr->print();
				}
		 cout<<endl;
		}

// --- GOAL --------------------------------------
pGoal Goal::copy() { return pGoal(new Goal( ghead->copy2(),
					gtail==nullptr ? nullptr : gtail->copy())); }
pGoal Goal::append(pGoal l){ return pGoal(new Goal(ghead,
					gtail==nullptr ?  l : gtail->append(l)));}
void Goal::print() {
		 ghead->print();
			if(gtail != nullptr) {cout<<", "; gtail->print();}
		    }

//int Goal::nans =0;

void Goal::solve(pProg p, int level, pVarMap tmap)
{ int Np=0;	
        if(Trace >=1) {  
	 	indent(level); cout<<"solve@ "<<level <<": ";
		this->print(); cout <<endl;
			 }
	for(pProg q = p; q != nullptr; q = q->pcdr)// Program clause loop
	{		
		pTrail t = Trail::Note(); 	// t = sofar
		pClause c = q->pcar->copy(); // top clause of prog:q	
		++Np;
		Trail::Undo(t);	
		    if(Trace >=2) {
		    indent(level); cout<<"try c= ";c->print();
			 	cout<<" Np= "<< Np <<endl; 
			 	}				 
		++Ntries;
		if( ghead->unify(c->head))
		 { 	++Goal::Nunifs;	
		  pGoal gdash = c->body==nullptr ? gtail : c->body->append(gtail);
		  if(gdash==nullptr)
			{   tmap->showanswer(); 
				 ++Goal::Nans; 
				cout<<" (level= "<< level << ", Nans= "<<Goal::Nans;
					double Etime=timediff(Goal::Timestart, time_now());
					cout<<", Elapsed time: "<< Etime <<")";
				cout <<endl<<endl;
			  
			   if(Goal::Nans > Goal::Maxans)
				{cout<<"MaxAnswers= "<< Goal::Maxans
					<<", level= "<<level  <<endl; exit(1); }
			 }	// gdash==nullptr
		  else { 
				gdash->solve(p,level+1, tmap);  }
	     }	// if(...unify )

		else { if(Trace>=2)	// not unified, do next Program clause
					{indent(level); cout<<" nomatch.  \n"; }	
			 }		
		Trail::Undo(t);
	}	// for()	Program clause loop
}	// Goal::solve()

// --- CLAUSE -----------------------------------------------
//										need	copy2()  virtual
pClause Clause::copy(){return pClause(new Clause(head->copy2(),
					body==nullptr ? nullptr : body->copy())); }

void Clause::print(){
			  if(head == nullptr) cout<<"head==nullptr";//ERROR
			  else head->print();
			  cout<<":- ";
			  if(body==nullptr) cout<<"true";
			  else body->print();
			 }

void Program::print(){ pcar->print(); cout<<"\n";
				if(pcdr) pcdr->print(); }	// added 8/17/21


void Program::solve(pGoal pg, int level, pVarMap tmap)
{ int Trace = 0;
  int Nr=0;		// rule number
 if(Trace >=1)
	{ indent(level); cout<<"solve@ "<<level<<": ";
		pg->print();  cout << endl;   }
  for( pProg q = shared_from_this(); q != nullptr; q = q->pcdr)
	{ ++Nr;	//indent(level); cout<<"Nr= "<<Nr << endl;
	  pTrail t = Trail::Note();
	  pClause c = q->pcar->copy();
	  Trail::Undo(t);
	  if(pg->ghead->unify(c->head))
	    { //indent(level); cout<<"Nr= "<< Nr <<endl;
	      pGoal gdash = c->body==nullptr ? pg->gtail : 
	    				c->body->append(pg->gtail);
	      if(gdash==nullptr)
	        { tmap->showanswer();
	        }
	      else { solve(gdash, level+1, tmap); }
	    }	// if
	   else	
	     { if(Trace >=2) { indent(level);cout<<" nomatch. \n"; }
	     }
	 Trail::Undo(t);
	}	// for
}	// Program::solve()



void TermVarMapping::showanswer()
	{ if(size==0) cout<<"yes\n";
	  else
	  { for(int i=0; i<size;++i)
			{ cout<<vartext[i] <<" = ";
			 varvar[i]->print();
				cout<<"\n";
			}
	  }
	}
TermVarMapping::TermVarMapping(map<string,pVar> mTVar)
{int kit=0;
 size = mTVar.size();
 vartext.resize(size);
 varvar.resize(size);
map<string, pVar>::const_iterator it;
for(it=mTVar.begin(); it!=mTVar.end();++it)
{ vartext[kit]= it->first;
  varvar[kit] = it->second;
  ++kit;
}
 }	// TermVarMapping()

// UTILITY --- start, stop times: (using <chrono>  )
Timept time_now()
	{return chrono::high_resolution_clock::now(); }
// time difference in seconds
double timediff(Timept start, Timept stop)
{chrono::duration<double> elapsed = stop-start;
 return elapsed.count();	// time diff. in seconds
}

// ---------------------------------------------------






