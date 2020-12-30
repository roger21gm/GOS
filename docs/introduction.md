# Introduction

**C**onstraint **S**atisfaction Problems (**CSP**s) consists on finding values for a set of variables subject to a set of constraints. Examples of CSPs are well-known puzzles such as Sudoku or problems appearing in industry such as Scheduling or Timetabling. This kind of problems can be easily modelled with declarative programming languages.

Declarative programming languages attempt to describe what the program must accomplish in terms of the problem domain, rather than describe how to accomplish it as a sequence of the programming language primitives. This is in contrast with imperative programming, which implements algorithms in explicit steps.

A subset of declarative languages are modelling languages. This project will be focused on this subset and the main purpose will be get a new declarative programming language for modelling any **CSP** to Boolean Satisfiability **SAT**.

### SAT

One of the most successful methodologies for solving CSP relies on the conversion into SAT problems, i.e., to **build a Boolean formula that has a solution if and only if the original CSP has also a solution**. The advantage is the wide availability of free and **eﬀicient SAT-solvers**.

# GOS & BUP

The of the tool is **GOS** (**G**irona **O**ptimization **S**ystem) and the language that uses is **BUP**.

> As a curiosity, the name choice lies in the fact that in [Catalan](https://en.wikipedia.org/wiki/Catalan_language), my mother tongue, GOS means dog and, also in Catalan, the onomatopoeia that describes the sound that dogs make (the language they speak) is BUP-BUP! (woof-woof!).
Therefore, GOS (dog) is the name of the tool implemented and BUP (woof) is the language defined that is used by GOS. Apart from that, a real dog (GOS) can be considered a tracker, and that is also what the project is about: looking for a solution to CSPs.

## What is GOS?

GOS is a declarative tool for modelling and solving any CSP to SAT, improving its expresiveness. **GOS gives you an easy gateway for modelling with SAT**.

![](https://i.imgur.com/orO0kZ8.jpg)

### Model file

Written in **BUP** language defining:

- Necessary **parameters** (initially fixed sudoku values, board size,...).
- **Variables** used to model the problem.
- [**Constraints**](https://github.com/roger21gm/GOS/wiki/Constraints) applied over those variables (no repeated numbers in each row, column and sub-square, initial values must be respected,...)
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

### Parameters file

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

### Output 

GOS compiler will process these data and will generate the propositional formula as a result of applying the defined constraints over the model variables. Once the formula is generated, the compiler can **print the formula in a standard format, DIMACS**, or **apply the solver to get a solution**. 

Basically, the process would be like doing a compilation of a high-level language (in our case, BUP), to assembler (where SAT is the assembler, the lowest-level language), using GOS compiler.
