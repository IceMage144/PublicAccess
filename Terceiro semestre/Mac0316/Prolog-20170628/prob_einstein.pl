/* -*- mode:prolog -*- */
/***************************************************
Problema atribuído a Einstein :

Em uma rua há cinco casas, uma de cada cor.

Em cada casa mora uma pessoa de uma nacionalidade diferente.  Cada um
dos moradores toma uma bebida distinta, fuma cigarros de uma marca
diferente e possui um animal de estimação único.

Queremos saber quem possui o peixe.

Existem 15 dicas:

 1. O inglês vive na casa vermelha.
 2. O sueco ama cachorros.
 3. O dinamarquês bebe chá.
 4. A casa verde é vizinha à esquerda da casa branca.
 5. O dono da casa verde bebe café.
 6. A pessoa que fuma  Pall Mall cria pássaros.
 7. O dono da casa amarela fuma Dunhill.
 8. O homem que mora da casa central bebe leite.
 9. O norueguês mora na primeira casa.
10. O fumante de Blends é vizinho do criador de gatos.
11. O homem que cuida de cavalos pé vizinho do fumante de Dunhill.
12. O fumante de  Blue Master bebe cerveja.
13. O alemão fuma Prince.
14. O norueguês mora ao lado da casa azul.
15. O fumante de  Blends tem um vizinho que bebe água.
*****************************************************/

/* Lista vazia */
persons(0, []) :- !.

/* Lista de N elementos */
persons(N, [(_Homem,_Cor,_Bebe,_Fuma,_Animal)|T]) :- N1 is N-1, persons(N1,T).

/* Pega o N-ésimo elemento */
/* H é head, T é tail*/
person(1, [H|_], H) :- !.
person(N, [_|T], R) :- N1 is N-1, person(N1, T, R).

/* Dicas */
%  1. O inglês vive na casa vermelha.
hint1([(inglês, vermelha,_, _, _)|_]).
hint1([_|T]) :- hint1(T).

%  2. O sueco ama cachorros.
hint2([(sueco,_,_,_,cachorro)|_]).
hint2([_|T]) :- hint2(T).

%  3. O dinamarquês bebe chá.
hint3([(dinamarquês,_,chá,_,_)|_]).
hint3([_|T]) :- hint3(T).

%  4. A casa verde é vizinha à esquerda da casa branca.
hint4([(_,verde,_,_,_),(_,branca,_,_,_)|_]).
hint4([_|T]) :- hint4(T).

%  5. O dono da casa verde bebe café.
hint5([(_,verde,café,_,_)|_]).
hint5([_|T]) :- hint5(T).
	 
%  6. A pessoa que fuma  Pall Mall cria pássaros.
hint6([(_,_,_,pallmall,pássaro)|_]).
hint6([_|T]) :- hint6(T).

%  7. O dono da casa amarela fuma Dunhill.
hint7([(_,amarela,_,dunhill,_)|_]).
hint7([_|T]) :- hint7(T).

%  8. O homem que mora da casa central bebe leite.
hint8(Persons) :- person(3, Persons, (_,_,leite,_,_)).

%  9. O norueguês mora na primeira casa.
hint9(Persons) :- person(1, Persons, (norueguês,_,_,_,_)).

% 10. O fumante de Blends é vizinho do criador de gatos.
hint10([(_,_,_,blends,_),(_,_,_,_,gato)|_]).
hint10([(_,_,_,_,gato),(_,_,_,blends,_)|_]).
hint10([_|T]) :- hint10(T).

% 11. O homem que cuida de cavalos pé vizinho do fumante de Dunhill.
hint11([(_,_,_,dunhill,_),(_,_,_,_,cavalo)|_]).
hint11([(_,_,_,_,cavalo),(_,_,_,dunhill,_)|_]).
hint11([_|T]) :- hint11(T).

% 12. O fumante de  Blue Master bebe cerveja.
hint12([(_,_,cerveja,bluemaster,_)|_]).
hint12([_|T]) :- hint12(T).

% 13. O alemão fuma Prince.
hint13([(alemão,_,_,prince,_)|_]).
hint13([_|T]) :- hint13(T).

% 14. O norueguês mora ao lado da casa azul.
hint14([(norueguês,_,_,_,_),(_,azul,_,_,_)|_]).
hint14([(_,azul,_,_,_),(norueguês,_,_,_,_)|_]).
hint14([_|T]) :- hint14(T).

% 15. O fumante de  Blends tem um vizinho que bebe água.
hint15([(_,_,_,blends,_),(_,_,água,_,_)|_]).
hint15([(_,_,água,_,_),(_,_,_,blends,_)|_]).
hint15([_|T]) :- hint15(T).



% quem tem o peixe?
question([(_,_,_,_,peixe)|_]).
question([_|T]) :- question(T).

/* O conjunto de soluções é dada por: */

solution(Persons) :-
  persons(5, Persons),			% cria 5 pessoas
  hint1(Persons),				% verifica as dicas
  hint2(Persons),
  hint3(Persons),
  hint4(Persons),
  hint5(Persons),
  hint6(Persons),
  hint7(Persons),
  hint8(Persons),
  hint9(Persons),
  hint10(Persons),
  hint11(Persons),
  hint12(Persons),
  hint13(Persons),
  hint14(Persons),
  hint15(Persons),
  question(Persons).			% verifica a pergunta

%% é só chamar solution(P)
