#include "io_tasks.h"

#include <iostream>

int main(int argc, char* argv[]) {

    std::cout << "===== COMMAND LINE =====\n\n";

    std::vector<double> numbers =
        readCommandLine(argc, argv);

    if (!numbers.empty()) {

        printTable(numbers);
    }

    std::string infile;
    std::string outfile;

    for (int i = 1; i < argc; i++) {

        std::string arg = argv[i];

        if (arg == "--input" && i + 1 < argc) {

            infile = argv[i + 1];
        }

        if (arg == "--output" && i + 1 < argc) {

            outfile = argv[i + 1];
        }
    }

    if (!infile.empty() && !outfile.empty()) {

        fileStreams(infile, outfile);

        std::cout << "Results written to "
                  << outfile << "\n";
    }

    return 0;
}