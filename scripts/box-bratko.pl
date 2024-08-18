% box-bratko.pl

% http://www.cs.otago.ac.nz/cosc347/References/LP/LeedsTutorial/node50.html
% An Example using the Byrd Box Model
% p.33


a(X,Y):- b(X,Y),c(Y).
b(X,Y):- d(X,Y),e(Y).
b(X,Y):- f(X).
c(4).
d(1,3).
d(2,4).
e(3).
f(4).

?- a(X,Y).






