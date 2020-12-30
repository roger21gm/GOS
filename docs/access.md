# Data access

Accesses can be used to **retrieve a value** (in parameters or in variables when they already have a value, i.e. in the output section), or to impose **constraints on variables**.

### Identifier access
```
<ident>
```
### Array index access
```
<
    <ident>
    | <entityAttrAccess>
    | <arrayIndexAccess>
> [<int_expr>]
```
### Matrix row access
*BUP* allows generating a list by accessing a row of a matrix using the operator `_`, for example `varsX[_][1]`.
```
<
    <ident>
    | <entityAttrAccess>
    | <arrayIndexAccess>
> [_] <[<int_expr>]>*
```
### Entity attribute access
```
<
    <ident>
    | <entityAttrAccess>
    | <arrayIndexAccess>
>.<ident>
```