%   wizard.pl   LPN, p.16

wizard(ron).
hasWand(harry).
quidditchPlayer(harry).
wizard(X):- hasBroom(X),hasWand(X).
hasBroom(X):-quidditchPlayer(X).

?- wizard(Y)


