#include <chrono>
#include <cmath>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

// Include Functions

// Functions defined below
double average(std::vector<int> values);
bool isLetter(char character);
bool isPunctuation(char character);
bool isSpecialCharacter(char character);
double stdev(std::vector<int> values);

int main() {
	std::cout << "You may begin typing at any time. Press escape to end:\n";
	
	// Variable declaration
	char pressed{};				// Char, for the most recently pressed key
	std::string str;			// String to hold all characters
	std::vector<int> intervals;	// int vector to hold ms intervals between keypresses
	// These two are used to measure the ms interval between keypresses
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();	
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	
	while ((pressed = _getch()) != 27) {	// 27 is ascii for ESC
		end = std::chrono::steady_clock::now();
		str += pressed;
		intervals.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
		begin = std::chrono::steady_clock::now();
	}

	std::cout << "\nLength of str : " << str.length();
	std::cout << "\nLength of intervals: " << intervals.size() << "\n";
	
	int countCharsPrinted{ 0 };
	// Print tab-spaced str
	for (unsigned int it{ 0 }; it < str.length(); ++it) {
		std::cout << str[it] << "|";
		++countCharsPrinted;
	}
	std::cout << "\n";

	int countIntervalsPrinted{ 0 };
	// Print tab-spaced intervals
	for (unsigned int it{ 0 }; it < intervals.size(); ++it) {
		std::cout << intervals[it] << "\t";
		++countIntervalsPrinted;
	}

	std::cout << "\n\nNumber of chars printed:\t" << countCharsPrinted << "\n";
	std::cout << "Number of intervals printed:\t" << countIntervalsPrinted;

	// Here begins the "Analytics"

	/* Old version here, used time AFTER typing instead of time before (which seemed like a good idea initially)
	std::vector<int> timeAfterLetter;
	std::vector<int> timeAfterSameLetter;
	std::vector<int> timeAfterSpace;
	std::vector<int> timeAfterBackspace;
	std::vector<int> timeAfterPunctuation;
	std::vector<int> timeAfterSpecial;

	// UPDATE: Make this use pointers instead
	for (unsigned int it{ 1 }; it < intervals.size(); ++it) {
		if (isLetter(str[it - 1])) {
			if ((it > 1) && (str[it - 1] == str[it - 2])) {
				timeAfterSameLetter.push_back(intervals[it]);
			}
			else {
				timeAfterLetter.push_back(intervals[it]);
			}
		}
		else if (isPunctuation(str[it - 1])) {
			timeAfterPunctuation.push_back(intervals[it]);
		}
		else if (isSpecialCharacter(str[it - 1])) {
			timeAfterSpecial.push_back(intervals[it]);
		}
		else if (str[it - 1] == 32) {
			timeAfterSpace.push_back(intervals[it]);
		}
		else if (str[it - 1] == 8) {
			timeAfterBackspace.push_back(intervals[it]);
		}
	}

	std::cout << "\n\nAverage time after letters: " << average(timeAfterLetter) << " +/- " << stdev(timeAfterLetter) << " (" << timeAfterLetter.size() << " total)\n";
	std::cout << "Average time after same letters: " << average(timeAfterSameLetter) << " +/- " << stdev(timeAfterSameLetter) << " (" << timeAfterSameLetter.size() << " total)\n";
	std::cout << "Average time after punctuation: " << average(timeAfterPunctuation) << " +/- " << stdev(timeAfterPunctuation) << " (" << timeAfterPunctuation.size() << " total)\n";
	std::cout << "Average time after special characters: " << average(timeAfterSpecial) << " +/- " << stdev(timeAfterSpecial) << " (" << timeAfterSpecial.size() << " total)\n";
	std::cout << "Average time after space: " << average(timeAfterSpace) << " +/- " << stdev(timeAfterSpace) << " (" << timeAfterSpace.size() << " total)\n";
	std::cout << "Average time after backspace: " << average(timeAfterBackspace) << " +/- " << stdev(timeAfterBackspace) << " (" << timeAfterBackspace.size() << " total)\n";
	*/

	std::vector<int> timeBeforeRepeat;					// Expected: short
	std::vector<int> timeBeforeSpaceAfterPunctuation;	// Expected: short
	std::vector<int> timeBeforeSpaceBetweenWords;		// Expected: short
	std::vector<int> timeBeforePunctuation;				// Expected: average
	std::vector<int> timeBeforeBackspace;				// Expected: long
	std::vector<int> timeBeforeSpecialCharacter;		// Expected: average
	std::vector<int> timeBeforeLetterAtStartOfSentence;	// Expected: very long
	std::vector<int> timeBeforeLetterAtBeginningOfWord;	// Expected: average
	std::vector<int> timeBeforeLetterInWord;			// Expected: short
	std::vector<char> others;							// For wacky things I missed?

	for (unsigned int it{ 1 }; it < intervals.size(); ++it) {	// Skip the first interval, it means nothing
		if (str[it] == str[it - 1]) {	// The interval came before a repeat
			timeBeforeRepeat.push_back(intervals[it]);
		}
		else if (str[it] == 32) {	// Intervals before spaces
			if (isPunctuation(str[it - 1])) {	// interval before a space after punctuation
				timeBeforeSpaceAfterPunctuation.push_back(intervals[it]);
			}
			else if (isLetter(str[it - 1])) {	// Interval beofre a space after a letter
				timeBeforeSpaceBetweenWords.push_back(intervals[it]);
			}
		}
		else if (isPunctuation(str[it])) {	// Intervals before punctuation
			timeBeforePunctuation.push_back(intervals[it]);
		}
		else if (str[it] == 8) {	// Intervals before backspaces
			timeBeforeBackspace.push_back(intervals[it]);
		}
		else if (isSpecialCharacter(str[it])) {	// Intervals before special characters
			timeBeforeSpecialCharacter.push_back(intervals[it]);
		}
		else if (isLetter(str[it])) {	// Intervals before letters
			if (str[it - 1] == 32) {	// Intervals after a space
				if ((it > 1) && (isPunctuation(str[it - 2]))) {
					timeBeforeLetterAtStartOfSentence.push_back(intervals[it]);	// Time before a letter after a punctuation and a space
				}
				else {
					timeBeforeLetterAtBeginningOfWord.push_back(intervals[it]);
				}
			}
			else {
				timeBeforeLetterInWord.push_back(intervals[it]);
			}
		}
		else {
			others.push_back(str[it]);
		}
	}

	std::ofstream outf{ "RecentTypingTesterLog.txt" };
	if (!outf) {	// If the file was unopenable
		std::cerr << "Yo the file was fucked" << std::endl;
		return 1;
	}
	// Print to File
	{
		// TODO: Do it here
	}

	return 0;
}

double average(std::vector<int> values) {
	int total{ 0 };
	for (unsigned int it{ 0 }; it < values.size(); ++it) {
		total += values[it];
	}
	return (total * 1.0) / values.size();
}

bool isLetter(char character) {
	return (((character >= 65) && (character <= 90)) || ((character >= 97) && (character <= 122)));
}

bool isPunctuation(char character) {
	switch ((int) character) {
		case 33: // !
		case 46: // .
		case 63: // ?
		case 44: // ,
			return true;
		default:
			return false;
	}
}

bool isSpecialCharacter(char character) {
	int characterInt{ (int)character };
	// Dodge "!" at the beginning
	if ((characterInt >= 34) && (characterInt <= 43)) {
		return true;
	}
	// Dodge ","
	else if (characterInt == 45) {
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

double stdev(std::vector<int> values) {
	double mean{ average(values) };
	double sum{ 0 };
	for (unsigned int it{ 0 }; it < values.size(); ++it) {
		double val = std::abs(values[it] - mean);
		sum += val * val;
	}
	sum /= values.size();
	return sqrt(sum);
}