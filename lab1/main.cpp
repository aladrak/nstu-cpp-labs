// x^2 - sin(5x) = 0
// x.min = -2.0     x.max = 1.0     h = 0.05


#include <iostream>
#include <cmath>
#include <list>
using namespace std;

const double X_MAX = 1., X_MIN = -2., H = 0.05, EPS = 0.001;

double func(double x) { return x*x - sin(5.*x); }

bool criteria(double x1, double x2 = 0.) { return (abs(func(x1) - x2) < EPS); }

//Половинное деление
double halving(double a, double b, int* c) 
{
    double z = (a+b)/2; (*c)++;
    if (abs(func(z)) < EPS) return z;
    if (func(a) * func(z) < 0) { return halving(a, z, c); }
    else { return halving(z, b, c); }
}

// Метод Хорд
double chord(double a, double b, int* c) 
{
    double x = (a*func(b) - b*func(a)) / (func(b) - func(a)); (*c)++;
    if (criteria(x)) return x;
    if (func(a) * func(x) < 0) { return halving(a, x, c); }
    else { return halving(x, b, c); }
}

double tangent(double x0, int* c) 
{
    double x1 = x0 - func(x0) / (2*x0 - 5*cos(5*x0)); (*c)++;
    if (criteria(x1)) { return x1; }
    else {return tangent(x1, c);}
}

double iteration(double x0, double x1, int* c) 
{
    double z = x0 - 1/(-2.061) * (2*x0 - 5*cos(5*x0)); (*c)++;
    if (criteria(z, x0)) { return z; }
    else { return iteration(z, x0, c); }
}

int main()
{
    list<pair<double, double>> listPair;
    for (double i = X_MIN; i < X_MAX; i += H) 
    {
        // if (i > -.05 && i < .05) i = 0;
        listPair.push_back(make_pair(i, i + 0.05));
        // cout << i << " \t" << func(i) << endl;
    }
    for (pair<double, double> i : listPair) 
    {
        int* c = new int();
        if (func(i.first) * func(i.second) < 0) 
        {
            cout << "\n[" << i.first << " \t" << i.second << "]" << endl;
            *c = 0;
            cout << "Halving = \t" << halving(i.first, i.second, c) << " \titrs: " << *c << endl;
            *c = 0;
            cout << "Chord = \t" << chord(i.first, i.second, c) << " \titrs: " << *c << endl;
            *c = 0;
            cout << "Tangent = \t" << tangent(i.first, c) << " \titrs: " << *c << endl;
            *c = 0;
            // cout << "Iteration = \t" << iteration(i.first, i.second, c) << " \titrs: " << *c << endl;
        }
    }
}