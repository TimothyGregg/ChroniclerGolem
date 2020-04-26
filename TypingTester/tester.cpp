#include <chrono>
#include <conio.h>
#include <iostream>
#include <vector>

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
	
	// Print tab-spaced str
	for (int it{ 0 }; it < str.length(); ++it) {
		std::cout << str[it] << "\t";
	}
	std::cout << "\n";

	// Print tab-spaced intervals
	for (int it{ 0 }; it < intervals.size(); ++it) {
		std::cout << intervals[it] << "\t";
	}

	return 0;
}