#pragma once

#include <ctime>
#include <fstream>
#include "../BigInt/BigInt.h"

void testSummation(const char* inputPath, const char* outputPath, int n = 100) {
    std::cout << "The summation test starts...\n";
    std::cout << std::fixed;
    std::cout.precision(6);

    std::ifstream input(inputPath);
    std::ofstream output(outputPath);
    BigInt first, second, result, myResult;
    int errors = 0, count = 0;
    float time = 0;

    clock_t start = clock();
    while (input.peek() != EOF && n != count) {
        count++;
        input >> first >> second >> result;
        myResult = first + second;
        if (myResult != result) {
            errors++;
            output << first << " " << second << " " << result << " " << myResult << std::endl;
        }
    }
    time = ((float)clock() - (float)start) / CLOCKS_PER_SEC;
    if (errors) {
        std::cout << errors << "/" << count << " errors reported in the " << outputPath << std::endl;
        input.close();
        output.close();
    }
    else {
        std::cout << "Summation tested in " << time << " seconds (0/"<< count <<" errors).\nAverage time: " << time / (float)count << " seconds\n\n";
        input.close();
        output.close();
        remove(outputPath);
    }
}

void testSubtraction(const char* inputPath, const char* outputPath, int n = 100) {
    std::cout << "The subtraction test starts...\n";
    std::cout << std::fixed;
    std::cout.precision(6);

    std::ifstream input(inputPath);
    std::ofstream output(outputPath);
    BigInt first, second, result, myResult;
    int errors = 0, count = 0;
    float time = 0;

    clock_t start = clock();
    while (input.peek() != EOF && n != count) {
        count++;
        input >> first >> second >> result;
        myResult = first - second;
        if (myResult != result) {
            errors++;
            output << first << " " << second << " " << result << " " << myResult << std::endl;
        }
    }
    time = ((float)clock() - (float)start) / CLOCKS_PER_SEC;
    if (errors) {
        std::cout << errors << "/" << count << " errors reported in the " << outputPath << std::endl;
        input.close();
        output.close();
    }
    else {
        std::cout << "Subtraction tested in " << time << " seconds (0/"<< count <<" errors).\nAverage time: " << time / (float)count << " seconds\n\n";
        input.close();
        output.close();
        remove(outputPath);
    }
}

void testMultiplication(const char* inputPath, const char* outputPath, int n = 100) {
    std::cout << "The multiplication test starts...\n";
    std::cout << std::fixed;
    std::cout.precision(6);

    std::ifstream input(inputPath);
    std::ofstream output(outputPath);
    BigInt first, second, result, myResult;
    int errors = 0, count = 0;
    float time = 0;

    clock_t start = clock();
    while (input.peek() != EOF && n != count) {
        count++;
        input >> first >> second >> result;
        myResult = first * second;
        if (myResult != result) {
            errors++;
            output << first << " " << second << " " << result << " " << myResult << std::endl;
        }
    }
    time = ((float)clock() - (float)start) / CLOCKS_PER_SEC;
    if (errors) {
        std::cout << errors << "/" << count << " errors reported in the " << outputPath << std::endl;
        input.close();
        output.close();
    }
    else {
        std::cout << "Multiplication tested in " << time << " seconds (0/"<< count <<" errors).\nAverage time: " << time / (float)count << " seconds\n\n";
        input.close();
        output.close();
        remove(outputPath);
    }
}

void testDivision(const char* inputPath, const char* outputPath, int n = 100) {
    std::cout << "The division test starts...\n";
    std::cout << std::fixed;
    std::cout.precision(6);

    std::ifstream input(inputPath);
    std::ofstream output(outputPath);
    BigInt first, second, result, myResult;
    int errors = 0, count = 0;
    float time = 0;

    clock_t start = clock();
    while (input.peek() != EOF && n != count) {
        count++;
        input >> first >> second >> result;
        myResult = BigInt::schoolDivision(first, second);
        if (myResult != result) {
            errors++;
            output << first << " " << second << " " << result << " " << myResult << std::endl;
        }
    }
    time = ((float)clock() - (float)start) / CLOCKS_PER_SEC;
    if (errors) {
        std::cout << errors << "/" << count << " errors reported in the " << outputPath << std::endl;
        input.close();
        output.close();
    }
    else {
        std::cout << "Division tested in " << time << " seconds (0/"<< count <<" errors).\nAverage time: " << time / (float)count << " seconds\n\n";
        input.close();
        output.close();
        remove(outputPath);
    }
}