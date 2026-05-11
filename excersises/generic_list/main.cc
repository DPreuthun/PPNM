#include "genlist.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

int main() {

    genlist<std::vector<double>> table;

    std::string line;

    // Read line by line
    while (std::getline(std::cin, line)) {

        std::stringstream ss(line);

        std::vector<double> row;

        double number;

        while (ss >> number) {
            row.push_back(number);
        }

        if (!row.empty()) {
            table.add(row);
        }
    }

    std::cout << "===== TABLE =====\n\n";

    std::cout << std::scientific
              << std::setprecision(6);

    for (int i = 0; i < table.getSize(); i++) {

        for (double value : table[i]) {

            std::cout << std::setw(15)
                      << value;
        }

        std::cout << "\n";
    }

    std::cout << "\n";

    // EXTRA: remove second row
    std::cout << "===== AFTER remove(1) =====\n\n";

    if (table.getSize() > 1) {
        table.remove(1);
    }

    for (int i = 0; i < table.getSize(); i++) {

        for (double value : table[i]) {

            std::cout << std::setw(15)
                      << value;
        }

        std::cout << "\n";
    }

    return 0;
}