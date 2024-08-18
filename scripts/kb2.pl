% LPN, p.4 kb2.pl

happy(yolanda).
listens2Music(mia).
listens2Music(yolanda):-happy(yolanda).
playsAirGuitar(mia):-listens2Music(mia).
playsAirGuitar(yolanda):-listens2Music(yolanda).

?- playsAirGuitar(X).


