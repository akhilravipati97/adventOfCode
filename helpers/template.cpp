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


int run_part1(std::vector<std::string>& lines) {
    return 0;
}

int run_part2(std::vector<std::string>& lines) {
    return 0;
}

void test() {
    std::vector<std::string> lines = {};
    int val = run_part1(lines);
    std::cout << "test part 1 val: " << val << std::endl;
    assert(val == 0);

    lines = {};
    val = run_part2(lines);
    std::cout << "test part 2 val: " << val << std::endl;
    assert(val == 0);
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "<DAY>");
    int val = run_part1(lines);
    std::cout << "ans part 1: " << val << std::endl;
    val = run_part2(lines);
    std::cout << "ans part 2: " << val << std::endl;
}
