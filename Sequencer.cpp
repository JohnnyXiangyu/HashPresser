#include "Sequencer.h"

#include <algorithm>

using namespace std;

Sequencer::Sequencer(int inLength)
{
	sequence = vector<int>(inLength);
	for (int i = 0; i < inLength; i++)
	{
		sequence[i] = i;
	}

	// adding some randomness to avoid extreme situation
	random_shuffle(sequence.begin(), sequence.end());
}

bool Sequencer::IsDepleted()
{
	return counter >= sequence.size();
}

int Sequencer::PeekRight()
{
	return sequence[counter];
}

void Sequencer::ShiftRight()
{
	counter++;
}

void Sequencer::Reset()
{
	counter = 0;
}
