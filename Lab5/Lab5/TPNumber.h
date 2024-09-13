#pragma once
#include <string>
#include <stdexcept>
#include <cctype>

namespace STP {

	class TPNumber
	{
	public:
		TPNumber(double value, int base, int precision);
		TPNumber(const std::string &value, const std::string &base, const std::string &precision);

		virtual ~TPNumber() = 0;

		virtual TPNumber* operator+(const TPNumber& d) const = 0;
		virtual TPNumber* operator-(const TPNumber& d) const = 0;
		virtual TPNumber* operator*(const TPNumber& d) const = 0;
		virtual TPNumber* operator/(const TPNumber& d) const = 0;

		virtual TPNumber* Invert() const = 0;
		virtual TPNumber* Square() const noexcept = 0;

		void setBase(const std::string& base);
		void setBase(const int& base);
		void setPrecision(const std::string& precision);
		void setPrecision(const int& precision);

		double number() const noexcept { return number_; }
		std::string numberString() const noexcept { return numberString_; }
		int base() const noexcept { return base_; }
		std::string baseString() const noexcept { return std::to_string(base_); }
		int precision() const noexcept { return precision_; }
		std::string precisionString() const noexcept { return std::to_string(precision_); }

		
	protected:
		std::string numberString_;
		double number_;
		int base_;
		int precision_;
	private: 
		std::string ConvertToBase(const double &value, const int &base, int precision) const noexcept;
		double StringToDouble(const std::string &value, const int &base) const;
	};

}