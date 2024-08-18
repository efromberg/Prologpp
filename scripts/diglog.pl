% diglog.pl 	parse digital logic expressions
% Roth, Logic Design
% Grammer: LPN,p.124, p.132, B.Strous-3rd.p.108, Grammers-Warren

% expr  -> expr + term		logical or
%		-> term
% term	-> term * factor	logical and
%		-> factor
% factor -> 0, 1			logical values
%		->  var				logical variable: a,b,c...
%		-> -factor			logical not
%		-> (expr)		
%
% 
% 
% 
% 
%

append([],L,L).
append([H|T], L2, [H|L3]) :- append(T,L2,L3).

cons([0|W],W).
cons([1|W],W).
var([a|W],W).
var([b|W],W).
var([c|W],W).


% expr --> term.			p.132
% expr --> term plus expr.
% plus --> [+].
% term --> [a].
% term --> [b].
plus([+|W],W).
mult([*|W],W).
lparen(['('|W],W).
rparen([')'|W],W).

expr(X,Z) :- term(X,Z).
expr(X,Z) :- term(X,Y1), plus(Y1,Y2), expr(Y2,Z).

%term(X,Z) :- var(X,Z).
term(X,Z) :- factor(X,Z).
term(X,Z) :- factor(X,Y1), mult(Y1,Y2), term(Y2,Z).
factor(X,Z) :- var(X,Z).
factor(X,Z) :- cons(X,Z).
factor(X,Z) :- lparen(X,Y1), expr(Y1,Y2), rparen(Y2,Z).


%?- expr([a],[]).
% ?- expr([a,+,b],[]).

