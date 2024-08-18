% facts
% http://learnprolognow.org/lpnpage.php?pagetype=html&pageid=lpn-htmlse7
% LPN, Exercise 2.4, p.41
% swipl

word(astante, a,s,t,a,n,t,e).
word(astoria, a,s,t,o,r,i,a).
word(baratto,  b,a,r,a,t,t,o).
word(cobalto,  c,o,b,a,l,t,o).
word(pistola,  p,i,s,t,o,l,a).
word(statale,  s,t,a,t,a,l,e).

word(abalone, a,b,a,l,o,n,e).
word(abandon, a,b,a,n,d,o,n).
word(enhance, e,n,h,a,n,c,e).
word(anagram, a,n,a,g,r,a,m).
word(connect, c,o,n,n,e,c,t).
word(elegant, e,l,e,g,a,n,t).


cwd11(H1,V1,X):- word(H1, _, X, _,_,_,_,_),word(V1, _, X, _,_,_,_,_).
cwd12(H1,V2,X):- word(H1, _, _, _,X,_,_,_),word(V2, _, X, _,_,_,_,_).
cwd13(H1,V3,X):- word(H1, _, _, _,_,_,X,_),word(V3, _, X, _,_,_,_,_).
cwd21(H2,V1,X):- word(H2, _, X, _,_,_,_,_),word(V1, _, _, _,X,_,_,_).
cwd22(H2,V2,X):- word(H2, _, _, _,X,_,_,_),word(V2, _, _, _,X,_,_,_).
cwd23(H2,V3,X):- word(H2, _, _, _,_,_,X,_),word(V3, _, _, _,X,_,_,_).
cwd31(H3,V1,X):- word(H3, _, X, _,_,_,_,_),word(V1, _, _, _,_,_,X,_).
cwd32(H3,V2,X):- word(H3, _, _, _,X,_,_,_),word(V2, _, _, _,_,_,X,_).
cwd33(H3,V3,X):- word(H3, _, _, _,_,_,X,_),word(V3, _, _, _,_,_,X,_).


puzzle(H1,H2,H3,V1,V2,V3):- 
		cwd11(H1,V1,_),cwd12(H1,V2,_),cwd13(H1,V3,_),
		cwd21(H2,V1,_),cwd22(H2,V2,_),cwd23(H2,V3,_),
		cwd31(H3,V1,_),cwd32(H3,V2,_),cwd33(H3,V3,_).

?- puzzle(H1,H2,H3,V1,V2,V3).


