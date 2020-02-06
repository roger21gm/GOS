grammar CSP2SAT;


TK_CLASS: 'class';

TK_CONST: 'const';
TK_VAR: 'var';
TK_AUX: 'aux';

TK_CONSTRAINT: 'constraint';

TK_INT_VALUE: ('1'..'9')('0'..'9')* | '0';
TK_BOOLEAN_VALUE: 'true' | 'false';

TK_BASE_TYPE: 'int' | 'bool';

TK_IN: 'in';
TK_RANG_DOTS: '..';

TK_IF: 'if';
TK_ELSEIF: 'else if';
TK_ELSE: 'else';

TK_LPAREN: '(';
TK_RPAREN: ')';

TK_LCLAUDATOR: '{';
TK_RCLAUDATOR: '}';

TK_LBRACKET: '[';
TK_RBRACKET: ']';

TK_PIPE: '|';

TK_COMMA: ',';
TK_DOT: '.';

TK_WHERE: 'where';

TK_FORALL: 'forall';


TK_OP_LOGIC_NOT: '!';
TK_OP_LOGIC_AND: '&&';
TK_OP_LOGIC_OR: '||';

TK_OP_ARIT_SUM: '+';
TK_OP_ARIT_DIFF: '-';
TK_OP_ARIT_MULT: '*';
TK_OP_ARIT_DIV: '/';
TK_OP_ARIT_MOD: '%';

TK_OP_REL_LT: '<';
TK_OP_REL_GT: '>';
TK_OP_REL_GE: '>=';
TK_OP_REL_LE: '<=';
TK_OP_REL_EQ: '==';
TK_OP_REL_NEQ: '!=';

TK_INTERROGANT: '?';
TK_DOSPUNTS: ':';

TK_EQ: '=';

TK_IDENT: ( ('a'..'z' | 'A'..'Z' | '_')('a'..'z' | 'A'..'Z' | '_' | '0'..'9')* );


// SINTÀCTIC

init: (defConst | defVariable | defVariableAux | defClass )*;

defConst: TK_CONST (TK_BASE_TYPE | TK_IDENT) (TK_IDENT | defArray) rang?;
defVariable: TK_VAR (TK_BASE_TYPE | TK_IDENT) (TK_IDENT | defArray) rang?;
defVariableAux: TK_AUX (TK_BASE_TYPE | TK_IDENT) TK_IDENT TK_EQ expr;

defArray: TK_IDENT TK_LBRACKET expr TK_RBRACKET (TK_LBRACKET expr TK_RBRACKET)?;

defClass: TK_CLASS TK_IDENT TK_LCLAUDATOR (defVariable | defVariableAux | defConst)* defNamedConstraint* TK_RCLAUDATOR;

defNamedConstraint: TK_CONSTRAINT TK_IDENT TK_LCLAUDATOR defConstraint* TK_RCLAUDATOR;
defConstraint: forall | conditional | expr | functionCall;

forall: TK_FORALL TK_LPAREN TK_IDENT rang TK_RPAREN TK_LCLAUDATOR defConstraint* TK_RCLAUDATOR;
conditional:
    TK_IF TK_LPAREN expr TK_RPAREN TK_LCLAUDATOR defConstraint* TK_RCLAUDATOR
    (TK_ELSEIF TK_LPAREN expr TK_RPAREN TK_LCLAUDATOR defConstraint* TK_RCLAUDATOR)*
    (TK_ELSE TK_LCLAUDATOR defConstraint* TK_RCLAUDATOR)*;

rang: TK_IN expr TK_RANG_DOTS expr;

functionCall: TK_IDENT TK_LPAREN list TK_RPAREN;


list: TK_IDENT | comprehensionList;

comprehensionList:
    TK_LBRACKET expr TK_PIPE
        ((TK_IDENT rang)(TK_COMMA TK_IDENT rang)*)
        (TK_WHERE expr)?
    TK_RBRACKET;

valueBaseType: TK_INT_VALUE | TK_BOOLEAN_VALUE;

array_access: TK_IDENT TK_LBRACKET expr TK_RBRACKET (TK_LBRACKET expr TK_RBRACKET)?;
object_attribute: (TK_IDENT | array_access) TK_DOT TK_IDENT;

expr: expr_6 | (expr_6 TK_INTERROGANT expr TK_DOSPUNTS expr);
expr_6: expr_5 (( TK_OP_LOGIC_AND | TK_OP_LOGIC_OR ) expr_5)*;
expr_5: expr_4 (( TK_OP_REL_LT | TK_OP_REL_GT | TK_OP_REL_GE | TK_OP_REL_LE | TK_OP_REL_EQ | TK_OP_REL_NEQ ) expr_4)*;
expr_4: expr_3 ((TK_OP_ARIT_SUM | TK_OP_ARIT_DIFF) expr_3)*;
expr_3: expr_2 ((TK_OP_ARIT_MULT | TK_OP_ARIT_DIV | TK_OP_ARIT_MOD) expr_2)*;
expr_2: TK_OP_LOGIC_NOT? expr_base;
expr_base: valueBaseType | TK_LPAREN expr TK_RPAREN | TK_IDENT | array_access | object_attribute | functionCall;