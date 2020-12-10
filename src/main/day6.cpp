#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <functional>

int num_unique_answers(std::vector<std::string> answers) {
    std::unordered_set<char> unique_answers;
    std::for_each(answers.begin(), answers.end(), [&unique_answers](std::string& answer) {
        std::for_each(answer.begin(), answer.end(), [&unique_answers](char&  c) {
            unique_answers.emplace(c);
       });
    });
    return unique_answers.size();
}

int num_common_answers(std::vector<std::string> answers) {
    std::unordered_map<char, int> common_answers;
    std::for_each(answers.begin(), answers.end(), [&common_answers](std::string& answer) {
        std::for_each(answer.begin(), answer.end(), [&common_answers](char&  c) {
            common_answers[c] += 1;
       });
    });
    return std::count_if(common_answers.begin(), common_answers.end(), [&answers](auto pair) { return pair.second == answers.size();});
}

int get_sum_answers_unique(std::vector<std::vector<std::string>> group_answers) {
    return std::accumulate(group_answers.begin(), group_answers.end(), 0, [](int count, auto answers) {
        return count + num_unique_answers(answers);
    });
}

int get_sum_answers_common(std::vector<std::vector<std::string>> group_answers) {
    return std::accumulate(group_answers.begin(), group_answers.end(), 0, [](int count, auto answers) {
        return count + num_common_answers(answers);
    });
}

void run() {
    std::ifstream ifile("./input/day6.txt");
    if(ifile.is_open()) {
        std::vector<std::vector<std::string>> group_answers;
        std::string line;
        std::vector<std::string> answers;
        while(std::getline(ifile, line)) {
            if(line.size() != 0) {
                answers.emplace_back(line);
            } else {
                group_answers.emplace_back(answers);
                answers.clear();
            }
        }
        if(answers.size() != 0) {
            group_answers.emplace_back(answers);
        }
        int sum = get_sum_answers_common(group_answers);
        std::cout << "Sum: " << sum << std::endl;
    } else {
        std::cout<< "File not open";
    }
}

void test() {
    assert(get_sum_answers_unique({{"abc"}, {"a", "b", "c"}, {"ab", "ac"}, {"a", "a", "a", "a"}, {"b"}}) == 11);
    assert(get_sum_answers_common({{"abc"}, {"a", "b", "c"}, {"ab", "ac"}, {"a", "a", "a", "a"}, {"b"}}) == 6);
}

int main() {
    test();
    run();
}
