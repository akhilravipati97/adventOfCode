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

std::vector<std::vector<int>> parseInts(std::vector<std::string> &lines) {
    std::vector<std::vector<int>> vals(lines.size(), std::vector<int>(lines[0].size()));
    for(size_t i=0; i<lines.size(); i+=1) {
        for(size_t j=0; j<lines[i].size(); j+=1) {
            vals[i][j] = lines[i][j] - '0';
        }
    }
    return vals;
}

int run_part1(std::vector<std::string>& lines) {
    std::vector<std::vector<int>> vals = parseInts(lines);
    std::vector<std::vector<int>> visible(lines.size(), std::vector<int>(lines[0].size()));

    const auto fn = [&vals, &visible](int i, int j, int &maxval) {
        if(i==0 || j == 0 || (i==(int)(vals.size()-1)) || (j == (int)(vals[i].size()-1))) {
            visible[i][j] = 1;
        } else if (vals[i][j] > maxval) {
            visible[i][j] = 1;
        }
        maxval = std::max(maxval, vals[i][j]);
    };


    int count = 0;
    for(size_t i=0; i<vals.size(); i+=1) {
        int maxval = -1;
        for(size_t j=0; j<vals[i].size(); j+=1) {
            fn(i, j, maxval);
        }
    }

    for(size_t i=0; i<vals.size(); i+=1) {
        int maxval = -1;
        for(int j= (int)vals[i].size()-1; j>=0;  j-=1) {
            fn(i, j, maxval);
        }
    }

    for(size_t j=0; j<vals[0].size(); j+=1) {
        int maxval = -1;
        for(size_t i=0; i<vals.size(); i+=1) {
            fn(i, j, maxval);
        }
    }

    for(size_t j=0; j<vals[0].size(); j+=1) {
        int maxval = -1;
        for(int i=(int)vals.size()-1; i>=0; i-=1) {
            fn(i, j, maxval);
        }
    }
    

    for(size_t i=0; i<visible.size(); i+=1) {
        for(size_t j=0; j<visible[i].size(); j+=1) {
            if(visible[i][j] == 1) {
                count += 1;
            }
        }
    }

    return count;
}

int run_part2(std::vector<std::string>& lines) {
    std::vector<std::vector<int>> vals = parseInts(lines);
    std::vector<std::vector<long long>> visible(lines.size(), std::vector<long long>(lines[0].size(), 1L));

    const auto fn = [&vals, &visible](int i, int j, std::deque<std::pair<int, int>> &mstack, int capture_first, int end_mode, int size) {
        while((mstack.size() != 0) && (mstack.back().first < vals[i][j])) {
            mstack.pop_back();
        }

        int idx = j;
        if (capture_first)
            idx = i;

        if (mstack.size() == 0) {
            int val = idx;
            if (end_mode) {
                val = (size-idx-1);
            }
            visible[i][j] *= val;
        } else {
            int val = (idx - mstack.back().second);
            if (end_mode) {
                val = (mstack.back().second - idx);
            }
            visible[i][j] *= val;
        }
        mstack.push_back({vals[i][j], idx}); 
    };

    for(size_t i=0; i<vals.size(); i+=1) {
        std::deque<std::pair<int, int>> mstack;
        for(size_t j=0; j<vals[i].size(); j+=1) {
            fn(i, j, mstack, 0, 0, 0);
        }
    }

    for(size_t i=0; i<vals.size(); i+=1) {
        std::deque<std::pair<int, int>> mstack;
        for(int j= (int)vals[i].size()-1; j>=0;  j-=1) {
            fn(i, j, mstack, 0, 1, vals[i].size());
        }
    }

    for(size_t j=0; j<vals[0].size(); j+=1) {
        std::deque<std::pair<int, int>> mstack;
        for(size_t i=0; i<vals.size(); i+=1) {
            fn(i, j, mstack, 1, 0, 0);
        }
    }

    for(size_t j=0; j<vals[0].size(); j+=1) {
        std::deque<std::pair<int, int>> mstack;
        for(int i=(int)vals.size()-1; i>=0; i-=1) {
            fn(i, j, mstack, 1, 1, vals.size());
        }
    }
    

    long long max_val = 0;
    for(size_t i=0; i<visible.size(); i+=1) {
        for(size_t j=0; j<visible[i].size(); j+=1) {
            max_val = std::max(max_val, visible[i][j]);
        }
    }

    return max_val;
}

void test() {
    std::vector<std::string> lines = {
        "30373",
        "25512",
        "65332",
        "33549",
        "35390",
    };
    std::cout << "running test" << std::endl;
    int val = run_part1(lines);
    std::cout << "test val part 1: " << val << std::endl;
    assert(val == 21);
    val = run_part2(lines);
    std::cout << "test val part 2: " << val << std::endl;
    assert(val == 8);
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "8");
    std::cout << "ans part 1: " << run_part1(lines) << std::endl;
    std::cout << "ans part 2: " << run_part2(lines) << std::endl;
}
