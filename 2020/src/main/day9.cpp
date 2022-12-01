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

static int PREAMBLE_SIZE = 25;

std::vector<long long> parse_input(std::vector<std::string>& lines) {
    std::vector<long long> nums;
    nums.reserve(lines.size());
    std::transform(std::begin(lines), std::end(lines), std::back_inserter(nums), [](auto str) { 
        // std::cout << "Applying for: " << str << std::endl;
        return std::stoll(str); 
    });
    return nums;
}

// check each element of the sorted set if the complement exists
// check only until the element is less than or equal to half the total
bool is_valid_num(long num, std::set<long long>& preamble) {
    long long half_num = num/2;
    for(auto itr = preamble.begin(); itr != preamble.end(); ++itr) {
        if(*itr > half_num) {
            return false;
        } else if(preamble.count(num - (*itr))) {
            return true;
        }
    }
    return false;
}

long long run_part1(std::vector<long long>& nums) {
    std::set<long long> preamble;

    // load the first 25
    for(int i=0; i<PREAMBLE_SIZE; i++) {
        preamble.emplace(nums[i]);
    }

    // for very other number check if sum pair exists
    for(int i=PREAMBLE_SIZE; i<nums.size(); i++) {
        if(is_valid_num(nums[i], preamble)) {
            preamble.erase(nums[i-PREAMBLE_SIZE]);
            preamble.emplace(nums[i]);
        } else {
            std::cout<< "Found bad number: " << nums[i] << std::endl;
            return nums[i];
        }
    }
    return -1;
}

void run_part2(long long bad_number, std::vector<long long>& nums) {
    for(int i=0; i<nums.size()-1; ++i) {
        long long sum = nums[i];
        long long min = sum;
        long long max = sum;
        for(int j=i+1; j<nums.size(); ++j) {
            sum += nums[j];
            min = std::min(min, nums[j]);
            max = std::max(max, nums[j]);
            if (sum == bad_number) {
                std::cout << "The sum: " << min + max << std::endl;
                return;
            }
        }
    }
}

void test() {
    // std::cout << "int" << std::numeric_limits<int>::max() << std::endl;
    // std::cout << "long" << std::numeric_limits<long>::max() << std::endl;
    // std::cout << "long int" << std::numeric_limits<long int>::max() << std::endl;
    // std::cout << "long long" << std::numeric_limits<long long>::max() << std::endl;
    // std::cout << "long long int" << std::numeric_limits<long long int>::max() << std::endl;
}

int main() {
    test();
    std::vector<std::string> lines = read_file("9");
    std::vector<long long> nums = parse_input(lines);
    long long bad_number = run_part1(nums);
    run_part2(bad_number, nums);
}
