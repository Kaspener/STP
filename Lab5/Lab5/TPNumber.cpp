#include "TPNumber.h"
#include <stdexcept>
#include <cmath>

namespace STP {

	TPNumber::TPNumber(double value, int base, int precision)
		: base_(base), precision_(precision) {

		if (base < 2 || base > 16) {
			throw std::invalid_argument("Base must be in the range [2..16]");
		}
		if (precision < 0) {
			throw std::invalid_argument("Precision must be non-negative");
		}

		number_ = value;
		numberString_ = ConvertToBase(value, base, precision);
	}

	TPNumber::TPNumber(const std::string& value, const std::string& base, const std::string& precision)
	{
		int baseInt, precisionInt;

		try {
			baseInt = std::stoi(base);
			precisionInt = std::stoi(precision);
		}
		catch (const std::invalid_argument&) {
			throw std::invalid_argument("Invalid base or precision string");
		}

		if (baseInt < 2 || baseInt > 16) {
			throw std::invalid_argument("Base must be in the range [2..16]");
		}
		if (precisionInt < 0) {
			throw std::invalid_argument("Precision must be non-negative");
		}

		base_ = baseInt;
		precision_ = precisionInt;
		number_ = StringToDouble(value, baseInt);
		numberString_ = value;
	}

	TPNumber::~TPNumber() = default;

	std::string TPNumber::ConvertToBase(const double& value, const int& base, int precision) const noexcept
	{
		std::string result;

		double absValue = std::fabs(value);
		long long intPart = static_cast<long long>(absValue);
		double fracPart = absValue - intPart;

		if (intPart == 0) {
			result = "0";
		}
		else {
			while (intPart > 0) {
				short digit = intPart % base;
				result.insert(0, 1, digit < 10 ? static_cast<char>('0' + digit) : static_cast<char>('A' + digit - 10));
				intPart /= base;
			}
		}

		if (precision > 0) {
			result += ".";
			while (precision-- > 0) {
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

		for (size_t i = startIndex; i < value.size(); ++i) {
			char ch = value[i];

			if (ch == '.') {
				isFraction = true;
				continue;
			}

			char upperCh = std::toupper(ch);

			short digit;
			if (upperCh >= '0' && upperCh <= '9') {
				digit = upperCh - '0';
			}
			else if (upperCh >= 'A' && upperCh <= 'F') {
				digit = upperCh - 'A' + 10;
			}
			else {
				throw std::invalid_argument("Invalid character in the number string");
			}

			if (digit >= base) {
				throw std::invalid_argument("Digit out of range for the specified base");
			}

			if (isFraction) {
				fractionMultiplier /= base;
				result += digit * fractionMultiplier;
			}
			else {
				result = result * base + digit;
			}
		}

		return isNegative ? -result : result;
	}

	void TPNumber::setBase(const std::string& base)
	{
		int newBase;
		try {
			newBase = std::stoi(base);
			if (newBase < 2 || newBase > 16) {
				throw std::out_of_range("Base must be between 2 and 16");
			}
		}
		catch (const std::invalid_argument&) {
			throw std::invalid_argument("Invalid argument: the string is not a valid integer");
		}
		catch (const std::out_of_range&) {
			throw std::out_of_range("The integer value is out of range");
		}

		base_ = newBase;
		numberString_ = ConvertToBase(number_, base_, precision_);
	}

	void TPNumber::setBase(const int& base)
	{
		if (base < 2 || base > 16) {
			throw std::out_of_range("Base must be between 2 and 16");
		}
		base_ = base;
		numberString_ = ConvertToBase(number_, base_, precision_);
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
			throw std::invalid_argument("Precision must be non-negative");
		}
		precision_ = newPrecision;
		numberString_ = ConvertToBase(number_, base_, precision_);
	}

	void TPNumber::setPrecision(const int& precision)
	{
		if (precision < 0) {
			throw std::invalid_argument("Precision must be non-negative");
		}
		precision_ = precision;
		numberString_ = ConvertToBase(number_, base_, precision_);
	}

}