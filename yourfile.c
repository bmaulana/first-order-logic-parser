#include <stdio.h>
#include <string.h>   /* for all the new-fangled string functions */
#include <stdlib.h>     /* malloc, free, rand */

char *segment(char *g, int i, int j) {
//if g represents a list of characters, this returns segment
//starting from i'th character of g up to j-1 th character
    char *seg = malloc(j-i+1);
    int a = 0;
    for (a = 0; a < (j-i); a++)
    {
        char n = g[i-1+a];
        seg[a]= n;
    }
    seg[j-i] = '\0';
    return seg;
}


int varchar(char x) {
//checks whether x is a variable
//i.e. 'x' or 'y' or 'z'
    if(x=='x' || x=='y' || x=='z') {
        return 1;
    } else {
        return 0;
    }
}

int vartonum(char x) {
//returns 0 for 'x'
//returns 1 for 'y'
//returns 2 for 'z'
    if(x=='x') {
        return 0;
    }
    if(x=='y') {
        return 1;
    }
    if(x=='z') {
        return 2;
    }
    return 0;
}

int quantchar(char x) {
//checks if character is a quantifier
//'A' or 'E'
    if(x=='A' || x=='E') {
        return 1;
    } else {
        return 0;
    }
}

int bc(char x) {
//checks of character is 'v', '^' or '>'
    if(x=='v' || x=='^' || x=='>') {
        return 1;
    } else {
        return 0;
    }
}

char bin(char *g) {
//if g is "(fmla1 bc fmla2)" it returns bc, where bc is 'v', '^' or '>'.
//if g is not a binary formula, it returns '0'.
    int brackets = 0, i = 0;
    while(1) {
        char c = g[i];
        if(c=='\0') {
            return '0';
        }
        if(c=='(') {
            brackets += 1;
        }
        if(c==')') {
            brackets -= 1;
        }
        if(bc(c)==1 && brackets==1) {
            return c;
        }
        i++;
    }
}

char *partone(char *g) {
//only called if g is binary formula
//if g is ``(fmla 1 bc fmla2)" this returns fmla1
    int brackets = 0, i = 0;
    while(1) {
        char c = g[i];
        if(c=='(') {
            brackets += 1;
        }
        if(c==')') {
            brackets -= 1;
        }
        if(bc(c)==1 && brackets==1) {
            char *fmla1 = segment(g,2,i+1);
            return fmla1;
            break;
        }
        i++;
    }
}

char *parttwo(char *g) {
//similar.
    int brackets = 0, i = 0;
    while(1) {
        char c = g[i];
        if(c=='(') {
            brackets += 1;
        }
        if(c==')') {
            brackets -= 1;
        }
        if(bc(c)==1 && brackets==1) {
            char *fmla2 = segment(g,i+2,strlen(g));
            return fmla2;
            break;
        }
        i++;
    }
}

int parse(char *g) {
    //Atomic
    if(g[0] == 'X' && g[1] == '[' && varchar(g[2]) == 1 && varchar(g[3]) == 1 && g[4] == ']' && g[5] == '\0') {
        return 1;
    }

    //Negation
    if(g[0] == '-') {
        char *tail = segment(g,2,strlen(g)+1);
        int check = parse(tail);
        if(check != 0) {
            return 2;
        }
    }

    //Binary
    if(g[0] == '(' && g[strlen(g)-1] == ')') {
        if(bin(g) != '0') {
            char *fmla1 = partone(g);
            char *fmla2 = parttwo(g);
            int check1 = parse(fmla1);
            int check2 = parse(fmla2);
            if(check1 != 0 && check2 != 0) {
                return 3;
            }
        }
    }

    //Existential
    if(g[0] == 'E' && varchar(g[1]) == 1) {
        char *tail = segment(g,3,strlen(g)+1);
        int check = parse(tail);
        if(check != 0) {
            return 4;
        }
    }

    //Universal
    if(*g == 'A' && varchar(g[1]) == 1) {
        char *tail = segment(g,3,strlen(g)+1);
        int check = parse(tail);
        if(check != 0) {
            return 5;
        }
    }

    return 0;
}

int varValue(char var, int V[3]) {
    int varnum = vartonum(var);
    return V[varnum];
}

int no_edges;

int checkIfEdge(int edges[no_edges][2],int val1,int val2) {
    int i = 0;
    for (i = 0; i < no_edges; i++) {
        if(edges[i][0] == val1 && edges[i][1] == val2){
            return 1;
        }
    }
    return 0;
}

int eval(char *fmla, int edges[no_edges][2], int size, int V[3]) {

    int type = parse(fmla);

    //Atomic
    if(type == 1) {
        char var1 = fmla[2];
        char var2 = fmla[3];
        int val1 = varValue(var1,V);
        int val2 = varValue(var2,V);
        int result = checkIfEdge(edges,val1,val2);
        return result;
    }

    //Negation
    if(type == 2) {
        char *tail = segment(fmla,2,strlen(fmla)+1);
        int valTail = eval(tail,edges,size,V);
        if(valTail==1) {
            return 0;
        } else {
            return 1;
        }
    }

    //Binary Connective
    if(type == 3) {
        char *fmla1 = partone(fmla);
        char conn = bin(fmla);
        char *fmla2 = parttwo(fmla);
        int valFmla1 = eval(fmla1,edges,size,V);
        int valFmla2 = eval(fmla2,edges,size,V);
        if(conn == '^') {
            if(valFmla1 == 1 && valFmla2 == 1) {
                return 1;
            }
        }
        if(conn == 'v') {
            if(valFmla1 == 1 || valFmla2 == 1) {
                return 1;
            }
        }
        if(conn == '>') {
            if(valFmla1 == 0 || valFmla2 == 1) {
                return 1;
            }
        }
        return 0;
    }

    //Existential
    if(type == 4) {
        char var = fmla[1];
        int varnum = vartonum(var);
        char *tail = segment(fmla,3,strlen(fmla)+1);
        int i = 0;
        for (i = 0; i < size; i++) {
            V[varnum] = i;
            int valTail = eval(tail,edges,size,V);
            if(valTail == 1) { //if any valuation of var is true, return true
                return 1;
            }
        }
        return 0;
    }

    //Universal
    if(type == 5) {
        char var = fmla[1];
        int varnum = vartonum(var);
        char *tail = segment(fmla,3,strlen(fmla)+1);
        int i = 0;
        for (i = 0; i < size; i++) {
            V[varnum] = i;
            int valTail = eval(tail,edges,size,V);
            if(valTail == 0) { //if any valuation of var is false, return false
                return 0;
            }
        }
        return 1;
    }

    return 0;
}