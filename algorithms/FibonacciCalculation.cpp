/**
 * This program calculates Fibonacci numbers and measures the time taken for each calculation.
 * It uses a recursive function to calculate the Fibonacci number for each step from 0 to n.
 * The time taken for each calculation is also displayed.
 *
 * Correct output before 47-th item, The GNU Multiple Precision Arithmetic Library or analogs are not used here.
 */

#include <iostream>
#include <chrono>

long Fibonacci(unsigned int n)
{
    return n <= 1 ? n : Fibonacci(n-1) + Fibonacci(n-2);
}

int main() {
    unsigned int n;
    long result;

    std::cout << "\nEnter the number of Fibonacci calculations to perform: ";
    std::cin >> n;
    std::cout << std::endl << std::endl;

    for(unsigned int i=0; i<n; i++) {
        auto begin = std::chrono::high_resolution_clock::now();
        result = Fibonacci(i);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        std::cout << "Step " << i << "     Fibonacci number = " << result << "      Calculation time (ms) = " << elapsed_ms.count() << std::endl;
    }

    std::cin.get();
    return 0;
}