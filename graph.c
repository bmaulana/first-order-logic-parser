#include <stdio.h>
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */
#include "yourfile.c"
/*your header file for your program.
You should supply a file called yourfile.c
See comments in yourfile.h
*/



int Fsize=50;
int no_edges;
int no_nodes;

int main()
{
  /*Input a string and check if its a formula*/
  char *name=malloc(Fsize);
  printf("Enter a formula:");
  scanf("%s", name);
  int p=parse(name);
  switch(p)
    {case 0: printf("Not a formula");break;
    case 1: printf("An atomic formula");break;
    case 2: printf("A negated formula");break;
    case 3: printf("A binary connective formula");break;
    case 4: printf("An existential formula");break;
    case 5: printf("A universal formula");break;
    default: printf("Not a formula");break;
    }

  /*Input a graph.  No. of nodes, edges, then input each edge.*/
  printf("How many nodes in the graph?\n");
  scanf(" %d", &no_nodes);
  printf("The nodes are 0, 1, ..., %d\n", no_nodes-1);
  printf("Now the edges\n");
  printf("How many edges?\n");
  scanf(" %d", &no_edges);

  int edges[no_edges][2];  /*Store edges in 2D array*/
  int  i, k, j;
  for(i=0;i<no_edges;i++)
    {printf("input a pair of nodes (<%d)", no_nodes);
      scanf(" %d", &j);scanf(" %d", &k);
      edges[i][0]=j; edges[i][1]=k;
    }

  /*Assign variables x, y, z to nodes */
  int V[3];
/*Store variable values in array
value of x in V[0]
value of y in V[1]
value of z in V[2] */
  printf("Assign variables x, y, z\n");
  printf("x is ?(<%d)", no_nodes);scanf(" %d", &V[0]);
  printf("y is ?");scanf(" %d", &V[1]);
  printf("z is ?");scanf(" %d", &V[2]);

  /*Now check if formula is true in the graph with given variable assignment. */
  if (eval(name, edges, no_nodes,  V)==1)
    printf("The formula %s is true", name); else printf("The formula %s is false", name);


  return(1);
}
