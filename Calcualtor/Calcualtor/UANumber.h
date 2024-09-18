#pragma once

#include <string>
#include <memory>
#include "Exceptions.h"

# define M_PI           3.14159265358979323846

class TANumber
{
public:
	virtual ~TANumber() = 0;

	std::string numberString() const noexcept { return m_numberStringRepresentation; }
	virtual void setNumber(const std::string& number) = 0;

	virtual bool isNull() const noexcept = 0;
	virtual std::unique_ptr<TANumber> Invert() const = 0;
	virtual std::unique_ptr<TANumber> Square() const noexcept = 0;

	virtual TANumber& operator = (const TANumber& B) = 0;
	virtual std::unique_ptr<TANumber> operator + (const TANumber& B) const = 0;
	virtual std::unique_ptr<TANumber> operator - (const TANumber& B) const = 0;
	virtual std::unique_ptr<TANumber> operator * (const TANumber& B) const = 0;
	virtual std::unique_ptr<TANumber> operator / (const TANumber& B) const = 0;
	virtual std::unique_ptr<TANumber> operator -() const noexcept = 0;
	virtual bool operator ==(const TANumber& B) const noexcept = 0;
	virtual bool operator !=(const TANumber& B) const noexcept = 0;

protected:
	std::string m_numberStringRepresentation;
};

class TPNumber : public TANumber
{
public:
	TPNumber(double value, int base, int precision);
	TPNumber(const std::string& value, const std::string& base, const std::string& precision);
	virtual ~TPNumber() = default;

	void setNumber(const std::string& number) override;
	double number() const noexcept { return m_number; }
	int base() const noexcept { return m_base; }
	int precision() const noexcept { return m_precision; }

	bool isNull() const noexcept override { return m_number == 0.0; }
	std::unique_ptr<TANumber> Invert() const override;
	std::unique_ptr<TANumber> Square() const noexcept override;

	TPNumber& operator = (const TANumber& B) override;
	std::unique_ptr<TANumber> operator+ (const TANumber& B) const override;
	std::unique_ptr<TANumber> operator- (const TANumber& B) const override;
	std::unique_ptr<TANumber> operator* (const TANumber& B) const override;
	std::unique_ptr<TANumber> operator/ (const TANumber& B) const override;
	std::unique_ptr<TANumber> operator-() const noexcept override;
	bool operator == (const TANumber& B) const noexcept;
	bool operator != (const TANumber& B) const noexcept { return !operator==(B); }

	void setBase(const std::string& base);
	void setBase(const int& base);
	void setPrecision(const std::string& precision);
	void setPrecision(const int& precision);

private:
	double m_number;
	int m_base;
	int m_precision;

	std::string ConvertToBase(const double& value, const int& base, int precision) const noexcept;
	double StringToDouble(const std::string& value, const int& base) const;
};

class TComplex : public TANumber
{
public:
	TComplex();
	TComplex(double actual, double imaginary);
	TComplex(const std::string& number);
	virtual ~TComplex() = default;

	void setNumber(const std::string& number) override;
	
	std::string getSeparator() { return m_separator; }
	double getActual() { return m_actual; }
	double getImaginary() { return m_imaginary; }
	std::string getActualString() { return std::to_string(m_actual); }
	std::string getImaginaryString() { return std::to_string(m_imaginary); }
	double Modulus() const noexcept;
	double AngleInRadians() const noexcept;
	double AngleInDegrees() const noexcept;
	std::unique_ptr<TANumber> Power(int n) const;
	std::unique_ptr<TANumber> Sqrt() const;

	bool isNull() const noexcept override;
	std::unique_ptr<TANumber> Invert() const override;
	std::unique_ptr<TANumber> Square() const noexcept override;

	TANumber& operator = (const TANumber& B) override;
	std::unique_ptr<TANumber> operator + (const TANumber& B) const override;
	std::unique_ptr<TANumber> operator - (const TANumber& B) const override;
	std::unique_ptr<TANumber> operator * (const TANumber& B) const override;
	std::unique_ptr<TANumber> operator / (const TANumber& B) const override;
	std::unique_ptr<TANumber> operator -() const noexcept override;
	bool operator ==(const TANumber& B) const noexcept override;
	bool operator !=(const TANumber& B) const noexcept override;

private:
	double m_actual;
	double m_imaginary;
	std::string m_separator = " + i * ";

	void updateStringRepresentation();
};

class TFrac : public TANumber
{
public:
	virtual ~TFrac() = default;
};