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


int run_part1(const std::string& line, int num_distinct) {
    std::unordered_map<char, int> mp;
    for(int i=0; i<(int)line.size(); i+=1) {
        if(i < num_distinct) {
            mp[line[i]] += 1;
        } else {
            if (((int)mp.size()) == num_distinct) {
                return i;
            }
            mp[line[i-num_distinct]] -= 1;
            if (mp[line[i-num_distinct]] == 0 ) {
                mp.erase(line[i-num_distinct]);
            }
            mp[line[i]] += 1;
        }
    }
    return line.size();
}

int run_part2(std::vector<std::string>& lines) {
    return 0;
}

void test() {
    std::vector<std::pair<std::string, int>> lines = {
        {"bvwbjplbgvbhsrlpgdmjqwftvncz", 5},
        {"nppdvjthqldpwncqszvftbrmjlhg", 6},
        {"nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 10},
        {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 11},
    };
    for(const auto &pr: lines) {
        int val = run_part1(pr.first, 4);
        //std::cout << "part1: " <<  pr.first << " -> got: " << val << ", expected: " << pr.second << std::endl;
        assert(val == pr.second);
    }

    lines = {
        {"mjqjpqmgbljsphdztnvjfqwrcgsmlb", 19},
        {"bvwbjplbgvbhsrlpgdmjqwftvncz", 23},
        {"nppdvjthqldpwncqszvftbrmjlhg", 23},
        {"nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg", 29},
        {"zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw", 26},
    };
    for(const auto &pr: lines) {
        int val = run_part1(pr.first, 14);
        // std::cout << "part2: " <<  pr.first << " -> got: " << val << ", expected: " << pr.second << std::endl;
        assert(val == pr.second);
    }
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "6");
    std::cout << "ans part 1: " << run_part1(lines[0], 4) << std::endl;
    std::cout << "ans part 2: " << run_part1(lines[0], 14) << std::endl;
}
