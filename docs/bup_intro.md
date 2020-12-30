

# BUP language specification

This chapter contains the specification of the **BUP** modelling language, the language of **GOS**. 

**BUP** is a SAT-oriented declarative CSP modelling programming language. Similarly as we do with imperative languages, we want models written in BUP language to be as much reusable as possible, i.e., we want to separate the problem definition from the data of a particular instance.

For this reason we deal with CSPs using two distinct files: 
- The **model file** (written in **BUP**), which describes the semantics of the problem at hand by means of defining the needed variables, parameters and constraints.
- The **parameters file** (written in **JSON**), which describes the values of the parameters of the particular instance we want to solve.
