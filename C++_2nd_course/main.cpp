#include <iostream>
#include <fstream>
#include <vector>
#include <random>

struct Point {
    double x, y;
public:
    Point() {};
    Point(double _x, double _y) : x(_x), y(_y) {};
};

struct Matrix {
    double a, b, c, d;
public:
    Point() {};
    Point(double _x, double _y) : x(_x), y(_y) {};
};

class F {
    int num;
public:
    Point operator() (double a, double b, double c, double d, double e, double f) {
        return Point((a * x + b * y + e), (c * x + d * y + f));
    }
    Point operator() (Matrix m, Point p, Vector v) {
        return Point((a * x + b * y + e), (c * x + d * y + f));
    }
};

//456

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    if (!fin.is_open() || !fout.is_open()) {
        std::cerr << "Error while trying to open input file.\n";
        return 1;
    }
}
