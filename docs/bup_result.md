# BUP

**BUP** is a new declarative programming language for modelling **CSP** and solve them using **SAT**.

As far as we know, there are no precedents of declarative modelling languages allowing to define tuples. BUP permits create complex data structures (called entities) that allow you to group params and variables in a common framework. In next iterations of the language it is possible to consider the idea of extending the use of tuples to object orientation, allowing for instance to include constraints over objects in the definition of the entities.

To sum up, BUP is a language that has emerged to **improve expressiveness when encoding any CSP to SAT** by allowing:
- **Define int or bool parameters**
- Use **forall structures** to loop over parameters.
- Use **if structures** for conditionally apply constraints.
- Generate clause lists by using **comprehension lists**.
- **Translate any formula to CNF** automatically.
- **Customize the output** when the model is satisfable.
- Produce a **clear CNF encoding** resulting of the individual conjunction of CNFs resulting from translating each particular constraint.
- Be **easily extendible** to support further constraints implemented in the SMT API.
