% Nqueens.pl		Bratko, p.116, List notation [ ]
% swipl Nqueens.pl	?- solution(20,S).  works


gen(N,N,[N]).
gen(N1,N2,[N1|List]):-
	<(N1, N2),
	is(M, +(N1,1)),
	gen(M,N2,List).

sol([],[],Dy,Du,Dv).
sol([Y|Ylist], [X|Dx1], Dy, Du, Dv):-
	del(Y,Dy,Dy1),
	is(U, -(X,Y)),
	del(U,Du,Du1),
	is(V, +(X,Y)),
	del(V, Dv, Dv1),
	sol(Ylist, Dx1, Dy1, Du1, Dv1).

del(A, [A|List], List).
del(A, [B|List], [B|List1]):-
	del(A, List, List1).

solution(N,S):-
	gen(1, N, Dxy),
	is(Nu1, -(1,N)),
	is(Nu2, -(N,1)),
	gen(Nu1, Nu2, Du),
	is(Nv2, +(N,N)),
	gen(2, Nv2, Dv),
	sol(S, Dxy, Dxy, Du, Dv).

?- solution(5,S).


