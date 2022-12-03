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


void run_part1(std::vector<std::string>& lines) {
    long max_sum = -1;
    long curr_sum = 0;
    for(const std::string &line : lines) {
        if (line == "") {
            max_sum = std::max(max_sum, curr_sum);
            curr_sum = 0;
            continue;
        } 
        curr_sum += std::stol(line);
    }
    if (curr_sum != 0) {
        max_sum = std::max(max_sum, curr_sum);
    }
    std::cout << "ans: " << max_sum << std::endl;
}

void run_part2(std::vector<std::string>& lines) {
    lines.push_back(""); // to avoid having to redo the code if curr_sum != 0 after for loop ends.
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    long curr_sum = 0;
    for(auto const &line: lines) {
        if (line == "") {
            if (pq.size() < 3) {
                pq.push(curr_sum);
            } else if (curr_sum > pq.top()) {
                pq.push(curr_sum);
                pq.pop();
            }
            curr_sum = 0;
        } else {
            curr_sum += std::stol(line);
        }
    }
    long total = 0;
    while(!pq.empty()) {
        total += pq.top();
        pq.pop();
    }
    std::cout << "ans: " << total << std::endl;
}

void test() {

}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "1");
    run_part1(lines);
    run_part2(lines);
}
