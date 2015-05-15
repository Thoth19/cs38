#include <complex>
#include <cmath>
#include <iostream>
#include <stdio.h>

/*
We want to compute all of the f(l,y) for a given l and return the maximum one. 
We are effectively given f(l,y) in the problem, which is g(leaf).
We are going to use the following heuristic. Since we have the second function
that they give us, we know that ancestors contribute to the values of children
So that means that if we have f(leaf), and we are looking at a node, then if 
f(node) + depth < f(leaf) then theres no way any decedant can be big enough 
to beat leaf, so don't bother to look.
*/
int static depth;
float static best_so_far;

float mod_by_one(float x)
{
    float ans = x;
    while(ans < 0)
    {
        ans ++;
    }
    while(ans >= 1)
    {
        ans --;
    }
    return ans;
}


float f(float y)
{
    return std::cos(2*3.141592653589793*y);
}
/*
height is how far into the tree we are, starting at one
node is the value of the node
sum_above is the sum of the f function on above values
*/
void recurse(int height, float node, float sum_above)
{   
    float temp;
    // printf("recurse call: height: %d node: %f sum_above: %f\n",height,node,sum_above);
    // printf("best so far %f\n", best_so_far);
    temp = (f(node) + (height-1)*sum_above)/(height);
    // printf("temp = %f\n", temp);
    if (height == depth)
    {
        if (best_so_far < temp)
        {
            best_so_far = temp;
        }
    }
    else
    {
        // printf("best so far %f\n", best_so_far);
        // printf("heuristic %f\n",temp + depth - height);
        if ((temp*height + (depth - height))/depth <best_so_far)
        {
            /* skip this subtree */
            // printf("skip\n");
        }
        else
        {
            /* investigate this subtree */
            // printf("recurse\n");
            recurse(height + 1, mod_by_one(node * 5.0/2.0), temp); //leftchild
            recurse(height + 1, mod_by_one((node * 5.0/2.0) +1.0/2.0), temp); //rightchild
        }
    }
}


int main(int argc, char const *argv[])
{
    depth = atoi(argv[1]);
    while(depth < 71)
    {
        best_so_far = -1*depth;
        recurse(1,1.0/2.0,0);
        printf("At L = %d. F(L) = %f\n", depth, best_so_far);
        depth ++;
        // break;
    }
    // l is fixed for each value of F(l) that we compute
    return 0;
}
