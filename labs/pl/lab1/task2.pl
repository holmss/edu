% Вариант 2
% Задание three.pl
:- ['three.pl'].

% 1. Напечатать средний балл для каждого студента и сдал ли он экзамены

% student(102,'Петров',[grade('LP',3),grade('MTH',4),grade('FP',4),grade('INF',4),grade('ENG',5),grade('PSY',4)]).
sum([], 0).
sum([H|Lst], Res) :-
    H=grade(_, Num),
    sum(Lst, Res2),
    Res is Num+Res2.

middle_grade_sum(Stud, Sum, Pass) :-
    student(_, Stud, Lst),
    sum(Lst, Summ),
    (   member(grade(_,2), Lst),
        Pass=no
    ;   Pass=yes
    ),
    length(Lst, Len),
    Sum is Summ/Len.

middle :-
    findall(Stud, student(_, Stud, _), Lst),
    middle(Lst).
middle([]).  
middle([H|List]):-
    middle_grade_sum(H,Sum,Pass),
    write(Sum),write(" это средняя оценка "),write(H),write(". Сдал: "),writeln(Pass),
    middle(List).

%2. Для каждого предмета, найти количество не сдавших студентов

getsubs :-
    setof(Sub, (student(_, _, Elem), member(grade(Sub, _), Elem)), Result),
    pass(Result).

pass([]).
pass([Sub|Subjects]):-
    pass(Subjects),
    findall(Name,(student(_,Name,Elem),member(grade(Sub,2),Elem)), Lst),
    length(Lst, Len),
    write(Len), write(" <- кол-во студентов, не сдавших "), writeln(Sub).

%3. Для каждой группы, найти студента (студентов) с максимальным средним баллом

sum([], 0).
sum([H|Lst], Res) :-
    H=grade(_, Num),
    sum(Lst, Res2),
    Res is Num+Res2.

middle_grade_sum(Stud, Sum) :-
    student(_, Stud, Lst),
    sum(Lst, Summ),
    length(Lst, Len),
    Sum is Summ/Len.

middle_grade_group_list(Group, [Student|Students], [MGGL|Grades]) :-
    middle_grade_sum(Student, MGGL),
    append(MGGL, Grades, Fin),
    middle_grade_group_list(Group, Students, Grades),
    write(Fin).
    

max([], 0).
max([H|Tail], M) :-
    max(Tail, N),
    (N > H -> M is N; M is H).

