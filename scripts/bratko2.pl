% Bratko, p.44

big(bear).
big(elephant).
small(cat).
brown(bear).
black(cat).
gray(elephant).
dark(Z) :- black(Z).
dark(Z) :- brown(Z).

?- dark(X),big(X).

?- big(X),dark(X).

