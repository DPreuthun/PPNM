#include "io_tasks.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

std::vector<double> readCommandLine(int argc, char* argv[]) {

    std::vector<double> numbers;

    for (int i = 1; i < argc; i++) {

        std::string arg = argv[i];

        if (arg == "-n" && i + 1 < argc) {

            numbers.push_back(std::stod(argv[i + 1]));

            i++;
        }
    }

    return numbers;
}

void printTable(const std::vector<double>& numbers) {

    std::cout << std::fixed << std::setprecision(6);

    std::cout << "============================================\n";
    std::cout << "x\t\tsin(x)\t\tcos(x)\n";
    std::cout << "============================================\n";

    for (double x : numbers) {

        std::cout << x << "\t"
                  << std::sin(x) << "\t"
                  << std::cos(x) << "\n";
    }

    std::cout << "\n";
}

void readFromStdin() {

    std::cout << "===== STANDARD INPUT =====\n\n";

    double x;

    while (std::cin >> x) {

        std::cout << x << " "
                  << std::sin(x) << " "
                  << std::cos(x) << "\n";
    }
}

void fileStreams(const std::string& infile,
                 const std::string& outfile) {

    std::ifstream myinput(infile);
    std::ofstream myoutput(outfile);

    if (!myinput.is_open() || !myoutput.is_open()) {

        std::cerr << "Error opening files\n";

        return;
    }

    double x;

    myoutput << std::fixed << std::setprecision(6);

    myoutput << "============================================\n";
    myoutput << "x\t\tsin(x)\t\tcos(x)\n";
    myoutput << "============================================\n";

    while (myinput >> x) {

        myoutput << x << "\t"
                 << std::sin(x) << "\t"
                 << std::cos(x) << "\n";
    }

    myinput.close();
    myoutput.close();
}
