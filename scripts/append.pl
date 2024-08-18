%  LPN p.106 Lists, Append		append.pl
% append/3 defined:
%	append([],L,L).
%	append([H|T], L2, [H|L3] :- append(T, L2, L3).
%  [a, b]== 	.(a, .(b,nullptr)).
%  [H | T] == .(H, .(T, nullptr)).
%	Problem:  nullptr is not a list
% or
%	[a, b] == .(a, .(b,[])).
%	[H | T] == .(H, T).
%	[] ==	Special list, = nil 
%	[ a ] == .(a,[]). == 
%	[a,b,c] == .(a, .(b, .(c,nil)))


%	nil.	
	append( nil,L,L).
%	append( dot(H, T), L2, dot(H, L3) ) :- append( T,L2,L3). 
	append( .(H,T), L2, .(H,L3)) :- append(T, L2, L3).append

% ?- append([a,b,c], [1,2,3], L3).
%?-	append( dot(a, dot(b, dot(c,nil))), dot(1,dot(2,dot(3,nil))), L3).
% nil explicitly appears in prefix notation for lists
%?- append( .(a, .(b, .(c,nil))), .(1, .(2, .(3,nil))) , L3).

?- append(X,Y, .(a, .(b, .(c, .(d, nil))))).

