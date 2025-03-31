// Варинат 27

#include <iostream>
#include <ctime>
using namespace std;

// Вершина всегда состоит из 4 элементов: поля данных и 3 указателей на возможные 
// вершины нижнего уровня. Указателям, не ссылающимся на вершины, присваивается значение NULL.

int doRand() { return rand() % 2001 - 1000; }

struct Vertex 
{
    int value;
    int count;  // Number of passes
    Vertex *b1;
    Vertex *b2;
    Vertex *b3;
};


class TripleTree
{
private:
    Vertex *_root;
    Vertex *newVertex(int val) 
    {
        Vertex *elem = new Vertex();
        elem->value = val;
        elem->count = 0;
        elem->b1 = elem->b2 = elem->b3 = nullptr;
        return elem;
    }
    Vertex *recurAdd(Vertex *p, int val) 
    {
        if (p == nullptr) 
        {
            p = newVertex(val); p->count = 1;
        }
        else 
        {
            p->count++;
            if (p->b1 != nullptr && p->b2 != nullptr && p->b3 != nullptr)
            {
                if (p->b1->count % 3 <= p->b2->count % 3)
                    p->b1 = recurAdd(p->b1, val);
                else if (p->b2->count % 3 <= p->b3->count % 3)
                    p->b2 = recurAdd(p->b2, val);
                else
                    p->b3 = recurAdd(p->b3, val);
            }
            else if (p->b1 == nullptr) 
                p->b1 = recurAdd(p->b1, val);
            else if (p->b2 == nullptr) 
                p->b2 = recurAdd(p->b2, val);
            else if (p->b3 == nullptr)
                p->b3 = recurAdd(p->b3, val);
        }
        return p;
    }
    void recurPrint(Vertex *p) 
    {
        if (p != nullptr) 
        {
            cout << p->count << " " << p->value << endl;
            recurPrint(p->b1);
            recurPrint(p->b2);
            recurPrint(p->b3);
        }
    }
public:
    TripleTree(): _root(nullptr) {}

    bool IsEmpty() { return _root == nullptr; }

    void AddVertex(int val) 
    {
        _root = recurAdd(_root, val);
    }

    void PrintAll() 
    {
        recurPrint(_root);
    }
};

int main() 
{
    srand(time(NULL));
    TripleTree cTree;
    for (int i = 0; i < 30; i++) 
    {
        cTree.AddVertex(doRand());
    }
    cTree.PrintAll();
}