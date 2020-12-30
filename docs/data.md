# Data types

BUP has two types of data, according to its nature:
- **Parameters**: Instance related. Used to describe the instance specification.
- **Variables**: Model related. We must differentiate this variables from the imperative languages variables. SAT variables are always boolean, but you cannot do arithmetic operations or assign them. Instead, you can define constraints over variables, expressed, for example, as propositional formulas. They are strictly designed for defining the SAT model and their value can only be retrieved in the output-block specification, where their value can be accessed similarly as is done with boolean parameters.

Both, parameters and variables, could be declared individually or using data structures: **multidimensional arrays or defined types (entities)**.

## Basic types

The basic types are those with which you can define parameters: 

- `int`: Represents an integer value.
- `bool`: Represents a boolean. It can take values true or false.

## Defined types: *Entities*

**BUP** allows defining new entities consisting of a tuple of data elements. These data elements can contain both parameters and variables. The only restriction is that entity types used in the definition of an element must have been declared previously.

```
<identifier> {
<
    <parameter declaration>
  | <variable declaration>
  | <entity declaration>
  | <array declaration>
>+
}
```

## n-dimentional arrays

It is allowed to define *n*-dimentional arrays of any basic type, variable or entity. The arrays index range from 0 to *m*-1, where *m* is the length of the indexed dimension of the array.

