# Lists

Lists can be used to generate ranges to loop over arrays in `forall` structures. It is also allowed applying constraints over lists of variables, i.e., cardinalities, [`and`](/constraints?id=propositional-formula) constraints, [`or`](/constraints?id=propositional-formula) constraints, etc.

A list could be:

## Range list
```
<int_expr>..<int_expr>
```
- `1..5` generates the list *[1,2,3,4,5]*.
- `1..15/5` generates the list *[1,2,3]*.

## Comprehension list

```
[<<expr | clause>> | <ident> in <list> (,<ident>} in <list>)* <where <bool_expr>>?]
```
- `[i | i in 1..5]` generates the list *[1,2,3,4,5]*.
- `[i*j | i in 1..3, j in 1..3]` generates the list *[1,2,3,2,4,6,3,6,9]*.
- `[i*j | i in 1..3, j in 1..3 where i < j]` generates the list *[2,3,6]*.

## Explicit list
```
[<<expr> | <clause>> <, <<expr> | <clause>>*]
```
- `[1,2,3,4,5]` generates the list *[1,2,3,4,5]*.
- `[1,2*4,7,14/2+1,76]` generates the list *[1,8,7,8,76]
> All elements of a integer explicit list must be of the same type
- `[a|b,a,c->d]` generates the list *[a V b, a, !c V d]*.

## One-dimentional array
```
<matrixRowAccess>
```
See [matrix row access](/access?id=matrix-row-access) section for more info.

Given a one-dimensional array `int arrayX[3]`:
- `arrayX` generates the list *[arrayX[0], arrayX[1], arrayX[2]]*

Given a multi-dimensional array `int arrayX[3][3][3]`:
- `arrayX[0][_][0]` generates the list *[arrayX[0][0][0], arrayX[0][1][0], arrayX[0][2][0]]*
- `arrayX[_][1][0]` generates the list *[arrayX[0][1][0], arrayX[1][1][0], arrayX[2][1][0]]*

## List aggregation operators

### `length`
The `length` operator returns the size of a list.
```
length( <list> )
```
### `sum`
The `sum` operator returns the size of a list of integers.
```
sum( <list_int> )
```
### `max`
The `max` operator returns the maximum number of a list of integers.
```
max( <list_int> )
```
### `min`
The `min` operator returns the minimum number of a list of integers.
```
min( <list_int> )
```

