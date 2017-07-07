/* Triplas pitagóricas com valores menores do que N */
pythag(X,Y,Z,N) :-
   length(_, N),
   between(1,N,X),
   between(1,N,Y),
   between(1,N,Z),
   Z*Z =:= X*X + Y*Y.
