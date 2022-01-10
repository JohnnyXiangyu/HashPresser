#include "StringGenerator.h"

using namespace std;

StringGenerator::StringGenerator(int size)
{
	targetSize = size;
	sequencers = vector<shared_ptr<Sequencer>>(size);

	for (auto& ptr : sequencers)
	{
		ptr = make_shared<Sequencer>();
	}
}

bool StringGenerator::Depleted()
{
	return isDepleted;
}

std::string StringGenerator::Peek()
{
	string result = "";

	for (auto& sequencer : sequencers)
	{
		result += (unsigned char)sequencer->PeekRight();
	}

	return result;
}

void StringGenerator::Next()
{
	int currentEnd = targetSize - 1;

	sequencers[currentEnd]->ShiftRight();

	while (sequencers[currentEnd]->IsDepleted())
	{
		if (currentEnd == 0)
		{
			isDepleted = true;
			return;
		}

		sequencers[currentEnd]->Reset();
		sequencers[currentEnd - 1]->ShiftRight();
		currentEnd--;
	}
}


