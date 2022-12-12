#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>
#include "../helpers/readInputFile.cpp"

std::pair<int, int> splitIntoPair(std::string &line, char delimiter) {
    int pos = line.find(delimiter);
    int val1 = std::stoi(line.substr(0, pos));
    int val2 = std::stoi(line.substr(pos+1, line.size()-pos+1));
    return std::pair<int, int>{val1, val2};
}


int run_part1(std::vector<std::string>& lines) {
    int count = 0; // Did not initialize to 0 initially and wasted 30min checking why my final count was incorrect.
    for(const auto &line : lines) {
        int pos = line.find(',');
        std::string pair1 = line.substr(0, pos);
        std::string pair2 = line.substr(pos+1, line.size()-pos+1);
        std::pair<int, int> p1 = splitIntoPair(pair1, '-');
        std::pair<int, int> p2 = splitIntoPair(pair2, '-');
        
        if((p1.first >= p2.first && p1.second <= p2.second) || (p2.first >= p1.first && p2.second <= p1.second)) {
            count += 1;
        }
    }
    return count;
}

int run_part2(std::vector<std::string>& lines) {
    int count = 0;
    for(const auto &line : lines) {
        int pos = line.find(',');
        std::string pair1 = line.substr(0, pos);
        std::string pair2 = line.substr(pos+1, line.size()-pos+1);
        std::pair<int, int> p1 = splitIntoPair(pair1, '-');
        std::pair<int, int> p2 = splitIntoPair(pair2, '-');
        
        if(!(p1.second < p2.first || p2.second < p1.first)) {
            count += 1;
        }
    }
    return count;
}

void test() {
    std::vector<std::string> lines = {
        "2-4,6-8",
        "2-3,4-5",
        "5-7,7-9",
        "2-8,3-7",
        "6-6,4-6",
        "2-6,4-8",
    };
    int val = run_part1(lines);
    std::cout << "part1: " << val << std::endl;
    assert(val == 2);
    val = run_part2(lines);
    std::cout << "part2: " << val << std::endl;
    assert(val == 4);
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "4");
    std::cout << "ans part 1: " << run_part1(lines) << std::endl;
    std::cout << "ans part 2: " << run_part2(lines) << std::endl;
}
