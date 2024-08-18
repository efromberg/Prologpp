% add.pl		LPN,  p.57

add(0,Y,Y).
add(succ(X),Y,succ(Z)):-add(X,Y,Z).

?- add(succ(succ(succ(0))), succ(succ(0)),R).	% R= 5 = 3 + 2



