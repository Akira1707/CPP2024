#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <iomanip>
#include <algorithm>

#include "lab1.h"

using namespace std;

struct QuadraticEquation {
    double a, b, c;
};

struct Letter {
    int number;
    string StudentName;
    vector<double> solution;
};

//������� ������ ��������� �� �����
vector<QuadraticEquation> readEquations(const string& filename) {
    vector<QuadraticEquation> equations;
    ifstream file(filename);
    double a, b, c;
    QuadraticEquation eq;

    while (file >> eq.a >> eq.b >> eq.c) {
        equations.push_back(eq);
    }
    file.close(); 
    return equations; 
}

//�������, ������� ������ ��� ���������
vector<vector<double>> SolveMultipleEquations(vector<QuadraticEquation> equations) {    
    vector<vector<double>> solutions;    

    for (const auto& eq : equations) {
        vector<double> root;
        SolveEquation2(eq.a, eq.b, eq.c, root);
        solutions.push_back(root);
    }
    return solutions;
}

//������ ��� ���������
map<string, int> StudentAssessment(queue<Letter> letters, int *n) {
    map<string, int> Students;
    Letter letter;
    vector<QuadraticEquation> equations;
    vector<vector<double>> solutions;

    equations = readEquations("input.txt");
    (*n) = int(equations.size());
    solutions = SolveMultipleEquations(equations);
    
    while (!letters.empty()) {
        letter = letters.front();
        if (Students.find(letter.StudentName) == Students.end()) {
            Students[letter.StudentName] = 0;
        }
        sort(letter.solution.begin(), letter.solution.end());
        sort(solutions[letter.number].begin(), solutions[letter.number].end());

        if (letter.solution == solutions[letter.number]){
            Students[letter.StudentName]+= 1;
        }
        letters.pop();
    }
    return Students;
}

//������� �������
void CreateTable(queue<Letter> letters) {
    ofstream output("output.txt");
    string evaluation;
    int n;

    map<string, int> Students = StudentAssessment(letters, &n);

    if (!output.is_open()) {
        cerr << "������ ��� �������� ����� ��� ������." <<endl;
        return;
    }

    output << left << setw(15) << "���" << setw(20) << "���������� �������" << setw(15) << "������" << endl;
    for (const auto& student : Students) {
        if (student.second == n) {
            evaluation = "������";
        }
        else if (student.second  >= 0.55 * n) {
            evaluation = "�������";
        }
        else { evaluation = "�����"; }

        output << left << setw(15) << student.first << setw(20) << student.second << setw(20) << evaluation << endl;
    }
    output.close();    
}

/*int main() {
    queue<Letter> letters;

    letters.push(Letter{ 0, "A", { 1.0 } });
    letters.push(Letter{ 1, "A", { 1.0, 2.0 } });
    letters.push(Letter{ 2, "A", { 3.0, 1.0 } });
    letters.push(Letter{ 3, "A", { 1.0, 4.0 } });
    letters.push(Letter{ 4, "A", { } });
    
    CreateTable(letters);

    return 0;
}*/
