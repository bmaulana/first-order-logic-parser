int parse(char *g);
/* 
g is pointer to char, so a string.  parse returns integer. 
0 for non-formula
1 for atomic formula e.g. X[xy] (5 chars)
2 for formula starting with '-', but check that rest of string is a formula.
3 for binary formula `(fmla bc fmla)'
4 for existential e.g. Ex fmla (but no spaces)
5 for universal e.g. Ax fmla (no spaces)
 */


/*
To help with your implementation of parser I recommend you implement the following (up to you though).

char *segment(char *g, int i, int j)
if g represents a list of characters, this returns segment 
starting from i'th character of g up to j-1 th character

int varchar(char x)
checks whether x is a variable
i.e. 'x' or 'y' or 'z'

int vartonum(char x)
returns 0 for 'x'
returns 1 for 'y'
returns 2 for 'z'


int quantchar(char x)
checks if character is a quantifier
'A' or 'E'

int bc(char x)
checks of character is 'v', '^' or '>'


char bin(char *g)
only called if g is a binary formula.
if g is "(fmla1 bc fmla2)" it returns bc, where bc is 'v', '^' or '>'

char *partone(char *g)
only called if g is binary formula
if g is ``(fmla 1 bc fmla2)" this returns fmla1

char *parttwo(char *g)
similar.


 */

int no_edges;

int eval(char *fmla, int edges[no_edges][2], int size, int V[3]);
/*
Character string fmla is formula to be evaluated.
edges is 2D array containing list of edges
Each edge consists of 2 nodes.
A node is 0 or 1 or  2 or ..., or size-1
size is number of nodes in the graph
V is array of 3 integers, contains values of variables x, y, z.
*/

