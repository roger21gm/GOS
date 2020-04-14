grammar CSP2SAT;

WS
   : [ \t\n\r] + -> skip
   ;

LINE_COMMENT : '//' ~[\r\n]* -> skip;

// basic structure
TK_ENTITIES: 'entities';
TK_VIEWPOINT: 'viewpoint';
TK_CONSTRAINTS: 'constraints';

TK_COLON: ':';
TK_SEMICOLON: ';';

TK_UNDERSCORE: '_';

TK_ASSIGN: ':=';

TK_PARAM: 'param';
TK_VAR: 'var';
TK_AUX: 'aux';

TK_CONSTRAINT: 'constraint';

TK_INT_VALUE: ('1'..'9')('0'..'9')* | '0';
TK_BOOLEAN_VALUE: 'true' | 'false';

TK_BASE_TYPE_INT : 'int';
TK_BASE_TYPE_BOOL : 'bool';

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


//EXPRESSIONS
TK_OP_LOGIC_NOT: 'not';
TK_OP_LOGIC_AND: 'and';
TK_OP_LOGIC_OR: 'or';

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

TK_CONSTRAINT_OR_PIPE: '|';
TK_CONSTRAINT_AND: '&';
TK_CONSTRAINT_NOT: '!';



TK_IDENT: ( ('a'..'z' | 'A'..'Z' | '_')('a'..'z' | 'A'..'Z' | '_' | '0'..'9')* );


// SINTÀCTIC

csp2sat: entityDefinitionBlock? viewpointBlock? constraintDefinitionBlock?;

entityDefinitionBlock: TK_ENTITIES TK_COLON entityDefinition* ;
entityDefinition: name=TK_IDENT TK_LBRACKET (varDefinition | paramDefinition)* TK_RBRACKET TK_SEMICOLON;

viewpointBlock: TK_VIEWPOINT TK_COLON (varDefinition | paramDefinition)*;

constraintDefinitionBlock: TK_CONSTRAINTS TK_COLON constraintDefinition*;



varDefinition: TK_VAR type=TK_BASE_TYPE_BOOL? name=TK_IDENT arrayDefinition TK_SEMICOLON;
paramDefinition: (
        TK_PARAM type=(TK_BASE_TYPE_BOOL | TK_BASE_TYPE_INT)
        | type=TK_IDENT
    ) name=TK_IDENT arrayDefinition TK_SEMICOLON;

arrayDefinition: (TK_LCLAUDATOR arraySize=expr TK_RCLAUDATOR)*;

constraintDefinition: (forall | ifThenElse | functionCall | constraint | list)* TK_SEMICOLON;

// CONSTRAINTS
range: TK_IDENT TK_IN min=expr TK_RANGE_DOTS max=expr;

forall:
      TK_FORALL TK_LPAREN range (TK_COMMA range)* TK_RPAREN TK_LBRACKET constraintDefinition* TK_RBRACKET #rangeForall
    | TK_FORALL TK_LPAREN auxName=TK_IDENT TK_IN (arrId=varAccess | list) TK_RPAREN TK_LBRACKET constraintDefinition* TK_RBRACKET #arrayForall;

ifThenElse:
    TK_IF TK_LPAREN expr TK_RPAREN TK_LBRACKET constraintDefinition* TK_RBRACKET
    (TK_ELSEIF TK_LPAREN expr TK_RPAREN TK_LBRACKET constraintDefinition* TK_RBRACKET)*
    (TK_ELSE TK_LPAREN expr TK_RPAREN TK_LBRACKET constraintDefinition* TK_RBRACKET)?;

functionCall: TK_IDENT TK_LPAREN (expr | list) TK_RPAREN;

list: (TK_LCLAUDATOR (varAcc=constraint_literal | resExpr=expr ) TK_CONSTRAINT_OR_PIPE range (TK_COMMA range)* (TK_WHERE condExpr=expr)? TK_RCLAUDATOR); // [a*b | a in 1..3, b in 1..3 where a < 2]
//    | (TK_LCLAUDATOR expr TK_OP_LOGIC_OR_PIPE TK_IDENT TK_IN TK_IDENT (TK_WHERE expr)? TK_RCLAUDATOR) // [ point.x | point in points where point.y < 3 ]
//    | (TK_IDENT TK_LCLAUDATOR expr TK_RCLAUDATOR TK_LCLAUDATOR TK_UNDERSCORE TK_RCLAUDATOR) // points[2][_]
//    | (TK_IDENT TK_LCLAUDATOR TK_UNDERSCORE TK_RCLAUDATOR TK_LCLAUDATOR expr TK_RCLAUDATOR); // points[_][2]


expr:
    exprAnd #exprTop
    | condition=exprAnd TK_INTERROGANT op1=expr TK_COLON op2=expr #exprTernary;

exprAnd: exprOr (TK_OP_LOGIC_AND exprOr)*;
exprOr: exprEq (TK_OP_LOGIC_OR exprEq)*;

opEquality: TK_OP_REL_EQ | TK_OP_REL_NEQ;
exprEq: exprRel (opEquality exprRel)*;

opRelational: TK_OP_REL_LT | TK_OP_REL_GT | TK_OP_REL_GE | TK_OP_REL_LE;
exprRel: exprSumDiff (opRelational exprSumDiff)*;

opSumDiff : TK_OP_ARIT_SUM | TK_OP_ARIT_DIFF;
exprSumDiff: exprMulDivMod (opSumDiff exprMulDivMod)*;

opMulDivMod: TK_OP_ARIT_MULT | TK_OP_ARIT_DIV | TK_OP_ARIT_MOD;
exprMulDivMod: exprNot (opMulDivMod exprNot)*;

exprNot: op=TK_OP_LOGIC_NOT? expr_base;

expr_base: valueBaseType | TK_LPAREN expr TK_RPAREN | varAccess;

varAccess: id=TK_IDENT varAccessObjectOrArray*;
varAccessObjectOrArray: (TK_DOT attr=TK_IDENT | TK_LCLAUDATOR index=expr TK_RCLAUDATOR);

valueBaseType: integer=TK_INT_VALUE | boolean=TK_BOOLEAN_VALUE;



constraint:
    constraint_double_implication
|   constraint_and_implication
|   constraint_or_implication
|   constraint_and
|   constraint_or
|   cLit=constraint_literal;

constraint_double_implication:
        constraint_literal TK_OP_DOUBLE_IMPLIC constraint_and
    |   constraint_and TK_OP_DOUBLE_IMPLIC constraint_literal
    |   constraint_literal TK_OP_DOUBLE_IMPLIC constraint_or
    |   constraint_or TK_OP_DOUBLE_IMPLIC constraint_literal;

constraint_and_implication: constraint_and TK_OP_IMPLIC_R constraint_or;
constraint_or_implication: constraint_or TK_OP_IMPLIC_L constraint_and;

constraint_and:
        constraint_literal (TK_CONSTRAINT_AND constraint_literal)+
    |   TK_CONSTRAINT_AND TK_CONSTRAINT_AND TK_LPAREN list TK_RPAREN;

constraint_or:
        constraint_literal (TK_CONSTRAINT_OR_PIPE constraint_literal)+         #cOrExpression
    |   TK_CONSTRAINT_OR_PIPE TK_CONSTRAINT_OR_PIPE TK_LPAREN list TK_RPAREN   #cOrList;

constraint_literal: TK_CONSTRAINT_NOT? varAccess;