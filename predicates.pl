% predicates.pl		standard predicates


=(X,X).


remove(X, [], []).
remove(X, L, Lxr) :-
	%split(X,L,L1,L2),
	append(L1, [X|L2], L),
	append(L1,L2,Lxr).


split(X, L, L1, L2)	:-	
	append( L1, [X|L2], L).

append([],L,L).
append([H|T], L2, [H|L3]) :- append(T, L2, L3).

member(X, [X|T]).
member(X, [H|T]) :- member(X,T).

length([],0).
length([H|T],N) :- length(T,Nt), is(N, +(Nt,1)).





