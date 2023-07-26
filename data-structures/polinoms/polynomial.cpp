/**
 * @file polynomial.cpp
 * @brief This file contains a template class for polynomial operations.
 * The Polynomial class supports addition, subtraction, multiplication, and evaluation of polynomials.
 */

#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class Polynomial
{
public:
    std::vector<T> coefficients; // a0 + a1*x + a2*x^2 + ... + an*x^n

    Polynomial() : coefficients(1, 0) {}
    explicit Polynomial(T a) : coefficients(1, a) {}
    Polynomial(int degree, T* coef) : coefficients(coef, coef + degree) {}
    Polynomial(const Polynomial& other) : coefficients(other.coefficients) {}

    Polynomial<T> operator-() const;
    Polynomial<T> operator+(const Polynomial<T>& other);
    Polynomial<T> operator-(const Polynomial<T>& other);
    Polynomial<T> operator*(const Polynomial<T>& other);
    Polynomial<T>& operator=(const Polynomial<T>& other);
    bool operator==(const Polynomial<T>& other);
    T operator()(T arg);
};

template <typename T>
Polynomial<T> Polynomial<T>::operator+(const Polynomial<T>& other)
{
    Polynomial<T> result;
    size_t maxDegree = std::max(this->coefficients.size(), other.coefficients.size());
    size_t minDegree = std::min(this->coefficients.size(), other.coefficients.size());
    result.coefficients.resize(maxDegree);
    for (size_t i = 0; i < minDegree; i++)
        result.coefficients[i] = this->coefficients[i] + other.coefficients[i];
    for (size_t i = minDegree; i < maxDegree; i++)
        result.coefficients[i] = (this->coefficients.size() > other.coefficients.size() ? this->coefficients[i] : other.coefficients[i]);
    return result;
}

template <typename T>
bool Polynomial<T>::operator==(const Polynomial<T>& other)
{
    return this->coefficients == other.coefficients;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Polynomial<T>& p)
{
    for (int i = p.coefficients.size() - 1; i >= 0; --i)
    {
        os << p.coefficients[i];
        if (i != 0)
            os << "x^" << i << " + ";
    }
    return os;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-() const
{
    Polynomial<T> result(*this);
    for (auto& coef : result.coefficients)
        coef = -coef;
    return result;
}

template <typename T>
Polynomial<T> Polynomial<T>::operator-(const Polynomial<T>& other)
{
    return *this + (-other);
}

template <typename T>
Polynomial<T> Polynomial<T>::operator*(const Polynomial<T>& other)
{
    Polynomial<T> result;
    result.coefficients.resize(this->coefficients.size() + other.coefficients.size() - 1);
    for (size_t i = 0; i < this->coefficients.size(); i++)
        for (size_t j = 0; j < other.coefficients.size(); j++)
            result.coefficients[i+j] += this->coefficients[i] * other.coefficients[j];
    return result;
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator=(const Polynomial<T>& other)
{
    this->coefficients = other.coefficients;
    return *this;
}

template <typename T>
T Polynomial<T>::operator()(T arg)
{
    size_t degree = coefficients.size();
    T result = coefficients[degree-1]*arg + coefficients[degree-2];
    for (size_t i = degree - 1; i > 1; i--)
        result = result*arg + coefficients[i-2];
    return result;
}

int main() {
    int degree1, degree2;

    // Get degree of first polynomial from user
    std::cout << "Enter the degree of the first polynomial: ";
    std::cin >> degree1;

    // Get coefficients of first polynomial from user
    std::vector<double> coef1(degree1 + 1);
    std::cout << "Enter the coefficients of the first polynomial from lowest to highest degree:\n";
    for (double& coef : coef1)
        std::cin >> coef;

    // Create first polynomial
    Polynomial<double> p1(degree1 + 1, coef1.data());

    // Get degree of second polynomial from user
    std::cout << "Enter the degree of the second polynomial: ";
    std::cin >> degree2;

    // Get coefficients of second polynomial from user
    std::vector<double> coef2(degree2 + 1);
    std::cout << "Enter the coefficients of the second polynomial from lowest to highest degree:\n";
    for (double& coef : coef2)
        std::cin >> coef;

    // Create second polynomial
    Polynomial<double> p2(degree2 + 1, coef2.data());

    // Add polynomials
    Polynomial<double> p3 = p1 + p2;
    std::cout << "The sum of the polynomials is: " << p3 << '\n';

    // Subtract polynomials
    Polynomial<double> p4 = p1 - p2;
    std::cout << "The difference of the polynomials is: " << p4 << '\n';

    // Multiply polynomials
    Polynomial<double> p5 = p1 * p2;
    std::cout << "The product of the polynomials is: " << p5 << '\n';

    // Evaluate first polynomial at a given point
    double x;
    std::cout << "Enter a value of x to evaluate the first polynomial: ";
    std::cin >> x;
    double val = p1(x);
    std::cout << "The value of the first polynomial at x = " << x << " is: " << val << '\n';

    return 0;
}