#pragma once
#include <fstream>
#include <string>
using namespace std;
string total() {
    int totalCount = 0;

  
    string files[] = { "business.txt","package.txt"};

    for (auto file : files) {
        ifstream fin(file);
        string line;
        while (getline(fin, line)) {
            if (!line.empty()) {
                totalCount++;
            }
        }
        fin.close();
    }

    return  "Total tours are: "+ to_string(totalCount);
}
