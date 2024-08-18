% Nqueens2.pl		Bratko, p.116,  prefix notation for lists
% swipl Nqueens.pl	?- solution(20,S).  works
% adapt for prologpp   prefix notation
% N,  level		seconds to first-final answer
% 4		94					(Nans=2)
% 5	    125					(Nans=10)
% 6		163					(Nans=4)
%				valgrind: no leaks are possible,  0 errors
% 7		201		.03-2.5		(Nans=40)
% 8		244		.6-10.3		(Nans=92)
% 9		283		.25-51.3	(Nans=352)
% 10	334		.76-251.8	(Nans=724)
% 11	390		.44-1333.9	(Nans=2680)
% 12	437		2.5 Total(max=100): 159.5
% 14	555		23,
% 15	601		18.9, 74.5
% 16	673		147.5	152.3,305.9,316.7,
%  Memory usage basic(no Firefox) is 2.5 GB, no extra for N=16
% 16	673		156.3				(2.5GB,Nans=137,Time=870.8) ^C
% 17	733		89.3, 109.
% 18	809		716.5, 15 answers,till 2271.9 sec, then Killed by OS
% 19
% Coords:  x,y, u,v; u = x-y (upward diags), v = x+y (downward diags)
% Domains: Dx=[1,...N]; Dy=[1,...N]; Du=[-(N-1),...,(N-1)]; Dv=[2,...2*N]
% Algorithm: Select N tuples (x,y,u,v);  each{x,y,u,v} unique
%	Each domain is a list
%	Select 1st pt: (x1,y1,u1,v1) remove it from the domains; (x1=1) 

gen(N,N,.(N,nil)).		% Generate Domain D=[N1,...N2]
gen(N1,N2, .(N1,List)):-
	<(N1,N2),
	is(M, +(N1,1)),
	gen(M,N2,List).		% List=[N1, N1+1,..., N2-1, N2]

sol(nil,nil,Dy,Du,Dv).
sol( .(Y,Ylist), .(X,Dx1), Dy, Du, Dv):-
	del(Y,Dy,Dy1),		
	is(U, -(X,Y)),		% U = X - Y	 upward diagonal, u=x-y
	del(U,Du,Du1),
	is(V, +(X,Y)),		% V = X + Y	 downward diagonal, v=x+y
	del(V,Dv,Dv1),
	sol(Ylist, Dx1,Dy1,Du1,Dv1).

del(A, .(A,List), List).		% delete A from List
del(A, .(B, List), .(B,List1)):-
	del(A, List, List1).

solution(N,S):-
	gen(1, N, Dxy),		% Dxy=[1, 2, ..., N]
	is(Nu1, -(1,N)),	% Nu1 = 1-N
	is(Nu2, -(N,1)),	% Nu2 = N-1
	gen(Nu1, Nu2, Du),	% Du = [1-N, ..., N-1]
	is(Nv2, +(N,N)),	% Nv2 = 2*N
	gen(2, Nv2, Dv),
	sol(S, Dxy, Dxy, Du, Dv).

?- solution(5, S).
%?- solution(5, .(5,.(2,.(4,.(1,.(3,nil)))))).
%?- solution(6,S).
%?- solution(7,S).

