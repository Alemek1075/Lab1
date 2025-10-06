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
        long double px, py;
        px = m[0][0] * p.x + m[0][1] * p.y + a;
        py = m[1][0] * p.x + m[1][1] * p.y + b;
        p.x = px; p.y = py;
    }
};

void readValuesFromFile(const string& filename, int& n, Point& p, double(&m)[2][2], double& a, double& b, vector<F>& functions) {

    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cant open file '" + filename + "'");
    }

    if (!(file >> n)) throw runtime_error("problem with amount of operations");
    if (!(file >> p.x)) throw runtime_error("problem with x coordinate of starting point.");
    if (!(file >> p.y)) throw runtime_error("problem with y coordinate of starting point.");

    string line;
    double values[6];
    int count;
    int index;
    getline(file, line);
    while (getline(file, line)) {
        istringstream ss(line);

        count = 0;

        while (ss >> values[count]) {
            ++count;
        }

        if (count > 6)
            throw runtime_error("More than 6 digits");

        if (count < 6)
            throw runtime_error("Less than 6 digits");

        index = 0;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                m[i][j] = static_cast<double>(values[index++]);
            }
        }

        a = static_cast<double>(values[4]);
        b = static_cast<double>(values[5]);

        functions.emplace_back(F(m, a, b));
    }
    file.close();
}

int main() {
    string input = "input.txt";
    string output = "output.txt";

    int n;
    Point p;
    double m[2][2];
    double a, b;
    vector<F> functions;

    try {
        readValuesFromFile(input, n, p, m, a, b, functions);
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, functions.size() - 1);

    ofstream outfile(output);
    if (!outfile.is_open()) {
        cerr << "Cant open the output file.";
        return 1;
    }

    int i = 0;
    while (i < n) {
        functions[dist(gen)](p);
        outfile << p.x << " " << p.y << endl;
        i++;
    }
    
    outfile.close();
    return 0;
}


