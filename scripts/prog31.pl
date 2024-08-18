%	prolog :- tutorial JRFisher
% https://www.cpp.edu/~jrfisher/
% https://skolemmachines.org/ThePrologTutorial/www/prolog_tutorial/pt_framer.html
% 3.1 Prolog derivation trees, choices, and unification
%  Datalog program (no functions).

p(a).
p(X) :- q(X),r(X).
p(X) :- u(X).
q(X) :- s(X).
r(a).
r(b).
s(a).
s(b).
s(c).
u(d).

?- p(X).

