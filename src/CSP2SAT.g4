grammar CSP2SAT;

WS  : [ \t\r]+ -> skip;

LINE_COMMENT : '//' ~[\r\n]* -> skip;

// basic structure
TK_TYPES: 'types';
TK_VARS: 'vars';
TK_CONSTRAINTS: 'constraints';

TK_COLON: ':';
TK_SEMICOLON: ';';

TK_UNDERSCORE: '_';

TK_ASSIGN: ':=';

TK_CONST: 'const';
TK_VAR: 'var';
TK_AUX: 'aux';

TK_CONSTRAINT: 'constraint';

TK_INT_VALUE: ('1'..'9')('0'..'9')* | '0';
TK_BOOLEAN_VALUE: 'true' | 'false';

TK_BASE_TYPE: 'int' | 'bool';

TK_IN: 'in';
TK_RANGE_DOTS: '..';

TK_IF: 'if';
TK_ELSEIF: 'else if';
TK_ELSE: 'else';

TK_LPAREN: '(';
TK_RPAREN: ')';

TK_LCLAUDATOR: '[';
TK_RCLAUDATOR: ']';

TK_LBRACKET: '{';
TK_RBRACKET: '}';


TK_COMMA: ',';
TK_DOT: '.';

TK_WHERE: 'where';

TK_FORALL: 'forall';


// EXPRESSIONS BOOLEANES
// NOT
// AND &&
// OR ||


//CLÀUSULES
TK_OP_LOGIC_NOT: '!';
TK_OP_LOGIC_AND: '&';
TK_OP_LOGIC_OR_PIPE: '|';

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

TK_OP_IMPLIC_R: '->';
TK_OP_IMPLIC_L: '<-';
TK_OP_DOUBLE_IMPLIC: '<->';

TK_INTERROGANT: '?';

TK_CONSTRAINT_OR: 'or';
TK_CONSTRAINT_AND: 'and';



TK_IDENT: ( ('a'..'z' | 'A'..'Z' | '_')('a'..'z' | 'A'..'Z' | '_' | '0'..'9')* );


// SINTÀCTIC

csp2sat: typeDefinitionBlock? varDefinitionBlock? constraintDefinitionBlock?;


typeDefinitionBlock: TK_TYPES TK_COLON typeDefinition* ;
typeDefinition: TK_IDENT TK_LBRACKET (varDefinition | constDefinition)* TK_RBRACKET TK_SEMICOLON;

varDefinitionBlock: TK_VARS TK_COLON (varDefinition | constDefinition)*;

constraintDefinitionBlock: TK_CONSTRAINTS TK_COLON constraintDefinition*;


varDefinition: TK_VAR varConstDef TK_SEMICOLON;
constDefinition: TK_CONST (varConstDef | auxiliarConstDef) TK_SEMICOLON;

varConstDef: type=(TK_IDENT | TK_BASE_TYPE) name=TK_IDENT (TK_LCLAUDATOR index=expr TK_RCLAUDATOR)*  rang=range?;
auxiliarConstDef: (TK_IDENT | TK_BASE_TYPE) TK_IDENT TK_ASSIGN expr;

constraintDefinition: (forall | ifThenElse | expr | functionCall) TK_SEMICOLON;

// CONSTRAINTS
forall: TK_FORALL TK_LPAREN TK_IDENT range TK_RPAREN TK_LBRACKET constraintDefinition* TK_RBRACKET;
ifThenElse:
    TK_IF TK_LPAREN expr TK_RPAREN TK_LBRACKET constraintDefinition* TK_RBRACKET
    (TK_ELSEIF TK_LPAREN expr TK_RPAREN TK_LBRACKET constraintDefinition* TK_RBRACKET)*
    (TK_ELSE TK_LPAREN expr TK_RPAREN TK_LBRACKET constraintDefinition* TK_RBRACKET)?;

functionCall: TK_IDENT TK_LPAREN (expr | list) TK_RPAREN;

list:
      (TK_LCLAUDATOR expr TK_OP_LOGIC_OR_PIPE TK_IDENT (TK_COMMA TK_IDENT)* range (TK_WHERE expr)? TK_RCLAUDATOR) // [a*b | a,b in 1..3 where a < 2]
    | (TK_LCLAUDATOR expr TK_OP_LOGIC_OR_PIPE TK_IDENT TK_IN TK_IDENT (TK_WHERE expr)? TK_RCLAUDATOR) // [ point.x | point in points where point.y < 3 ]
    | (TK_IDENT TK_LCLAUDATOR expr TK_RCLAUDATOR TK_LCLAUDATOR TK_UNDERSCORE TK_RCLAUDATOR) // points[2][_]
    | (TK_IDENT TK_LCLAUDATOR TK_UNDERSCORE TK_RCLAUDATOR TK_LCLAUDATOR expr TK_RCLAUDATOR); // points[_][2]

range: TK_IN expr TK_RANGE_DOTS expr;

expr: expr_6 | (expr_6 TK_INTERROGANT expr TK_COLON expr);
expr_6: expr_5 (op=( TK_OP_LOGIC_AND | TK_OP_LOGIC_OR_PIPE ) expr_5)*;
expr_5: expr_4 (op=( TK_OP_REL_LT | TK_OP_REL_GT | TK_OP_REL_GE | TK_OP_REL_LE | TK_OP_REL_EQ | TK_OP_REL_NEQ ) expr_4)*;
expr_4: expr_3 (op=(TK_OP_ARIT_SUM | TK_OP_ARIT_DIFF) expr_3)*;
expr_3: expr_2 (op=(TK_OP_ARIT_MULT | TK_OP_ARIT_DIV | TK_OP_ARIT_MOD) expr_2)*;
expr_2: op=TK_OP_LOGIC_NOT? expr_base;
expr_base: valueBaseType | TK_LPAREN expr TK_RPAREN | TK_IDENT | array_access | object_attribute; //TODO: Function CALL??

valueBaseType: TK_INT_VALUE | TK_BOOLEAN_VALUE;
array_access: TK_IDENT TK_LCLAUDATOR expr TK_RCLAUDATOR (TK_LCLAUDATOR expr TK_RCLAUDATOR)?;
object_attribute: (TK_IDENT | array_access) TK_DOT expr;


constraint:
    constraint_double_implication
|   constraint_and_implication
|   constraint_or_implication
|   constraint_and
|   constraint_or
|   constraint_literal;

constraint_double_implication:
        constraint_literal TK_OP_DOUBLE_IMPLIC constraint_and
    |   constraint_and TK_OP_DOUBLE_IMPLIC constraint_literal
    |   constraint_literal TK_OP_DOUBLE_IMPLIC constraint_or
    |   constraint_or TK_OP_DOUBLE_IMPLIC constraint_literal;

constraint_and_implication: constraint_and TK_OP_IMPLIC_R constraint_or;
constraint_or_implication: constraint_or TK_OP_IMPLIC_L constraint_and;

constraint_and:
        constraint_literal (TK_OP_LOGIC_AND constraint_literal)*
    |   TK_CONSTRAINT_AND TK_LPAREN list TK_RPAREN;
constraint_or:
        constraint_literal (TK_OP_LOGIC_OR_PIPE constraint_literal)*
    |   TK_CONSTRAINT_OR TK_LPAREN list TK_RPAREN;
constraint_literal: TK_OP_LOGIC_NOT? constraint_var;
constraint_var: TK_IDENT | array_access | object_attribute;