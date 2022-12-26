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

typedef std::pair<std::string, int> instr;

instr getInstr(std::string &line) {
    std::string cmd = line.substr(0, 4);
    if (cmd == "noop") return {cmd, 0};
    int val = std::stoi(line.substr(5, line.size() - 5));
    return {cmd, val};
}

int run_part1(std::vector<std::string>& lines) {
    std::unordered_map<std::string, int> cyclesMap = {{"addx", 2}, {"noop", 1}};
    std::vector<int> cycles = {20, 60, 100, 140, 180, 220};
    int idx = 0;
    int instrIdx = 0;
    int totalCycles = 0;
    int power = 0;
    int xVal = 1;
    while(idx < (int)cycles.size()) {
        const auto &instr = getInstr(lines[instrIdx]);
        instrIdx += 1;
        totalCycles += cyclesMap[instr.first];
        if (totalCycles >= cycles[idx]) {
            power += cycles[idx]*xVal;
            idx +=1;
        }
        xVal += instr.second;
    }
    return power;
}

int run_part2(std::vector<std::string>& lines) {
    std::unordered_map<std::string, int> cyclesMap = {{"addx", 2}, {"noop", 1}};
    int instrIdx = 0;
    int totalCycles = 0;
    int xVal = 1;
    int completedCycles = 0;
    std::string printLine = "";
    while(completedCycles < 240) {
        const auto &instr = getInstr(lines[instrIdx]);
        instrIdx += 1;
        totalCycles += cyclesMap[instr.first];
        while (completedCycles < totalCycles) {
            int lineIdx = completedCycles % 40;
            if(xVal == lineIdx || xVal == lineIdx+1 || xVal == lineIdx-1) { //edges?
                printLine += "#";
            } else {
                printLine += ".";
            }
            completedCycles += 1;
            if (completedCycles % 40 == 0) {
                std::cout << printLine << std::endl;
                printLine = "";
            }
        }
        xVal += instr.second;
    }
    return 0;
}

void test() {
    std::vector<std::string> lines = {
        "addx 15",
        "addx -11",
        "addx 6",
        "addx -3",
        "addx 5",
        "addx -1",
        "addx -8",
        "addx 13",
        "addx 4",
        "noop",
        "addx -1",
        "addx 5",
        "addx -1",
        "addx 5",
        "addx -1",
        "addx 5",
        "addx -1",
        "addx 5",
        "addx -1",
        "addx -35",
        "addx 1",
        "addx 24",
        "addx -19",
        "addx 1",
        "addx 16",
        "addx -11",
        "noop",
        "noop",
        "addx 21",
        "addx -15",
        "noop",
        "noop",
        "addx -3",
        "addx 9",
        "addx 1",
        "addx -3",
        "addx 8",
        "addx 1",
        "addx 5",
        "noop",
        "noop",
        "noop",
        "noop",
        "noop",
        "addx -36",
        "noop",
        "addx 1",
        "addx 7",
        "noop",
        "noop",
        "noop",
        "addx 2",
        "addx 6",
        "noop",
        "noop",
        "noop",
        "noop",
        "noop",
        "addx 1",
        "noop",
        "noop",
        "addx 7",
        "addx 1",
        "noop",
        "addx -13",
        "addx 13",
        "addx 7",
        "noop",
        "addx 1",
        "addx -33",
        "noop",
        "noop",
        "noop",
        "addx 2",
        "noop",
        "noop",
        "noop",
        "addx 8",
        "noop",
        "addx -1",
        "addx 2",
        "addx 1",
        "noop",
        "addx 17",
        "addx -9",
        "addx 1",
        "addx 1",
        "addx -3",
        "addx 11",
        "noop",
        "noop",
        "addx 1",
        "noop",
        "addx 1",
        "noop",
        "noop",
        "addx -13",
        "addx -19",
        "addx 1",
        "addx 3",
        "addx 26",
        "addx -30",
        "addx 12",
        "addx -1",
        "addx 3",
        "addx 1",
        "noop",
        "noop",
        "noop",
        "addx -9",
        "addx 18",
        "addx 1",
        "addx 2",
        "noop",
        "noop",
        "addx 9",
        "noop",
        "noop",
        "noop",
        "addx -1",
        "addx 2",
        "addx -37",
        "addx 1",
        "addx 3",
        "noop",
        "addx 15",
        "addx -21",
        "addx 22",
        "addx -6",
        "addx 1",
        "noop",
        "addx 2",
        "addx 1",
        "noop",
        "addx -10",
        "noop",
        "noop",
        "addx 20",
        "addx 1",
        "addx 2",
        "addx 2",
        "addx -6",
        "addx -11",
        "noop",
        "noop",
        "noop",
    };
    int val = run_part1(lines);
    std::cout << "test part 1 ans: " << val << std::endl;
    assert(val == 13140);
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "10");
    std::cout << "ans part 1: " << run_part1(lines) << std::endl;
    std::cout << "ans part 2: \n" << run_part2(lines) << std::endl;
}
