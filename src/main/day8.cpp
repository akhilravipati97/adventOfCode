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
        int offset = std::stoi(line.substr(4, line.size()-4));
        instructions.emplace_back(std::make_pair(instruction, offset));
    });
    return instructions;
}

bool is_loop(instr& instructions, int& acc) {
    std::unordered_set<int> visited;
    int i = 0;
    std::string instruction;
    int offset;
    while(!visited.count(i) && i<instructions.size()) {
        visited.emplace(i);
        std::tie(instruction, offset) = instructions[i];
        if(instruction == "jmp") {
            i = i + offset;
        } else if (instruction == "acc") {
            acc += offset;
            i += 1;
        } else {
            i += 1;
        }
    }
    return i != instructions.size(); 
}


void run_part1(std::vector<std::string>& lines) {
    instr instructions = parse_instruction(lines);
    int acc = 0;
    is_loop(instructions, acc);
    std::cout<<"Last acc value: " << acc <<std::endl;
}

void run_part2(std::vector<std::string>& lines) {
    instr instructions = parse_instruction(lines);
    std::string curr_instr;
    int offset;
    for(int i=0; i<instructions.size(); i++) {
        std::tie(curr_instr, offset) = instructions[i];
        int acc = 0;
        bool is_lp = true;
        if(curr_instr == "nop") {
            instructions[i].first= "jmp";
            is_lp = is_loop(instructions, acc);
        } else if (curr_instr == "jmp") {
            instructions[i].first = "nop";
            is_lp = is_loop(instructions, acc);
        }
        
        if(!is_lp) {
            std::cout<<"Found no loop. Acc value: " << acc << std::endl;
            break;
        }
        instructions[i].first = curr_instr;
    }
}

void test() {

}

int main() {
    test();
    std::vector<std::string> lines = read_file("8");
    run_part1(lines);
    run_part2(lines);
}
