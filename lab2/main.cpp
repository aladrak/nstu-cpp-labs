// Вариант 9
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;

int dwRand() { return (rand() % 7 + 1) * 100 + (rand() % 8) * 10 + (rand() % 8); }

int* readFile(char *path) 
{
    ifstream f; int *arr {new int[]}; 
    f.open(path, ios::in);
    if (f.is_open()) {
        while (f.getline()) {}
    }
    f.close();
}

void GenerateDataset (char *filename, int num) 
{
    ofstream f;
    f.open(filename, ios::out);
    for (int i = 0; i < num; i++) {
        f << dwRand() << endl;
    }
    f.close();
}

int SortDataset (char *filename) // Сортировка Шелла
{
    return 0;
}


int main() 
{
    srand(time(NULL));
    char *f = new char*[] = "./data.txt";
    GenerateDataset(f, 40);
    cout << "Hello" << endl;
}