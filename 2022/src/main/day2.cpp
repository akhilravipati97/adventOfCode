#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>
#include <queue>
#include <vector>
#include "../helpers/readInputFile.cpp"


int run_part1(std::vector<std::string>& lines) {
    std::unordered_map<char, char> cm = {{'A', 'A'}, {'B', 'B'}, {'C', 'C'}, {'X', 'A'}, {'Y', 'B'}, {'Z', 'C'}};
    std::unordered_map<char, int> points = {{'A', 1}, {'B', 2}, {'C', 3}};
    std::unordered_map<char, char> beats = {{'A', 'C'}, {'B', 'A'}, {'C', 'B'}};

    int num_points = 0;
    for(std::string line: lines) {
        int pos = line.find(' ');
        char first = cm[line.substr(0, pos)[0]];
        line.erase(0, pos+1);
        char second = cm[line[0]];
        // std::cout << first << " " << second << std::endl;
        num_points += points[second];
        if (first == second) {
            num_points += 3;
        } else if (beats[second] == first) {
            num_points += 6;
        }
    }
    std::cout << "part 1: " << num_points << std::endl;
    return num_points;
}

int run_part2(std::vector<std::string>& lines) {
    std::unordered_map<char, char> cm = {{'A', 'A'}, {'B', 'B'}, {'C', 'C'}, {'X', 'A'}, {'Y', 'B'}, {'Z', 'C'}};
    std::unordered_map<char, int> points = {{'A', 1}, {'B', 2}, {'C', 3}};
    std::unordered_map<char, char> beats = {{'A', 'C'}, {'B', 'A'}, {'C', 'B'}};
    std::unordered_map<char, char> loses = {{'A', 'B'}, {'B', 'C'}, {'C', 'A'}};

    int num_points = 0;
    for(std::string line: lines) {
        int pos = line.find(' ');
        char first = cm[line.substr(0, pos)[0]];
        line.erase(0, pos+1);
        char second = cm[line[0]];

        if (second == 'A') {
            second = beats[first];
        } else if (second == 'B') {
            second = first;
        } else {
            second = loses[first];
        }
        
        num_points += points[second];
        if (first == second) {
            num_points += 3;
        } else if (beats[second] == first) {
            num_points += 6;
        }
    }
    std::cout << "part 2: " << num_points << std::endl;
    return num_points;  
}

void test() {
    std::vector<std::string> lines = {{"A Y"}, {"B X"}, {"C Z"}};
    assert(run_part1(lines) == 15);
    assert(run_part2(lines) == 12);
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "2");
    run_part1(lines);
    run_part2(lines);
}
