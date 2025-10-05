#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

void readValuesFromFile(const string& filename, double(&arr)[4], double& a, double& b) {
    try {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("ERROR: Can't open file" + filename + "'");
        }

        string line;
        if (!getline(file, line)) {
            throw runtime_error("ERROR: Empty file");
        }

        stringstream ss(line);
        double values[6];
        int count = 0;

        while (ss >> values[count]) {
            ++count;
            if (count > 6)
                throw runtime_error("ERROR: too much numbers in file");
        }

        if (count < 6)
            throw runtime_error("ERROR: not enought numbers in file");


        for (int i = 0; i < 4; ++i)
            arr[i] = values[i];


        a = values[4];
        b = values[5];

    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        throw; 
    }
}

int main() {
    double arr[4];
    double a, b;

    try {
        readValuesFromFile("data.txt", arr, a, b);

        cout << "arr = ";
        for (double x : arr) cout << x << " ";
        cout << "\na = " << a << ", b = " << b << endl;
    }
    catch (...) {
        cerr << "ERROR" << endl;
    }

    return 0;
}

