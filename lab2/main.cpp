// Вариант 9
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <utility>
#include <cmath>
using namespace std;

int dwRand() { return (rand() % 7 + 1) * 100 + (rand() % 8) * 10 + (rand() % 8); }

pair<int*, int> readFile(char *path) 
{
    ifstream f(path, ios::in);
    int i = 0, cap = 1024;
    int *memloc = new int[cap];
    int *arr = memloc;
    if (f.is_open()) 
    {
        for (string s; getline(f, s); ++i) 
        {
            if (i > cap - 1) // extend capacity
            {
                memloc = new int[cap * 2];
                copy(arr, arr + cap, memloc);
                cap *= 2;
                delete[] arr;
                arr = (memloc);
            }
            *(arr + i) = stoi(s);
        }
    }
    f.close();
    return make_pair(arr, i);
}

void writeFile(string path, int *arr, size_t size) 
{
    ofstream f(path, ios::out);
    if (f.is_open()) 
    {
        for (int i = 0; i < size; ++i) 
        {
            f << *(arr + i) << endl;
        }
    }
    f.close();
}

void GenerateDataset (char *filename, int num) 
{
    ofstream f(filename, ios::out);
    if (f.is_open()) 
    {
        for (int i = 0; i < num; ++i) 
        {
            f << dwRand() << endl;
        }
    }
    f.close();
}

void trSmooth() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 7; j++) { cout << pow(2, i) * pow(3, j) << endl; }
    }
}

int SortDataset (char *filename)
{
    pair<int*, int> dataPair = readFile(filename);
    int *arr = dataPair.first;
    unsigned long comps = 0; 
    size_t size = dataPair.second;
    // int gaps[]{1750, 701, 301, 132, 57, 23, 10, 4, 1}; // Ciura seq
    int gaps[]{729, 576, 512, 432, 384, 288, 256, 243, 192, 144, 128, 
        96, 81, 72, 64, 54, 48, 36, 32, 24, 16, 18, 12, 9, 6, 3, 2, 1}; // Pratt seq

    for (int s : gaps) {
        for (int i = s; i < size; ++i) {
            for (int j = i - s; j >= 0 && arr[j] > arr[j + s]; j -= s, ++comps) {
                swap(arr[j], arr[j + s]);
            }
        }
    }

    string s(filename); 
    s.insert(s.find(".", 2), ".sort");
    writeFile(s, arr, size);
    delete[] arr;
    return comps;
}


int main() 
{
    srand(time(NULL));
    trSmooth();
    string path("./data.txt");
    GenerateDataset(path.data(), 1033);
    cout << "Shell sort" << endl <<
    "Compare count: \t" << SortDataset(path.data()) << endl;
}