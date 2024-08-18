% 8queens6a.pl, 	WORKS with:  $ parse2 ../8queens6a.pl    !!!!

% from 8queens6.pl
% Bratko, p.134, 3rd version of 8 queens
% 6:   swipl: OK,  gprolog: fails
% 61:  swipl: fails
% solution(Ylist):-
%  sol(Ylist, 
%	[1,2,3,4,5,6,7,8],
%	[1,2,3,4,5,6,7,8],
%	[-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7],
%	[2,3,4,5,6,7,8,9,10,11,12,12,14,15,16] ).


solution(Ylist):-
  sol(Ylist,
	.(1, .(2, .(3, .(4, .(5, .(6, .(7, .(8, nil)))))))),
	.(1, .(2, .(3, .(4, .(5, .(6, .(7, .(8,nil)))))))),
	.(-7, .(-6, .(-5, .(-4, .(-3, .(-2, .(-1, .(0, .(1, .(2, .(3, .(4, .(5, .(6, .(7, nil))))))))))))))),
	.(2, .(3, .(4, .(5, .(6, .(7, .(8, .(9, .(10, .(11,
		.(12, .(13, .(14, .(15, .(16,nil))))))))))))))) ).

% sol([],[],Dy,Du,Dv).
sol(nil,nil,Dy,Du,Dv).

%sol([Y | Ylist],[X|Dx1],Dy,Du,Dv):-
sol( .(Y, Ylist), .(X,Dx1),Dy,Du,Dv):-
 del(Y,Dy,Dy1),
% U is X-Y,
 is(U, -(X,Y)),	% X-Y),
 del(U,Du,Du1),
% V is X+Y,
 is(V, +(X,Y)), 	%  X+Y),
 del(V,Dv,Dv1),
 sol(Ylist,Dx1,Dy1,Du1,Dv1).

% del(A, [A|List], List).
% del(A, [B | List], [B |List1]) :-
%	del(A, List, List1).

del(A, .(A, List), List).
del(A, .(B, List), .(B, List1)):-
	del(A, List, List1).

?- solution(X).


