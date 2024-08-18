% 
% http://learnprolognow.org/lpnpage.php?pagetype=html&pageid=lpn-htmlse7
% LPN, Exercise 2.4, p.41
% 

% FACTS: List of words (5 letters each)
word(astan, a,s,t,a,n).
word(astor, a,s,t,o,r).
word(barat,  b,a,r,a,t).
word(cobal,  c,o,b,a,l).
word(pisto,  p,i,s,t,o).
word(stata,  s,t,a,t,a).

% RULES: Common letter at each intersection, H,V are words, X a letter
cwd11(H1,V1,X):- word(H1, _, X, _,_,_),word(V1, _, X, _,_,_).
cwd12(H1,V2,X):- word(H1, _, _, _,X,_),word(V2, _, X, _,_,_).

cwd21(H2,V1,X):- word(H2, _, X, _,_,_),word(V1, _, _, _,X,_).
cwd22(H2,V2,X):- word(H2, _, _, _,X,_),word(V2, _, _, _,X,_).

% Solution: Common letter at all intersections
puzzle(H1,H2,V1,V2):- 
		cwd11(H1,V1,_),cwd12(H1,V2,_),
		cwd21(H2,V1,_),cwd22(H2,V2,_).

% Query:
?- puzzle(H1,H2,V1,V2).

