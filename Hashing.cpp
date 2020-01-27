#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

//structure to hold protein sequence and its count
struct arrayelement {
 char protein[30];
 int count;
};
arrayelement proteins[40];

// find hash code
int findHashCode(char firstLetter, char lastLetter)
{
    return ((int(firstLetter)-65)+(2*(int(lastLetter)-65)))%40;
}

// check if given protein exists in structure
bool isFound(char pro[40], int nelem)
{
    for (int k=0; k<nelem; k++)
    {
        if(strcmp(pro,proteins[k].protein)==0)
        {
            proteins[k].count = proteins[k].count+1;
            return true;
        }
    }
    return false;
}

int main()
{
    char pro[30];
    int n;
    int k;
    int nelem = 0;
    int found = 0;

    // open source file
    ifstream fin("C:\\Users\\knguye2\\Documents\\proteins.txt");
    if (!fin) { cerr << "Input file could not be opened\n"; exit(1); }

    // initialize the protein structure
    for (k=0; k<40; k++)
    {
        strcpy(proteins[k].protein, " ");
        proteins[k].count=0;
    }

    while(!fin.eof())
    {
        found=0;
        fin >> pro;

        // enter element if not found in the structure
        if (!isFound(pro, nelem))
        {
            n = strlen(pro);
            int k = findHashCode(pro[0], pro[n-1]);
            nelem++;
            while(1)
            {
                if (k >= 40)
                    k = 0;
                if (strcmp(proteins[k].protein," ")==0)
                {
                    strcpy(proteins[k].protein, pro);

                    proteins[k].count = proteins[k].count+1;
                    break;
                }
                k++;
            }
        }

    }
    cout << endl;

    // print structure
    for (int k=0; k<40; k++)
    {
        if (strcmp(proteins[k].protein, " ")!= 0)
            cout << proteins[k].protein << " "
            << proteins[k].count << endl;
    }

    return 0;

    // close file
    fin.close();

}



