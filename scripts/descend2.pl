% descend2.pl		LPN, p.60

child(anne,bridget).
child(bridget,caroline).
child(caroline, donna).
child(donna, emily).

descend(X,Y):-child(X,Z),descend(Z,Y).
descend(X,Y):-child(X,Y).

?-descend(X,Y).





