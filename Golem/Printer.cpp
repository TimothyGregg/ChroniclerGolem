#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

// Include Functions

// Functions defined below
//std::vector<int> buildGapVector(std::string str);
bool isLetter(char character);
bool isPunctuation(char character);
bool isSpecialCharacter(char character);

class Generator {
    /*
    Random numbers on a normal curve within a range
    Stolen from https://stackoverflow.com/a/28619226
    */
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
    //std::vector<int> gaps{ buildGapVector(str) };   // ms gaps after each character
    
    /*for (unsigned int it{ 0 }; it < str.size(); ++it) {
        std::cout << str[it];
        if ((it % 80) == 79) {
            std::cout << "\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(gaps[it]));
    }*/
}

/* TODO: This is going to get reworked
// Add in misspellings and corrections to those misspellings
std::string humanify(std::string str) {
    std::string out;
    for (int it{ 0 }; it < str.size(); ++it) {

    }

    return out;
}

// Construct the vector of ms gaps to come after each letter "typed
std::vector<int> buildGapVector(std::string str) {
    // These are sorted by priority of likelihood
    Generator punctuationGenerator(71, 19, 30, 150);        // After punctuation 
    Generator spaceGenerator(235, 120, 63, 375);            // Before a space
    Generator letterGenerator(143, 103, 63, 200);           // After a letter
    Generator sameLetterGenerator(236, 322, 63, 200);       // This is AFTER, not before. I need to redo my analyzer.
    Generator specialCharacterGenerator(90, 16, 30, 150);   // This is after a special character.
    Generator backspaceGenerator(185, 73, 160, 210);        // Placeholder

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
        else if (str[it - 1] == 8) {    // Gap after a backspace
            if (str[it - 2] == 8) {     // Gap after a repeated backspace (short, and should never be sooner than the second character)
                gaps.push_back(135);    // This is like 8-9 per second, which is about as quick as I thought was reasonable for clicks of a single button
            }
            else {

            }
        }
    }

    return gaps;
}
*/

bool isLetter(char character) {
    return (((character >= 65) && (character <= 90)) || ((character >= 97) && (character <= 122)));
}

bool isPunctuation(char character) {
    switch ((int)character) {
    case 33: // !
    case 46: // .
    case 63: // ?
        return true;
    default:
        return false;
    }
}

bool isSpecialCharacter(char character) {
    int characterInt{ (int)character };
    // Dodge "!" at the beginning
    if ((characterInt >= 34) && (characterInt <= 45)) {
        return true;
    }
    // Dodge "."
    else if (characterInt == 47) {
        return true;
    }
    else if ((characterInt >= 58) && (characterInt <= 62)) {
        return true;
    }
    // Dodge "?"
    else if (characterInt == 64) {
        return true;
    }
    else if ((characterInt >= 91) && (characterInt <= 96)) {
        return true;
    }
    else {
        return false;
    }
}