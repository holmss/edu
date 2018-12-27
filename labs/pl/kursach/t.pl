sex(P,S):-
    parent(_,P,_),
    S = m,!;
    parent(_,_,P), 
    S = f,!.

