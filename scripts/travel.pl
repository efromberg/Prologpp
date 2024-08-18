% travel.pl		Sect. 2.6 T. van Le


% direct(A,B) facts:  A,B are integers

direct(1,2).
direct(2,4).
direct(1,3).
direct(3,5).
direct(4,5).



travelling(A,B) :- travel(A,B,[A]).

travel(A,B,_) :- direct(A,B).
travel(A,B,List) :-
	direct(A,C),
	not_visit(C, List),
	travel(C,B,[C|List]).

not_visit(_, []).
not_visit(C,[C1|List]) :-
	=\=(C,C1),
	not_visit(C,List).




% ?- travelling(1,4).	yes

