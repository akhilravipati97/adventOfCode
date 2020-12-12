#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>

void run() {
    std::ifstream ifile("./input/day1.txt");
    std::unordered_set<int> numbers;
    int num;
    while(ifile >> num) {
        // std::cout << "Number is: " << num;
        numbers.insert(num);
    }
}

void test() {

}

int main() {
    test();
    run();
}
