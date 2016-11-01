/*
 * TASK: Given an integer n >= 0 and a filename, print the last n lines of the
 *       given file.
 */

#include <queue>
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>

int main(int argc, char** argv)
{
	assert(argc > 2);

	int n = std::stoi(argv[1]);
	assert(n >= 0);

	std::ifstream in_file(argv[2]);
	assert(in_file.is_open() == true);

	std::string line;
	std::deque< std::string > lines;

	while (std::getline(in_file, line).good() == true)
	{
		if (lines.size() == static_cast< size_t >(n))
		{
			lines.pop_front();
		}

		lines.push_back(line);
	}

	for (const std::string& line : lines)
	{
		std::cout << line << "\n";
	}

	return 0;
}
