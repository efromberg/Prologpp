% lpn106.pl, p.124,   10/26/22


append([],L,L).
append([H|T], L2, [H|L3]) :- append(T,L2,L3).

% ?- append([a,b,c],[1,2,3],L3).
% p.124

s(Z) :-  np(X), vp(Y), append(X,Y,Z).
np(Z) :- det(X), n(Y), append(X,Y,Z).
vp(Z) :-  v(X),np(Y), append(X,Y,Z).
vp(Z) :- v(Z).

det([the]).
det([a]).
n([woman]).
n([man]).
v([shoots]).

% ?- s(X).
