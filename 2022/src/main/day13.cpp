#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>
#include "../helpers/readInputFile.cpp"

struct Elem {
    int val;
    std::vector<Elem> vec;
    char type;
};

std::string elemToStr(const Elem e) {
    std::string val = "";
    if(e.type=='i') val += std::to_string(e.val);
    else {
        val += "[";
        for(size_t i=0; i<e.vec.size(); i+=1) {
            const auto &elem = e.vec[i];
            if(i == e.vec.size()-1) {
                val += elemToStr(elem);    
            } else {
                val += elemToStr(elem) + ",";
            }
        }
        val += "]";
    }
    return val;
}

std::pair<Elem, size_t> parseLine(const std::string& line, size_t i) {
    assert(line[i] == '[');
    Elem curr = {.type='v'};
    i += 1;
    std::string intVal = "";
    while(i < line.size()) {
        if(line[i] == '[') {
            auto parsedElem = parseLine(line, i);
            i = parsedElem.second;
            curr.vec.push_back(parsedElem.first);
            curr.type='v';
        } else if (line[i] == ',') {
            if(intVal != "") {
                curr.vec.push_back(Elem{.val=std::stoi(intVal), .type='i'});
                curr.type='v';
                intVal = "";
            }
            i += 1;
        } else if (line[i] == ']') {
            if(intVal != "") {
                curr.vec.push_back(Elem{.val=std::stoi(intVal), .type='i'});
                curr.type='v';
                intVal = "";
            }
            return {curr, i+1};
        } else {
            intVal += line[i];
            i += 1;
        }
    }
    return {curr, i};
}

int compare(Elem e1, Elem e2) {
    if(e1.type == 'i' && e2.type == 'i') {
        if (e1.val < e2.val) return 1;
        else if(e1.val > e2.val) return -1;
        else return 0;
    } else if(e1.type == 'v' && e2.type == 'v') {
        size_t i = 0, j = 0;
        while(i < e1.vec.size() && j < e2.vec.size()) {
            int val = compare(e1.vec[i], e2.vec[j]);
            if(val != 0) return val;
            i += 1; j += 1;
        }
        if (i == e1.vec.size() && j == e2.vec.size()) return 0;
        else if (i == e1.vec.size()) return 1;
        else return -1;
    } else {
        int mul = 1;
        if (e2.type == 'i') {
            Elem temp = e1;
            e1 = e2;
            e2 = temp;
            mul = -1;
        }
        e1 = Elem{.vec=std::vector<Elem>{e1}, .type='v'};
        return mul*compare(e1, e2);
    }
}


int run_part1(std::vector<std::string>& lines) {
    int sumOfIdx = 0;
    for(size_t i=0; i<lines.size(); i+=3) {
        const auto p1 = parseLine(lines[i], 0);
        const auto p2 = parseLine(lines[i+1], 0);
        assert(p2.second == lines[i+1].size());
        if(compare(p1.first, p2.first) == 1) {
            sumOfIdx += ((i/3)+1);
        }
    }
    return sumOfIdx;
}

int run_part2(std::vector<std::string> &lines) {
    std::vector<Elem> parsedLines;
    for(size_t i=0; i<lines.size(); i+=3) {
        const auto p1 = parseLine(lines[i], 0);
        const auto p2 = parseLine(lines[i+1], 0);
        parsedLines.push_back(p1.first);
        parsedLines.push_back(p2.first);
    }
    parsedLines.push_back(parseLine("[[2]]", 0).first);
    parsedLines.push_back(parseLine("[[6]]", 0).first);

    std::sort(parsedLines.begin(), parsedLines.end(), [](Elem e1, Elem e2) {
        return compare(e1, e2) == 1;
    });

    int mux = 1;
    for(size_t i=0; i<parsedLines.size(); i+=1) {
        std::string strVal = elemToStr(parsedLines[i]);
        if(strVal== "[[2]]" || strVal == "[[6]]") mux *= (i+1);
    }
    
    return mux;
}

void test() {
    std::vector<std::string> lines = {
        "[1,1,3,1,1]",
        "[1,1,5,1,1]",
        "",
        "[[1],[2,3,4]]",
        "[[1],4]",
        "",
        "[9]",
        "[[8,7,6]]",
        "",
        "[[4,4],4,4]",
        "[[4,4],4,4,4]",
        "",
        "[7,7,7,7]",
        "[7,7,7]",
        "",
        "[]",
        "[3]",
        "",
        "[[[]]]",
        "[[]]",
        "",
        "[1,[2,[3,[4,[5,6,7]]]],8,9]",
        "[1,[2,[3,[4,[5,6,0]]]],8,9]",
    };
    int val = run_part1(lines);
    std::cout << "test part 1 val: " << val << std::endl;
    assert(val == 13);

    val = run_part2(lines);
    std::cout << "test part 2 val: " << val << std::endl;
    assert(val == 140);
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "13");
    int val = run_part1(lines);
    std::cout << "ans part 1: " << val << std::endl;
    val = run_part2(lines);
    std::cout << "ans part 2: " << val << std::endl;
}
