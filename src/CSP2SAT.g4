grammar CSP2SAT;

INT : [0-9]+;
WS  : [ \t\r]+ -> skip;
NL  : '\n';

input
    : NL? EOF
    ;
