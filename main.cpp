#include "Test/test.cpp"

auto main() -> int {
    testSummation("../Test/Cases/summation.txt", "../Test/Reports/summation.txt");
    testSubtraction("../Test/Cases/subtraction.txt", "../Test/Reports/subtraction.txt");
    testMultiplication("../Test/Cases/multiplication.txt","../Test/Reports/multiplication.txt");
    testSchoolMultiplication("../Test/Cases/multiplication.txt","../Test/Reports/multiplication.txt");
    testKaratsubaMultiplication("../Test/Cases/multiplication.txt","../Test/Reports/multiplication.txt");
    testFFTMultiplication("../Test/Cases/multiplication.txt","../Test/Reports/multiplication.txt");
    return 0;
}