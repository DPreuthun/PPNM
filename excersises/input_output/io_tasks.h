#ifndef IO_TASKS_H
#define IO_TASKS_H

#include <vector>
#include <string>

std::vector<double> readCommandLine(int argc, char* argv[]);

void printTable(const std::vector<double>& numbers);

void readFromStdin();

void fileStreams(const std::string& infile,
                 const std::string& outfile);

#endif