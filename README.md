# Language specification

## Data types

### Basic types

**`int`**  Represents an integer. 

**`bool`**  Represents a boolean. It can take **true** or **false** values.



### User defined types

- **Entities** Struct constructed by variables `var` and parameters `param` of any type.

  ```java
  entity_name {
    <
      <parameter definition> |
      <variable definition>
    >*
  }
  ```

- **Arrays** You can define *n*-dimentional arrays of any basic type or defined entity.

- **Sets** You can define a set of any type and limit its domain from a range. (???)

  

## General program structure

A program will be written in at least two files that will define a model for a particular problem.

- **Model file:** It will describe the structure of the problem.

  ```pseudocode
  entities: <<user-defined entities definition> ; >*
  viewpoint: <<<var definition> | <param definition>> ; >*
  constraints: <<constraint definition> ; >*
  ```

- **Data file:** It will contain the params required by the model. The data file must be in a JSON format fitting the required params from the model.

  ```pseudocode
  <Parameters assignation block>
  ```



## Identifiers

The **identifiers** are words without whitespaces. It can only contain characters from the Gregorian alphabet, numbers and underscores:

```pseudocode
_*[A-Z|a-z][A-Z|a-z|0-9|_]*
```



## Comments

One liner **comments** must begin with a pad, **#**

```pseudocode
//.*
```

- multiline

## Expressions

An expression could be:

- A **constant value** of a basic type.

- A **constant** or **variable**.

- An **access to a defined type property**:

  - User-defined type:

    ```pseudocode
    𝑖𝑑𝑒𝑛𝑡𝑖𝑓𝑖𝑒𝑟<.<𝑎𝑡𝑡𝑟𝑖𝑏𝑢𝑡𝑒_𝑛𝑎𝑚𝑒>>+
    ```

  - Array access:

    ```pseudocode
    𝑖𝑑𝑒𝑛𝑡𝑖𝑓𝑖𝑒𝑟[<expr_int>]<[expr_int]>*
    ```

- An **operation** between one or some expressions.

- An `if-then-else` structure, expressed as:

  ```pseudocode
  condition ? exprTrue : exprFalse
  ```

  - ***condition*** must be a boolean expression.

  - ***exprTrue*** i ***exprFalse*** must be expressions of the same type.

    



The expression **operators** are:

- `+`,  `-`,  `*`:  **add**, **diff** and **multiply**. The result is an `int`.
- `/`,  `mod`: **integer division** i **module**. The result is an `int`.
- `==`, `!=`: **equality** i **inequality**. The result is a `bool`.
- `<`, `<=`, `>`, `>=`: **lower**, **lower or equal**, **greater** or **greater or equal**. The result is a `bool`.
- `!`, `&`, `|`: **logic negation**, **logic *and***, **logic *or***. Only defined for bool expressions. The result is a `bool`

The operator priority is:

 1.  `!`

 2.  `/`,  `mod`,`*`

 3.  `+`,  `-`

 4.  `==`, `!=`, `<`, `<=`, `>`, `>=`

 5.  `&&`, `||`

 6.  `if-then-else`

     

     

     

## Variable and params definition

They must be preceded by `var` and `param` respectively. It will be assigned through the data file. There are two ways of defining a variable or constant:

- Defining an **instance of a basic**:

  ```pseudocode
  <param|𝐯𝐚𝐫> <basic type> 𝑖𝑑𝑒𝑛𝑡𝑖𝑓𝑖𝑒𝑟; 
  ```

- Defining an **instance of a defined entity**:

  ```pseudocode
  <type> 𝑖𝑑𝑒𝑛𝑡𝑖𝑓𝑖𝑒𝑟; 
  ```
  
- Defining an **array** of a basic type or defined entity:

  ```pseudocode
  <instance basic | instance entity> [<expr_int>] <[<intenger_expr>]>*;
  ```

It is also possible to define a pre-defined auxiliary basic type constants by assigning the value in the model:

```pseudocode
<instance basic> := <expr>
```



### Constraints

It will be able possible to define constraints in the boolean decision variables on the model:

- `forall` loops

  - Array iteration

    ```
    𝐟𝐨𝐫𝐚𝐥𝐥(𝑣𝑎𝑟_𝑛𝑎𝑚𝑒 in <arr_identifier | list>) {
    	<constraint>*
    }
    ```

  - Range

    ```
    𝐟𝐨𝐫𝐚𝐥𝐥(𝑣𝑎𝑟_𝑛𝑎𝑚𝑒 <range>) {
    	<constraint>*
    }
    ```

- `if-then-else` 

  ```pseudocode
  <𝐢𝐟 ( <boolean_expr> ){	<constraint>* }>
  <𝐞𝐥𝐬𝐞 𝐢𝐟 (<boolean_expr>){ <constraint>* }>*
  <𝐞𝐥𝐬𝐞 { <constraint>* }>?
  ```

- relational operation

  - **Variable** : 
    - Single variable identifier: `x`
    - Array access: `x[0]`
    - User defined type attribute: `x.attr`
  - **Literal** : It could be a variable or it's negation: `x` and `!x`
  - **OR** operation:
    - Using operator `|`  between literals: `x1 | x2 | ... | xn`
    - Using prefix operator `||`  and a list of literals:  `||( <literal list> )`
  - **AND** operation: 
    - Using operator `&` between literals:  `x1 & x2 & ... & xn`
    - Using prefix operator `&& ` and a list of literals: `&&( <literal list> )`
  - **Implication**: Between **AND** and **OR** operations.
    - **AND ⇒ OR** 
    - **OR ⇐  AND**
  - **Biconditional**:
    - **literal ⇔ AND**
    - **literal ⇔ OR**
    - **AND ⇔ literal**
    - **OR ⇔ literal**

- Global constraints:

  - Cardinalities
    - **EO**
      - EO( [ X[a] [b] | a in 1..3, b in 1..3 ] )
      - EO( [ X[i] | i in 1..n ])
      - EO( [!X[i] | i in 1..n])
      - EO( varX )
      - EO( varX[_] [0]  )
      - EO( varX[_] [0]  )
      - EO( varX[_] [0] [0] )
      - EO( [x, y, !z] )
    - **AMO**
    - **ALO**
    - EK



IF: 

- and - or - not

CLÀSUSULES: 

- ! - & - |
- &&(<list>) - ||(<list>)





**ALLOWED FORMULAS**

LITERAL és "a"

AND_LITERALS pot ser un LITERAL o bé "a & b & c"

OR_LITERALS pot ser un LITERAL o bé "a | b | c"

AND_CLAUSES pot ser un AND_LITERALS si "a & b & c" o bé pot ser "(a | b) & a & (c | d | e)"

- **NOT**
  - !AND_LITERALS  ======> OR_LITERALS
    - !a =====> !a
    - !(a & b & c) =====> !a | !b | !c
  - !OR_LITERALS =====> AND_LITERALS
- **AND**
  - OR_LITERALS & OR_LITERALS   =======> AND_CLAUSES 
    - (a | b) & (c | d)  =====> C1: (a | b), C2: (c | d)
  - OR_LITERALS & AND_LITERALS =======> AND_CLAUSES
    - (a | b) & (b & c & e) ======> C1: (a | b), C2: b, C3: c, C4: e
  - AND_LITERALS & OR_LITERALS =======> AND_CLAUSES
    - (a & b) & (c | d)  =====> C1: a, C2: b, C3: (c | d)
  - AND_LITERALS & AND_LITERALS ======> AND_LITERALS
    - (a & b) & (c & d)  ======> C1: a, C2: b, C3: c, C4: d
  - AND_CLAUSES & AND_CLAUSES =====> AND_CLAUSES
    - ((a & b) & (a & c)) & (d & e) ======> C1: a, C2: b,  C3: a, C4: c, C5: d, C6: e
- **OR**
  - OR_LITERALS | OR_LITERALS ======> OR_LITERALS
    - (a |b) | (c |d) ====> a | b | c | d
  - //TODO: OR_LITERALS | AND_LITERALS ======> AND_CLAUSES
    - (a | b) | (c & d) =====> C1: a | b | c, C2: a | b | d
- **IMPLICATION**
  - AND_LITERALS => OR_LITERALS  // OR_LITERALS => AND_LITERALS ======> OR_LITERALS
    - (a & b) => (c | d) ======> !a | !b | c | d
    - a => (c | d) =====> !a | c | d
  - //TODO : LITERAL => AND_LITERALS =====> AND_CLAUSES
    - a => (c & d) =====> C1: !a | c,  C2: !a | d 
  - No permetem OR_LITERALS => AND_LITERALS 
- **DOUBLE IMPLICATION**
  - LITERAL <-> AND_LITERALS ====> AND_CLAUSES
    - a <-> (b & c). =======> C1: !a | b, C2: !a | c, C3: a | !b | !c
  - LITERAL <-> OR_LITERALS ====> AND_CLAUSES
    - a <-> (b | c). =======> C1: a | !b, C2: a | !c, C3: !a | b | c





  ```pseudocode
  [ <expr_int> | <var_id> in <array> <where <expr_bool>>?]
  ```

- From two-dimensional arrays:

  ```pseudocode
  array[i][_] equival a [ sudoku[i][j] | j in 1..n ]
  array[_][j] equival a [ sudoku[i][j] | i in 1..n ]
  ```





### Problemes

- Accés a variables des del viewpoint: p.e. per definir arrays  `var varX[n][n]` on `param int n`.
  - Fer una lectura prèvia del fitxer d'entrada i quedar-se amb els valors enters?
- Arrays comencen per 0 o per 1?
- Què genera 1..3?
  - 1, 2, 3

- Permetre triar la implementació de AK, ALK (lineal, log,...)



#### Idees

Posar noms a dominis





## Implementation details

### Symbol Table

Symbol table will be used to store variables and constants definitions and its values. Mainly it will answer two questions:

- Given a declaration of a name, is there already a declaration of the same name in the current scope?
- Given a use of a name, to which declaration does it correspond using the "most closely nested" rule, or is it undelcared?

#### Assumptions

- Use static scoping
- Require that all names must be declared before they are used
- Do not allow multiple declarations of a name in the same scope (even for different types)
- Do allow the same name to be declared in multiple nested scopes.

#### Operations

1. Look up a name in the current scope only (to check if it's multiply declared)

2. Look up a name in the current and enclosing scopes

   1. To check for a use of an undeclared name.
   2. To link a use with the corresponding symbol-table entry

3. Insert a new name into the symbol table with its attributes.

4. Do what must be done when a new scope is entered.

5. Do what must be done when a scope is exited.

   

#### Implementation - Table per scope

This implementation consistis using one symbol table per scope and chaining it together in a list based on level of nesting.



#### Implementation - Global table

This implementation consists on representing all symbols in one table and nesting level to all items.



#### Implemented class diagram

![CSP2SAT](https://www.lucidchart.com/publicSegments/view/8e8e563e-99ce-4d85-b132-69ef4e8ff61f/image.png)
