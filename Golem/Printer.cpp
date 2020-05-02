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
static short g_spellingErrorChance = 25;   // This is chance in 100, so do what you will with that.

template<typename First, typename ... T>
bool is_in(First &&first, T && ... t) {
    /* 
    Nifty fold expression for checking multiple values
    Stolen from https://stackoverflow.com/a/15181949
    */
    return ((first == t) || ...);
}

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
    std::srand(0);
    std::vector<int> intervals;

    Generator repeatedCharacterGenerator(80, 20, 55, 110);
    Generator spaceBetweenWordsGenerator(100, 40, 60, 120);
    Generator spaceAfterPunctuationGenerator(100, 30, 60, 120);
    Generator punctuationGenerator(245, 91, 100, 300);
    Generator backspaceGenerator(380, 70, 150, 500);
    Generator specialCharacterGenerator(350, 200, 250, 550);
    Generator letterAtStartOfSentenceGenerator(450, 120, 150, 1000);
    Generator letterAtStartOfWordGenerator(230, 180, 60, 250);
    Generator letterGenerator(100, 70, 60, 150);

    Generator goofGenerator(1.5, 2, 0, 3);
    
    intervals.push_back(1000);

    // Loop iterated through letters and determines the interval that must be waited for each
    // TODO: Make this safe at the end of strings AND fix the weird behavior it shows at the end of the current string. Also, it errors with the declaration, so thats fun.
    unsigned int pos{ 1 };
    int offset{ 0 };
    while (pos < str.size()) {
        if ((pos > 0) && (str[pos] == str[pos - 1])) { // Repeated characters are never messed up
            intervals.push_back(static_cast<int>(repeatedCharacterGenerator()));
            ++pos;
            if (offset > 0) --offset;
        }
        else {  // Anything that isn't repeated has a chance to mess up
            if ((offset == 0) && ((std::rand() % 100) < g_spellingErrorChance)) {  // This means there should be a misspelling
                unsigned int tempPos{ pos };
                std::string errorStr{};
                int charactersUntilFix = static_cast<int>(goofGenerator());
                int charactersInserted{ 0 };

                if (std::rand() % 2 == 0) {
                    // Swap a letter (and any repeats if it repeats after itself)
                    // Only goof on these letters, because these are the ones I typically mess up on
                    while (!is_in(str[tempPos], 's', 'd', 'g', 'f', 'c', 'v', 'b', 'n', 'm', 't', 'y')) {
                        ++tempPos;
                        ++offset;
                    }
                    // Figure out what to swap the letter with based on what the letter is
                    if (str[tempPos] == 's') {
                        errorStr += "d\b";
                    }
                    else if (str[tempPos] == 'd') {
                        errorStr += "s\b";
                    }
                    else if (str[tempPos] == 'g') {
                        errorStr += "f\b";
                    }
                    else if (str[tempPos] == 'f') {
                        errorStr += "g\b";
                    }
                    else if (str[tempPos] == 'c') {
                        errorStr += "v\b";
                    }
                    else if (str[tempPos] == 'v') {
                        if (std::rand() % 2 == 0) {
                            errorStr += "c\b";
                        }
                        else {
                            errorStr += "b\b";
                        }
                    }
                    else if (str[tempPos] == 'b') {
                        errorStr += "v\b";
                    }
                    else if (str[tempPos] == 'n') {
                        errorStr += "m\b";
                    }
                    else if (str[tempPos] == 'm') {
                        errorStr += "n\b";
                    }
                    else if (str[tempPos] == 't') {
                        errorStr += "y\b";
                    }
                    else if (str[tempPos] == 'y') {
                        errorStr += "t\b";
                    }
                    // Walk forward until the error string is complete
                    while (charactersInserted < charactersUntilFix) {
                        ++charactersInserted;
                        // These need to be substrings, not indexed chars, because insert wants std::string input
                        if ((str[tempPos + charactersInserted] == str[tempPos + charactersInserted - 1]) && (errorStr.size() == 2)) {
                            errorStr.insert(charactersInserted, errorStr.substr(0, 1) + "\b");
                        }
                        else {
                            errorStr.insert(charactersInserted, str.substr(tempPos + charactersInserted, 1) + "\b");
                        }
                    }
                    str.insert(tempPos, errorStr);
                    offset += errorStr.size();
                }
                else {
                    // Find the next space, and mess it up
                }
            }
            else {
                if (str[pos] == 32) {    // It's a space
                    if (isLetter(str[pos - 1])) {    // It's a space after a word
                        intervals.push_back(static_cast<int>(spaceBetweenWordsGenerator()));
                    }
                    else if (isPunctuation(str[pos - 1])) {
                        intervals.push_back(static_cast<int>(spaceAfterPunctuationGenerator()));
                    }
                }
                else if (isPunctuation(str[pos])) {  // It's punctuation
                    intervals.push_back(static_cast<int>(punctuationGenerator()));
                }
                else if (str[pos] == 8) {    // It's a backspace
                    intervals.push_back(static_cast<int>(backspaceGenerator()));
                }
                else if (isSpecialCharacter(str[pos])) { // It's a special character
                    intervals.push_back(static_cast<int>(specialCharacterGenerator()));
                }
                else if (isLetter(str[pos])) {   // It's a letter
                    if ((pos > 0) && (str[pos - 1] == 32)) {    // There is a space before the letter
                        if (pos > 1 && isPunctuation(str[pos - 2])) { // There is punctuation before the space before the letter, indicating that this is the beginning of a sentence.
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
                ++pos;
                if (offset > 0) --offset;
            }
        }
    }

    return HumanString{ str, intervals };
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