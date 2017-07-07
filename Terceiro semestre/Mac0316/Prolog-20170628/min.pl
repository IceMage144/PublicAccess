minimo(X,Y,X) :-
	X < Y,
	!.
minimo(X,Y,Y) :-
	Y < X.

