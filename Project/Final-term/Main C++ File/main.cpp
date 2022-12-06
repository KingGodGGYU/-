#include <iostream>
#include <queue>
#include <vector>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <algorithm>
#include <list>
#include <utility>
using namespace std;

vector<string> split(string input, char delimiter, vector<string> output) {
    stringstream ss(input);
    string temp;

    while (getline(ss, temp, delimiter)) {
        output.push_back(temp);
    }
    return output;
}

int main() {
    vector<string> temp;
    vector<string> temp2;
    vector<int> region;
    vector<double> points;

    vector<pair<int, double>> data;
    priority_queue<pair<int, double>> original;

    ifstream infile("PointsData.csv");
    if (!infile.is_open()) {
        cout << "error" << endl;
        return false;
    }
    int cnt = 0;
    string line;
    while (getline(infile, line, ',')) {
        temp.push_back(line);
        cnt++;
    }


    for (int j = 0; j < temp.size(); j++) {
        if ((j % 2) == 0) {
            stringstream ss(temp[j]);
            int num1;
            ss >> num1;
            region.push_back(num1);
        }
        else {
            stringstream ss(temp[j]);
            double num2;
            ss >> num2;
            points.push_back(num2);
        }
    }

    for (int i = 0; i < points.size(); i++) {
        data.push_back(make_pair(region[i], points[i]));
    }
    for (auto& i : data) {
        original.push(make_pair(i.second,i.first));
    }
    cout << "점수" << '\t' << "구역 번호" << endl;
    int priority = 1;
    while (!original.empty()) {
        cout << priority<<". "<<original.top().first << "\t" << original.top().second << endl;
        original.pop();
        priority++;
    }

    return 0;
}