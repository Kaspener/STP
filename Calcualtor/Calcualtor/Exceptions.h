#pragma once

#include <stdexcept>
#include <string>

class InvalidBaseException : public std::invalid_argument {
public:
    InvalidBaseException(const int &base)
        : std::invalid_argument("Invalid base: " + std::to_string(base) + ". Base must be between 2 and 16") {}
};

class InvalidBaseDigitException : public InvalidBaseException {
public:
    InvalidBaseDigitException(const int& base)
        : InvalidBaseException(base) {}
};

class InvalidPrecisionException : public std::invalid_argument {
public:
    InvalidPrecisionException(const int &precision)
        : std::invalid_argument("Invalid precision: " + std::to_string(precision) + ". Precision must be non-negative") {}

};

class TypeMismatchException : public std::invalid_argument {
public:
    explicit TypeMismatchException()
        : std::invalid_argument("Different types in operations") {}
};

class DifferentBaseOrPrecision : public std::invalid_argument {
public:
    DifferentBaseOrPrecision(int base1, int base2, int precision1, int precision2)
        : std::invalid_argument("Base 1 = " + std::to_string(base1) + " | Base 2 = " + std::to_string(base2) + "\n Precision 1 = " + std::to_string(precision1) + " | Precision 2 = " + std::to_string(precision2)) {}
};

class DivisionByZeroException : public std::invalid_argument {
public:
    DivisionByZeroException() : std::invalid_argument("Division by zero is undefined") {}
};

class ComplexNumberParseException : public std::invalid_argument {
public:
    ComplexNumberParseException(const std::string& message) : std::invalid_argument(message) {}
};

class FracNumberParseException : public std::invalid_argument {
public:
    FracNumberParseException(const std::string& message) : std::invalid_argument(message) {}
};

class NegativPowerException : public std::invalid_argument {
public:
    NegativPowerException() : std::invalid_argument("Exponent must be non-negative") {}
};