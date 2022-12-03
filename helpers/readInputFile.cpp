#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<filesystem>

namespace fs = std::filesystem;

// for backwards compatibility
std::vector<std::string> read_file(std::string day) {
    // std::cout << "Current path: " << fs::current_path() << std::endl;
    std::ifstream ifile("D:\\Projects\\adventofCode2020\\input\\day" + day + ".txt");
    if(!ifile) {
        throw std::runtime_error("No file found!");
    }
    std::string line;
    std::vector<std::string> lines;
    while(std::getline(ifile, line)) {
        lines.emplace_back(line);
    }
    return lines;
}

std::vector<std::string> read_file(std::string year, std::string day) {
    // std::cout << "Current path: " << fs::current_path() << std::endl;
    std::ifstream ifile("D:\\Projects\\adventofCode\\" + year + "\\input\\day" + day + ".txt");
    if(!ifile) {
        throw std::runtime_error("No file found!");
    }
    std::string line;
    std::vector<std::string> lines;
    while(std::getline(ifile, line)) {
        lines.emplace_back(line);
    }
    return lines;
}

std::vector<long long> parse_input(std::vector<std::string>& lines) {
    std::vector<long long> nums;
    nums.reserve(lines.size());
    std::transform(std::begin(lines), std::end(lines), std::back_inserter(nums), [](auto str) { 
        // std::cout << "Applying for: " << str << std::endl;
        return std::stoll(str); 
    });
    return nums;
}
