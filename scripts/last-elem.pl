% P01 (*): Find the last element of a list
% https://www.ic.unicamp.br/~meidanis/courses/mc336/2009s2/prolog/problemas/
% my_last(X,L) :- X is the last element of the list L
%    (element,list) (?,?)

% Note: last(?Elem, ?List) is predefined

my_last(X,[X]).
my_last(X,[_|L]) :- my_last(X,L).

% ?- my_last(X, [a, b, c]).
