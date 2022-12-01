#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <numeric>
#include <functional>

long long count_simple(std::ifstream& ifile, const std::vector<std::pair<int, int>>& slopes) {
    std::vector<std::string> lines;
    std::string line; 
    while(ifile >> line) {
        lines.emplace_back(line);
    }

    long long mul = 1;
    for(int i=0; i<slopes.size(); i++) {
        int start = slopes[i].first;
        int count = 0;
        for(int j=slopes[i].second; j<lines.size(); j+=slopes[i].second) {
            if (lines[j][start] == '#') count += 1;
            start = (start + slopes[i].first) % line.size();
        }
        mul *= count;
    }
    return mul;
}

int main() {
    std::ifstream ifile("./input/day3.txt");
    std::cout<< count_simple(ifile, std::vector<std::pair<int, int>>{ {1,1}, {3, 1}, {5, 1}, {7, 1}, {1,2}});
}
