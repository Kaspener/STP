#include "UANumber.h"
#include <cmath>

TANumber::~TANumber() = default;

TPNumber::TPNumber(double value, int base, int precision)
	: m_base(base), m_precision(precision) 
{

	if (base < 2 || base > 16) 
	{
		throw InvalidBaseException(base);
	}
	if (precision < 0) 
	{
		throw InvalidPrecisionException(precision);
	}

	m_number = value;
	m_numberStringRepresentation = ConvertToBase(value, base, precision);
}

TPNumber::TPNumber(const std::string& value, const std::string& base, const std::string& precision)
{
	int baseInt, precisionInt;

	try 
	{
		baseInt = std::stoi(base);
		precisionInt = std::stoi(precision);
	}
	catch (const std::invalid_argument&) 
	{
		throw std::invalid_argument("Invalid base or precision string");
	}

	if (baseInt < 2 || baseInt > 16) 
	{
		throw InvalidBaseException(baseInt);
	}
	if (precisionInt < 0) 
	{
		throw InvalidPrecisionException(precisionInt);
	}

	m_base = baseInt;
	m_precision = precisionInt;
	m_number = StringToDouble(value, baseInt);
	m_numberStringRepresentation = ConvertToBase(m_number, m_base, m_precision);
}

void TPNumber::setNumber(const std::string& number)
{
	m_number = StringToDouble(number, m_base);
	m_numberStringRepresentation = ConvertToBase(m_number, m_base, m_precision);
}

std::unique_ptr<TANumber> TPNumber::Invert() const
{
	if (isNull()) {
		throw DivisionByZeroException();
	}
	double resultValue = 1.0 / m_number;
	return std::make_unique<TPNumber>(resultValue, m_base, m_precision);
}

std::unique_ptr<TANumber> TPNumber::Square() const noexcept
{
	double resultValue = m_number * m_number;
	return std::make_unique<TPNumber>(resultValue, m_base, m_precision);
}

TPNumber& TPNumber::operator=(const TANumber& B)
{
	const TPNumber* pB = dynamic_cast<const TPNumber*>(&B);
	if (!pB) {
		throw TypeMismatchException();
	}
	m_base = pB->m_base;
	m_precision = pB->m_precision;
	m_number = pB->m_number;
	m_numberStringRepresentation = pB->m_numberStringRepresentation;

	return *this;
}

std::unique_ptr<TANumber> TPNumber::operator+(const TANumber& B) const
{
	const TPNumber* pB = dynamic_cast<const TPNumber*>(&B);
	if (!pB) 
	{
		throw TypeMismatchException();
	}

	if (m_base != pB->m_base || m_precision != pB->m_precision) 
	{
		throw DifferentBaseOrPrecision(m_base, pB->m_base, m_precision, pB->m_precision);
	}

	double resultValue = m_number + pB->m_number;

	return std::make_unique<TPNumber>(resultValue, this->m_base, this->m_precision);
}

std::unique_ptr<TANumber> TPNumber::operator-(const TANumber& B) const
{
	const TPNumber* pB = dynamic_cast<const TPNumber*>(&B);
	if (!pB) 
	{
		throw TypeMismatchException();
	}

	if (m_base != pB->m_base || m_precision != pB->m_precision) 
	{
		throw DifferentBaseOrPrecision(m_base, pB->m_base, m_precision, pB->m_precision);
	}

	double resultValue = m_number - pB->m_number;

	return std::make_unique<TPNumber>(resultValue, this->m_base, this->m_precision);
}

std::unique_ptr<TANumber> TPNumber::operator*(const TANumber& B) const
{
	const TPNumber* pB = dynamic_cast<const TPNumber*>(&B);
	if (!pB)
	{
		throw TypeMismatchException();
	}

	if (m_base != pB->m_base || m_precision != pB->m_precision)
	{
		throw DifferentBaseOrPrecision(m_base, pB->m_base, m_precision, pB->m_precision);
	}

	double resultValue = m_number * pB->m_number;

	return std::make_unique<TPNumber>(resultValue, this->m_base, this->m_precision);
}

std::unique_ptr<TANumber> TPNumber::operator/(const TANumber& B) const
{
	const TPNumber* pB = dynamic_cast<const TPNumber*>(&B);
	if (!pB)
	{
		throw TypeMismatchException();
	}

	if (m_base != pB->m_base || m_precision != pB->m_precision)
	{
		throw DifferentBaseOrPrecision(m_base, pB->m_base, m_precision, pB->m_precision);
	}

	if (pB->isNull())
	{
		throw DivisionByZeroException();
	}

	double resultValue = m_number / pB->m_number;

	return std::make_unique<TPNumber>(resultValue, this->m_base, this->m_precision);
}

std::unique_ptr<TANumber> TPNumber::operator-() const noexcept
{
	return std::make_unique<TPNumber>(-this->m_number, this->m_base, this->m_precision);
}

bool TPNumber::operator==(const TANumber& B) const noexcept
{
	const TPNumber* pB = dynamic_cast<const TPNumber*>(&B);
	if (!pB) return false;
	return (m_base == pB->m_base && m_precision == pB->m_precision && m_number == pB->m_number);
}

void TPNumber::setBase(const std::string& base)
{
	int newBase;
	try 
	{
		newBase = std::stoi(base);
	}
	catch (const std::invalid_argument&) 
	{
		throw std::invalid_argument("Invalid argument: the string is not a valid integer");
	}
	if (newBase < 2 || newBase > 16) 
	{
		throw InvalidBaseException(newBase);
	}

	m_base = newBase;
	m_numberStringRepresentation = ConvertToBase(m_number, m_base, m_precision);
}

void TPNumber::setBase(const int& base)
{
	if (base < 2 || base > 16) 
	{
		throw InvalidBaseException(base);
	}
	m_base = base;
	m_numberStringRepresentation = ConvertToBase(m_number, m_base, m_precision);
}

void TPNumber::setPrecision(const std::string& precision)
{
	int newPrecision;
	try {
		newPrecision = std::stoi(precision);
	}
	catch (const std::invalid_argument&) {
		throw std::invalid_argument("Invalid argument: the string is not a valid integer");
	}
	if (newPrecision < 0) {
		throw InvalidPrecisionException(newPrecision);
	}
	m_precision = newPrecision;
	m_numberStringRepresentation = ConvertToBase(m_number, m_base, m_precision);
}

void TPNumber::setPrecision(const int& precision)
{
	if (precision < 0) {
		throw InvalidPrecisionException(precision);
	}
	m_precision = precision;
	m_numberStringRepresentation = ConvertToBase(m_number, m_base, m_precision);
}

std::string TPNumber::ConvertToBase(const double& value, const int& base, int precision) const noexcept
{
	std::string result;

	double absValue = std::fabs(value);
	long long intPart = static_cast<long long>(absValue);
	double fracPart = absValue - intPart;

	if (intPart == 0) 
	{
		result = "0";
	}
	else 
	{
		while (intPart > 0) 
		{
			short digit = intPart % base;
			result.insert(0, 1, digit < 10 ? static_cast<char>('0' + digit) : static_cast<char>('A' + digit - 10));
			intPart /= base;
		}
	}

	if (precision > 0) 
	{
		result += ".";
		while (precision-- > 0) 
		{
			fracPart *= base;
			short digit = static_cast<long long>(fracPart);
			fracPart -= digit;
			result += (digit < 10 ? static_cast<char>('0' + digit) : static_cast<char>('A' + digit - 10));
		}
	}
	if (value < 0) result.insert(0, 1, '-');
	return result;
}

double TPNumber::StringToDouble(const std::string& value, const int& base) const
{
	double result = 0.0;
	bool isFraction = false;
	double fractionMultiplier = 1.0;
	bool isNegative = (value[0] == '-');

	size_t startIndex = (isNegative || value[0] == '+') ? 1 : 0;

	for (size_t i = startIndex; i < value.size(); ++i) 
	{
		char ch = value[i];

		if (ch == '.') 
		{
			isFraction = true;
			continue;
		}

		char upperCh = std::toupper(ch);

		short digit;
		if (upperCh >= '0' && upperCh <= '9') 
		{
			digit = upperCh - '0';
		}
		else if (upperCh >= 'A' && upperCh <= 'F') 
		{
			digit = upperCh - 'A' + 10;
		}
		else 
		{
			throw InvalidBaseDigitException(upperCh - 'A' + 10);
		}

		if (digit >= base) 
		{
			throw InvalidBaseDigitException(digit);
		}

		if (isFraction) 
		{
			fractionMultiplier /= base;
			result += digit * fractionMultiplier;
		}
		else 
		{
			result = result * base + digit;
		}
	}

	return isNegative ? -result : result;
}

TComplex::TComplex() : m_actual(0), m_imaginary(0)
{
	updateStringRepresentation();
}

TComplex::TComplex(double actual, double imaginary) : m_actual(actual), m_imaginary(imaginary)
{
	updateStringRepresentation();
}

TComplex::TComplex(const std::string& number)
{
	setNumber(number);
}

void TComplex::setNumber(const std::string& number)
{
	size_t plus_pos = number.find(" + i * ");
	size_t minus_pos = number.find(" - i * ");

	if (plus_pos == std::string::npos && minus_pos == std::string::npos) {
		throw ComplexNumberParseException("Invalid complex number format: " + number);
	}

	try {
		if (plus_pos != std::string::npos) {
			m_actual = std::stod(number.substr(0, plus_pos));
			m_imaginary = std::stod(number.substr(plus_pos + 7));
		}
		else if (minus_pos != std::string::npos) {
			m_actual = std::stod(number.substr(0, minus_pos));
			m_imaginary = -std::stod(number.substr(minus_pos + 7));
		}
	}
	catch (const std::exception&) {
		throw ComplexNumberParseException("Error parsing the number: " + number);
	}

	updateStringRepresentation();
}

double TComplex::Modulus() const noexcept
{
	return std::sqrt(m_actual * m_actual + m_imaginary * m_imaginary);
}

double TComplex::AngleInRadians() const noexcept
{
	return std::atan2(m_imaginary, m_actual);
}

double TComplex::AngleInDegrees() const noexcept
{
	return AngleInRadians() * (180.0 / M_PI);
}

std::unique_ptr<TANumber> TComplex::Power(int n) const {
	if (n < 0) {
		throw NegativPowerException();
	}

	double r = Modulus();
	double theta = AngleInRadians();

	double r_n = std::pow(r, n);
	double new_theta = n * theta;

	double realPart = r_n * std::cos(new_theta);
	double imaginaryPart = r_n * std::sin(new_theta);

	return std::make_unique<TComplex>(realPart, imaginaryPart);
}

std::unique_ptr<TANumber> TComplex::Sqrt() const {
	double r = Modulus();
	double theta = AngleInRadians();

	double sqrt_r = std::sqrt(r);
	double half_theta = theta / 2.0;

	double realPart = sqrt_r * std::cos(half_theta);
	double imaginaryPart = sqrt_r * std::sin(half_theta);

	return std::make_unique<TComplex>(realPart, imaginaryPart);
}

bool TComplex::isNull() const noexcept
{
	return (m_actual == 0.0 && m_imaginary == 0.0);
}

std::unique_ptr<TANumber> TComplex::Invert() const
{
	double denominator = m_actual * m_actual + m_imaginary * m_imaginary;
	if (std::abs(denominator) < 1e-9) {
		throw ComplexNumberParseException("Cannot invert zero complex number.");
	}
	double realPart = m_actual / denominator;
	double imaginaryPart = -m_imaginary / denominator;
	return std::make_unique<TComplex>(realPart, imaginaryPart);
}

std::unique_ptr<TANumber> TComplex::Square() const noexcept
{
	double realPart = m_actual * m_actual - m_imaginary * m_imaginary;
	double imaginaryPart = 2 * m_actual * m_imaginary;
	return std::make_unique<TComplex>(realPart, imaginaryPart);
}

TANumber& TComplex::operator=(const TANumber& B)
{
	const TComplex* pB = dynamic_cast<const TComplex*>(&B);
	if (!pB) {
		throw TypeMismatchException();
	}
	m_separator = pB->m_separator;
	m_actual = pB->m_actual;
	m_imaginary = pB->m_imaginary;
	m_numberStringRepresentation = pB->m_numberStringRepresentation;

	return *this;
}

std::unique_ptr<TANumber> TComplex::operator+(const TANumber& B) const
{

	const TComplex* pB = dynamic_cast<const TComplex*>(&B);
	if (!pB)
	{
		throw TypeMismatchException();
	}

	return std::make_unique<TComplex>(m_actual + pB->m_actual, m_imaginary + pB->m_imaginary);
}

std::unique_ptr<TANumber> TComplex::operator-(const TANumber& B) const
{
	const TComplex* pB = dynamic_cast<const TComplex*>(&B);
	if (!pB)
	{
		throw TypeMismatchException();
	}

	return std::make_unique<TComplex>(m_actual - pB->m_actual, m_imaginary - pB->m_imaginary);
}

std::unique_ptr<TANumber> TComplex::operator*(const TANumber& B) const
{
	const TComplex* pB = dynamic_cast<const TComplex*>(&B);
	if (!pB)
	{
		throw TypeMismatchException();
	}

	return std::make_unique<TComplex>(m_actual * pB->m_actual - m_imaginary * pB->m_imaginary, m_actual * pB->m_imaginary + m_imaginary * pB->m_actual);
}

std::unique_ptr<TANumber> TComplex::operator/(const TANumber& B) const
{
	const TComplex* pB = dynamic_cast<const TComplex*>(&B);
	if (!pB)
	{
		throw TypeMismatchException();
	}
	double denominator = pB->m_actual * pB->m_actual + pB->m_imaginary * pB->m_imaginary;
	if (denominator == 0) {
		throw DivisionByZeroException();
	}
	double real_part = (m_actual * pB->m_actual + m_imaginary * pB->m_imaginary) / denominator;
	double imaginary_part = (m_imaginary * pB->m_actual - m_actual * pB->m_imaginary) / denominator;
	return std::make_unique<TComplex>(real_part, imaginary_part);
}

std::unique_ptr<TANumber> TComplex::operator-() const noexcept
{
	return std::make_unique<TComplex>(-m_actual, -m_imaginary);
}

bool TComplex::operator==(const TANumber& B) const noexcept
{
	const TComplex* pB = dynamic_cast<const TComplex*>(&B);
	return m_actual == pB->m_actual && m_imaginary == pB->m_imaginary;
}

bool TComplex::operator!=(const TANumber& B) const noexcept
{
	const TComplex* pB = dynamic_cast<const TComplex*>(&B);
	return !(this == pB);
}

void TComplex::updateStringRepresentation()
{
	std::string result;
	if (floor(m_actual) == m_actual)
		result = std::to_string(static_cast<int>(m_actual));
	else
		result = std::to_string(m_actual);

	if (m_imaginary >= 0) {
		m_separator[1] = '+';
	}
	else {
		m_separator[1] = '-';
	}
	result += m_separator;

	if (floor(m_imaginary) == m_imaginary)
		result += std::to_string(std::abs(static_cast<int>(m_imaginary)));
	else
		result += std::to_string(std::fabs(m_imaginary));

	m_numberStringRepresentation = result;
}
