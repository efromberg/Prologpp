% length3.pl	11/10/22  length of a list

length([],0).
length([H|T], N) :- 
	length(T, N1), is(N, +(N1,1)).
	
	



