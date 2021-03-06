#include <chrono>
#include <cmath>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
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

	int time{ static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count()) };
	
	// Variable declaration
	char pressed{};				// Char, for the most recently pressed key
	std::string str;			// String to hold all characters
	std::vector<int> intervals;	// int vector to hold ms intervals between keypresses
	// These two are used to measure the ms interval between keypresses
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();	
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	
	while ((pressed = static_cast<char>(_getch())) != 27) {	// 27 is ascii for ESC
		end = std::chrono::steady_clock::now();
		str += pressed;
		intervals.push_back(static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()));
		begin = std::chrono::steady_clock::now();
	}

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

	// Code block just for collapsibility in IDE and visual distinctness
	// Print to File
	{
		std::ofstream outf{ "RecentTypingTesterLog" + std::to_string(time) + ".txt" };
		if (!outf) {	// If the file was unopenable
			std::cerr << "Yo the file was fucked" << std::endl;
			return 1;
		}
		outf << "Average time before repeated character: " << average(timeBeforeRepeat) << " +/- " << stdev(timeBeforeRepeat) << " (" << timeBeforeRepeat.size() << " total)\n";
		outf << "Average time before space after punctuation: " << average(timeBeforeSpaceAfterPunctuation) << " +/- " << stdev(timeBeforeSpaceAfterPunctuation) << " (" << timeBeforeSpaceAfterPunctuation.size() << " total)\n";
		outf << "Average time before space between words: " << average(timeBeforeSpaceBetweenWords) << " +/- " << stdev(timeBeforeSpaceBetweenWords) << " (" << timeBeforeSpaceBetweenWords.size() << " total)\n";
		outf << "Average time before punctuation: " << average(timeBeforePunctuation) << " +/- " << stdev(timeBeforePunctuation) << " (" << timeBeforePunctuation.size() << " total)\n";
		outf << "Average time before backspace: " << average(timeBeforeBackspace) << " +/- " << stdev(timeBeforeBackspace) << " (" << timeBeforeBackspace.size() << " total)\n";
		outf << "Average time before special character: " << average(timeBeforeSpecialCharacter) << " +/- " << stdev(timeBeforeSpecialCharacter) << " (" << timeBeforeSpecialCharacter.size() << " total)\n";
		outf << "Average time before letter at start of sentence: " << average(timeBeforeLetterAtStartOfSentence) << " +/- " << stdev(timeBeforeLetterAtStartOfSentence) << " (" << timeBeforeLetterAtStartOfSentence.size() << " total)\n";
		outf << "Average time before letter at start of word: " << average(timeBeforeLetterAtBeginningOfWord) << " +/- " << stdev(timeBeforeLetterAtBeginningOfWord) << " (" << timeBeforeLetterAtBeginningOfWord.size() << " total)\n";
		outf << "Average time before letter in word: " << average(timeBeforeLetterInWord) << " +/- " << stdev(timeBeforeLetterInWord) << " (" << timeBeforeLetterInWord.size() << " total)\n";
		if (others.size() > 0) outf << "Others include ascii values: |";
		for (unsigned int it{ 0 }; it < others.size(); ++it) {
			outf << static_cast<int>(others[it]) << "|";
		}
		outf << "\n\n";
		for (unsigned int it{ 0 }; it < str.size(); ++it) {
			outf << "[" << str[it] << " - " << intervals[it] << "]\n";
		}
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