#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>
#include <limits>
#include <iterator>
#include "src/helpers/readInputFile.cpp"


long long run_part1(std::vector<std::string>& grid) {
    std::vector<std::string> new_grid = grid;
    std::vector<std::pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
    int num_changes = 1;
    while(num_changes) {
        num_changes = 0;
        for(size_t i=0; i<grid.size(); ++i) {
            for(size_t j=0; j<grid[i].size(); ++j) {
                if(grid[i][j] == '.') continue;

                int adj_occupied = 0;
                for(auto& [x,y]: directions) {
                    size_t ni=i+x, nj=j+y;
                    if(ni < 0 || ni >= grid.size()) continue;
                    else if (nj < 0 || nj >= grid[i].size()) continue;
                    else if (grid[ni][nj] == '#') adj_occupied+=1;
                }

                if(grid[i][j] == 'L' && adj_occupied == 0) new_grid[i][j] = '#';
                else if(grid[i][j] == '#' && adj_occupied >= 4) new_grid[i][j] = 'L';

                if (grid[i][j] != new_grid[i][j]) num_changes+=1;
            }
        }
        grid = new_grid;
    }
    
    int num_occupied = 0;
    for(size_t i=0; i<grid.size(); ++i) {
        for(size_t j=0; j<grid[i].size(); ++j) {
            if(grid[i][j] == '#') num_occupied += 1;
        }
    }
    return num_occupied;
}

char first_seat_in_direction(std::vector<std::string>& grid, size_t i, size_t j, size_t x, size_t y) {
    size_t ni = i + x, nj = j + y;
    char seat = 'x';
    while(ni >=0 && ni < grid.size() && nj >= 0 && nj < grid[0].size()) {
        seat = grid[ni][nj];
        if(seat != '.') break;
        ni += x;
        nj += y;
    }
    return seat;
}


long long run_part2(std::vector<std::string>& grid) {
    std::vector<std::string> new_grid = grid;
    std::vector<std::pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};
    int num_changes = 1;
    while(num_changes) {
        num_changes = 0;
        for(size_t i=0; i<grid.size(); ++i) {
            for(size_t j=0; j<grid[i].size(); ++j) {
                if(grid[i][j] == '.') continue;

                int adj_occupied = 0;
                for(auto& [x,y]: directions) {
                    char first_seat = first_seat_in_direction(grid, i, j, x, y);
                    if (first_seat == '#') adj_occupied+=1;
                }

                if(grid[i][j] == 'L' && adj_occupied == 0) new_grid[i][j] = '#';
                else if(grid[i][j] == '#' && adj_occupied >= 5) new_grid[i][j] = 'L';

                if (grid[i][j] != new_grid[i][j]) num_changes+=1;
            }
        }
        grid = new_grid;
    }
    
    int num_occupied = 0;
    for(size_t i=0; i<grid.size(); ++i) {
        for(size_t j=0; j<grid[i].size(); ++j) {
            if(grid[i][j] == '#') num_occupied += 1;
        }
    }
    return num_occupied;
}

void test() {
}

int main() {
    test();
    std::vector<std::string> lines = read_file("11");
    std::cout << "test2: " << run_part2(lines);
    return 0;
}
