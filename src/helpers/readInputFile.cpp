#include<iostream>
#include<string>
#include<fstream>
#include<vector>


std::vector<std::string> read_file(std::string day) {
    std::ifstream ifile("./input/day" + day + ".txt");
    std::string line;
    std::vector<std::string> lines;
    while(std::getline(ifile, line)) {
        lines.emplace_back(line);
    }
    return lines;
}
