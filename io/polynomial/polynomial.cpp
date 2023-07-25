/**
 * @file polynomial.cpp
 * @brief This program reads a polynomial from a file and simplifies it.
 */

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <algorithm>

struct PolynomialElement
{
    int power;
    double coefficient;
};

void simplifyPolynomial(std::vector<PolynomialElement>& polynomial)
{
    std::sort(polynomial.begin(), polynomial.end(), [](const PolynomialElement& a, const PolynomialElement& b)
    {
        return a.power > b.power;
    });

    for(auto it = polynomial.begin(); it != polynomial.end() - 1; )
    {
        if(it->power == (it + 1)->power)
        {
            it->coefficient += (it + 1)->coefficient;
            polynomial.erase(it + 1);
        }
        else
        {
            ++it;
        }
    }
}

void printPolynomial(const std::vector<PolynomialElement>& polynomial)
{
    for(const auto& element : polynomial)
    {
        std::cout << element.coefficient << "x^" << element.power;
        if(&element != &polynomial.back())
        {
            std::cout << " + ";
        }
    }
    std::cout << std::endl;
}

int main()
{
    std::string filename;
    std::cout << "Enter the filename containing the polynomial: ";
    std::cin >> filename;

    std::ifstream fin(filename);
    if(!fin)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::vector<PolynomialElement> polynomial;

    int power;
    double coefficient;
    while(fin >> power >> coefficient)
    {
        polynomial.push_back({power, coefficient});
    }

    std::cout << "Original Polynomial: ";
    printPolynomial(polynomial);

    simplifyPolynomial(polynomial);

    std::cout << "Simplified Polynomial: ";
    printPolynomial(polynomial);

    return 0;
}
