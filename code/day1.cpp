#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

void partTwo(std::unordered_set<int>& numbersSet) {
    int sum = 2020;
    std::vector<int> numbersList (numbersSet.begin(), numbersSet.end());
    for(int i = 0; i<numbersList.size(); ++i) {
        int num1 = numbersList[i];
        bool found = false;
        for(int j=i; j<numbersList.size(); ++j) {
            int num2 = numbersList[j];
            int num3 = sum - num1 - num2;
            if (num3 >= 0 && numbersSet.count(num3)) {
                std::cout<<"FOund: "<< num1*num2*num3<<std::endl;
                found = true;
                break;
            }
        }
        if (found) break;
    }
}

void partOne(std::unordered_set<int>& numbers) {
    int sum = 2020;
    int threshold = (sum/2) + 1;
    for(int num : numbers) {
        std::cout << "checking: " << num << ", " << sum - num << std::endl;
        if (numbers.count(sum - num)) {
            std::cout<<"Ans: " << (sum - num)*num;
            break;
        }
    }
}

int main() {
    std::ifstream ifile("./input/day1.txt");
    std::unordered_set<int> numbers;
    int num;
    while(ifile >> num) {
        // std::cout << "Number is: " << num;
        numbers.insert(num);
    }
    ifile.close();
    partTwo(numbers);

}
