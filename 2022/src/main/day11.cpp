#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>
#include <functional>
#include <regex>
#include "../helpers/readInputFile.cpp"

std::regex lastNumber("^[^0-9]*([0-9]+).*$");

std::string vecToStr(const std::vector<long long>& items) {
    std::string s = "";
    for(const auto i: items) {
        s += std::to_string(i) + " ";
    }
    return s;
}

struct Monkey {
    int num, operationNum, divisibleNum, trueMonkey, falseMonkey;
    char op;
    std::vector<long long> items = {};
    long long numInspections = 0;
    int worryManager = 1;
    int mainMod = -1;

    int monkeyToSendTo(long long worryLevel) {
        if ((worryLevel % divisibleNum) == 0) return trueMonkey;
        return falseMonkey;
    }

    long long worry(long long item) {
        long long otherVal = operationNum;
        long long val = item;
        if (operationNum == -1) {
            otherVal = item;
        }

        switch(op) {
            case '*':
                val *= otherVal;
                break;
            case '+':
                val += otherVal;
                break;
        }
        val = val/worryManager;
        if (mainMod != -1) {
            val = val % mainMod;
        }
        // if (val < item) {
        //     std::cout << "overflow for item: " << item << std::endl;
        // }
        return val;
    }

    std::vector<std::pair<int, long long>> throwItemsToMonkeys() {
        std::vector<std::pair<int, long long>> throwItems;
        for(long long item: items) {
            long long worryLevel = worry(item);
            throwItems.push_back({monkeyToSendTo(worryLevel), worryLevel});
            numInspections += 1;
        }
        items = {};
        return throwItems;
    }

    void takeItem(long long item) {
        items.push_back(item);
    }

    friend std::ostream& operator<<(std::ostream& os, const Monkey& m) {
        return os << "{num=" << m.num << ", opNum=" << m.operationNum << ", divNum=" << m.divisibleNum << ", trueMonkey=" << m.trueMonkey << ", falseMonkey=" << m.falseMonkey << ", op=" << m.op << ", items=" << vecToStr(m.items) << std::endl;
    }
};
 
std::vector<long long> buildStartingItems(std::string line) {
    std::string delimiter = ", ";
    size_t pos_start = 0, pos_end, delim_len = delimiter.size();
    std::string token;
    std::vector<long long> res = {};

    while ((pos_end = line.find(delimiter, pos_start)) != std::string::npos) {
        token = line.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(std::stoi(token));
    }

    res.push_back(std::stoi(line.substr(pos_start)));
    return res;
}

int getLastNum(const std::string& line) {
    std::smatch matches;
    if(std::regex_match(line, matches, lastNumber)) {
        return std::stoi(matches[1].str());
    } else {
        throw std::runtime_error("regex failed to work for line: " + line);
    }
}

int getOperationNumber(const std::string& line) {
    try {
        return getLastNum(line);
    } catch (const std::exception &e) {
        if(line.find("Operation: new = old * old") != std::string::npos) {
            return -1;
        }
        throw e;
    }
}

std::vector<Monkey> buildMonkeys(std::vector<std::string>& lines, int worryManager) {
    size_t idx = 0;
    std::vector<Monkey> monkeyVec = {};
    while(idx < lines.size()) {
        std::smatch matches;
        int monkeyNum = getLastNum(lines[idx++]);
        std::vector<long long> startingItems = buildStartingItems(lines[idx++].substr(18, 100));
        int operationNum = getOperationNumber(lines[idx]);
        char op = lines[idx++][23];
        int divisibleNum = getLastNum(lines[idx++]);
        int testTrue = getLastNum(lines[idx++]);
        int testFalse = getLastNum(lines[idx++]);
        Monkey monkey = {
            .num = monkeyNum, 
            .operationNum = operationNum, 
            .divisibleNum = divisibleNum,
            .trueMonkey = testTrue,
            .falseMonkey = testFalse,
            .op = op,
            .items = startingItems,
            .worryManager = worryManager,
        };
        monkeyVec.push_back(monkey);
        // std::cout << monkey << std::endl;
        idx++;
    }
    return monkeyVec;
}


long long run_part1(std::vector<std::string>& lines) {
    std::vector<Monkey> monkeys = buildMonkeys(lines, 3);
    for(int i=0; i<20; i+=1) {
        for(size_t j=0; j<monkeys.size(); j+=1) {
            const auto &toThrow = monkeys[j].throwItemsToMonkeys();
            for(const auto &p: toThrow) {
                monkeys[p.first].takeItem(p.second);
            }
        }
    }
    std::sort(monkeys.begin(), monkeys.end(), [](const Monkey& left, const Monkey& right) {
        return left.numInspections > right.numInspections;
    });

    return monkeys[0].numInspections * monkeys[1].numInspections;
}

void printMonkeyTimes(int roundNum, const std::vector<Monkey> monkeys) {
    std::cout << "Round Num: " << roundNum << std::endl;
    for(const auto &m : monkeys) {
        std::cout << "Monkey " << m.num << " inspected items " << m.numInspections << " times."  << std::endl;
    }
    std::cout << std::endl;
}

long long run_part2(std::vector<std::string>& lines) {
    std::vector<Monkey> monkeys = buildMonkeys(lines, 1);
    long long mainMod = 1;
    for(const auto &monkey: monkeys) {
        mainMod *= monkey.divisibleNum;
    }
    for(size_t i=0; i<monkeys.size(); i+=1) {
        monkeys[i].mainMod = mainMod;
    }
    for(int i=0; i<10000; i+=1) {
        for(size_t j=0; j<monkeys.size(); j+=1) {
            const auto &toThrow = monkeys[j].throwItemsToMonkeys();
            for(const auto &p: toThrow) {
                auto &monkey = monkeys[p.first];
                monkey.takeItem(p.second);
                monkeys[p.first] = monkey;
            }
        }
        // if ((i % 1000 == 0) || (i == 19)) printMonkeyTimes(i, monkeys); 
    }
    std::sort(monkeys.begin(), monkeys.end(), [](const Monkey& left, const Monkey& right) {
        return left.numInspections > right.numInspections;
    });

    return monkeys[0].numInspections * monkeys[1].numInspections;
}

void test() {
    std::vector<std::string> lines = {
        "Monkey 0:",
        "  Starting items: 79, 98",
        "  Operation: new = old * 19",
        "  Test: divisible by 23",
        "    If true: throw to monkey 2",
        "    If false: throw to monkey 3",
        "",
        "Monkey 1:",
        "  Starting items: 54, 65, 75, 74",
        "  Operation: new = old + 6",
        "  Test: divisible by 19",
        "    If true: throw to monkey 2",
        "    If false: throw to monkey 0",
        "",
        "Monkey 2:",
        "  Starting items: 79, 60, 97",
        "  Operation: new = old * old",
        "  Test: divisible by 13",
        "    If true: throw to monkey 1",
        "    If false: throw to monkey 3",
        "",
        "Monkey 3:",
        "  Starting items: 74",
        "  Operation: new = old + 3",
        "  Test: divisible by 17",
        "    If true: throw to monkey 0",
        "    If false: throw to monkey 1",
    };
    long long val = run_part1(lines);
    std::cout << "test value from part 1: " << val << std::endl;
    assert(val == 10605);

    val = run_part2(lines);
    std::cout << "test value from part 2: " << val << std::endl;
    assert(val == 2713310158);
}

int main() {
    test();
    std::vector<std::string> lines = read_file("2022", "11");
    std::cout << "ans part 1: " << run_part1(lines) << std::endl;
    std::cout << "ans part 2: " << run_part2(lines) << std::endl;
}
