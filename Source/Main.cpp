#include <iostream>
#include <thread>
#include <chrono>
#include <string>

class ScopedTimer {
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
	const char* m_functionName;
public:
	ScopedTimer(const char* functionName) {
		m_functionName = functionName;
		startTime = std::chrono::high_resolution_clock::now();
	}
	~ScopedTimer()
	{
		endTime = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::duration duration = endTime - startTime;
		printf("The function <%s> took %.0000fms", m_functionName, duration.count() / 1000000.0);
		std::cout << std::endl;
	}
};

void TypingEffect(const std::string& txt, unsigned int speedMulitplier = 1, bool endLine = true) {
	//ScopedTimer sT(__func__);
	for (char c : txt) {
		int randNum = (rand() % 5) + 1;
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

	// config
	int speed = 3;
	while (true) {
		// get user input
		std::string input;
		std::cout << "Input: ";
		std::getline(std::cin, input);

		// check for speed change request
		if (input.substr(0, 7) == ">!spd!<") {
			try {
				speed = std::stoi(input.substr(7, input.length() - 7));
				std::cout << "Speed set to " << speed << std::endl;
			}
			catch (const std::exception& e) {
				std::cout << "Error changing speed" << std::endl;
			}
		}

		else {
			TypingEffect(input, speed);
		}
	}

	return 0;
}