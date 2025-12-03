#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>

void DayOne() {
	const char* PATH = "data/secretEntranceData.txt";

	int currentPosition = 50;
	int amountOfZeros = 0;
	int amountOfZerosDuringRotation = 0;
	int prevPos = currentPosition;

	std::ifstream fileStream(PATH);
	std::string value;

	if (fileStream.is_open()) {
		while (fileStream >> value) {

			prevPos = currentPosition;
			int dir = (value[0] == 'R') ? 1 : -1;
			int step = std::stoi(value.substr(1));
			int rotation = dir * step;

			if (dir == 1) {
				amountOfZerosDuringRotation += (prevPos + step) / 100;
			}
			else {

				if (prevPos == 0) {
					amountOfZerosDuringRotation += (prevPos + step) / 100;
				}
				else if (step >= prevPos) {
					amountOfZerosDuringRotation += 1 + (step - prevPos) / 100;
				}

			}

			currentPosition += rotation;
			currentPosition = (currentPosition % 100 + 100) % 100;

			if (currentPosition == 0) {
				amountOfZeros++;
			}

		}
		fileStream.close();
	}

	std::cout << "Day One \n===================== \n";
	std::cout << "Actual password to open the door: " << amountOfZeros << std::endl;
	std::cout << "Actual password to open the second door: " << amountOfZerosDuringRotation << std::endl;
}

long long CheckIDsInRange(long long a, long long b) {
	long long amount = 0;
	std::string s;

	long long i = 1;
	while (i < b) {

		std::cout << i;

		if (i < a) {
			i++;
			continue;
		}

		s = std::to_string(i);
		s = s + s;

		amount += std::stoll(s);

		i++;
	}

	return amount;
}


void DayTwo() {

	const char* PATH = "data/IDs.txt";
	std::ifstream fileStream(PATH);
	std::string value;

	if (fileStream.is_open()) {
		fileStream >> value;
	}

	long long sumOfIDs = 0;
	std::string t;

	std::stringstream stringStream(value);
	std::stringstream ID_Stream(value);

	char splitAt = ',';
	char splitID = '-';

	while (std::getline(stringStream, t, splitAt)) {

		std::stringstream ID_Stream(t);
		std::string ID;
		int prevID = -1;
		while (std::getline(ID_Stream, ID, splitID)) {
			if (prevID != -1) continue;
			prevID = std::stoll(ID);
		}

		std::cout << "From: " << prevID << " to " << ID << std::endl;
		sumOfIDs += CheckIDsInRange(prevID, std::stoll(ID));

	}
		

	std::cout << "Day Two \n===================== \n";
	std::cout << "Sum of IDs: " << sumOfIDs << std::endl;
}

void DayThree() {
	const char* PATH = "data/joltages.txt";
	std::ifstream fileStream(PATH);

	std::string value;
	int sumJoltage = 0;


	while (fileStream >> value) {          

		int best = 0;
		for (size_t i = 0; i < value.size() - 1; i++) {
			int tens = value[i] - '0';

			for (size_t j = i + 1; j < value.size(); j++) {
				int ones = value[j] - '0';
				int candidate = tens * 10 + ones;
				if (candidate > best) best = candidate;
			}
		}

		sumJoltage += best;

	}

	std::cout << "Max Joltage: " << sumJoltage << std::endl;


}

int main() {
	DayOne();
	//DayTwo(); 
	DayThree();
}
