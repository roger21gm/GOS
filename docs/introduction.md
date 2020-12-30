# Introduction

**C**onstraint **S**atisfaction Problems (**CSP**s) consists on finding values for a set of variables subject to a set of constraints. Examples of CSPs are well-known puzzles such as Sudoku or problems appearing in industry such as Scheduling or Timetabling. This kind of problems can be easily modelled with declarative programming languages.

Declarative programming languages attempt to **describe what the program must accomplish in terms of the problem domain**, rather than describe how to accomplish it as a sequence of the programming language primitives. This is in contrast with imperative programming, which implements algorithms in explicit steps.

A subset of declarative languages are **modelling languages**. This project will be focused on this subset and the main purpose will be get a new declarative programming language for modelling any **CSP** to Boolean Satisfiability **SAT**.

#### SAT

One of the most successful methodologies for solving CSP relies on the conversion into SAT problems, i.e., to **build a Boolean formula that has a solution if and only if the original CSP has also a solution**. The advantage is the wide availability of free and **eﬀicient SAT-solvers**.

#### GOS & BUP

The of the tool is **GOS** (**G**irona **O**ptimization **S**ystem) and the language that uses is **BUP**.

> As a curiosity, the name choice lies in the fact that in [Catalan](https://en.wikipedia.org/wiki/Catalan_language), my mother tongue, GOS means dog and, also in Catalan, the onomatopoeia that describes the sound that dogs make (the language they speak) is BUP-BUP! (woof-woof!).
Therefore, GOS (dog) is the name of the tool implemented and BUP (woof) is the language defined that is used by GOS. Apart from that, a real dog (GOS) can be considered a tracker, and that is also what the project is about: looking for a solution to CSPs.
