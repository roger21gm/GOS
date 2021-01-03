![a](https://i.imgur.com/dqq0PTd.png)

## Introduction

**C**onstraint **S**atisfaction Problems \(**CSP**s\) consists on finding values for a set of variables subject to a set of constraints. Examples of CSPs are well-known puzzles such as Sudoku or problems appearing in industry such as Scheduling or Timetabling. This kind of problems can be easily modelled with declarative programming languages.

Declarative programming languages attempt to describe what the program must accomplish in terms of the problem domain, rather than describe how to accomplish it as a sequence of the programming language primitives. This is in contrast with imperative programming, which implements algorithms in explicit steps.

A subset of declarative languages are modelling languages. This project will be focused on this subset and the main purpose will be get a new declarative programming language for modelling any **CSP** to Boolean Satisfiability **SAT**.

#### SAT

One of the most successful methodologies for solving CSP relies on the conversion into SAT problems, i.e., to **build a Boolean formula that has a solution if and only if the original CSP has also a solution**. The advantage is the wide availability of free and **eﬀicient SAT-solvers**.

## GOS & BUP

The of the tool is **GOS** \(**G**irona **O**ptimization **S**ystem\) and the language that uses is **BUP**.

> As a curiosity, the name choice lies in the fact that in [Catalan](https://en.wikipedia.org/wiki/Catalan_language), my mother tongue, GOS means dog (:dog:) and, also in Catalan, the onomatopoeia that describes the sound that dogs make \(the language they speak\) is BUP-BUP! \(woof-woof!\). Therefore, GOS \(dog\) is the name of the tool implemented and BUP \(woof\) is the language defined that is used by GOS. Apart from that, a real dog \(GOS\) can be considered a tracker, and that is also what the project is about: looking for a solution to CSPs.

### What is GOS?

GOS is a declarative tool for modelling and solving any CSP to SAT, improving its expresiveness. **GOS gives you an easy gateway for modelling with SAT**.

![](https://i.imgur.com/orO0kZ8.jpg)

# Resources

:house: Homepage: https://roger21gm.github.io/GOS <br/>
:books: Documentation: https://roger21gm.github.io/GOS <br/>
:page_facing_up: Report: https://drive.google.com/file/d/1mGZyVckfyidUqUQMpDpq69XqbsYwamMT/view?usp=sharing <br/>
:file_folder: Source Code: https://github.com/roger21gm/GOS <br/>
:globe_with_meridians: Online demo: https://gos.rgeneroso.online <br/>

# Building GOS

To get the compiler executable follow the following steps:

1. Clone the GOS GitHub repository
```
git clone https://github.com/roger21gm/GOS
```
2. Change current directory to the cloned repository
```
cd GOS
```
3. Create a directory to build the project
```
mkdir build
```
4. Change current directory to the created build directory
```
cd build
```
5. Run CMake to generate the makefile according to your OS and hardware
```
cmake ..
```
6. Finally run the makefile to generate the executable
```
make
```

# Running GOS

Once make process ends, the executable file `./gos` is generated inside build directory. You can use *GOS* by adding two input files:
- Model file written in BUP (see [documentation](https://roger21gm.github.io/GOS))
- Parameters file written in JSON 

Having the current directory in the build directory, to run the compiler and get a solution, only write:
```
./gos <path_to_model_file> <path_to_model_file>
```

On the other hand, if you want to get the CNF formula in DIMACS format include the option `-pf=1` or `--print-formula`:
```
./gos -pf=1 <path_to_model_file> <path_to_model_file>
```
