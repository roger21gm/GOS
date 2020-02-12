# Language specification

## Data types

### Basic types

**`int`**  Represents an integer. 

**`bool`**  Represents a boolean. It can take **true** or **false** values.

`_`  Represents a **null** value.



### User defined types

- **Types** Struct constructed by variables `var` and constants `const` of any type.

  ```java
  type type_name {
    <
      <constant definition> |
      <variable definition>
    >*
    <comparator implentation>?
  }
  ```

  - **Comparator implementation** It will be possible to implement the operators `<` and `==` and use boolean operations between instances of the same type.

    ```
    
    ```

- **Arrays** You can define one or two-dimentional arrays of any type. You can also limit variables domain from a range.

- **Sets** You can define a set of any type and limit its domain from a range.

  

## General structure of a program

A program will be written in at least two files that will define a model for a particular problem.

- **Model file:** It will describe the structure of the problem.

  ```pseudocode
  types: <<type definition> ; >*
  vars: <<<var definition> | <const definition>> ; >*
  constraints: <<constraint definition> ; >*
  ```

- **Data file:** It will contain the constants and variables required by the model. The data file must be in a JSON format fitting the required constants from the model.

  ```pseudocode
  <bloc d'assignació de constants>
  ```



## Identifiers

The **identifiers** are words without whitespaces. It can only contain characters from the Gregorian alphabet, numbers and underscores:

```pseudocode
[A-Z|a-z|_][A-Z|a-z|0-9|_]*
```



## Comments

One liner **comments** must begin with a pad, **#**

```pseudocode
#.*
```



## Expressions

An expression could be:

- A **constant value** of a basic type.

- A **constant** or **variable**.

- An **access to a property of a defined type**:

  - User-defined type:

    ```pseudocode
    𝑖𝑑𝑒𝑛𝑡𝑖𝑓𝑖𝑒𝑟<.<𝑎𝑡𝑡𝑟𝑖𝑏𝑢𝑡𝑒_𝑛𝑎𝑚𝑒>>+
    ```

  - Array access:

    ```pseudocode
    𝑖𝑑𝑒𝑛𝑡𝑖𝑓𝑖𝑒𝑟[<expr_int>]<[expr_int]>?<.<𝑎𝑡𝑡𝑟𝑖𝑏𝑢𝑡𝑒_𝑛𝑎𝑚𝑒>>*
    ```

- An **operation** between one or some expressions.

- An `if-then-else` structure, expressed as:

  ```pseudocode
  condition ? exprTrue : exprFalse
  ```

  - ***condition*** must be a boolean expression.
  - ***exprTrue*** i ***exprFalse*** must be expressions of the same type.

- A defined **function**:

  - `sum(𝑣𝑎𝑟_𝑛𝑎𝑚𝑒 in <range|array>) { <expr> } `

- A **null** value `_`

The expression **operators** are:

- `+`,  `-`,  `*`:  **add**, **diff** and **multiply**. The result is an `int`.
- `/`,  `mod`: **integer division** i **module**. The result is an `int`.
- `==`, `!=`: **equality** i **inequality**. The result is a `bool`.
- `<`, `<=`, `>`, `>=`: **lower**, **lower or equal**, **greater** or **greater or equal**. The result is a `bool`.
- `!`, `&&`, `||`: **logic negation**, **logic *and***, **logic *or***. Only defined for bool expressions. The result is a `bool`



## Variable and constant definition

They must be preceded by `var` and `const` respectively. It will be assigned through the data file. There are two ways of defining a variable or constant:

- Defining an **instance of a basic or defined type**:

  ```pseudocode
  <𝐜𝐨𝐧𝐬𝐭|𝐯𝐚𝐫> <type> 𝑖𝑑𝑒𝑛𝑡𝑖𝑓𝑖𝑒𝑟 <range>?; 
  ```

- Defining an **array** of a basic or defined type:

  ```pseudocode
  <𝐜𝐨𝐧𝐬𝐭|𝐯𝐚𝐫> <type> 𝑖𝑑𝑒𝑛𝑡𝑖𝑓𝑖𝑒𝑟 [<expr_int>] <[<intenger_expr>]>? <range>?; 
  ```

It is also possible to define a pre-defined auxiliary constants by assigning the value in the model:

```pseudocode
<𝐜𝐨𝐧𝐬𝐭> <type> 𝑖𝑑𝑒𝑛𝑡𝑖𝑓𝑖𝑒𝑟 := <expr>
```



### Constraints

It will be able possible to define constraints on the variables in the model:

- `forall` loops

  ```pseudocode
  𝐟𝐨𝐫𝐚𝐥𝐥(𝑣𝑎𝑟_𝑛𝑎𝑚𝑒 in <range|array>) {
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

  - `==`, `!=`: **equality** and **inequality**.
  - `<`, `<=`, `>`, `>=`: **lower**, **lower or equal**, **greater** or **greater or equal**.

- constraint function

  - AMO
  - ALO
  - (...)
  




## Estructures generadores

### Ranges

We can define ranges to limit the possible values of a domain.

```javascript
in <expr_int>..<expr_int>
```



### Comprehension lists

A comprehension list will define an anonymous array. It is possible to generate comprehension lists in a multiple ways:

- From temporal variables: `[ a * b | b, a in 1..10 where b < 3 and a != 4]`:

  ```pseudocode
  [<expr_int> | <var_id><,<var_id>>? <range> <<var_id><,<var_id>>? <range>>? <where <expr_bool>>?]
  ```

- From a one-dimensional predefined array: `[ point.x * 2 | point in points where point.y > 4]`

  ```pseudocode
  [ <expr_int> | <var_id> in <array> <where <expr_bool>>?]
  ```

- From two-dimensional arrays:

  ```pseudocode
  array[i][_] equival a [ sudoku[i][j] | j in 1..n ]
  array[_][j] equival a [ sudoku[i][j] | i in 1..n ]
  ```



## Exemples

### Problema de les _n_-reines

Amb input:

```json
nQueens: {
  n: 7
}
```

I el model:

```pseudocode

types:
  Queens {
      const int n;
      var int q[n] in 1..n;
  }

vars:
	const Queens nQueens;


constraint:
   forall (i in 1..n) {
   	forall (j in i+1..n) {
   		q[i] != q[j];
   		q[i]+i != q[j]+j;
   		q[i]-i != q[j]-j;
   	};
   };
    


```

### Sudoku 

Amb input:

```json
inisudoku : {
	n: 9,
	initial: [
      1, _, _, 5, _, _, _, _, 1,
      _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, 8, _,
      _, 8, _, _, _, 5, _, _, _,
      _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _,
      _, _, _, 9, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _,
      _, _, 7, _, _, _, _, _, 2,
  ]
}
```

I el model:

```pseudocode
types:
	Sudoku {
  		const int n;
    	const int initial[n][n] in 1..n;
    
    	# Variables auxiliars
    	const int ssSize := sqrt(n); //subSquareSize
    
    	# Variables a calcular
    	var int sudoku[n][n] in 1..n;
 }
	

vars:
	const Sudoku iniSudoku;


constraint:

    # Fill initial
    forall (i in 1..n) {
    		forall (j in 1..n) {
    				if( initial[i][j] != _ )
    					sudoku[i][j] == initial[i][j]
    		}
    }
    
    # uniqueRowsCols
    forall (i in 1..n) {
    		all_different(sudoku[i][_])
    		all_different(sudoku[_][i])
    }
    
    # uniqueSubSquares    
    forall (i in 1..ssSize) {
	  		forall (j in 1..ssSize) {
  		  		alldifferent(
    					[ sudoku[a][b] | a, b in (i*(ssSize-1))..(i*(ssSize-1)+ssSize) ]
    				);
    		}
    }
    
}
```



## Packing squares problem

Amb input:

```json
bigSquare : {
    sideSize: 5,
    nSquares: 8,
    s:[
        {
          size: 3,
        },
        {
          size: 2,
        },
        {
          size: 2,
        },
        {
          size: 3,
        },
        {
          size: 2,
        },
        {
          size: 2,
        },
        {
          size: 2,
        },
        {
          size: 2,
        }
    ]
} 
```

I el model:

```pseudocode
types:
		Square {
				var int x;
        var int y;
        const int size;
		}
		PackSquare {
				const int sideSize;
        const int nSquares;
        const Square s[nSquares];
		}
		
		
vars:
		const PackSquare bigSquare;


constraints:
		
		# inside
		forall(i in 1..nSquares){
			s[i].x <= sideSize - s[i].size + 1;
			s[i].y <= sideSize - s[i].size + 1;
		}
		
		# noOverlap
		forall (i in 1..nSquares){
			forall (j in i+1..nSquares){
				   s[i].x + s[i].size <= s[j].x 
				|| s[j].x + s[j].size <= s[i].x 
				|| s[i].y + s[i].size <= s[i].y 
				|| s[j].y + s[j].size <= s[i].y 
			}
		}
		
		# fitArea
		sum (i in 1..nSquares){s[i].size *f s[i].size} == sideSize * sideSize;
```

