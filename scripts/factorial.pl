% factorial.pl	T. Van Le,  Figure 2.5, Example 2.3

factorial(0,1).
factorial(N,F) :-
	>(N,0), is(N1,-(N,1)),
	factorial(N1,F1),
	is(F, *(N,F1)).
	



