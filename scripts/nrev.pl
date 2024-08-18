% nrev.pl  LPN, p113,  naive reverse of a list

	nil.
	append( nil,L,L).
	append( .(H,T), L2, .(H,L3)) :- append(T, L2, L3).



	nrev(nil, nil).
	nrev( .(H,T), R) :- nrev( T, RevT), append(RevT, .(H,nil), R).

?- nrev( .(a, .(b, .(c,nil))) , R).





