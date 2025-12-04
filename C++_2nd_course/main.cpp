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

struct Transform {
    double m[2][2];
    double a, b;
};

class F {
    vector<Transform> transforms;
    mt19937 gen;

public:
    F() {
        random_device rd;
        gen.seed(rd());
    }

    void add(double m[2][2], double a, double b) {
        Transform t;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                t.m[i][j] = m[i][j];
        t.a = a;
        t.b = b;
        transforms.push_back(t);
    }

    Point operator() (Point p) {
        if (transforms.empty()) return p;
        uniform_int_distribution<> dist(0, transforms.size() - 1);
        const auto& t = transforms[dist(gen)];

        return {
            t.m[0][0] * p.x + t.m[0][1] * p.y + t.a,
            t.m[1][0] * p.x + t.m[1][1] * p.y + t.b
        };
    }
};

void readValuesFromFile(const string& filename, int& n, Point& p, F& f) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cant open file '" + filename + "'");
    }

    if (!(file >> n)) throw runtime_error("problem with amount of operations");
    if (!(file >> p.x)) throw runtime_error("problem with x coordinate of starting point.");
    if (!(file >> p.y)) throw runtime_error("problem with y coordinate of starting point.");

    string line;
    double values[6];
    double m[2][2];
    double a, b;
    int count;
    int index;

    getline(file, line);
    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream ss(line);

        count = 0;
        while (ss >> values[count]) {
            ++count;
        }

        if (count > 6) throw runtime_error("More than 6 digits");
        if (count < 6) throw runtime_error("Less than 6 digits");

        index = 0;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                m[i][j] = static_cast<double>(values[index++]);
            }
        }

        a = static_cast<double>(values[4]);
        b = static_cast<double>(values[5]);

        f.add(m, a, b);
    }
    file.close();
}

int main() {
    string input = "input.txt";
    string output = "output.txt";

    int n;
    Point p;
    F f;

    try {
        readValuesFromFile(input, n, p, f);
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    ofstream outfile(output);
    if (!outfile.is_open()) {
        cerr << "Cant open the output file.";
        return 1;
    }

    int i = 0;
    while (i < n) {
        p = f(p);
        outfile << p.x << " " << p.y << endl;
        i++;
    }

    outfile.close();
    return 0;
}
