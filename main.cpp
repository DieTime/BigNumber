#include "Test/test.cpp"

using namespace std;

auto main() -> int {
    testMultiplication("../Test/Cases/multiplication1000000.txt", "../Test/Reports/multiplication1000000.txt");
    return 0;
}