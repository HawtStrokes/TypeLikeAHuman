#include <iostream>
#include <thread>
#include <string>
#include <random>

void TypingEffect(const std::string& txt, unsigned int speedMulitplier = 1, bool endLine = true) {
	std::random_device rD{};
	std::mt19937 twister{ rD()};
	std::uniform_int_distribution<int> dist(1, 5);
	for (char c : txt) {
		int randNum = dist(twister);
		std::this_thread::sleep_for(std::chrono::milliseconds(randNum * (100 / speedMulitplier)));
		printf("%c", c);
	}
	if (endLine == true) std::cout << std::endl;
}

int main(int argc, char** argv) {
	if (argc != 1) {
		int speed = 3;
		bool withDash = true;
		for (int i = 1; i < argc; ++i) {
			if (std::string(argv[i]).substr(0, 1) == "-") {
				if (std::string(argv[i]).substr(1, 1) == "s") {
					try {
						speed = std::stoi(argv[i + 1]);
					}
					catch (const std::exception&) {
						printf("Error changing the speed. Reverting back to default 3...");
					}
				}

				else if (std::string(argv[i]).substr(1, 1) == "t") {
					for (int j = i + 1; j < argc; ++j) {
						TypingEffect(std::string(argv[j]) + " ", speed, false);
					}
					withDash = false;
				}
			}
		}
		return 0;
	}

	int speed = 3;
	while (true) {
		std::string input;
		std::cout << "Input: ";
		std::getline(std::cin, input);
		if (input.substr(0, 7) == ">!spd!<") {
			try {
				speed = std::stoi(input.substr(7, input.length() - 7));
				std::cout << "Speed set to " << speed << std::endl;
			}
			catch (const std::exception&) {
				std::cout << "Error changing speed" << std::endl;
			}
		}

		else {
			TypingEffect(input, speed);
		}
	}

	return 0;
}