#include "Coder.h"
#include "SHA256.h"
#include "StringGenerator.h"

#include <thread>
#include <vector>
#include <iostream>

using namespace std;

std::string Coder::Encode(std::string plaintext)
{
    int length = plaintext.length();
    string digest = Digest(plaintext);

    return to_string(length) + ":" + digest;
}

std::string Coder::Decode(std::string ciphertext)
{
	done = false;
	decodeResult = "";

	vector<thread> threads;

	// TODO: spawn threads with worker routine
	for (int i = 0; i < thread::hardware_concurrency(); i++)
	{
		int total = thread::hardware_concurrency();

		threads.push_back(thread([this, i, total, ciphertext]()
			{
				int length = ceil(256.0 / total);
				int start = i * length;
				int end = min(length * (i + 1) - 1, 255);

				// extract length and target digest
				bool isDigest = false;
				string lengthStr = "";
				string targetDigest = "";
				int targetLength = 0;

				for (char c : ciphertext)
				{
					if (c == ':')
					{
						isDigest = true;
					}
					else if (isDigest)
					{
						targetDigest += c;
					}
					else
					{
						lengthStr += c;
					}
				}
				targetLength = stoi(lengthStr);

				// TODO: start iteration
				for (int head = start; head <= end; head++)
				{
					StringGenerator gen(targetLength - 1);

					while (!gen.Depleted() && !done)
					{
						string tail = "";
						tail += (unsigned char)head;
						tail += gen.Peek();

						string currentDigest = Digest(tail);

						if (currentDigest == targetDigest)
						{
							done = true;
							decodeResult = tail;
							return;
						}
						else
						{
							gen.Next();
						}
					}
				}
			}));
	}

	for (thread& worker : threads)
	{
		worker.join();
	}

	return decodeResult;
}

std::string Coder::Digest(std::string input)
{
	SHA256 sha;
	sha.update(input);

	uint8_t * digest = sha.digest();
	string result = SHA256::toString(digest);
	delete[] digest;
	
	return result;
}
