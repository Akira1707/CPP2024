#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
void SolveEquation2(double a, double b, double c, vector<double>& root) {
    double delta, x1, x2;
    root.clear();

    if (a == 0) {
        if (b == 0) {
            return;
        }
        else {
            root.push_back(-c / b);
            return;
        }
    }

    delta = b * b - 4 * a * c;

    if (delta > 0) {
        x1 = (-b + sqrt(delta)) / (2 * a);
        x2 = (-b - sqrt(delta)) / (2 * a);
        root.push_back(x1);
        root.push_back(x2);
    }
    else if (delta == 0) {
        x1 = -b / (2 * a);
        root.push_back(x1);
    }
}

int main() {
    double a, b, c;
    vector<double> root;

    cout << "Enter a, b, c: ";
    cin >> a >> b >> c;

    SolveEquation2(a, b, c, root);

    if (!root.empty()) {
        cout << "Solution of quadratic equation:" << endl;
        for (size_t i = 0; i < root.size(); ++i) {
            cout << root[i] << endl;
        }
    }
    else {
        cout << "The equation has no solution";
    }

    return 0;
}
