#pragma once

#include <vector>

class Sequencer
{
public:
	Sequencer(int length = 256);
	bool IsDepleted();
	int PeekRight();
	void ShiftRight();
	void Reset();

private:
	int counter = 0;
	std::vector<int> sequence;
};
