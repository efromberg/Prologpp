% father.pl		Clocksin p.74

father(mary, george).
father(john, george).
father(sue, harry).
father(george, edward).

?- father(_,Y).	% prints value of _, should suppress that.


