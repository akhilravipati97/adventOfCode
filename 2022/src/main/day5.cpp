#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>
#include <deque>
#include <regex>
#include "../helpers/readInputFile.cpp"

void printStacks(const std::vector<std::deque<char>> stacks) {
    std::cout << "stacks\n";
    for(const auto &stack : stacks) {
        for(const auto &ch : stack) {
            std::cout << ch << " ";
        }
        std::cout << std::endl;
    }
    std::cout<<"-----\n";
}

std::string getTopOfStacks(const std::vector<std::deque<char>> stacks) {
    std::string topOfStacks = "";
    for(const auto &stack: stacks) {
        if(stack.size() == 0) {
            topOfStacks += " ";
            continue;
        }
        topOfStacks += stack.back();
    }
    return topOfStacks;
}

std::vector<std::deque<char>> parseInitStacks(std::vector<std::string>& lines) {
    int i=0;
    for(; i<(int)lines.size(); i++) {
        if (lines[i] == "") {
            break;
        }
    }
    i -= 2;
    std::vector<std::deque<char>> stacks;
    char numStacks = *(lines[i+1].end()-2);
    for(int k=std::stoi(std::string(1,numStacks)); k>0; k--) {
        stacks.push_back(std::deque<char>());
    }
    while(i >= 0) {
        std::deque<char> stack;
        const auto &line = lines[i];
        size_t j =0;
        int iter =0;
        while(j < line.size()) {
            if(line[j] != ' ') {
                stacks[iter].push_back(line[j+1]);
            }
            j += 4;
            iter += 1; 
        }
        i -= 1;
    }
    return stacks;
}

void move_stacks(std::vector<std::deque<char>> &stacks, int moveCount, int from, int to) {
    from -= 1;
    to -= 1;
    for(int i=0; i< moveCount; i+=1) {
        stacks[to].push_back(stacks[from].back());
        stacks[from].pop_back();
    }
}

void move_stacks_9001(std::vector<std::deque<char>> &stacks, int moveCount, int from, int to) {
    from -= 1;
    to -= 1;
    std::deque<char> temp;
    for(int i=0; i< moveCount; i+=1) {
        temp.push_back(stacks[from].back());
        stacks[from].pop_back();
    }
    for(int i=0; i<moveCount; i+=1) {
        stacks[to].push_back(temp.back());
        temp.pop_back();
    }
}


int run_part1(std::vector<std::string>& lines) {
    auto stacks = parseInitStacks(lines);

    int i=0;
    for(; i<(int)lines.size(); i++) {
        if (lines[i] == "") {
            break;
        }
    }
    i += 1;

    std::regex rgx("^.* ([0-9]+) .* ([0-9]+) .* ([0-9]+).*$");
    for(; i<(int)lines.size(); i++) {
        const auto &instr = lines[i];
        std::smatch matches;
        if (std::regex_match(instr, matches, rgx)) {
            move_stacks(stacks, std::stoi(matches[1].str()), std::stoi(matches[2].str()), std::stoi(matches[3].str()));
        } else {
            throw std::runtime_error("regex match failed for line: " + instr);
        }
    }

    std::cout << "part 1 , top of stack: " << getTopOfStacks(stacks) << std::endl;

    return 0;
}

int run_part2(std::vector<std::string>& lines) {
    auto stacks = parseInitStacks(lines);

    int i=0;
    for(; i<(int)lines.size(); i++) {
        if (lines[i] == "") {
            break;
        }
    }
    i += 1;

    std::regex rgx("^.* ([0-9]+) .* ([0-9]+) .* ([0-9]+).*$");
    for(; i<(int)lines.size(); i++) {
        const auto &instr = lines[i];
        std::smatch matches;
        if (std::regex_match(instr, matches, rgx)) {
            move_stacks_9001(stacks, std::stoi(matches[1].str()), std::stoi(matches[2].str()), std::stoi(matches[3].str()));
        } else {
            throw std::runtime_error("regex match failed for line: " + instr);
        }
    }

    std::cout << "part 2 , top of stack: " << getTopOfStacks(stacks) << std::endl;

    return 0;
}

void test() {
    std::vector<std::string> lines = {
        "    [D]    ",
        "[N] [C]    ",
        "[Z] [M] [P]",
        " 1   2   3 ",
        "",
        "move 1 from 2 to 1",
        "move 3 from 1 to 3",
        "move 2 from 2 to 1",
        "move 1 from 1 to 2",
    };
    std::cout << "testing-----------------" << std::endl;
    run_part1(lines);
    std::cout << "testing done ------------" << std::endl;
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "5");
    std::cout << "ans part 1: " << run_part1(lines) << std::endl;
    std::cout << "ans part 2: " << run_part2(lines) << std::endl;
}
