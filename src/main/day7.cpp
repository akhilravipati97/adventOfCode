#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>
#include <regex>

struct pair_hash {
    inline std::size_t operator()(const std::pair<std::string,int> & v) const {
        return std::hash<std::string>{}(v.first)*31+v.second;
    }
};

typedef std::unordered_set<std::pair<std::string, int>, pair_hash> pair_set;

std::regex main_bag_regex("(.*) bags contain (.*)");
std::string no_bags = "no other bags";
std::regex inner_bag_regex(" *(\\d)* ([^,.]+) bag[.,s]");
std::string shiny_gold_bag = "shiny gold";
std::sregex_iterator rend; // default end



std::pair<std::string, std::unordered_set<std::string>> get_node_from_line(std::string& line) {
    std::smatch match;
    if(std::regex_search(line, match, main_bag_regex)) {
        if(match.size() == 3) {
            std::string main_bag = match[1];
            std::string the_rest = match[2];
            std::unordered_set<std::string> can_contain;
            int idx = the_rest.find(no_bags);
            if(idx == std::string::npos) {
                std::sregex_iterator ritr ( the_rest.begin(), the_rest.end(), inner_bag_regex);
                while (ritr != rend) {
                    can_contain.emplace((*ritr)[2]);
                    ++ritr;
                }
            } else {
                std::cout<< "No bags ---->" << line  << std::endl;
            }
            return std::make_pair(main_bag, can_contain);
        } else {
            std::cout<< "Not enough matches!" << std::endl;
        }
    } else {
        std::cout<< "Match NOT found!" << std::endl;
    }
    return std::make_pair(std::string(""), std::unordered_set<std::string>{});
}

void get_node_from_line_part_2(std::unordered_map<std::string, pair_set>& bag_vol_graph, std::string& line) {
    std::smatch match;
    pair_set can_contain;
    if(std::regex_search(line, match, main_bag_regex)) {
        if(match.size() == 3) {
            std::string main_bag = match[1];
            std::string the_rest = match[2];
            int idx = the_rest.find(no_bags);
            if(idx == std::string::npos) {
                std::sregex_iterator ritr ( the_rest.begin(), the_rest.end(), inner_bag_regex);
                while (ritr != rend) {
                    std::pair<std::string, int> p1((*ritr)[2], std::stoi((*ritr)[1]));
                    can_contain.emplace(p1);
                    ++ritr;
                }
            } else {
                std::cout<< "No bags ---->" << line  << std::endl;
            }
            bag_vol_graph[main_bag] = can_contain;
        } else {
            std::cout<< "Not enough matches!" << std::endl;
        }
    } else {
        std::cout<< "Match NOT found!" << std::endl;
    }
}

bool find_gold_bag(std::unordered_map<std::string, std::unordered_set<std::string>>& bag_graph, const std::string& bag) {
    std::unordered_set<std::string>& bags = bag_graph[bag];
    return bags.count(shiny_gold_bag) || std::any_of(bags.begin(), bags.end(), [&bag_graph](const std::string& inner_bag) {
        return find_gold_bag(bag_graph, inner_bag);
    });
}

long long find_gold_bag_size(std::unordered_map<std::string, pair_set>& bag_vol_graph, const std::string& bag) {
    pair_set& bags = bag_vol_graph[bag];
    return std::accumulate(bags.begin(), bags.end(), 0, [&bag_vol_graph](int num, auto pair){
        int inner_val = find_gold_bag_size(bag_vol_graph, pair.first);
        std::cout<<"bag: " <<pair.first << ", num: " << pair.second << ", inner_val: "<< inner_val << std::endl;
        return num + pair.second + pair.second * inner_val;
    });
}

void run() {
    std::ifstream ifile("./input/day7.txt");
    std::string line;
    std::unordered_map<std::string, std::unordered_set<std::string>> bag_graph;
    std::vector<std::string> lines;
    while(std::getline(ifile, line)) {
        lines.emplace_back(line);
    }
    // part 1
    // std::for_each(lines.begin(), lines.end(), [&bag_graph](auto line) {
    //     bag_graph.emplace(get_node_from_line(line));
    // });
    // int count = std::count_if(bag_graph.begin(), bag_graph.end(), [&bag_graph](auto pair) {
    //     return find_gold_bag(bag_graph, pair.first);
    // });
    // std::cout << "Count: " << count << std::endl;

    // part 2
    std::unordered_map<std::string, pair_set> bag_vol_graph;
    std::for_each(lines.begin(), lines.end(), [&bag_vol_graph](auto line) {
        get_node_from_line_part_2(bag_vol_graph, line);
    });
    long long total = find_gold_bag_size(bag_vol_graph, shiny_gold_bag);
    std::cout << "Total: " << total << std::endl;
}

void test() {
    // part 1
    // std::string line = "light red bags contain 1 bright white bag, 2 muted yellow bags.";
    // auto pair= get_node_from_line(line);
    // std::cout << "First: " << pair.first << std::endl;
    // std::for_each(pair.second.begin(), pair.second.end(), [](auto val) {
    //     std::cout<< val << " ";
    // });

    // part 2
    std::vector<std::string> lines = { "shiny gold bags contain 2 dark red bags.", "dark red bags contain 2 dark orange bags.", "dark orange bags contain 2 dark yellow bags.", "dark yellow bags contain 2 dark green bags.", "dark green bags contain 2 dark blue bags.", "dark blue bags contain 2 dark violet bags.", "dark violet bags contain no other bags.", };
    std::unordered_map<std::string, pair_set> bag_vol_graph;
    std::for_each(lines.begin(), lines.end(), [&bag_vol_graph](auto line) {
        get_node_from_line_part_2(bag_vol_graph, line);
    });
    int num_bags = find_gold_bag_size(bag_vol_graph, shiny_gold_bag);
    std::cout << "Num bags: " << num_bags << std::endl; 
    assert(126 == num_bags);
}

int main() {
    test();
    std::cout<<"Test over *********** \n";
    run();
    std::cout<<"Run over *********** \n";
}
