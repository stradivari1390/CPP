/**
 * @file VectorOperations.cpp
 * @brief This program performs operations on vectors.
 * 
 * The program defines a class Vector that represents a mathematical vector.
 * It supports operations such as addition, scalar multiplication, assignment, and increment.
 * It also provides methods to print the vector and calculate its modulus.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

class Vector
{
    int size;
    std::unique_ptr<float[]> elements;

public:
    Vector(int size);
    Vector(int size, float elements[]);
    Vector(const Vector &other);
    Vector operator+(const Vector &other);
    Vector operator*(float scalar);
    Vector &operator=(const Vector &other);
    Vector &operator++();
    float scalarProduct(const Vector &other);
    float modulus();
    ~Vector();
    void print();
};

Vector::Vector(int size) : size(size), elements(new float[size]())
{
}

Vector::Vector(int size, float elements[]) : size(size), elements(new float[size])
{
    std::copy(elements, elements + size, this->elements.get());
}

Vector::Vector(const Vector &other) : size(other.size), elements(new float[other.size])
{
    std::copy(other.elements.get(), other.elements.get() + size, this->elements.get());
}

Vector Vector::operator+(const Vector &other)
{
    Vector result(size);
    for (int i = 0; i < size; i++)
    {
        result.elements[i] = elements[i] + other.elements[i];
    }
    return result;
}

Vector Vector::operator*(float scalar)
{
    Vector result(size);
    for (int i = 0; i < size; i++)
    {
        result.elements[i] = elements[i] * scalar;
    }
    return result;
}

Vector &Vector::operator=(const Vector &other)
{
    if (this != &other)
    {
        size = other.size;
        elements.reset(new float[size]);
        std::copy(other.elements.get(), other.elements.get() + size, elements.get());
    }
    return *this;
}

Vector &Vector::operator++()
{
    for (int i = 0; i < size; i++)
    {
        ++elements[i];
    }
    return *this;
}

float Vector::scalarProduct(const Vector &other)
{
    float product = 0;
    for (int i = 0; i < size; i++)
    {
        product += elements[i] * other.elements[i];
    }
    return product;
}

float Vector::modulus()
{
    float sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += elements[i] * elements[i];
    }
    return std::sqrt(sum);
}

Vector::~Vector()
{
}

void Vector::print()
{
    for (int i = 0; i < size; i++)
    {
        std::cout << elements[i] << ' ';
    }
    std::cout << '\n';
}

int main()
{
    int size;
    std::cout << "Enter the size of the vectors: ";
    std::cin >> size;

    std::unique_ptr<float[]> elements1(new float[size]);
    std::unique_ptr<float[]> elements2(new float[size]);

    std::cout << "Enter the elements of the first vector:\n";
    for (int i = 0; i < size; i++)
    {
        std::cin >> elements1[i];
    }

    std::cout << "Enter the elements of the second vector:\n";
    for (int i = 0; i < size; i++)
    {
        std::cin >> elements2[i];
    }

    Vector vector1(size, elements1.get()), vector2(size, elements2.get());
    Vector vector3(size);

    std::cout << "The result of the operation (vector1 * 3 + vector2) is:\n";
    (vector1 * 3 + vector2).print();

    std::cout << "The initial state of vector3 is:\n";
    vector3.print();

    return 0;
}