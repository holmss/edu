%В одном городе живут 5 человек. Их имена Леонид, Михаил, Николай, Олег и Петр. 
%Их фамилии Атаров, Бартенев, Кленов, Данилин и Иванов. 
%Бартенев знаком только с двумя из перечисленных мужчин. Петр знаком со всеми, кроме одного. 
%Леонид знаком только с одним из всех. Данилин и Михаил незнакомы. Николай и Иванов знают друг друга. 
%Михаил, Николай и Олег знакомы между собой. Атаров незнаком только с одним из всех. Только один из всех знаком с Кленовым. 
%Назовите имена и фамилии каждого. С кем знаком каждый из них?

% name("Леонид").
% name("Михаил").
% name("Николай").
% name("Олег").
% name("Петр").

% surname("Атаров").
% surname("Бартенев").
% surname("Кленов").
% surname("Данилин").
% surname("Иванов").

% person(Name, Surname,[]) :- name(Name), surname(Surname).

% familiar(P1, P2, Flist) :- member([P1,P2], Flist); member([P2,P1], Flist).

% friends_num(_,[],0).
% friends_num(X,[H|Tail],N):-familiar(X,H,N1),!,friends_num(X,Tail,N1), N is N1+1.
% friends_num(X,[_|Tail],N):-friends_num(X,Tail,N).


solve([leonid/F1/Z1, mihail/F2/Z2, nikolai/F3/Z3, oleg/F4/Z4, petr/F5/Z5]):-
    permutation([atarov, bartenev, klenov, danilin, ivanov], [F1, F2, F3, F4, F5]), F3 \= ivanov,
    sublist(Z5, [leonid/F1, mihail/F2, nikolai/F3, oleg/F4]), Z5 = [_, _, _],
    sublist(Z1, [petr/F5, mihail/F2, nikolai/F3, oleg/F4]), Z1 = [_],
    member(mihail, Z3), member(mihail, Z4), member(nikolai, Z2), member(nikolai, Z4),
    member(oleg, Z2), member(oleg, Z3), F2 \= danilin, (not(member(leonid, mihail)):- F1 == danilin).