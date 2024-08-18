% vhline.pl,  vert. & horiz. lines, LPN, p.31

vertical(line(point(X,Y), point(X,Z))).
horizontal(line(point(X,Y), point(Z,Y))).

?- vertical(line(point(1,1),point(1,3))).
?- vertical(line(point(1,1),point(3,2))).
?- horizontal(line(point(1,1), point(2,Y))).
?- horizontal(line(point(2,3), P)).




