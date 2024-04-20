#include <iostream>
#include <vector>
#include <string>
#include <map>


using namespace std;

/*
Consider the following configuration of 64 triangles:

       /\
      /\/\
     /\/\/\
    /\/\/\/\
   /\/\/\/\/\
  /\/\/\/\/\/\
 /\/\/\/\/\/\/\
/\/\/\/\/\/\/\/\

We wish to colour the interior of each triangle with one of three colours: red, green or blue,
so that no two neighbouring triangles have the same colour. Such a colouring shall be called valid.
Here, two triangles are said to be neighbouring if they share an edge.
Note: if they only share a vertex, then they are not neighbours.

For example, here is a valid colouring of the above grid:

A colouring C' which is obtained from a colouring C by rotation or reflection is considered distinct from C unless the two are identical.

How many distinct valid colourings are there for the above configuration?

*/

enum Color { red=1, green=2, blue=3, none=4 };
struct Cell
{
    Cell* up;
    Cell* left;
    int line;
    Color color;
};


map <string, long long unsigned> storage;

string toStr(const vector <Cell*>& liste_cells, unsigned line)
{
    string ret("");
    for (unsigned i=(line-1)*(line-1); i<line*line; i++)
        ret+=liste_cells[i]->color+'A';
    return ret;
}

#define NLINES  8

unsigned long long backtracking (const vector <Cell*>& liste_cells, unsigned k)
{
    if (k==NLINES*NLINES) return 1;
    else
    {
        string key;
        if (liste_cells[k]->line != -1)
        {
            key = toStr(liste_cells,liste_cells[k]->line);
            map <string, long long unsigned>::iterator f = storage.find(key);
            if (f != storage.end())
            {
                return f->second;
            }
        }

        unsigned long long ret = 0;
        for (int candidate=red; candidate!=none; ++candidate)
        {
            if ( (liste_cells[k]->up == NULL || liste_cells[k]->up->color != candidate) &&
                    (liste_cells[k]->left == NULL || liste_cells[k]->left->color != candidate) )
            {
                liste_cells[k]->color = (Color)candidate;
                long long unsigned n=backtracking (liste_cells, k+1);
                ret += n;
            }
        }

        if (liste_cells[k]->line != -1)
            storage.insert( make_pair(key,ret) );

        return ret;
    }
}

int main()
{
    Cell pyramide[NLINES][NLINES*NLINES];
    vector <Cell*> liste_cells;

    for (unsigned i=0; i<NLINES; i++)
    {
        for (unsigned j=0; j<(2*i)+1; j++)
        {
            Cell curr;
            curr.up = (i>0 && j%2 ? &pyramide[i-1][j-1] : NULL);
            curr.left = (j>0 ? &pyramide[i][j-1] : NULL);
            curr.line = (j==0 ? i : -1);
            curr.color = none;

            pyramide[i][j] = curr;
            liste_cells.push_back(&pyramide[i][j]);
        }
    }

    cout << backtracking(liste_cells, 0) << endl;

    return 0;
}