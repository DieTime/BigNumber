#include "Test/test.cpp"

using namespace std;

auto main() -> int {
    testSummation("../Test/Cases/summation.txt", "../Test/Reports/summation.txt", 100);
    testSubtraction("../Test/Cases/subtraction.txt", "../Test/Reports/subtraction.txt", 100);
    testMultiplication("../Test/Cases/multiplication.txt", "../Test/Reports/multiplication.txt", 100);
    return 0;
}