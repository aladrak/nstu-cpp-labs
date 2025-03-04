// Вариант 26

#include <iostream>
#include <ctime>
#include <utility>
#include <conio.h>
#include <cstring>
using namespace std;

const int STR_SIZE {5};

// Generates random string
char *randStr() 
{
    char *s = new char[STR_SIZE + 1], *a = s;
    a += STR_SIZE; *a = '\0';
    for (--a; a >= s; --a) 
    {
        *a = rand() % 25 + 65;
    }
    return s;
}

class CyclicList 
{
private:
    int _count = 0;
    bool _isEmpty = true;
    struct Node 
    {
        Node *next;
        int num;
        char *str;
    };
    Node *_first = nullptr;
    Node *newElement(char *s) 
    {
        Node *newElem = new Node();
        newElem->num = _count;
        newElem->next = nullptr;
        newElem->str = s;
        return newElem;
    }
    void freeElem(Node *elem) 
    {
        elem->next = nullptr;
        delete elem;
    }
public:
    CyclicList() { }
    bool IsEmpty() { return _isEmpty; }
    void recList(Node *curr, char *s) {
        if (strcmp(curr->str, s) > 0) {}
    }
    void AddElem() 
    {
        Node *elem = newElement(randStr()); ++_count;
        if (_isEmpty)
        {
            _first = elem;
            _isEmpty = false;
            return;
        }
        if (_first->next == nullptr) 
        {
            elem->next = _first;
            _first->next = elem;
            if (strcmp(_first->str, elem->str) > 0) 
            {
                _first = elem;
                return;
            }
        
        Node *curr = _first;
        Node *prev = _first;
        while (1)
        {
            if (strcmp(curr->str, elem->str) < 0) 
            {

            }
            if (curr->next == _first) {

            }
        }
        if (strcmp(curr->str, elem->str) > 0)
        {
            elem->next = curr;
            prev->next = elem;
            return;
        }
        curr->next = elem;
        elem->next = _first;
    }

    void PrintAll() 
    {
        if (_isEmpty) { cerr << "Empty list!" << endl; return; }
        Node *curr = _first;
        while (curr->next != _first && curr->next != nullptr) 
        {
            cout << curr->num << " " << curr->str << endl;
            curr = curr->next;
        }
        cout << curr->num << " " << curr->str << endl;
    }

    void Remove()
    {
        if (_isEmpty) { cerr << "Empty list!" << endl; return; }
        Node *picked = _first;
        while (1)
        {
            char c = _getch();
            switch (c) 
            {
                case 87: // W
                    break;
                case 83: // S
                    break;
                case 8: // Backspace
                    freeElem(picked);
                    break; 
            }
        }
    }

    pair<int, char*> Find(string s) 
    {
        if (_isEmpty) { cerr << "Empty list!" << endl; return make_pair(NULL, nullptr); }
        Node *elem = _first;

        return make_pair(elem->num, elem->str);
    }
};

int main() 
{
    srand(time(NULL));
    CyclicList clist{};
    for (int i = 0; i < 10; i++) 
    {
        clist.AddElem();
    }
    clist.PrintAll();
    // clist.Remove();
    // cout << randStr() << endl;
}