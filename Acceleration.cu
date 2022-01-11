#include "Acceleration.cuh"
#include "StringGenerator.h"
#include "SHA256.h"

#include <iostream>

using namespace std;

__global__ void PerCharacter(std::string targetDigest, int targetLength, string* decodeResult, bool* done)
{
	// TODO: move all logic inside this block (calling host function from device function is not allowed)
	StringGenerator gen(targetLength - 1);
	unsigned char head = threadIdx.x; // TODO: figure out what's wrong with thread index

	while (!gen.Depleted() && !(*done))
	{
		string tail = "";
		tail += head;
		tail += gen.Peek();

		string currentDigest = "";
		{
			SHA256 sha;
			sha.update(tail);

			uint8_t* digest = sha.digest();
			currentDigest = SHA256::toString(digest);
			delete[] digest;
		}

		if (currentDigest == targetDigest)
		{
			*done = true;
			*decodeResult = tail;
			return;
		}
		else
		{
			gen.Next();
		}
	}
}
