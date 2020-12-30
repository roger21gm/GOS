# Strings

*BUP* allows string *only* in the output block. A string could be:

- An **explicit string** by adding quotes at the beginning and at the end of the text:
- A **string concat** using `++` operator:
```
<string> <++ <string>>*
```
- A **string between parenthesis**:
```
( <string> )
```
- A **ternary operation** having a string expression to the both sides:
```
<boolExpression> : ? <string1> : <string2>
```
- A variable or param access automatically casted to string.
    > Strings are only allowed in output block, where variables are treated as bool basic type

    > Variables are automatically casted to bool basic type to do operations between expressions in the output-block.
- An expression result, automatically casted to string.
- A list automatically casted to string.
  
    > Lists are casted to string using the format `"[<expr> , <expr*>]"`