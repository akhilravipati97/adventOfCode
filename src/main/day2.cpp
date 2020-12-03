#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cassert>

bool is_valid_password_part1(const int& lower_bound, const int& upper_bound, const char& letter, const std::string& password) {
    int freq = 0;
    for(int i=0; i<password.size(); ++i) {
        if (password[i] == letter) {
            freq++;
            if (freq > upper_bound) {
                return false;
            }
        }
    }
    return freq >= lower_bound;
}

bool is_valid_password_part2(const int& lower_bound, const int& upper_bound, const char& letter, const std::string& password) {
    if(password.size() < upper_bound) return false;
    char pos1 = password[lower_bound-1];
    char pos2 = password[upper_bound-1];
    return (pos1 != pos2) && (pos1 == letter || pos2 == letter);
}

/*
 * Line I/O from https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
 */
void run_main() {
    std::ifstream input_file("./input/day2.txt");
    if (input_file.is_open()) {
        int valid_passwords = 0;
        int lower_bound, upper_bound;
        char dash, letter, colon;
        std::string password;

        while(input_file >> lower_bound >> dash >> upper_bound >> letter >> colon >> password) {
            // std::cout << "lower bound: " << lower_bound << " upper_bound: " << upper_bound << std::endl;
            if(is_valid_password_part2(lower_bound, upper_bound, letter, password)) {
                valid_passwords++;
            }
        }
        std::cout << "Valid passwords: " << valid_passwords << std::endl;
    }
}

void run_tests() {
    assert(is_valid_password_part1(2,5,'a',"abca") == true);
    assert(is_valid_password_part1(10,20,'a',"abca") == false);
    assert(is_valid_password_part2(1,2, 'a', "cccc") == false);
    assert(is_valid_password_part2(1,2, 'a', "aacc") == false);
    assert(is_valid_password_part2(5,6, 'a', "cccc") == false);
    assert(is_valid_password_part2(5,6, 'a', "ccccaa") == false);
    assert(is_valid_password_part2(5,6, 'a', "ccccap") == true);
    assert(is_valid_password_part2(5,6, 'a', "ccccpa") == true);
}



int main() {
    // run_tests();
    run_main();
}
