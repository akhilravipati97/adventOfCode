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

std::string pairHash(const std::pair<int, int> p) {
    return std::to_string(p.first) + "," + std::to_string(p.second);
}

std::pair<char, int> getMoveFromLine(const std::string& line) {
    char move = line[0];
    int places = std::stoi(line.substr(2, line.size()-2));
    return {move, places};
}

std::pair<int, int> getTailMove(const std::pair<int, int> &headPos, const std::pair<int, int> &tailPos) {
    int dist = std::abs(headPos.first - tailPos.first) + std::abs(headPos.second - tailPos.second);
    if(headPos.first == tailPos.first && dist > 1) {
        if(headPos.second > tailPos.second)
            return {headPos.first, tailPos.second + 1};
        return {headPos.first, tailPos.second - 1};
    } else if (headPos.second == tailPos.second && dist > 1) {
        if(headPos.first > tailPos.first) 
            return {tailPos.first + 1, tailPos.second};
        return {tailPos.first-1, tailPos.second};
    } else if (headPos.first != tailPos.first && headPos.second != tailPos.second && dist > 2) {
        int ud = -1, lr = -1;
        if(headPos.first > tailPos.first)
            ud = 1;
        if(headPos.second > tailPos.second)
            lr = 1;
        const std::pair<int, int> newTailPos = {tailPos.first + ud, tailPos.second + lr};
        //std::cout << "head: " << pairHash(headPos) << " old tail: " << pairHash(tailPos) << " new tail: " << pairHash(newTailPos) << std::endl;
        return newTailPos;
    }
    return tailPos;
}

int run_part1(std::vector<std::string>& lines) {
    std::pair<int, int> head = {0,0}, tail = {0, 0};
    std::unordered_set<std::string> tailPlaces;
    tailPlaces.insert(pairHash(tail));

    std::unordered_map<char, std::pair<int, int>> dirMap = {
        {'U', {1,0}},
        {'D', {-1,0}},
        {'L', {0,-1}},
        {'R', {0,1}}
    };

    for(const auto &line: lines) {
        auto move = getMoveFromLine(line);
        const auto dir = dirMap[move.first];
        while(move.second != 0) {
            const std::pair<int, int> newHeadPos = {head.first + dir.first, head.second + dir.second};
            const auto newTailPos = getTailMove(newHeadPos, tail);
            tailPlaces.insert(pairHash(newTailPos));
            head = newHeadPos;
            tail = newTailPos;
            move.second -= 1;
        }
    }
    return tailPlaces.size();
}

int run_part2(std::vector<std::string>& lines) {
    std::vector<std::pair<int, int>> knots = {10, std::pair<int, int>{0, 0}};
    std::unordered_set<std::string> tailPlaces;
    tailPlaces.insert(pairHash(knots[9]));

    std::unordered_map<char, std::pair<int, int>> dirMap = {
        {'U', {1,0}},
        {'D', {-1,0}},
        {'L', {0,-1}},
        {'R', {0,1}}
    };

    for(const auto &line: lines) {
        auto move = getMoveFromLine(line);
        const auto dir = dirMap[move.first];
        while(move.second != 0) {
            const auto head = knots[0];
            knots[0] = {head.first + dir.first, head.second + dir.second};
            for(int i=1; i<10; i+=1) {
                knots[i] = getTailMove(knots[i-1], knots[i]);
            }
            tailPlaces.insert(pairHash(knots[9]));
            move.second -= 1;
        }
    }
    return tailPlaces.size();
}

void test() {
    std::vector<std::string> lines = {
        "R 4",
        "U 4",
        "L 3",
        "D 1",
        "R 4",
        "D 1",
        "L 5",
        "R 2",
    };
    int val = run_part1(lines);
    std::cout << "test part 1: " << val << std::endl;
    assert(val == 13);

    lines = {
        "R 5",
        "U 8",
        "L 8",
        "D 3",
        "R 17",
        "D 10",
        "L 25",
        "U 20",
    };
    val = run_part2(lines);
    std::cout << "test part 2: " << val << std::endl;
    assert(val == 36);
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "9");
    std::cout << "ans part 1: " << run_part1(lines) << std::endl;
    std::cout << "ans part 2: " << run_part2(lines) << std::endl;
}
