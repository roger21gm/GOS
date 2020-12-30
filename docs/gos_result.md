# GOS (Girona Optimization System)
#### What is GOS?

GOS is a declarative tool for modelling and solving any CSP to SAT, improving its expresiveness. **GOS gives you an easy gateway for modelling with SAT**.

![](https://i.imgur.com/orO0kZ8.jpg)

## Model

Model files is written in **BUP** language and defines:

- Necessary **parameters** (initially fixed sudoku values, board size,...).
- **Variables** used to model the problem.
- [**Constraints**](/constraints) applied over those variables (no repeated numbers in each row, column and sub-square, initial values must be respected,...)
- **Output** format.


Using BUP for modelling the **Sudoku** problem:
```
viewpoint:
    var p[9][9][9];
    param int iniSudoku[9][9];

constraints:
    forall(i in 0..8, j in 0..8){
        EO(p[i][j][_]); // One value per cell
        AMO(p[i][_][j]); // Each value one time per row
        AMO(p[_][i][j]); // Each value one time per column
    };
    
    //Each value one time per block
    forall(i in [0,3,6], j in [0,3,6], k in 0..8){
        AMK([p[i+l][j+g][k] | l in 0..2, g in 0..2], 1);
    };
    
    //Initialize input fixed sudoku values.
    forall(i in 0..8, j in 0..8){
        if(iniSudoku[i][j] != 0){
            p[i][j][iniSudoku[i][j]-1];
        };    
    };
    
output:
    "Sudoku solution: \n";
    [ k+1 ++ " " ++ ((j+1) % 3 == 0 ? " " : "") ++ (j==8 ? (i+1) % 3 == 0 ? "\n←􏰁 􏰀→ \n": "\n" : "") | i in 0..8, j in 0..8, k in 0..8 where p[i][j][k]];
```
The model has a parameter `iniSudoku`, that is the actual sudoku to solve, and an array of variables `p`, where `p[i][j][k]` is true when the cell with row `i` and column `j` has the value `k`.

## Parameters

The parameters file, fills the requiered model parameters with concret values, according to the instance. The language used for the parameters file is **JSON** since supports all the data structures used by BUP.


The following snippet is an example of a parameters file for the previous Sudoku model:

```
{
    "iniSudoku" : [
        [8, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 3, 6, 0, 0, 0, 0, 0],
        [0, 7, 0, 0, 9, 0, 2, 0, 0],
        [0, 5, 0, 0, 0, 7, 0, 0, 0],
        [0, 0, 0, 0, 4, 5, 7, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 3, 0],
        [0, 0, 1, 0, 0, 0, 0, 6, 8],
        [0, 0, 8, 5, 0, 0, 0, 1, 0],
        [0, 9, 0, 0, 0, 0, 4, 0, 0]
    ] 
}
```

## Output 

GOS compiler will process these data and will generate the propositional formula as a result of applying the defined constraints over the model variables. Once the formula is generated, the compiler can **print the formula in a standard format, DIMACS**, or **apply the solver to get a solution**. 

Basically, the process would be like doing a compilation of a high-level language (in our case, BUP), to assembler (where SAT is the assembler, the lowest-level language), using GOS compiler.

## Summary

The **GOS** compiler allows to use the defined language, **BUP**, to solve **CSP**s. 

Given a BUP model and a JSON file with the data of a particular instance at hand, GOS compiler makes the translation to SAT and gives the option to print the resulting formula in a standard format, DIMACS, or to obtain a solution by using MiniSAT SAT-solver.

There are two ways of using GOS compiler: 
- By building the project using CMake 
- By using the published online version (currently unavailable)