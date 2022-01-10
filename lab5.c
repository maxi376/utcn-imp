#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define LETTER 257
#define NEWLINE '\n'
int symbol;
char yylval;
typedef struct _tree {
	struct _tree *left, *right;
	char k;
}tree;

void next_symbol();
void error(int line);
tree *E();
tree *F();
tree *T();
tree *P();


void next_symbol()
{
    symbol = yylex();
}

int yywrap()
{
    return 1;
}

void error(int line) 
{
    printf ("Error on the line %d\n", line);
}

tree *E() 
{
    tree *t = T(); //left
    if (symbol == '|') 
    {
        next_symbol();
        
        tree *var = E(); //right
        
        tree *new = (tree *) malloc(sizeof(struct _tree));
        new->left = t;
        new->right = var;
        new->k = '|';
        
        return new;
    }
    
    return t;
}

tree *F() 
{
    tree *t;
    
    //apeleaza P
    t = P();
    if (symbol == '*') 
    {
        next_symbol();
        
        tree *var = (tree *) malloc(sizeof(struct _tree));
        var->left = NULL;
        var->right = NULL;
        var->k = '*';
        
        var->left = t;
        
        return var;
        
    }
    else 
    {
        return t;
    }
}

tree *T()
{
    tree *t = F();
    
    if (symbol == LETTER || symbol == '(') 
    {
        tree *var = (tree *) malloc(sizeof(struct _tree));
        var->k = '&';

     
        tree *treeright = T();
        var->left = t;
        var->right = treeright;
        
        return var;
    }
    
    return t;
}

tree *P()
{
    tree *var;
    if (symbol == '(') 
    {
        next_symbol();
        var = E();
       
        if (symbol == ')') 
        {
            next_symbol();
            return var;
        }
        else
        {
             error(__LINE__);
        }
    }
    else if (symbol == LETTER) 
    {
        var = (tree*) malloc(sizeof(struct _tree));
        var->left = NULL;
        var->right = NULL;
        var->k = yylval;
        
        next_symbol();
    }
    
    return var;
}

void print_tree(tree *t)
{

    if (t != NULL) 
    {
        if (t->right) 
        {
            printf("    ");
            print_tree(t->right);
        }
        if (t->left) 
        {
            printf("    ");
            print_tree(t->left);
        }
        printf("%c \n", t->k);
    }

}

void parser() 
{
    print_tree(E());

    if (symbol != '\n')
        error(__LINE__);
}

int main ()
{
    next_symbol();
    while(symbol !=0)
    {
        parser();
        next_symbol();
    }
    return 0;
}
