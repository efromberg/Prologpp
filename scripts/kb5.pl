% kb5.pl, p.10 LPN

loves(vincent, mia).
loves(marsellus,mia).
loves(pumpkin, honey_bunny).
loves(honey_bunny,pumpkin).
jealous(X,Y):- loves(X,Z),loves(Y,Z).

?- jealous(marsellus,W).
%?- jealous(vincent,X).

