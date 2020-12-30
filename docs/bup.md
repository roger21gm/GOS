
# BUP program structure

The model file structure is divided in four blocks:
- **Entity definition block**, where entities are defined.
- **Viewpoint block**, where variables and parameters are declared.
- **Constraints block**, where constraints are defined.
- **Output block**, where custom output is defined.

```
<entityDefinitionBlock>?
<viewpointBlock>
<constraintsBlock>
<outputBlock>?
```

## Entity Definition block

This block is used to define the new entities (a kind of tuples) to be used at the viewpoint.
```
<<entityDefinition>;>*
```

## Viewpoint block

This block is used to define the variables and parameters used to model the problem.
```
viewpoint : 
<<
      <variableDeclaration>
    | <parameterDeclaration>
    | <entityDeclaration>
    | <arrayDeclaration>
>;>*
```

### Variable declaration
```
var bool? <ident>
```
### Param declaration
```
param <int | bool> <ident>
```
### Entity declaration
```
<entity_ident> <ident>
```
### Array declaration
Array indexes range from 0 to *n*-1, where *n* is the array size.
```
<
      <varDeclaration>
    | <paramDeclaration>
    | <entityDeclaration>
> <[<int_expr>]>*
```

## Constraints block

```
constraints: <<constraint>;>*
```

## Output block

```
output: <<string>;>*
```
