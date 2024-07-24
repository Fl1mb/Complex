#include "Complex.h"
#include <iostream>
#include <fstream>
#include <vector>

int main() {
    // ��������� ���� � ������������ �������
    std::ifstream inputFile("input.txt");
    if (inputFile.is_open()) {
        std::cerr << "Error opening input file!" << std::endl;
        return 1;
    }

    //��������� ����� � ���� Real + ������ + Image
    double real, imag;
    while (inputFile >> real >> imag) {
        ComplexNumber<double, double> complex(real, imag);
        std::cout << complex << std::endl;
    }
    inputFile.close();
    //��������� ����
    // 
    // 
    // C������� ������ �� ���������� ����������� �����
    std::vector<ComplexNumber<double, double>> uniqueComplexNumbers;
    for (const auto& num : uniqueComplexNumbers) {
        if (num != 0.0) {
            uniqueComplexNumbers.push_back(num);
        }
    }

    // ������� ���� ������ ����������� �����
    std::cout << "Unique complex numbers:" << std::endl;
    for (const auto& num : uniqueComplexNumbers) {
        std::cout << num << std::endl;
    }

    // ����� � ������������ input Complex Number
    double inputNumber;
    std::cout << "Enter a number: ";
    std::cin >> inputNumber;

    std::vector<ComplexNumber<double, double>> result;
    for (auto& num : uniqueComplexNumbers) {
        if (num.GetModule() > inputNumber) {
            result.push_back(num);
        }
    }

    // ������� ���������
    std::cout << "Complex numbers with modulus greater than " << inputNumber << ":" << std::endl;
    for (const auto& num : result) {
        std::cout << num << std::endl;
    }

    // ��������� ��������� � ���� output
    std::ofstream outputFile("output.txt", std::ios_base::app);
    if (!outputFile) {
        std::cerr << "Error opening output file!" << std::endl;
        return 1;
    }
    for (const auto& num : result) {
        outputFile << num << std::endl;
    }
    outputFile.close();

    return 0;
}