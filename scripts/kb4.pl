% kb4.pl, LPN, p.8

woman(mia).
woman(jody).
woman(yolanda).

loves(vincent,mia).
loves(marcellus,mia).
loves(pumpkin,honey_bunny).
loves(honey_bunny,pumpkin).

%?- woman(X).
?- loves(marcellus,X),woman(X).






