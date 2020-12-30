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

### Variable
Accés to a declared variable
### Negation
The negation operator has the following truth table:


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

### And
### Or
### Implication
### Double Implication


## Cardinality Constraint
## `forall` Structure
## `if` Structure
