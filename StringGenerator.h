#pragma once

#include <string>
#include <vector>
#include <stack>
#include <memory>

#include "Sequencer.h"

class StringGenerator
{
	// TODO: write code here to generate all possible strings with a certain length

public:
	StringGenerator(int size);
	bool Depleted();
	std::string Peek();
	void Next();

private:
	bool isDepleted = false;
	int targetSize = 0;
	std::vector<std::shared_ptr<Sequencer>> sequencers;
};

