grammar CSP2SAT;

WS
   : [ \t\n\r] + -> skip
   ;

LINE_COMMENT : '//' ~[\r\n]* -> skip;

BLOCK_COMMENT : '/*' .*? '*/' -> skip;

// basic structure
TK_ENTITIES: 'entities';
TK_VIEWPOINT: 'viewpoint';
TK_CONSTRAINTS: 'constraints';
TK_OUTPUT: 'output';

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

TK_CONSTRAINT_AGG_EK : 'EK';
TK_CONSTRAINT_AGG_ALK : 'ALK';
TK_CONSTRAINT_AGG_AMK : 'AMK';

TK_IDENT: ( ('a'..'z' | 'A'..'Z' | '_')('a'..'z' | 'A'..'Z' | '_' | '0'..'9')* );


//OUTPUT
fragment ESCAPED_QUOTE : '\\"';
TK_STRING :   '"' ( ESCAPED_QUOTE | ~('"') )*? '"';

TK_STRING_AGG_OP: '++';

// SINTÀCTIC

csp2sat: entityDefinitionBlock? viewpointBlock constraintDefinitionBlock outputBlock?;

definition: varDefinition | paramDefinition;

entityDefinitionBlock: TK_ENTITIES TK_COLON entityDefinition* ;
entityDefinition: name=TK_IDENT TK_LBRACKET definition* TK_RBRACKET TK_SEMICOLON;

viewpointBlock: TK_VIEWPOINT TK_COLON definition*;

constraintDefinitionBlock: TK_CONSTRAINTS TK_COLON constraintDefinition*;

outputBlock: TK_OUTPUT TK_COLON (string TK_SEMICOLON)*;

varDefinition: TK_VAR type=TK_BASE_TYPE_BOOL? name=TK_IDENT arrayDefinition TK_SEMICOLON;
paramDefinition: (
        TK_PARAM type=(TK_BASE_TYPE_BOOL | TK_BASE_TYPE_INT)
        | type=TK_IDENT
    ) name=TK_IDENT arrayDefinition TK_SEMICOLON;

arrayDefinition: (TK_LCLAUDATOR arraySize=expr TK_RCLAUDATOR)*;


// EXPRESSIONS

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

varAccessObjectOrArray:
    TK_DOT attr=TK_IDENT
    | TK_LCLAUDATOR index=expr TK_RCLAUDATOR
    | TK_LCLAUDATOR underscore=TK_UNDERSCORE TK_RCLAUDATOR;

valueBaseType: integer=TK_INT_VALUE | boolean=TK_BOOLEAN_VALUE;


// CONSTRAINTS

constraintDefinition: ( forall | ifThenElse | constraint ) TK_SEMICOLON;

auxiliarListAssignation: TK_IDENT TK_IN list;

localConstraintDefinitionBlock: constraintDefinition*;

forall: TK_FORALL TK_LPAREN auxiliarListAssignation (TK_COMMA auxiliarListAssignation)* TK_RPAREN TK_LBRACKET localConstraintDefinitionBlock TK_RBRACKET;

ifThenElse:
    TK_IF TK_LPAREN expr TK_RPAREN TK_LBRACKET localConstraintDefinitionBlock TK_RBRACKET
    (TK_ELSEIF TK_LPAREN expr TK_RPAREN TK_LBRACKET localConstraintDefinitionBlock TK_RBRACKET)*
    (TK_ELSE TK_LBRACKET localConstraintDefinitionBlock TK_RBRACKET)?;

list: min=expr TK_RANGE_DOTS max=expr #rangList
    | TK_LCLAUDATOR listResultExpr TK_CONSTRAINT_OR_PIPE auxiliarListAssignation (TK_COMMA auxiliarListAssignation)* (TK_WHERE condExpr=expr)? TK_RCLAUDATOR #comprehensionList
    | TK_LCLAUDATOR listResultExpr (TK_COMMA listResultExpr)* TK_RCLAUDATOR #explicitList
    | varAccess #varAccessList;


listResultExpr:
    | varAcc=constraint_literal
    | resExpr=expr
    | string;

constraint: constraint_expression | constraint_aggreggate_op;

constraint_expression: constraint_double_implication;

constraint_double_implication: constraint_implication (TK_OP_DOUBLE_IMPLIC constraint_implication)*;


implication_operator: (TK_OP_IMPLIC_L | TK_OP_IMPLIC_R);
constraint_implication: constraint_or (implication_operator constraint_or)*;

constraint_or:
    constraint_and (TK_CONSTRAINT_OR_PIPE constraint_and)*                   #cOrExpression
    | TK_CONSTRAINT_OR_PIPE TK_CONSTRAINT_OR_PIPE TK_LPAREN list TK_RPAREN   #cOrList;

constraint_and:
      constraint_literal (TK_CONSTRAINT_AND  constraint_literal)*    #cAndExpression
    | TK_CONSTRAINT_AND TK_CONSTRAINT_AND TK_LPAREN list TK_RPAREN   #cAndList;

constraint_literal: TK_CONSTRAINT_NOT? constraint_base;

constraint_base:
    varAccess
    | TK_BOOLEAN_VALUE
    | TK_LPAREN constraint_expression TK_RPAREN;

aggregate_op: TK_CONSTRAINT_AGG_EK | TK_CONSTRAINT_AGG_AMK | TK_CONSTRAINT_AGG_ALK;
constraint_aggreggate_op: aggregate_op TK_LPAREN list TK_COMMA param=expr TK_RPAREN;


//OUTPUT

string:
    string concatString
    | TK_LPAREN string TK_RPAREN
    | stringTernary
    | varAccess
    | expr
    | list
    | TK_STRING;

stringTernary:
    condition=exprAnd TK_INTERROGANT op1=string TK_COLON op2=string;

concatString:
    TK_STRING_AGG_OP string concatString?;
