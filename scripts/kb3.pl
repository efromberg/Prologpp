% LPN, p.6 kb3.pl

happy(vincent).
listens2Music(butch).
playsAirGuitar(vincent):- listens2Music(vincent),happy(vincent).
playsAirGuitar(butch):- happy(butch).
playsAirGuitar(butch):- listens2Music(butch).

?- playsAirGuitar(vincent).
?- playsAirGuitar(butch).







