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

long long Greedy(std::string Data, int k) {
	int n = Data.length();
	std::string longest = "";
	int j = 0; 
	for (int r = k; r > 0; r--) {
		char max_digit = '0';
		int pos = j;
		for (int i = j; i <= n - r; i++) {
			if (Data[i] > max_digit) {
				max_digit = Data[i];
				pos = i;
			}
		}
		longest += max_digit;
		j = pos + 1; 
	}

	return std::stoll(longest);
}

void DayThree() {
	const char* PATH = "data/joltages.txt";
	std::ifstream fileStream(PATH);

	std::string value;
	int sumJoltage = 0;
	unsigned long long int sum = 0;


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

		sum += Greedy(value, 12);
	}

	std::cout << "Max Joltage: " << sumJoltage << std::endl;
	std::cout << "Max for 12 Joltage: " << sum << std::endl;


}

std::vector<std::vector<long long>> mergeIntervals(std::vector<std::vector<long long>>& dataArray) {
	std::sort(dataArray.begin(), dataArray.end());

	std::vector<std::vector<long long>> merged;
	merged.push_back(dataArray[0]);
	
	for (int i = 0; i < dataArray.size(); i++) {
		std::vector<long long>& lastVal = merged.back();
		std::vector<long long>& currentVal = dataArray[i];

		if (currentVal[0] <= lastVal[1]) {
			lastVal[1] = std::max(lastVal[1], currentVal[1]);
		}
		else {
			merged.push_back(currentVal);
		}
	}

	return merged;
}

void DayFive() {
	const char* PATH = "data/cafeteria.txt";
	std::ifstream fileStream(PATH);
	long long value;
	std::vector<long long> tempArr;
	std::vector<std::vector<long long>> dataArray;
	std::vector<long long> IDs;
	bool bDidSwitch = false;

	std::string line;
	while (std::getline(fileStream, line)) {
		if (line.empty()) {
			bDidSwitch = true;
			continue;
		}

		std::istringstream iss(line);

		

		while (iss >> value) {

			value = std::abs(value);

			if (!bDidSwitch) {
				tempArr.push_back(value);

				if (tempArr.size() == 2) {
					dataArray.push_back(tempArr);
					tempArr.clear();
				}
			}
			else {
				IDs.push_back(value);
			}
		}
	}


	dataArray = mergeIntervals(dataArray);

	std::cout << "Amount of IDs " << IDs.size() << std::endl;

	int amountOfSpoiled = 0;
	for (int i = 0; i < IDs.size(); i++) {
		for (int j = 0; j < dataArray.size(); j++) {
			if (IDs[i] >= dataArray[j][0] && IDs[i] <= dataArray[j][1]) {
				amountOfSpoiled++;
				break;
			}
		}
	}

	std::cout << "Amount of Spoiled IDs " << amountOfSpoiled << std::endl;


	long long freshIdAmount = 0;
	for (int i = 0; i < dataArray.size(); i++) {
		freshIdAmount += (dataArray[i][1] - dataArray[i][0] + 1);
	}
	std::cout << "Fresh IDs " << freshIdAmount << std::endl;

}

int main() {
	DayOne();
	//DayTwo(); 
	DayThree();
	DayFive();
}
