#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <random>

using namespace std;

struct Point {
    long double x, y;
};

class F {
    double m[2][2];
    double a, b;
public:
    F(double(&_m)[2][2], double _a, double _b) : a(_a), b(_b) {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                m[i][j] = _m[i][j];
    };

    void operator() (Point& p) {
        double px, py;
        px = m[0][0] * p.x + m[0][1] * p.y + a;
        py = m[1][0] * p.x + m[1][1] * p.y + b;
        p.x = px; p.y = py;
    }
};
