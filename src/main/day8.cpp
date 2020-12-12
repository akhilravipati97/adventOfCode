#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>
#include "src/helpers/readInputFile.cpp"

typedef std::vector<std::pair<std::string, int>> instr;

instr parse_instruction(std::vector<std::string>& lines) {
    instr instructions;
    instructions.reserve(lines.size());
    std::for_each(lines.begin(), lines.end(), [&instructions](auto line) {
        std::string instruction = line.substr(0, 3);
        int offset = instruction == "nop" ? 0 : std::stoi(line.substr(4, line.size()-4));
        instructions.emplace_back(std::make_pair(instruction, offset));
    });
    return instructions;
}

void run_part1(std::vector<std::string>& lines) {
    instr instructions = parse_instruction(lines);
    std::unordered_set<int> visited;
    int acc = 0;
    int i = 0;
    std::string instruction;
    int offset;
    while(!visited.count(i)) {
        visited.emplace(i);
        std::tie(instruction, offset) = instructions[i];
        if(instruction == "jmp") {
            i = i + offset;
        } else {
            i += 1;
            acc += offset;
        }
    }
    std::cout<<"Last acc value: " << acc <<std::endl;
}

void run_part2(std::vector<std::string>& lines) {

}

void test() {

}

int main() {
    test();
    std::vector<std::string> lines = read_file("8");
    run_part1(lines);
    run_part2(lines);
}
