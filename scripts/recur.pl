% recur.pl,  LPN p.55

numeral(0).
numeral(succ(X)) :- numeral(X).

?-  numeral(succ(succ(succ(0)))).
% ?- numeral(X).

add(0,Y,Y).
add(succ(X),Y,succ(Z)) :- add(X,Y,Z).

?- add(succ(succ(succ(0))), succ(succ(0)),R).
