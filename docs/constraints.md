A **constraint** in GOS can be (and only be) a:

- Propositional Formula
- Cardinality Constraint
- `forall` structure
- `if` structure

## Propositional Formula

Although the GOS compiler can recognize syntactically any propositional formula, the BUP language only permits those formulas with trivial translation to [CNF](https://github.com/roger21gm/GOS/wiki/Definitions#cnf---conjunction-normal-form), more precisely, formulas that can be translated to a linear number of clauses without adding auxiliary variables. 

This decision was taken for the first version of BUP, but since GOS's parser already supports any kind of propositional formula, it would be easy to support any propositional formula in future versions if desired.

> This decision was taken mainly for the sake of a clear correspondence with the BUP file and the generated SAT formulas. Also, good reformulations of more complex formulas involve challenges such as detection of common sub-expressions, which are out of the scope of the first stage of the project.

<details> <summary> Example of <b>allowed</b> and <b>not allowed</b> propositional formulas </summary>
<p>

For instance, given the following propositional formula:
```
a & b & c | d & e
```
A translation to CNF without intro ducing auxiliary variables would be:
```
(a | d) & (a | e) & (b | d) & (b | e) & (c | d) & (c | e)
```
It generates a quadratic number of new clauses. **This propositional formula is not semantically allowed by GOS**. 
Given this other formula:
```
a & b & c | d
```
The translation to CNF would be
```
(a | d) & (b | d) & (c | d)
```
It generates a linear number of clauses. **This propositional formula is allowed by GOS**.

</p>
</details>

Therefore, the GOS compiler does a semantic checks to ensure that the formulas contained in a BUP file fulil certain properties. The semantic rules that GOS applies over Boolean operations are described in the following subsections.

The following figure shows how different operands could be treated in GOS when constructing Boolean Formulas:

- `LITERAL` is a `VARIABLE` or its negation
- `AND_LITERALS` is an *and* operation between literals. A `LITERAL` is a particular case of `AND_LITERALS` where there is only one literal.
- `OR_LITERALS` is an or operation between literals. A `LITERAL` is a particular case of `OR_LITERALS` where there is only one literal.
- `AND_CLAUSES` is an and operations between clauses. `OR_LITERALS` is a particular case of `AND_CLAUSES` where there is only one clause. `AND_LITERAL` is a particular case of `AND_CLAUSES` where all the clauses are unitary.

![](https://i.imgur.com/xiMHuj8.png)

These are the **GOS** operators and their precedence:


| Name               | Operator | Associativity | Precedence |
|--------------------|----------|---------------|------------|
| Negation           | !        | -             | 1          |
| And                | &        | Left          | 2          |
| Or                 | \|        | Left          | 3          |
| Implication        | ->       | Left          | 4          |
| Double Implication | <->      | Left          | 5          |

<!-- tabs:start -->

#### ** Variable **
Acces to a declared variable

```
x
```

#### ** Negation **
```
!x
```

The *negation* operator has the following truth table:


| a | !a |
|----------|-------------|
| 0        | 1  |
| 1        | 0  |


The allowed operations using `!` operator are:


| Result         | Expression      |
| -------------- | --------------- |
| `LITERAL`      | `!LITERAL`      |
| `OR_LITERALS`  | `!AND_LITERALS` |
| `AND_LITERALS` | `!OR_LITERALS`  |


#### **And**
```
a & b
```

The *and* operator `&` has the following truth table:


| a | b | a & b |
|:-:|:-:|:-:|
| 0 | 0 | 0 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |

The *And* operation could also be constructed through a list using the operator `&&` and a list of clauses. As it is a unary operator, `&&` has the precedence in the same level as the negation operator (see operator precedence)

```
&&( <list> )
```


The allowed operations using `&` operator are:


| Result         | Expression      |
| -------------- | --------------- |
| `OR_LITERALS & OR_LITERALS`      | `AND_CLAUSES`      |
| `OR_LITERALS & AND_LITERALS`  | `AND_CLAUSES` |
| `AND_LITERALS & OR_LITERALS` | `AND_CLAUSES`  |
| `AND_LITERALS & AND_LITERALS` | `AND_LITERALS`  |
| `AND_CLAUSES & AND_CLAUSES` | `AND_CLAUSES`  |
| `AND_LITERALS & OR_LITERALS` | `AND_CLAUSES`  |
| `AND_CLAUSES & AND_CLAUSES` | `AND_CLAUSES`  |

#### **Or**
```
a | b
```

The *Or* operator `|` has the following truth table:


| a | b | a \| b |
|:-:|:-:|:-:|
| 0 | 0 | 0 |
| 0 | 1 | 1 |
| 1 | 0 | 1 |
| 1 | 1 | 1 |

The *Or* operation could also be constructed through a list using the operator `||` and a list of clauses. As it is a unary operator, `||` has the precedence in the same level as the negation operator (see operator precedence)

```
||( <list> )
```


The allowed operations using `&` operator are:


| Result         | Expression      |
| -------------- | --------------- |
| `LITERAL | LITERAL`      | `OR_LITERALS`      |
| `OR_LITERALS | OR_LITERALS`      | `OR_LITERALS`      |
| `OR_LITERALS | AND_LITERALS`      | `AND_CLAUSES`      |

#### **Implication**
```
a -> b
```

The *implication* operator has the following truth table:


| a | b | a -> b |
|:-:|:-:|:-:|
| 0 | 0 | 1 |
| 0 | 1 | 1 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |


The allowed operations using `->` operator are:


| Result         | Expression      |
| -------------- | --------------- |
| `AND_LITERALS -> OR_LITERALS`      | `OR_LITERALS`      |
| `OR_LITERALS <- AND_LITERALS`  | `OR_LITERALS` |
| `LITERAL -> AND_LITERALS` | `AND_CLAUSES`  |
| `AND_LITERALS <- LITERAL` | `AND_CLAUSES`  |


#### **Double Implication**
```
a <-> b
```


The *double implication* operator has the following truth table:


| a | b | a <-> b |
|:-:|:-:|:-:|
| 0 | 0 | 1 |
| 0 | 1 | 0 |
| 1 | 0 | 0 |
| 1 | 1 | 1 |


The allowed operations using `<->` operator are:


| Result         | Expression      |
| -------------- | --------------- |
| `LITERAL <-> AND_LITERALS`      | `AND_CLAUSES`      |
| `AND_LITERALS <-> LITERAL`  | `AND_CLAUSES` |
| `LITERAL <-> OR_LITERALS` | `AND_CLAUSES`  |
| `OR_LITERALS <-> LITERAL` | `AND_CLAUSES`  |

<!-- tabs:end -->

## Cardinality Constraints
Apart from simple boolean formulas, **BUP** allows *Cardinality Constraints* in the model specification, that are later automatically translated to CNF by **GOS**. These kind of constraints state that at most (at least, or exactly) *k* out of a propositional literals list can be true.

- Exactly One:  `EO( <list> )`
- At Most One:  `AMO ( <list> )`
- At Least One:  `ALO ( <list> )`
- Exactly *k*:  `EK( <list> )`
- At Most *k*:   `AMK ( <list> )`
- At Least *k*:  `ALK ( <list> )`

## `forall` Structure
*BUP* language support `forall` structures used to loop lists and add constraints to the model.

```
forall ( <ident> in <list> <, <ident> in <list> >*) {
    <constraint>*
};
```

## `if` Structure

BUP supports `if` structures used to conditionally add constraints to the model.

```
<if ( <boolExpression> ) { <constraint>* } >
<else if ( <boolExpression> ) { <constraint>* } >*
<else { <constraint>* } >?
```
