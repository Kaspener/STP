#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>

double calculateProgramLength(int operators, int operands) {
    double eta = operators + operands;
    return 0.9 * eta * log2(eta);
}

double calculateVariance(int eta) {
    return (M_PI * M_PI * eta * eta) / 6.0;
}

double simulateProgramLength(int eta) {
    std::vector<bool> dictionary(eta, false);
    int drawn = 0;
    int length = 0;

    while (drawn < eta) {
        int randomIndex = rand() % eta;
        length++;
        if (!dictionary[randomIndex]) {
            dictionary[randomIndex] = true;
            drawn++;
        }
    }
    return length;
}

int main() {
    srand(time(0));

    std::vector<int> dictionarySizes = {16, 32, 64, 128};

    for (int eta : dictionarySizes) {
        double theoreticalLength = calculateProgramLength(eta / 2, eta / 2);
        double theoreticalVariance = calculateVariance(eta);
        double standardDeviation = sqrt(theoreticalVariance);
        double delta = 1.0 / (2 * log2(eta));

        double simulatedLength = simulateProgramLength(eta);

        std::cout << "For a dictionary size of " << eta << ":" << std::endl;
        std::cout << "Theoretical program length: " << theoreticalLength << std::endl;
        std::cout << "Simulated program length: " << simulatedLength << std::endl;
        std::cout << "Theoretical variance: " << theoreticalVariance << std::endl;
        std::cout << "Standard deviation: " << standardDeviation << std::endl;
        std::cout << "Relative error: " << delta << std::endl;
        std::cout << "--------------------------" << std::endl;
    }

    return 0;
}