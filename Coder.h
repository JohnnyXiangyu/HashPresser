#pragma once
#include <string>

class Coder
{
public:
	std::string Encode(std::string plaintext);
	std::string Decode(std::string ciphertext);

private:
	bool done = false;
	std::string decodeResult = "";
	std::string Digest(std::string input);
	// void WorkerRoutine(int index, int total, std::string target);
};

