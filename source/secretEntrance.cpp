#include <iostream>
#include <fstream>
#include <string>

int main() {

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

	std::cout << "Actual password to open the door: " << amountOfZeros << std::endl;
	std::cout << "Actual password to open the second door: " << amountOfZerosDuringRotation << std::endl;
}
