/*
 * TASK: Given an integer n >= 0 and a filename, print the last n lines of the
 *       given file.
 */

#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

int main(int argc, char** argv)
{
    /*
     * usage: ./solve <num-lines> <filename>
     * example: ./solve 10 solve.cpp
     */

    assert(argc > 2);

    int n = std::stoi(argv[1]);
    assert(n >= 0);

    std::ifstream in_file(argv[2]);
    assert(in_file.is_open() == true);

    std::string line;
    std::deque<std::string> lines;

    while (std::getline(in_file, line).good() == true)
    {
        lines.push_back(line);

        /* if we reach n+1 lines, discard the oldest one */
        if (lines.size() == static_cast<size_t>(n + 1))
        {
            lines.pop_front();
        }
    }

    for (const std::string& line : lines)
    {
        std::cout << line << "\n";
    }

    return EXIT_SUCCESS;
}
