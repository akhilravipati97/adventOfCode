#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>
#include <limits>
#include "src/helpers/readInputFile.cpp"

long long run_part1(std::vector<long long> nums) {
    nums.push_back((*std::max_element(nums.begin(), nums.end())) + 3);
    nums.push_back(0);
    std::sort(nums.begin(), nums.end());
    long long one_diff=0, three_diff=0;
    for(long long unsigned int i=1; i<nums.size(); ++i) {
        int diff = nums[i] - nums[i-1];
        if(diff == 1) one_diff++;
        else if (diff == 3) three_diff++;
    }
    return one_diff*three_diff;
}

long long num_ways(std::unordered_map<long long, long long>& memo, std::vector<long long>& nums, long long unsigned int idx) {
    //std::cout << "call for idx: " << idx << std::endl;
    if(idx >= nums.size()) return 0;
    else if(idx == (nums.size()-1)) return 1;
    else if (memo.count(idx)) return memo.at(idx);

    long long total = 0;
    for(long long unsigned int i=idx+1; i<nums.size(); ++i) {
        if((nums[i] - nums[idx]) > 3) break;
        else if (memo.count(i)) total += memo.at(i);
        else total += num_ways(memo, nums, i);
    }
    //std::cout << "Count for idx: " << idx << " is: " << total << std::endl;
    memo[idx] = total;
    return total;
}

long long run_part2(std::vector<long long> nums) {
    std::unordered_map<long long, long long> memo;
    nums.push_back((*std::max_element(nums.begin(), nums.end())) + 3);
    nums.push_back(0);
    std::sort(nums.begin(), nums.end());

    num_ways(memo, nums, 0);
    return memo[0];
}

void test() {
}

int main() {
    test();
    std::vector<std::string> lines = read_file("10");
    std::vector<long long> nums = parse_input(lines);
    // std::cout << "test2: " << run_part2({16, 10, 15, 5, 1, 11, 7, 19, 6, 12, 4});
    // std::cout << "test2: " << run_part2({28, 33, 18, 42, 31, 14, 46, 20, 48, 47, 24, 23, 49, 45, 19, 38, 39, 11, 1, 32, 25, 35, 8, 17, 7, 9, 4, 2, 34, 10, 3});
    // std::cout << "test2: " << run_part2({1, 2, 3});
    std::cout << "test2: " << run_part2(nums);
    return 0;
}
