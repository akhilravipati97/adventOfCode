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
#include "../helpers/readInputFile.cpp"

struct BFS {
    std::pair<int, int> pos = {0,0};
    int numSteps = 0;
};

std::string bfsToStr(const BFS &b) {
    return "{numSteps=" + std::to_string(b.numSteps) + ", pos=["  + std::to_string(b.pos.first) + "," + std::to_string(b.pos.second) + "]}";
}


char toChar(char c) {
    if(c == 'E') return 'z';
    if(c == 'S') return 'a';
    return c;
}

std::pair<int, int> findPos(const std::vector<std::string>& grid, char pos) {
    size_t m = grid.size(), n = grid[0].size();
    for(size_t i=0; i<m; i+=1) 
        for(size_t j=0; j<n; j+=1)
            if(grid[i][j] == pos)
                return {i,j};
    return {-1, -1};
}

std::vector<std::pair<int, int>> findAllPos(const std::vector<std::string>& grid, char pos) {
    std::vector<std::pair<int, int>> allPos;
    size_t m = grid.size(), n = grid[0].size();
    for(size_t i=0; i<m; i+=1) 
        for(size_t j=0; j<n; j+=1)
            if(toChar(grid[i][j]) == pos)
                allPos.push_back({i,j});
    return allPos;
}


bool isValidMove(const std::vector<std::string>& grid, std::pair<int, int> newPos, std::pair<int, int> currPos) {
    char newChar = toChar(grid[newPos.first][newPos.second]);
    char currChar = toChar(grid[currPos.first][currPos.second]);
    return (newChar <= (currChar+1));
}

int getMinSteps(const std::vector<std::string>& lines, const std::pair<int, int> start) {
    int m = lines.size(), n = lines[0].size();
    bool visited[m][n];
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j+=1)
            visited[i][j] = false;

    auto cmp = [](BFS& v1, BFS& v2) {
        return v1.numSteps > v2.numSteps;
    };
    std::priority_queue<BFS, std::vector<BFS>, decltype(cmp)> pq(cmp);
    std::vector<std::pair<int, int>> dirs = {{-1,0}, {0,-1}, {1,0}, {0,1}};
    pq.push(BFS{.pos=start, .numSteps=0});
    visited[start.first][start.second] = true;

    int shortestDist = -1;
    while(!pq.empty()) {
        BFS curr = pq.top();
        pq.pop();
        if(lines[curr.pos.first][curr.pos.second] == 'E') {
            shortestDist = curr.numSteps;
            break;
        }
        for(const auto &dir: dirs) {
            const std::pair<int, int> newPos = {curr.pos.first + dir.first, curr.pos.second + dir.second};
            if(
                (newPos.first >=0) && (newPos.first <m) && (newPos.second>=0) && (newPos.second < n) && 
                isValidMove(lines, newPos, curr.pos) &&
                !visited[newPos.first][newPos.second]) {
                visited[newPos.first][newPos.second] = true;
                const BFS newBFS = BFS{.pos=newPos, .numSteps=(curr.numSteps+1)};
                pq.push(newBFS);
            }
        }
    }

    return shortestDist;
}

int run_part1(std::vector<std::string>& lines) {
    auto start = findPos(lines, 'S');
    return getMinSteps(lines, start);
}

int run_part2(std::vector<std::string>& lines) {
    auto starts = findAllPos(lines, 'a');
    int minDist = std::numeric_limits<int>::max();
    for(auto &start: starts) {
        int val = getMinSteps(lines, start);
        if(val != -1)
            minDist = std::min(minDist, val);
    }
    return minDist;
}

void test() {
    std::vector<std::string> lines = {
        "Sabqponm",
        "abcryxxl",
        "accszExk",
        "acctuvwj",
        "abdefghi",
    };
    int val = run_part1(lines);
    std::cout << "test part 1 val: " << val << std::endl;
    assert(val == 31);

    val = run_part2(lines);
    std::cout << "test part 2 val: " << val << std::endl;
    assert(val == 29);
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "12");
    std::cout << "ans part 1: " << run_part1(lines) << std::endl;
    std::cout << "ans part 2: " << run_part2(lines) << std::endl;
}
