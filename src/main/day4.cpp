#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>

std::unordered_set<std::string> needed_keys {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
std::unordered_set<std::string> eye_color {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

// check if each char is in the str is digit
bool is_digit_str(std::string& str) {
    return std::all_of(str.begin(), str.end(), [](char c) { 
        int val = c - '0';
        return (val >= 0 && val <= 9 );  
    });
}

// key and validation function map - to perform correct validation for each key
std::unordered_map<std::string, std::function<bool(std::string)>> validation_map {
    { "byr", [](std::string value) {
        if (value.size() == 4 && is_digit_str(value)) {
            int num = std::stoi(value);
            return num >= 1920 && num <=2002;
        }
        return false;
    }},
    { "iyr", [](std::string value) {
        if (value.size() == 4 && is_digit_str(value)) {
            int num = std::stoi(value);
            return num >= 2010 && num <=2020;
        }
        return false;
    }},
    { "eyr", [](std::string value) {
        if (value.size() == 4 && is_digit_str(value)) {
            int num = std::stoi(value);
            return num >= 2020 && num <=2030;
        }
        return false;
    }},
    { "hgt", [](std::string value) {
        std::string units = value.substr(value.size()-2);
        std::string num_str = value.substr(0, value.size()-2);
        if (num_str.size() == 0 || !is_digit_str(num_str)) return false;
        if(units == "cm") {
            int num = std::stoi(num_str);
            return num >= 150 && num <=193;
        } else if (units == "in") {
            int num = std::stoi(num_str);
            return num >= 59 && num <=76;
        }
        return false;
    }},
    { "hcl", [](std::string value) {
        if(value.size() == 7 && value[0] == '#') {
            return std::all_of(std::next(value.begin(), 1), value.end(), [](char c){ 
                int val = c - '0';
                return (val >= 0 && val <= 9 ) || ( val >= 49 && val <=54);
            });
        }
        return false;
    }},
    { "ecl", [](std::string value) {
        return eye_color.count(value);
    }},
    { "pid", [](std::string value) {
        return value.size() == 9  && is_digit_str(value);
    }}
};

void print_map(const std::unordered_map<std::string, std::string>& map) {
     for( const auto& n : map ) {
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
    }
    std::cout << "\n\n";
}

// just check if all the needed keys are present
int valid_passports_part1(const std::vector<std::unordered_map<std::string, std::string>>& passports) {
    return std::count_if(passports.begin(), passports.end(), [](const std::unordered_map<std::string, std::string>& passport) {
        return std::all_of(needed_keys.begin(), needed_keys.end(), [&passport](std::string key) {
            return passport.count(key);
        }); 
    });
}

// check if all the needed keys are present and that each key's value passes validation
int valid_passports_part2(const std::vector<std::unordered_map<std::string, std::string>>& passports) {
    return std::count_if(passports.begin(), passports.end(), [](const std::unordered_map<std::string, std::string>& passport) {
        bool valid = std::all_of(needed_keys.begin(), needed_keys.end(), [&passport](std::string key) {
            return passport.count(key) && validation_map[key](passport.at(key));
        }); 
        return valid;
    });
}

std::unordered_map<std::string, std::string> get_passport(std::vector<std::string>& lines) {
    std::unordered_map<std::string, std::string> passport;
    std::string key, value, str;
    for(std::string& line: lines) {
        std::istringstream iss(line);
        while(iss >> str) {
            auto itr = str.find(":");
            passport[str.substr(0, itr)] = str.substr(itr+1);
        }
    }
    return passport;
}

void run() {
    std::ifstream ifile("./input/day4.txt");
    std::string line;
    std::vector<std::unordered_map<std::string, std::string>> passports;
    std::vector<std::string> lines;

    while(std::getline(ifile, line)) {
        if(line.size() == 0) {
            passports.emplace_back(get_passport(lines));
            lines.clear();
        } else {
            lines.emplace_back(line);
        }
    }
    if (!lines.empty()) {
        passports.emplace_back(get_passport(lines));
    }

    std::cout << "Num valid: " << valid_passports_part2(passports);
}

// byr, iyr and eyr are similar - so one byr test suffices
void byr_test() {
    assert(true == validation_map["byr"]("1980"));
    assert(true == validation_map["byr"]("1920"));
    assert(true == validation_map["byr"]("2001"));
    assert(false == validation_map["byr"]("02001"));
    assert(false == validation_map["byr"]("a2001"));
    assert(false == validation_map["byr"]("1986a"));
    assert(false == validation_map["byr"]("abc"));
    assert(false == validation_map["byr"]("0021"));
}

void hgt_test() {
    assert(true  == validation_map["hgt"]("156cm"));
    assert(true  == validation_map["hgt"]("193cm"));
    assert(true  == validation_map["hgt"]("0193cm"));
    assert(false  == validation_map["hgt"]("012cm"));
    assert(false  == validation_map["hgt"]("1560cm"));
    assert(false  == validation_map["hgt"]("001cm"));
    assert(false  == validation_map["hgt"]("1cm"));
    assert(true  == validation_map["hgt"]("59in"));
    assert(true  == validation_map["hgt"]("64in"));
    assert(true  == validation_map["hgt"]("059in"));
    assert(false  == validation_map["hgt"]("590in"));
    assert(false  == validation_map["hgt"]("59"));
    assert(false  == validation_map["hgt"]("59i"));
    assert(false  == validation_map["hgt"]("cm"));
    assert(false  == validation_map["hgt"]("in"));
    assert(false  == validation_map["hgt"]("170cms"));
}

void hcl_test() {
    assert(true == validation_map["hcl"]("#0a9f3c"));
    assert(true == validation_map["hcl"]("#0123fd"));
    assert(true == validation_map["hcl"]("#ffffff"));
    assert(true == validation_map["hcl"]("#000000"));
    assert(false == validation_map["hcl"]("000000"));
    assert(false == validation_map["hcl"]("ffffff"));
    assert(false == validation_map["hcl"]("#123zdf"));
    assert(false == validation_map["hcl"]("#123afg"));
    assert(false == validation_map["hcl"]("#123ag"));
    assert(false == validation_map["hcl"]("#123zdf"));
}

void ecl_test() {
    assert(true == validation_map["ecl"]("amb"));
    assert(true == validation_map["ecl"]("blu"));
    assert(true == validation_map["ecl"]("brn"));
    assert(true == validation_map["ecl"]("gry"));
    assert(true == validation_map["ecl"]("grn"));
    assert(true == validation_map["ecl"]("hzl"));
    assert(true == validation_map["ecl"]("oth"));
    assert(false == validation_map["ecl"]("xyz"));
    assert(false == validation_map["ecl"]("xy"));
    assert(false == validation_map["ecl"]("br"));
    assert(false == validation_map["ecl"]("am"));
    assert(false == validation_map["ecl"]("x55"));
    assert(false == validation_map["ecl"]("amb "));
    assert(false == validation_map["ecl"](" blu"));
    assert(false == validation_map["ecl"](" gry "));
}

void pid_test() {
    assert(true == validation_map["pid"]("999999999"));
    assert(true == validation_map["pid"]("001234566"));
    assert(true == validation_map["pid"]("999999900"));
    assert(true == validation_map["pid"]("000000000"));
    assert(false == validation_map["pid"]("adfgertyu"));
    assert(false == validation_map["pid"]("adfgert00"));
    assert(false == validation_map["pid"]("000dfiuop"));
    assert(false == validation_map["pid"]("adfgert"));
    assert(false == validation_map["pid"]("0000"));
    assert(false == validation_map["pid"]("adfefw087796"));
    assert(false == validation_map["pid"]("9999999999"));    
}

void test() {    
    byr_test();
    hgt_test();
    hcl_test();
    ecl_test();
    pid_test();
}


int main() {
    test();
    run();
}


