# Expressions

Expressions are only permitted between parameters of basic types. An expression could be:

- A **value of basic type**.
- A **data access**.
- A **list aggregation operation**.
- An **operation between one or more expressions**. In the following table we can find all implemented operators with their associativity and types. They are sorted according to their priority: 

| Operator | Associativity | Input type | Output type |
|:-:|:-:|:-:|:-:|
| `not` | - | *bool* | *bool* |
| `/`, `%`, `*` | Left | *int* | *int* |
| `+`, `-` | Left | *int* | *int* |
| `<`, `<=`, `>`, `>=` | Left | *int* | *bool* |
| `==`, `!=` | Left | *int* or *bool* | *bool* |
| `and`, `or` | Left | *bool* | *bool* |
| `if-then-else` | Right | *int* or *bool* | *int* or *bool*  |

##  `if-then-else` structure
```
<bool_expr> ? <expr1> : <expr2>
```
If `<bool_expr>` evaluates true resolves `<expr1>` else `<expr2>`.