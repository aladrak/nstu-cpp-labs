// Варинат 27

#include <iostream>
#include <ctime>
using namespace std;

const int MAX_BRANCHES = 3;

int doRand() { return rand() % 2001 - 1000; }

struct Vertex 
{
    int value;
    int count;  // Number of passes
    Vertex *b1;
    Vertex *b2;
    Vertex *b3;
    // Vertex *(*branch);
};


class TripleTree
{
private:
    Vertex *_head;
    unsigned _maxBranches;
    Vertex *newVertex() 
    {
        Vertex *elem = new Vertex();
        elem->value = 0;
        elem->count = 0;
        elem->b1 = nullptr;
        // Vertex **branch = elem->branch;
        // int i;
        // for (i = 0; i < _maxBranches; ++i, ++branch) 
        // {
        //     *branch = nullptr;
        // }
        return elem;
    }
public:
    TripleTree(unsigned maxBranches): _head(nullptr), _maxBranches(maxBranches) {}
    void AddVertex(int val) 
    {
        Vertex *elem = newVertex();
        _head = elem;
        elem->count = 1;
        elem->value = val;
    }
    void PrintAll() 
    {
        cout << _head->value << endl;
    }
};

int main() {
    TripleTree cTree{MAX_BRANCHES};
    cTree.AddVertex(2);
    cout << "Hello" << endl;
}