#pragma once

#include <ctime>
#include <fstream>
#include "../BigInt/BigInt.h"

void testSummation(const char* inputPath, const char* outputPath, int n = 100) {
    std::cout << "The summation test starts...\n";

    std::ifstream input(inputPath);
    std::ofstream output(outputPath);
    std::string first, second, result, myResult;
    int errors = 0, count = 0;
    float time = 0;
    BigInt a, b;

    clock_t start = clock();
    while (input.peek() != EOF && n != count) {
        count++;
        input >> first >> second >> result;
        a = first;
        b = second;
        myResult = (a + b).str();
        if (myResult != result) {
            errors++;
            output << first << " " << second << " " << result << " " << myResult << std::endl;
        }
    }
    if (errors) {
        std::cout << errors << "/" << count << " errors reported in the " << outputPath << std::endl;
        input.close();
        output.close();
    }
    else {
        time = ((float)clock() - (float)start) / CLOCKS_PER_SEC;
        std::cout << std::fixed;
        std::cout.precision(6);
        std::cout << "Summation tested in " << time << " seconds (0/"<< count <<" errors).\nAverage time: " << time / (float)count << " seconds\n\n";
        input.close();
        output.close();
        remove(outputPath);
    }
}

void testSubtraction(const char* inputPath, const char* outputPath, int n = 100) {
    std::cout << "The subtraction test starts...\n";

    std::ifstream input(inputPath);
    std::ofstream output(outputPath);
    std::string first, second, result, myResult;
    int errors = 0, count = 0;
    float time;
    BigInt a, b;

    clock_t start = clock();
    while (input.peek() != EOF && n != count) {
        count++;
        input >> first >> second >> result;
        a = first;
        b = second;
        myResult = (a - b).str();
        if (myResult != result) {
            errors++;
            output << first << " " << second << " " << result << " " << myResult << std::endl;
        }
    }
    if (errors > 0) {
        std::cout << errors << "/" << count << " errors reported in the " << outputPath << std::endl;
        input.close();
        output.close();
    }
    else {
        time = ((float)clock() - (float)start) / CLOCKS_PER_SEC;
        std::cout << std::fixed;
        std::cout.precision(6);
        std::cout << "Subtraction tested in " << time << " seconds (0/"<< count <<" errors).\nAverage time: " << time / (float)count << " seconds\n\n";
        input.close();
        output.close();
        remove(outputPath);
    }
}

void testMultiplication(const char* inputPath, const char* outputPath, int n = 100) {
    std::cout << "The multiplication test starts...\n";

    std::ifstream input(inputPath);
    std::ofstream output(outputPath);
    std::string first, second, result, myResult;
    int errors = 0, count = 0;
    float time = 0;
    BigInt a, b;

    clock_t start = clock();
    while (input.peek() != EOF && n != count) {
        count++;
        input >> first >> second >> result;
        a = first;
        b = second;
        myResult = (a * b).str();
        if (myResult != result) {
            errors++;
            output << first << " " << second << " " << result << " " << myResult << std::endl;
        }
    }
    if (errors) {
        std::cout << errors << "/" << count << " errors reported in the " << outputPath << std::endl;
        input.close();
        output.close();
    }
    else {
        time = ((float)clock() - (float)start) / CLOCKS_PER_SEC;
        std::cout << std::fixed;
        std::cout.precision(6);
        std::cout << "Multiplication tested in " << time << " seconds (0/"<< count <<" errors).\nAverage time: " << time / (float)count << " seconds\n\n";
        input.close();
        output.close();
        remove(outputPath);
    }
}