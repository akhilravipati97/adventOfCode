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

int priority(char c) {
    if(std::isupper(c)) {
        return 27 + c-'A';
    } else {
        return 1 + c-'a';
    }
}


int run_part1(std::vector<std::string>& lines) {
    int prio;
    for(const auto &line: lines) {
        int size = line.size();
        std::unordered_set<char> left;
        for(int i=0; i<size/2; i += 1){
            left.insert(line[i]);
        }
        for(int i=size/2; i<size; i+=1) {
            if (left.count(line[i])) {
                prio += priority(line[i]);
                break;
            }
        }
    }
    return prio;
}

int run_part2(std::vector<std::string>& lines) {
    int num_groups = lines.size()/3;
    auto count_chars = [](std::unordered_map<char, int> &map, std::string &line) {
        std::unordered_set<char> uniq_chars;
        for(char c: line) {
            uniq_chars.insert(c);
        }
        for(char c: uniq_chars) {
            map[c] += 1;
        }
    };

    int prio;
    for(int i=0; i<num_groups; i+=1) {
        std::unordered_map<char, int> freq;
        for(int j=0; j<3; j++) {
            count_chars(freq, lines[i*3+j]);
        }
        for(const auto &x : freq) {
            if(x.second == 3) {
                prio += priority(x.first);
            }
        }
    }
    return prio;
}

void test() {
    std::vector<std::string> lines = {
        "vJrwpWtwJgWrhcsFMMfFFhFp",
        "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
        "PmmdzqPrVvPwwTWBwg",
        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
        "ttgJtRGJQctTZtZT",
        "CrZsJsPPZsGzwwsLwLmpwMDw",
    };

    int val = run_part2(lines);
    assert(val == 70);
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "3");
    std::cout << "ans part 1: " << run_part1(lines) << std::endl;
    std::cout << "ans part 2: " << run_part2(lines) << std::endl;
}
