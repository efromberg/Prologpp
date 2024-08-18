% 8queens1.pl  Bratko, version 1, 4.5.1, p.109
% use p(X,Y), not X/Y
% p(X,Y): (column, row) of queen
% 

solution([]).					% no queens ==> no attack
solution([p(X,Y) | Others]) :-
	solution(Others),
	member(Y,[1,2,3,4,5,6,7,8]),
	noattack(p(X,Y), Others).
	
noattack(_, []).

noattack(p(X,Y), [ p(X1,Y1) | Others]) :-
	=\=(Y,Y1),					% both not on same row
	=\=(-(Y1,Y), -(X1,X)),		% both not on up diagonal
	=\=(-(Y1,Y), -(X,X1)),		% both not on down diagonal
	noattack(p(X,Y), Others).
	
member(X, [X|L]).
member(X, [Y|L]) :- member( X, L).

%     Y1 is in column 1, Y2 is in column 2,...
template( [p(1,Y1), p(2,Y2), p(3,Y3), p(4,Y4),
	p(5,Y5), p(6,Y6), p(7, Y7), p(8, Y8)]).

?- template(S),solution(S).


 
