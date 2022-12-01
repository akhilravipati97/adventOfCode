#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

std::unordered_map<int, std::pair<char, char>> id_calc_map = {
    { 0 , {'F', 'B'}},
    { 7 , {'L', 'R'}}
};

// Since the intervals are even, the mid-point will always land on the last element of the first half
// Based on that we decide what's the start and end of interval at each selection
// The last movement of start/end is the final id.
int get_id(std::string& line, int itr_start, int itr_end, int start, int end) {
    int id = 0;
    char start_char = id_calc_map[itr_start].first;
    char end_char = id_calc_map[itr_start].second;
    for(int i=itr_start; i<itr_end; i++) {
        char c = line[i];
        int point = start + (end - start)/2;
        if ( c == start_char ) {
            end = point;
            id = end;
        } else if ( c == end_char) {
            start = point + 1;
            id = start;
        }
    }
    return id;
}

// Get the max of all ids.
int get_max_id_part1(std::vector<std::string>& lines) {
    int max_id = 0;
    for(std::string& line: lines) {
        int row_id = get_id(line, 0, 7, 0, 127);
        int col_id = get_id(line, 7, 10, 0, 7);
        max_id = std::max(max_id, row_id*8 + col_id);
    }
    return max_id;
}

// Get the min_id, max_id and dump everything into a set
// To get the missing id whose left and right are present, just start from min_id+1 to max_id-1
// and find that id which is missing from the set.
int get_max_id_part2(std::vector<std::string>& lines) {
    std::unordered_set<int> ids;
    int min_id = 1000000, max_id= (-1);
    for(std::string& line: lines) {
        int row_id = get_id(line, 0, 7, 0, 127);
        int col_id = get_id(line, 7, 10, 0, 7);
        int id = row_id*8 + col_id;
        min_id = std::min(min_id, id);
        max_id = std::max(max_id, id);
        ids.emplace(id);
    }

    for(int id = min_id+1; id <=max_id-1; ++id) {
        if(!ids.count(id)) {
            return id;
        }
    }

}

void run() {
    std::ifstream ifile("./input/day5.txt");
    std::vector<std::string> lines;
    std::string line;
    while(ifile >> line) {
        lines.emplace_back(line);
    }
    int id = get_max_id_part1(lines);
    std::cout << "ID: " << id << std::endl;

    int my_id = get_max_id_part2(lines);
    std::cout << "MY ID: " << my_id << std::endl;
}

void test() {
    std::string word = "FBFBBFFRLR";
    assert(get_id(word, 0, 7, 0, 127) == 44);
    assert(get_id(word, 7, 10, 0, 7) == 5);
}

int main() {
    test();
    run();
}
