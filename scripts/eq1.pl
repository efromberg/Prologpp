% eq1.pl,  LPN, p.24, 27
% https://www.metalevel.at/prolog/concepts Built-ins
%	=,  true.,  false.
% https://en.wikibooks.org/wiki/Prolog/Lists built-in definitions (on lists)
%	last(), member(), append(), reverse(), length()

=(X,X).				% define =/2
%true.				% define true/0
%false :- =(a,b).	% define false/0



?- =( k(s(g),Y),k(X,t(k))).
?- =( k(s(g),t(k)), k(X,t(Y))).
?- =( loves(X,X), loves(mia,mia)).

% ?- =( father(X), X).		% core dump LPN, p.29


