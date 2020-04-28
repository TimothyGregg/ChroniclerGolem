#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>
#include "tester.h"

// Include Functions
bool isLetter(char character);
bool isPunctuation(char character);
bool isSpecialCharacter(char character);

// Functions defined below
std::vector<int> buildGapVector(std::string str);

/* 
Random numbers on a normal curve within a range
Stolen from https://stackoverflow.com/a/28619226
*/

class Generator {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;
    double min;
    double max;
public:
    Generator(double mean, double stddev, double min, double max) :
        distribution(mean, stddev), min(min), max(max)
    {}

    double operator ()() {
        while (true) {
            double number = this->distribution(generator);
            if (number >= this->min && number <= this->max)
                return number;
        }
    }
};

void print(std::string str) {
    std::vector<int> gaps{ buildGapVector(str) };   // ms gaps after each character
    
    for (unsigned int it{ 0 }; it < str.size(); ++it) {
        std::cout << str[it];
        if ((it % 80) == 79) {
            std::cout << "\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(gaps[it]));
    }
}

// Construct the vector of ms gaps to come after each letter "typed
std::vector<int> buildGapVector(std::string str) {
    Generator letterGenerator(143, 103, 63, 200);
    Generator sameLetterGenerator(236, 322, 63, 200);   // This is AFTER, not before. I need to redo my analyzer.
    Generator punctuationGenerator(78, 19, 30, 150);
    Generator specialCharacterGenerator(90, 16, 30, 150);
    Generator spaceGenerator(235, 120, 63, 375);

    std::vector<int> gaps{ 0 }; // No gap on the first value printed 
    for (unsigned int it{ 1 }; it < str.size(); ++it) {
        if (isLetter(str[it - 1])) { // Gap after a letter
            if (str[it] == str[it - 1]) {   // Gap after a same letter
                gaps.push_back(sameLetterGenerator());
            }
            else {  // Gap after a letter that isn't being repeated
                gaps.push_back(letterGenerator());
            }
        }
        else if (isPunctuation(str[it - 1])) {  // Gap after punctuation
            gaps.push_back(punctuationGenerator());
        }
        else if (isSpecialCharacter(str[it - 1])) { // Gap after special character
            gaps.push_back(specialCharacterGenerator());
        }
        else if (str[it - 1] == 32) {   // Gap after space
            gaps.push_back(spaceGenerator());
        }
    }

    return gaps;
}