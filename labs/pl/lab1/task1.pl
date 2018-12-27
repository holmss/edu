% Реализация стандартных предикатов обработки списков

% Длина списка
% (список, длина)
my_length([], 0).
my_length([_|L], N):-my_length(L, M), N is M + 1.

% Принадлежность элемента списку
% (элемент, список)
my_member(X, [X|_]).
my_member(X, [_|T]):-my_member(X, T).

% Конкатeнация списков
% (список1, список2, список1+2)
my_append([], L, L).
my_append([X|L1], L2, [X|L3]):-my_append(L1, L2, L3).

% Удаление элемента из списка
% (элемент, список, список без элемента)
my_remove(X, [X|T], T).
my_remove(X, [Y|T], [Y|Z]):-my_remove(X, T, Z).

% Удаление элемента с заданным номером
% (номер элемента, список, список без элемента)
change(0, [_|Res], Res).
change(N, [H|Lst], Res) :-
N>0,
N1 is N-1,
change(N1, Lst, R),
append([H], R, Res), !.

stdchange(Num, Lst, Res) :-
Num>=0,
length(HelpLst, Num),
append(HelpLst, Tail, Lst),
[_|TTail]=Tail,
append(HelpLst, TTail, Res).

% Перестановки элементов в списке
% (список, перестановка)
my_permute([], []).
my_permute(L, [X|T]):-my_remove(X, L, Y), my_permute(Y, T).

% Подсписки списка
% (подсписок, список)
my_sublist(S, L):-my_append(_, L1, L), my_append(S, _, L1).

% Добавление элемента в конец списка
% (элемент, список, список с новым элементом)
add_last_std(X, L1, L2):-append(L1, [X], L2).

% Добавление элемента в конец списка (без стандартных предикатов)
% (элемент, список, список с новым элементом)
add_last(X, [], [X]).
add_last(X, [H|T], [H|R]):-add_last(X, T, R).

% Вычисление суммы двух векторов-списков 
%(с учетом возможного несовпадения размерностей)
vector_sum([],[],[]).
vector_sum([Xh|X], [Yh|Y], [RRes|Res]) :-
RRes is Xh+Yh,
vector_sum(X,Y,Res).