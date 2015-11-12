# first-order-logic-parser
A first-order logic parser written in C.

This program parses formulas in a first-order language with no function symbols and one binary predicate symbol 'X'.

'X' denotes the edge relation in a graph, so X[xy] means that there is an edge from x to y. 

A binary connective is a character 'v', '^' or '>' (denoting or, and, implies).

A variable is a character 'x', 'y' or 'z'. There are no constants and no function symbols, so a term is just a variable.

A formula is defined by: φ::=X[ts]|−φ|(φ◦φ)|Ezφ|Azφ where ◦ is a binary connective and t, s, z are variables. We will not include any spaces in our formulas.

To compile: gcc -Wall graph.c yourfile.c -o output

To run: ./output

Created for an university project during my first year. 
More details in graph_cwk.pdf
