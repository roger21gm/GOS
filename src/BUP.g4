grammar BUP;

WS
   : [ \t\n\r] + -> skip
   ;

LINE_COMMENT : '//' ~[\r\n]* -> skip;

BLOCK_COMMENT : '/*' .*? '*/' -> skip;

// basic structure
TK_ENTITIES: 'entities';
TK_VIEWPOINT: 'viewpoint';
TK_PREDICATES: 'predicates';
TK_CONSTRAINTS: 'constraints';
TK_OUTPUT: 'output';

TK_COLON: ':';
TK_SEMICOLON: ';';

TK_UNDERSCORE: '_';

TK_ASSIGN: ':=';

TK_PARAM: 'param';
TK_VAR: 'var';
TK_AUX: 'aux';

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

TK_INCLUDE: 'include';

//EXPRESSIONS
TK_OP_AGG_SIZEOF: 'sizeof';
TK_OP_AGG_SUM: 'sum';
TK_OP_AGG_LENGTH: 'length';
TK_OP_AGG_MAX: 'max';
TK_OP_AGG_MIN: 'min';

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
TK_CONSTRAINT_AGG_EO : 'EO';
TK_CONSTRAINT_AGG_ALK : 'ALK';
TK_CONSTRAINT_AGG_ALO : 'ALO';
TK_CONSTRAINT_AGG_AMK : 'AMK';
TK_CONSTRAINT_AGG_AMO : 'AMO';

TK_IDENT: ( ('a'..'z' | 'A'..'Z' | '_')('a'..'z' | 'A'..'Z' | '_' | '0'..'9')* );


//OUTPUT
fragment ESCAPED_QUOTE : '\\"';
TK_STRING :   '"' ( ESCAPED_QUOTE | ~('"') )*? '"';

TK_STRING_AGG_OP: '++';

// SINTÀCTIC

csp2sat: entityDefinitionBlock? viewpointBlock predDefBlock? constraintDefinitionBlock outputBlock?;

entityDefinitionBlock: TK_ENTITIES TK_COLON entityDefinition* ;
entityDefinition: name=TK_IDENT TK_LBRACKET (definition TK_SEMICOLON)* TK_RBRACKET TK_SEMICOLON;

viewpointBlock: TK_VIEWPOINT TK_COLON (definition TK_SEMICOLON)*;

// TODO Parlar sobre com implementar els predicats per poder fer <constraint: XOR(a,b) -> XOR(c,b);>
// Mirar si podem resoldre les funcions en temps de compilacio, llavors no podrien rebre variables de decisió
// En canvi els predicats sí (pensar com)
predDefBlock: TK_PREDICATES TK_COLON predDefBlockBody;
predDefBlockBody: (predDef | predInclude)*;
predDef: name=TK_IDENT TK_LPAREN predDefParams? TK_RPAREN TK_LBRACKET predDefBody TK_RBRACKET;
predDefParams: definition (TK_COMMA definition)*; // TODO permetre passar estructures (llistes) Cal pensar si passar entities
predDefBody: predVarDefinitionBlock constraintDefinition+;
predCall: name=TK_IDENT TK_LPAREN predCallParams? TK_RPAREN;
predCallParams: predCallParam (TK_COMMA predCallParam)*;
predCallParam:
    varAccess
    | expr
    | list;
predVarDefinitionBlock: (varDefinition TK_SEMICOLON)*;
predInclude: TK_INCLUDE TK_STRING TK_SEMICOLON;


// TODO permetre passar de tot com a parametre
// TODO soft constraints permetre pesos amb notació @ {expressió que es resolgui en temps de compilació}



constraintDefinitionBlock: TK_CONSTRAINTS TK_COLON constraintDefinition*;

outputBlock: TK_OUTPUT TK_COLON (string TK_SEMICOLON)*;

definition: varDefinition | paramDefinition;
varDefinition: TK_VAR type=TK_BASE_TYPE_BOOL? name=TK_IDENT arrayDefinition;
paramDefinition: (
        TK_PARAM type=(TK_BASE_TYPE_BOOL | TK_BASE_TYPE_INT)
        | type=TK_IDENT
    ) name=TK_IDENT arrayDefinition;
arrayDefinition: (TK_LCLAUDATOR arraySize=expr? TK_RCLAUDATOR)*;

// EXPRESSIONS

expr: condition=exprAnd (TK_INTERROGANT op1=expr TK_COLON op2=expr)?; // Ternary

opAggregateExpr: TK_OP_AGG_LENGTH | TK_OP_AGG_MAX | TK_OP_AGG_MIN | TK_OP_AGG_SUM | TK_OP_AGG_SIZEOF;
exprListAgg: opAggregateExpr TK_LPAREN list TK_RPAREN;

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

expr_base: valueBaseType | TK_LPAREN expr TK_RPAREN | varAccess | exprListAgg;

varAccess: id=TK_IDENT varAccessObjectOrArray*;

varAccessObjectOrArray:
    TK_DOT attr=TK_IDENT
    | TK_LCLAUDATOR index=expr TK_RCLAUDATOR
    | TK_LCLAUDATOR underscore=TK_UNDERSCORE TK_RCLAUDATOR;

valueBaseType: integer=TK_INT_VALUE | boolean=TK_BOOLEAN_VALUE;


// CONSTRAINTS

constraintDefinition: ( forall | ifThenElse | constraint ) TK_SEMICOLON;

auxiliarListAssignation: name=TK_IDENT TK_IN list;

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
    varAcc=varAccess
    | resExpr=expr
    | constraint_expression
    | string;

constraint: constraint_expression | constraint_aggreggate_op;

constraint_expression: constraint_double_implication;

constraint_double_implication: constraint_implication (TK_OP_DOUBLE_IMPLIC constraint_implication)*;


implication_operator: (TK_OP_IMPLIC_L | TK_OP_IMPLIC_R);
constraint_implication: constraint_or (implication_operator constraint_or)*;


constraint_or: constraint_or_2 (TK_CONSTRAINT_OR_PIPE constraint_or_2)* #cOrExpression;

constraint_or_2:
    TK_CONSTRAINT_OR_PIPE TK_CONSTRAINT_OR_PIPE TK_LPAREN list TK_RPAREN #cOrList
    | constraint_and #cAnd;


constraint_and: constraint_and_2 (TK_CONSTRAINT_AND constraint_and_2)* #cAndExpression;

constraint_and_2:
    TK_CONSTRAINT_AND TK_CONSTRAINT_AND TK_LPAREN list TK_RPAREN #cAndList
    | constraint_literal #cLit;

constraint_literal: TK_CONSTRAINT_NOT? constraint_base;

constraint_base:
    varAccess
    | predCall
    | TK_BOOLEAN_VALUE
    | TK_LPAREN constraint_expression TK_RPAREN;

aggregate_op:
    TK_CONSTRAINT_AGG_EK
    | TK_CONSTRAINT_AGG_EO
    | TK_CONSTRAINT_AGG_AMK
    | TK_CONSTRAINT_AGG_AMO
    | TK_CONSTRAINT_AGG_ALK
    | TK_CONSTRAINT_AGG_ALO;

constraint_aggreggate_op: aggregate_op TK_LPAREN list (TK_COMMA param=expr)? TK_RPAREN;


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
