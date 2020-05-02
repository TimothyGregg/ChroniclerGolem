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

// Static variables
static short g_spellingErrorChance = 2;   // This is chance in 100, so do what you will with that.

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

// This is the struct to hold the makeHumanString output. It holds all the information needed to print a "human" string.
struct HumanString {
    std::string str;
    std::vector<int> intervals;
};

// Add in misspellings and corrections to those misspellings
HumanString makeHumanString(std::string str) {
    std::string outStr;
    std::vector<int> intervals;

    Generator repeatedCharacterGenerator(80, 20, 55, 110);
    Generator spaceBetweenWordsGenerator(100, 40, 60, 120);
    Generator spaceAfterPunctuationGenerator(100, 30, 60, 120);
    Generator punctuationGenerator(245, 91, 100, 300);
    Generator backspaceGenerator(380, 70, 500, 150);
    Generator specialCharacterGenerator(350, 200, 250, 550);
    Generator letterAtStartOfSentenceGenerator(450, 120, 150, 1000);
    Generator letterAtStartOfWordGenerator(230, 180, 60, 250);
    Generator letterGenerator(100, 70, 60, 150);

    outStr += str[0];
    intervals.push_back(1000);

    // Loop iterated through letters and determines the interval that must be waited for each
    for (unsigned int it{ 1 }; it < str.size(); ++it) {
        outStr += str[it];
        if (str[it] == (str[it - 1])) { // Repeated characters are never messed up
            intervals.push_back(static_cast<int>(repeatedCharacterGenerator()));
        }
        else {  // Anything that isn't repeated has a chance to mess up
            if ((std::rand() % 100) < g_spellingErrorChance) {  // This means there should be a misspelling
            // TODO: Implement
            // To implement the misspell and overshoot thing, I may need to make this a while loop
            }
            if (str[it] == 32) {    // It's a space
                if (isLetter(str[it - 1])) {    // It's a space after a word
                    intervals.push_back(static_cast<int>(spaceBetweenWordsGenerator()));
                }
                else if (isPunctuation(str[it - 1])) {
                    intervals.push_back(static_cast<int>(spaceAfterPunctuationGenerator()));
                }
            }
            else if (isPunctuation(str[it])) {  // It's punctuation
                intervals.push_back(static_cast<int>(punctuationGenerator()));
            }
            else if (str[it] == 8) {    // It's a backspace
                intervals.push_back(static_cast<int>(backspaceGenerator()));
            }
            else if (isSpecialCharacter(str[it])) { // It's a special character
                intervals.push_back(static_cast<int>(specialCharacterGenerator()));
            }
            else if (isLetter(str[it])) {   // It's a letter
                if (str[it - 1] == 32) {    // There is a space before the letter
                    if (it > 1 && isPunctuation(str[it - 2])) { // There is punctuation before the space before the letter, indicating that this is the beginning of a sentence.
                        intervals.push_back(static_cast<int>(letterAtStartOfSentenceGenerator()));
                    }
                    else {  // There is no punctuation before the space, so it's in the middle of a sentence.
                        intervals.push_back(static_cast<int>(letterAtStartOfWordGenerator()));
                    }
                }
                else {  // Nothing special, this character is found in a word.
                    intervals.push_back(static_cast<int>(letterGenerator()));
                }
            }
        }
    }

    return HumanString{ outStr, intervals };
}

void print(std::string str) {
    HumanString printable{ makeHumanString(str) };

    for (unsigned int it{ 0 }; it < printable.str.size(); ++it) {
        std::cout << printable.str[it];
        if ((it % 80) == 79) {
            std::cout << "\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(printable.intervals[it]));
    }
}

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