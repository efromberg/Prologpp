%  lpn74.pl		head, tail of a list

=(X,X).			% not a built in predicate (yet) !

% [H|T] = [mia, vincent, jules, yolanda].

%?- =( .(H, T), .(mia, .(vincent, .(jules, .(yolanda,nil))))).
?- =( .(H1, .(H2,T)), .( .(mia,nil), .(vincent, .(jules, .(yolanda,nil))))).

